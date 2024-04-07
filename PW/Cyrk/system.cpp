#include "system.hpp"
#include <thread>
#include <iostream>
#include <future>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <deque>
#include <chrono>
#include <atomic>
#include <map>
#include <vector>
#include <unordered_map>
#include <functional>

void CoasterPager::wait() const {
    std::unique_lock<std::mutex> lock( *systemMutex );
    orderReadyCond->wait(lock, [this]() { return *isReadyPtr; });
    std::cout << "It's working!" << std::endl;
}

void CoasterPager::wait(unsigned int timeout) const {
    std::unique_lock<std::mutex> lock( *systemMutex );
    orderReadyCond->wait_for(lock, std::chrono::milliseconds(timeout), [this]() { return *isReadyPtr; });
}

bool CoasterPager::isReady() const {
    return *isReadyPtr;
}

CoasterPager::CoasterPager(unsigned int id, std::condition_variable *orderReadyCond, std::mutex *systemMutex, std::shared_ptr<bool> isReady) {
    this->id = id;
    this->orderReadyCond = orderReadyCond;
    this->systemMutex = systemMutex;
    this->isReadyPtr = isReady;
}
unsigned int CoasterPager::getId() const {
    return id;
}

System::System(machines_t machines, unsigned int numberOfWorkers, unsigned int clientTimeout) {
    this->orderId = 0;
    this->running = true;
    this->numberOfWorkers = numberOfWorkers;
    this->clientTimeout = clientTimeout;
    this->machines = machines;
    this->reports.resize(numberOfWorkers);
    this->systemMutex = new std::mutex();
    for (auto &machine : machines) {
        machine.second->start();
        isBroken[machine.second] = false;
    }
    
    for (unsigned int i = 0; i < numberOfWorkers; i++) {
        workers.push_back(std::thread([this, i]() {
            std::vector<std::string> collected;
            std::vector<std::string> abandoned;
            std::vector<std::string> failed;
            while (running || !newOrders.empty()) {
                std::unique_lock<std::mutex> lock(*systemMutex);
                std::cout << "worker " << i << " waiting for order" << std::endl;
                newOrderCond.wait(lock, [this]() { return !newOrders.empty() || !running; });

                // Bez tego jest SEGFAULT z oczywistych względów.
                if (newOrders.empty()) {
                    lock.unlock();
                    return;
                }

                Order order = newOrders.front();
                std::cout << "worker " << i << " got order " << order.id << std::endl;
                newOrders.pop_front();
                lock.unlock();
                for(auto &product: order.products) {

                    std::unique_lock<std::mutex> lock(productsToOrders[product].mutex);
                    
                    if(productsToOrders[product].deque.front() != order.id) {
                        productsToOrders[product].cond.wait(lock, [this, &order, &product]() { return productsToOrders[product].deque.front() == order.id; });
                    }
                    
                    auto machine = this->machines[product];
                    
                    try {
                        auto productPtr = std::move(machine->getProduct());
                        order.collectedProducts->push_back(std::move(productPtr));
                    }
                    catch(MachineFailure &e) {
                        isBroken[machine] = true;
                        *(order.machineIsBroken) = true;
                        //Raport

                    }
                    
                    productsToOrders[product].deque.pop_front();
                    
                    lock.unlock();
                    productsToOrders[product].cond.notify_all();
                }
                *(order.isReady) = true;
                order.orderReadyCond->notify_all();
                
            }
            reports[i].collectedOrders.push_back(collected);
            reports[i].abandonedOrders.push_back(abandoned);
            reports[i].failedOrders.push_back(failed);
        }));
    }

}
std::vector<std::string> System::getMenu() const {
    std::unique_lock<std::mutex> lock(*systemMutex);
    std::vector<std::string> menu;
    for (auto &machine : machines) {
        if(!isBroken.at(machine.second))
        menu.push_back(machine.first);
    }
    lock.unlock();
    return menu;
}

std::vector<unsigned int> System::getPendingOrders() const {
    std::unique_lock<std::mutex> lock(*systemMutex);
    std::vector<unsigned int> pendingOrders;
    for (auto &order : allOrders) {
        if (*(order.isActive)) {
            pendingOrders.push_back(order.id);
        }
    }
    for(auto &order: newOrders) {
        pendingOrders.push_back(order.id);
    }
    lock.unlock();
    return pendingOrders;
}

std::vector<WorkerReport> System::shutdown() {
    this->running = false;
    newOrderCond.notify_all();
    for (auto &worker : workers) {
        worker.join();
    }
    for(auto &machine: machines) {
        machine.second->stop();
    }
    return reports;
}

std::unique_ptr<CoasterPager> System::order(std::vector<std::string> products) {
    //TODO dodać timer do zamówienia
    std::unique_lock<std::mutex> lock(*systemMutex);
    if(!running) {
        throw RestaurantClosedException();
    }
    std::vector<std::string> menu;
    for (auto &machine : machines) {
        if(!isBroken.at(machine.second))
        menu.push_back(machine.first);
    }
    for (auto &product : products) {
        if (std::find(menu.begin(), menu.end(), product) == menu.end()) {
            throw BadOrderException();
        }
    }
    Order newOrder;
    newOrder.id = orderId;
    newOrder.products = products;
    newOrder.isReady = std::make_shared<bool>(false);
    newOrder.isActive = std::make_shared<bool>(true);
    newOrder.isExpired = std::make_shared<bool>(false);
    newOrder.machineIsBroken = std::make_shared<bool>(false);
    newOrder.orderReadyCond = new std::condition_variable();
    newOrder.orderCollectCond = new std::condition_variable();
    newOrder.collectedProducts = new std::vector<std::unique_ptr<Product>>();

    newOrders.push_back(newOrder);
    allOrders.push_back(newOrder);
    for(auto &product: products) {
        productsToOrders[product].mutex.lock();
        productsToOrders[product].deque.push_back(orderId);
        productsToOrders[product].mutex.unlock();
    }
    orderId++;
    lock.unlock();
    newOrderCond.notify_one();
    return std::make_unique<CoasterPager>(newOrder.id, newOrder.orderReadyCond, systemMutex, newOrder.isReady);
}

std::vector<std::unique_ptr<Product>> System::collectOrder(std::unique_ptr<CoasterPager> CoasterPager) {
    std::unique_lock<std::mutex> lock(*systemMutex);
    auto order = allOrders.at(CoasterPager->id);
    if(!(*(order.isActive)) && (*(order.isReady))) {
        throw BadPagerException();
    }
    
    if(*(order.machineIsBroken)) {
        throw FulfillmentFailure();
    }
    if(*(order.isExpired)) {
        throw OrderExpiredException();
    }

    if(!(*(order.isReady))) {
        throw OrderNotReadyException();
    }

    std::vector<std::unique_ptr<Product>> collectedProducts;
    return std::move(*order.collectedProducts);
}

unsigned int System::getClientTimeout() const {
    return clientTimeout;
}