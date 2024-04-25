#ifndef SAFESET_HPP
#define SAFESET_HPP

#include <vector>
#include <queue>
#include <stdint.h>
#include <pthread.h>
#include <mutex>
#include <set>
#include "buffer.hpp"
#include "communication.hpp"

class SafeSet {
    public:
        SafeSet();
        void clear();
        void insert(std::vector<uint64_t> &vec);
        std::vector<uint64_t> getAndClear();
        std::vector<uint64_t> get();
  private:
    std::mutex mutex;
    std::set<uint64_t> set;

};

#endif