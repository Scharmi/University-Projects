#include <thread>
#include <condition_variable>
#include <mutex>

#include "log.hpp"

class Barrier {
public:
    Barrier(int resistance)
        : resistance(resistance) {
    }
    void reach();

private:
    int resistance;
    std::mutex mut;
    std::condition_variable cv;
    // TODO: add more fields if necessary
};

void Barrier::reach() {
    std::unique_lock<std::mutex> lock(mut);
    if(resistance == 0)  {
        return;
    }
    if(resistance == 1) {
        resistance--;
        lock.unlock();
        cv.notify_all();
    } else {
        resistance--;
        cv.wait(lock, [this] { return resistance == 0; });
    }
}

void attack(const std::string id, Barrier& b) {
    log("attacking: "+id);
    b.reach();
    log("victory: "+id);
}

int main() {
    
    Barrier b{3};
    std::thread t1{[&b] { attack("a", b); }};
    std::thread t2{[&b] { attack("b", b); }};
    std::thread t3{[&b] { attack("c", b); }};
    std::thread t4{[&b] { attack("d", b); }};
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
}
