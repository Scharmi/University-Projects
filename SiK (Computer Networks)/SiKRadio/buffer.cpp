#include "buffer.hpp"
#include <limits.h>

CyclicBuffer::CyclicBuffer(uint64_t size, int portion_size) {
    this->buffer = std::vector<uint8_t>(size);
    this->writer_index = 0;
    this->reader_index = 0;
    this->portion_size = portion_size;
    this->size = size;
}
CyclicBuffer::CyclicBuffer(uint64_t size) {
    this->buffer = std::vector<uint8_t>(size);
    this->writer_index = 0;
    this->reader_index = 0;
    this->portion_size = 1;
    this->size = size;
}
void CyclicBuffer::write(std::vector<uint8_t> data, uint64_t package_number) {
    this->package_numbers.push(package_number);
    for(uint64_t i = 0; i < data.size(); i++) {
        this->buffer[this->writer_index] = data[i];
        this->writer_index = (this->writer_index + 1) % this->buffer.size();
    }
}
void CyclicBuffer::setPortionSize(uint64_t portion_size) {
    this->portion_size = portion_size;
}
std::vector<uint8_t> CyclicBuffer::read() {
    std::vector<uint8_t> result;
    for(uint64_t i = 0; i < this->portion_size; i++) {
        result.push_back(this->buffer[this->reader_index]);
        this->reader_index = (this->reader_index + 1) % this->buffer.size();
    }
    return result;
}
uint64_t CyclicBuffer::get_package_number() {
    if(this->package_numbers.empty()) {
        return INT_MAX;
    }
    uint64_t result = this->package_numbers.top();
    return result;
}
void CyclicBuffer::pop_package_number() {
    this->package_numbers.pop();
}
std::vector<uint8_t> CyclicBuffer::get_buffer() {
    return this->buffer;
}
uint64_t CyclicBuffer::get_size() {
    return this->size;
}
uint64_t CyclicBuffer::get_package_size() {
    return this->portion_size;
}