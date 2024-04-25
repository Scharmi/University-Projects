#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vector>
#include <queue>
#include <stdint.h>
#include <pthread.h>


class CyclicBuffer {
    public:
        CyclicBuffer(uint64_t size, int portion_size);
        CyclicBuffer(uint64_t size);
        void write(std::vector<uint8_t> data, uint64_t package_number);
        void setPortionSize(uint64_t portion_size);
        std::vector<uint8_t> read();
        uint64_t get_package_number();
        uint64_t get_package_size();
        std::vector<uint8_t> get_buffer();
        void pop_package_number();
        uint64_t get_size();
    private:
        std::vector<uint8_t> buffer;
        std::priority_queue<uint64_t, std::vector<uint64_t>, std::greater<>> package_numbers;
        ssize_t writer_index;
        ssize_t reader_index;
        uint64_t portion_size;
        uint64_t size;
};

#endif