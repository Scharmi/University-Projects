#ifndef KVFIFO_H
#define KVFIFO_H

#include <utility>
#include <memory>
#include <list>
#include <map>
#include <iostream>
template <typename K, typename V> 
class kvfifo{
    private:

    using kvList = std::list<std::pair<K,V>>;
    using itType = typename kvList::iterator;
    using listPtr = std::shared_ptr<kvList>;
    using kvMap = std::map<K,std::list<itType>>;
    using mapPtr = std::shared_ptr<kvMap>;
    
    mapPtr fifoMapPtr;
    listPtr fifoListPtr;
    bool referenced;
    void make_copy(){
        mapPtr oldMapPtr = fifoMapPtr;
        listPtr oldListPtr = fifoListPtr;
        try{
            kvfifo newKvfifo;
            for(auto i: *fifoListPtr) {
                newKvfifo.push(i.first, i.second);
            }
            fifoMapPtr = newKvfifo.fifoMapPtr;
            fifoListPtr = newKvfifo.fifoListPtr;
            referenced = false;
        }
        catch(...){
            fifoMapPtr = oldMapPtr;
            fifoListPtr = oldListPtr;
            throw;
        }
    }

    public:
    kvfifo(): 
    fifoMapPtr(std::make_shared<kvMap>()), 
    fifoListPtr(std::make_shared<kvList>()),
    referenced(false){}

    kvfifo(const kvfifo &other):
    fifoMapPtr(other.fifoMapPtr),
    fifoListPtr(other.fifoListPtr),
    referenced(other.referenced){
        if(referenced){
            make_copy();
        }
    }

    kvfifo(const kvfifo &&other):
    fifoMapPtr(std::move(other.fifoMapPtr)),
    fifoListPtr(std::move(other.fifoListPtr)),
    referenced(std::move(other.referenced)){}
    
    kvfifo& operator=(kvfifo other){
        mapPtr oldMapPtr = fifoMapPtr;
        listPtr oldListPtr = fifoListPtr;
        try{
            fifoMapPtr = other.fifoMapPtr;
            fifoListPtr = other.fifoListPtr;
            if(other.referenced){
                make_copy();
            }
            return *this;
        }
        catch(...){
            fifoMapPtr = oldMapPtr;
            fifoListPtr = oldListPtr;
            throw;
        }
    }
    
    void push(K const &k, V const &v){
        bool newItList = false;
        bool addedItem = false;
        try{
            if(!fifoMapPtr.unique() || !fifoListPtr.unique()){
                make_copy();
            }
            kvList & fifoList = *fifoListPtr;
            kvMap & fifoMap = *fifoMapPtr;
            itType newElementIt = fifoList.insert(fifoList.end(), {k,v});
            addedItem = true;
            if(!fifoMapPtr->contains(k)){
                std::list<itType> newList;
                fifoMap.insert({k, newList});
                newItList = false;
            }
            fifoMap[k].push_back(newElementIt);
        }catch(...){
            if(addedItem){
                
            }
            throw;
        }
    }
    void pop(K const &) {
        try {
            if(!fifoMapPtr.unique() || !fifoListPtr.unique()){
                make_copy();
            }
            kvList & fifoList = *fifoListPtr;
            kvMap & fifoMap = *fifoMapPtr;
            if(fifoMap.contains(K)) {

            }
            else {
                throw std::invalid_argument("Queue does not contain given key")
            }
        } catch(...) {
            
        }

    }

    void pop() {
        try {
            if(!fifoMapPtr.unique() || !fifoListPtr.unique()){
                make_copy();
            }
            kvList & fifoList = *fifoListPtr;
            kvMap & fifoMap = *fifoMapPtr;
            if(!fifoList.empty()) {
                pop(front());
            }
            else {
                throw std::invalid_argument("Queue empty");
            }

    } catch(...) {
        throw;
        }
    }
    

    void move_to_back(K const &k){
        try{
            if(!fifoMapPtr.unique() || !fifoListPtr.unique()){
                make_copy();
            }
            for(auto x : fifoMapPtr[k]){
                fifoListPtr->splice(fifoListPtr->end(), fifoListPtr, x);
            }
        }catch(...){
            throw;
        }
    }

    void clear(){
        try{
            if(!fifoMapPtr.unique() || !fifoListPtr.unique()){
                make_copy();
            }
            fifoListPtr->clear();
            fifoMapPtr->clear();
        }
        catch(...){
            throw;
        }
    }
    
    size_t count(K const &k) const noexcept{
        return fifoMapPtr[k].size();
    }

    bool empty() const noexcept{
        return fifoListPtr->empty();
    }

    

    std::pair<K const &, V &> first(K const &key) {
        try{
            if(!fifoListPtr.unique() || !fifoMapPtr.unique()){
                make_copy();
            }
        }
        catch(...){
            throw;
        }
        if(fifoMapPtr->contains(key)){
            auto it = (*fifoMapPtr)[key].front();
            K const & first = it->first;
            V const & second = it->second;
            std::pair<K const &, V const &> result(first, second);
            return result;
        }
        else{
            throw std::invalid_argument("First(): key not in queue.");
        }
    }

    std::pair<K const &, V const &> first(K const &key) const{
        if(fifoMapPtr->contains(key)){
            auto it = (*fifoMapPtr)[key].front();
            K const & first = it->first;
            V const & second = it->second;
            std::pair<K const &, V const &> result(first, second);
            return result;
        }
        else{
            throw std::invalid_argument("First(): key not in queue.");
        }
    }

    std::pair<K const &, V &> last(K const &key){
        try{
            if(!fifoListPtr.unique() || !fifoMapPtr.unique()){
                make_copy();
            }
        }
        catch(...){
            throw;
        }
        if(fifoMapPtr->contains(key)){
            auto it = (*fifoMapPtr)[key].back();
            K const & first = it->first;
            V & second = it->second;
            std::pair<K const &, V &> result(first, second);
            referenced = true;
            return result;
        }
        else{
            throw std::invalid_argument("Last(): key not in queue.");
        }
    }

    std::pair<K const &, V const &> last(K const &key) const{
        if(!fifoMapPtr.unique() || !fifoListPtr.unique()){
            make_copy();
        }
        if(fifoMapPtr->contains(key)){
            auto it = (*fifoMapPtr)[key].back();
            K const & first = it->first;
            V const & second = it->second;
            std::pair<K const &, V const &> result(first, second);
            return result;
        }
        else{
            throw std::invalid_argument("Last(): key not in queue.");
        }
    }

    std::pair<K const &, V &> front() {
        try{
            if(!fifoMapPtr.unique() || !fifoListPtr.unique()){
                make_copy();
            }
        }
        catch(...){
            throw;
        }
        if(!fifoMapPtr->empty()){
            K const & first = (*fifoListPtr).front().first;
            V & second = (*fifoListPtr).front().second;
            std::pair<K const &, V &> result(first, second);
            referenced = true;
            return result;
        }
        else{
            throw std::invalid_argument("Front(): queue empty.");
        }
    }
    std::pair<K const &, V const &> front() const;
    std::pair<K const &, V &> back();
    std::pair<K const &, V const &> back() const;

};
#endif