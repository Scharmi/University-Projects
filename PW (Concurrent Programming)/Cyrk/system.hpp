#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <exception>
#include <vector>
#include <unordered_map>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <deque>
#include <map>

#include "machine.hpp"

class FulfillmentFailure : public std::exception
{
};

class OrderNotReadyException : public std::exception
{
};

class BadOrderException : public std::exception
{
};

class BadPagerException : public std::exception
{
};

class OrderExpiredException : public std::exception
{
};

class RestaurantClosedException : public std::exception
{
};

struct WorkerReport
{
    std::vector<std::vector<std::string>> collectedOrders;
    std::vector<std::vector<std::string>> abandonedOrders;
    std::vector<std::vector<std::string>> failedOrders;
    std::vector<std::string> failedProducts;
};
struct Order
{
    std::shared_ptr<bool> isReady;
    std::shared_ptr<bool> isExpired;
    std::shared_ptr<bool> isActive;
    std::shared_ptr<bool> machineIsBroken;
    unsigned int id;
    std::vector<std::string> products;
    std::vector<std::unique_ptr<Product>> *collectedProducts;
    std::condition_variable *orderReadyCond;
    std::condition_variable *orderCollectCond;
};
struct MutexDeque
{
    std::deque<unsigned int> deque;
    std::mutex mutex;
    std::condition_variable cond;
};
class System;
class CoasterPager
{

public:
    

    void wait() const;

    void wait(unsigned int timeout) const;

    [[nodiscard]] unsigned int getId() const;

    [[nodiscard]] bool isReady() const;

    CoasterPager(unsigned int id, std::condition_variable *orderReadyCond, std::mutex *systemMutex, std::shared_ptr<bool> isReady);

    private:
    friend class System;
    unsigned int id;
    std::condition_variable *orderReadyCond;
    std::mutex *systemMutex;
    std::shared_ptr<bool> isReadyPtr;
    
};

class System
{
friend class CoasterPager;
public:

    typedef std::unordered_map<std::string, std::shared_ptr<Machine>> machines_t;
    
    System(machines_t machines, unsigned int numberOfWorkers, unsigned int clientTimeout);

    std::vector<WorkerReport> shutdown();

    std::vector<std::string> getMenu() const;

    std::vector<unsigned int> getPendingOrders() const;

    std::unique_ptr<CoasterPager> order(std::vector<std::string> products);

    std::vector<std::unique_ptr<Product>> collectOrder(std::unique_ptr<CoasterPager> CoasterPager);

    unsigned int getClientTimeout() const;
private:
    unsigned int numberOfWorkers;
    unsigned int clientTimeout;
    machines_t machines;
    std::unordered_map <std::shared_ptr<Machine>, bool> isBroken;
    std::deque<Order> newOrders;
    std::vector<Order> allOrders;
    std::vector<WorkerReport> reports;
    std::vector<std::thread> workers;
    mutable std::mutex *systemMutex;
    std::condition_variable newOrderCond;
    std::map<std::string, MutexDeque> productsToOrders;
    bool running;
    unsigned int orderId;

};


#endif // SYSTEM_HPP