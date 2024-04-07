#include "safe_set.hpp"

SafeSet::SafeSet() {
    this->set = std::set<uint64_t>();
}

void SafeSet::clear() {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->set.clear();
}

void SafeSet::insert(std::vector<uint64_t> &vec) {
    std::lock_guard<std::mutex> lock(this->mutex);
    for(auto it = vec.begin(); it != vec.end(); it++) {
        this->set.insert(*it);
    }
}

std::vector<uint64_t> SafeSet::getAndClear() {
    std::lock_guard<std::mutex> lock(this->mutex);
    std::vector<uint64_t> vec(this->set.begin(), this->set.end());
    this->set.clear();
    return vec;
}

std::vector<uint64_t> SafeSet::get() {
    std::lock_guard<std::mutex> lock(this->mutex);
    std::vector<uint64_t> vec(this->set.begin(), this->set.end());
    return vec;
}