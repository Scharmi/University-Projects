#include "safe_fifo.hpp"

SafeFifo::SafeFifo(uint64_t fifo_size, uint64_t portion_size) {
    this->bytes_written = 0;
    this->fifo_size = fifo_size;
    this->buffer = std::vector<uint8_t>(fifo_size);
    this->portion_size = portion_size;
}

void SafeFifo::write_byte(uint8_t byte) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->buffer[(this->bytes_written) % this->fifo_size] = byte;
    this->bytes_written++;
}

std::vector<uint8_t> SafeFifo::getBytesByFirstByteNum(uint64_t first_byte_num) {
    std::lock_guard<std::mutex> lock(this->mutex);
    if(first_byte_num + this->portion_size > this->bytes_written) {
        return std::vector<uint8_t>();
    }
    if(this->bytes_written > this->fifo_size + first_byte_num) {
        return std::vector<uint8_t>();
    }
    std::vector<uint8_t> result;
    for(uint64_t i = first_byte_num; i < first_byte_num + portion_size; i++) {
        result.push_back(this->buffer[i % this->fifo_size]);
    }
    return result;
}
uint64_t SafeFifo::getSize() {
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->bytes_written;
}


