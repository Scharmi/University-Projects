#ifndef SAFEFIFO_HPP
#define SAFEFIFO_HPP

#include <vector>
#include <queue>
#include <stdint.h>
#include <pthread.h>
#include <mutex>
#include "buffer.hpp"
#include "communication.hpp"

class SafeFifo {
    public:
        SafeFifo(uint64_t size, uint64_t portion_size);
        void write_byte(uint8_t byte);
        uint64_t getSize();
        Package getPackageByFirstByteNum(uint64_t first_byte_num);
        std::vector<uint8_t> getBytesByFirstByteNum(uint64_t first_byte_num);
    private:
        std::mutex mutex;
        uint64_t bytes_written;
        uint64_t fifo_size;
        std::vector<uint8_t> buffer;
        uint64_t portion_size;
};

#endif