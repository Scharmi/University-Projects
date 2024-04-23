#ifndef KVFIFO_H
#define KVFIFO_H

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <utility>
template <typename K, typename V>
class kvfifo {
   private:
    using kvList = std::list<std::pair<K, V>>;
    using itType = typename kvList::iterator;
    using listPtr = std::shared_ptr<kvList>;
    using kvMap = std::map<K, std::list<itType>>;
    using mapPtr = std::shared_ptr<kvMap>;

    mapPtr fifoMapPtr;
    listPtr fifoListPtr;
    bool referenced;
    void make_copy() {
        mapPtr oldMapPtr = fifoMapPtr;
        listPtr oldListPtr = fifoListPtr;
        try {
            kvfifo newKvfifo;
            for (auto i : *fifoListPtr) {
                newKvfifo.push(i.first, i.second);
            }
            fifoMapPtr = newKvfifo.fifoMapPtr;
            fifoListPtr = newKvfifo.fifoListPtr;
            referenced = false;
        } catch (...) {
            fifoMapPtr = oldMapPtr;
            fifoListPtr = oldListPtr;
            throw;
        }
    }

   public:
    class k_iterator {
       public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = typename kvMap::iterator;
        using difference_type = std::ptrdiff_t;
        using pointer = const K *;
        using reference = const K &;

        k_iterator(value_type const p) : it(p) {}

        reference operator*() noexcept { return it->first; }
        pointer operator->() noexcept { return &(it->first); }
        k_iterator &operator++() noexcept {
            it++;
            return *this;
        }

        k_iterator &operator--() noexcept {
            it--;
            return *this;
        }
        k_iterator operator++(int) noexcept {
            k_iterator result(*this);
            operator++();
            return result;
        }

        k_iterator operator--(int) noexcept {
            k_iterator result(*this);
            operator--();
            return result;
        }
        friend bool operator==(k_iterator const &a,
                               k_iterator const &b) noexcept {
            return a.it->first == b.it->first;
        }
        friend bool operator!=(k_iterator const &a,
                               k_iterator const &b) noexcept {
            return !(a == b);
        }

       private:
        value_type it;
    };

    k_iterator k_begin() {
        k_iterator it(fifoMapPtr->begin());
        return it;
    }

    k_iterator k_end() {
        k_iterator it(fifoMapPtr->end());
        return it;
    }

    kvfifo()
        : fifoMapPtr(std::make_shared<kvMap>()),
          fifoListPtr(std::make_shared<kvList>()),
          referenced(false) {}

    kvfifo(const kvfifo &other)
        : fifoMapPtr(other.fifoMapPtr),
          fifoListPtr(other.fifoListPtr),
          referenced(other.referenced) {
        if (referenced) {
            make_copy();
        }
    }

    kvfifo(const kvfifo &&other)
        : fifoMapPtr(std::move(other.fifoMapPtr)),
          fifoListPtr(std::move(other.fifoListPtr)),
          referenced(std::move(other.referenced)) {}

    kvfifo &operator=(kvfifo other) {
        mapPtr oldMapPtr = fifoMapPtr;
        listPtr oldListPtr = fifoListPtr;
        try {
            fifoMapPtr = other.fifoMapPtr;
            fifoListPtr = other.fifoListPtr;
            if (other.referenced) {
                make_copy();
            }
            return *this;
        } catch (...) {
            fifoMapPtr = oldMapPtr;
            fifoListPtr = oldListPtr;
            throw;
        }
    }

    void push(K const &k, V const &v) {
        bool newItList = false;
        bool addedItem = false;
        try {
            if (!fifoMapPtr.unique() || !fifoListPtr.unique()) {
                make_copy();
            }
            kvList &fifoList = *fifoListPtr;
            kvMap &fifoMap = *fifoMapPtr;
            itType newElementIt = fifoList.insert(fifoList.end(), {k, v});
            addedItem = true;
            if (!fifoMapPtr->contains(k)) {
                std::list<itType> newList;
                fifoMap.insert({k, newList});
                newItList = true;
            }
            fifoMap[k].push_back(newElementIt);
        } catch (...) {
            if (addedItem) {
                fifoListPtr->pop_back();
            }
            if (newItList) {
                fifoMapPtr->erase(k);
            }
            throw;
        }
    }

    void pop(K const &k) {
        try {
            if (!fifoMapPtr.unique() || !fifoListPtr.unique()) {
                make_copy();
            }
            kvList &fifoList = *fifoListPtr;
            kvMap &fifoMap = *fifoMapPtr;
            if (fifoMap.contains(k)) {
                itType toErase = fifoMap[k].front();
                fifoList.erase(toErase);
                fifoMap[k].pop_front();
            } else {
                throw std::invalid_argument("Queue does not contain given key");
            }
        } catch (...) {
            throw;
        }
    }

    void pop() {
        try {
            if (!fifoMapPtr.unique() || !fifoListPtr.unique()) {
                make_copy();
            }
            kvList &fifoList = *fifoListPtr;
            kvMap &fifoMap = *fifoMapPtr;
            if (!fifoList.empty()) {
                pop(front().first);
            } else {
                throw std::invalid_argument("Queue empty");
            }

        } catch (...) {
            throw;
        }
    }

    void move_to_back(K const &k) {
        try {
            if (!fifoMapPtr.unique() || !fifoListPtr.unique()) {
                make_copy();
            }
            for (auto x : (*fifoMapPtr)[k]) {
                fifoListPtr->splice(fifoListPtr->end(), *fifoListPtr, x);
            }
        } catch (...) {
            throw;
        }
    }

    void clear() {
        try {
            if (!fifoMapPtr.unique() || !fifoListPtr.unique()) {
                make_copy();
            }
            fifoListPtr->clear();
            fifoMapPtr->clear();
        } catch (...) {
            throw;
        }
    }

    size_t count(K const &k) const noexcept {
        if (fifoMapPtr->contains(k)) return (*fifoMapPtr)[k].size();
        return 0;
    }

    bool empty() const noexcept { return fifoListPtr->empty(); }

    size_t size() const noexcept { return fifoListPtr->size(); }

    std::pair<K const &, V &> first(K const &key) {
        try {
            if (!fifoListPtr.unique() || !fifoMapPtr.unique()) {
                make_copy();
            }
        } catch (...) {
            throw;
        }
        if (fifoMapPtr->contains(key)) {
            auto it = (*fifoMapPtr)[key].front();
            K const &first = it->first;
            V &second = it->second;
            std::pair<K const &, V &> result(first, second);
            return result;
        } else {
            throw std::invalid_argument("First(): key not in queue.");
        }
    }

    std::pair<K const &, V const &> first(K const &key) const {
        if (fifoMapPtr->contains(key)) {
            auto it = (*fifoMapPtr)[key].front();
            K const &first = it->first;
            V const &second = it->second;
            std::pair<K const &, V const &> result(first, second);
            return result;
        } else {
            throw std::invalid_argument("First(): key not in queue.");
        }
    }

    std::pair<K const &, V &> last(K const &key) {
        try {
            if (!fifoListPtr.unique() || !fifoMapPtr.unique()) {
                make_copy();
            }
        } catch (...) {
            throw;
        }
        if (fifoMapPtr->contains(key)) {
            auto it = (*fifoMapPtr)[key].back();
            K const &first = it->first;
            V &second = it->second;
            std::pair<K const &, V &> result(first, second);
            referenced = true;
            return result;
        } else {
            throw std::invalid_argument("Last(): key not in queue.");
        }
    }

    std::pair<K const &, V const &> last(K const &key) const {
        if (fifoMapPtr->contains(key)) {
            auto it = (*fifoMapPtr)[key].back();
            K const &first = it->first;
            V const &second = it->second;
            std::pair<K const &, V const &> result(first, second);
            return result;
        } else {
            throw std::invalid_argument("Last(): key not in queue.");
        }
    }

    std::pair<K const &, V &> front() {
        try {
            if (!fifoMapPtr.unique() || !fifoListPtr.unique()) {
                make_copy();
            }
        } catch (...) {
            throw;
        }
        if (!fifoMapPtr->empty()) {
            K const &first = (*fifoListPtr).front().first;
            V &second = (*fifoListPtr).front().second;
            std::pair<K const &, V &> result(first, second);
            referenced = true;
            return result;
        } else {
            throw std::invalid_argument("Front(): queue empty.");
        }
    }
    std::pair<K const &, V const &> front() const {
        if (!fifoMapPtr->empty()) {
            K const &first = (*fifoListPtr).front().first;
            V &second = (*fifoListPtr).front().second;
            std::pair<K const &, V const &> result(first, second);
            return result;
        } else {
            throw std::invalid_argument("Front(): queue empty.");
        }
    }
    std::pair<K const &, V &> back() {
        try {
            if (!fifoMapPtr.unique() || !fifoListPtr.unique()) {
                make_copy();
            }
        } catch (...) {
            throw;
        }
        if (!fifoMapPtr->empty()) {
            K const &first = (*fifoListPtr).back().first;
            V &second = (*fifoListPtr).back().second;
            std::pair<K const &, V &> result(first, second);
            referenced = true;
            return result;
        } else {
            throw std::invalid_argument("Back(): queue empty.");
        }
    }
    std::pair<K const &, V const &> back() const {
        if (!fifoMapPtr->empty()) {
            K const &first = (*fifoListPtr).back().first;
            V &second = (*fifoListPtr).back().second;
            std::pair<K const &, V const &> result(first, second);
            return result;
        } else {
            throw std::invalid_argument("Back(): queue empty.");
        }
    }
};
#endif