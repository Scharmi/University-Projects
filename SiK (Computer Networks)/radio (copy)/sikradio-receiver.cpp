#include "communication.hpp"
#include "buffer.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <ctime>
#include <thread>
#include <atomic>
#include <mutex>

using namespace boost::program_options;

#define DEFAULT_PORT 20004
void reader(CyclicBuffer &buffer, std::mutex &buffer_mutex, std::mutex &empty_mutex, std::atomic_bool &newSession, uint64_t byte0) {
    empty_mutex.lock();
    uint64_t package_number = 0;
    std::vector<uint64_t> missing_numbers;
    buffer_mutex.lock();
    uint64_t package_size = buffer.get_package_size();
    buffer_mutex.unlock();
    std::vector<uint8_t> data;
    while(!newSession) {
        bool read = false;
        buffer_mutex.lock();
        uint64_t top = buffer.get_package_number();
        if(top == INT_MAX) {
            buffer_mutex.unlock();
            continue;
        }
        if((top-byte0)/package_size != package_number) {
            missing_numbers.push_back(package_number);
            package_number++;
            
        }
        else {
            if((top-byte0)/package_size == package_number) {
                data = buffer.read();
                read = true;
                package_number++;
                buffer.pop_package_number();
            }
        }
        buffer_mutex.unlock();
        if(read) {
            fwrite(data.data(), sizeof(uint8_t), data.size(), stdout);
            for(uint16_t i = 0; i < missing_numbers.size(); i++) {
                std::cerr << "MISSING: BEFORE " << package_number << " EXPECTED " << missing_numbers[i] << std::endl;
            }
        }
    }
    
    while(!newSession) {
        buffer_mutex.lock();
        std::vector<uint8_t> data = buffer.read();

        buffer_mutex.unlock();
    }

}
void writer(CyclicBuffer &buffer, Receiver &receiver, std::mutex &buffer_mutex, std::mutex &empty_mutex, std::atomic_bool &newSession, uint64_t session_id, uint64_t byte0) {
    bool startedReader = false;
    empty_mutex.lock();
    std::thread readerThread(reader, std::ref(buffer), std::ref(buffer_mutex), std::ref(empty_mutex), std::ref(newSession), byte0);
    while(!newSession) {
            Package package = receiver.receive_package();
            if(package.get_first_byte_num() != INT_MAX) {
                if(package.get_session_id() > session_id) {
                    newSession = true;
                    break;
                }
                if(package.get_session_id() == session_id) {
                    if(!startedReader && package.get_first_byte_num() >= byte0 + (3*  buffer.get_size()) / 4) {
                        startedReader = true;
                        empty_mutex.unlock();
                    }
                    buffer_mutex.lock();
                    buffer.write(package.get_audio_data(), package.get_first_byte_num());
                    buffer_mutex.unlock();
                }
            }
    }
    readerThread.join();
}

int main(int argc, const char *argv[]) {
    options_description desc{"Options"};
    desc.add_options()
    ("SEND_ADDR,a", value<std::string>()->required(), "Destination address")
    ("DATA_PORT,P", value<int>()->default_value(DEFAULT_PORT), "Data port")
    ("PSIZE,p", value<int>()->default_value(512), "Package size")
    ("BSIZE,b", value<int>()->default_value(65536));
    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);
    std::string send_addr = vm["SEND_ADDR"].as<std::string>();
    Receiver receiver(send_addr, vm["DATA_PORT"].as<int>());
    while(true) {
        bool gotRightPackage = false;
        uint64_t byte0;
        uint64_t session_id;
        CyclicBuffer buffer = CyclicBuffer(vm["BSIZE"].as<int>());
        while(!gotRightPackage) {
            Package package = receiver.receive_package();
            if(package.get_first_byte_num() != INT_MAX) {
                buffer.setPortionSize(package.get_audio_data().size());
                buffer.write(package.get_audio_data(), package.get_first_byte_num());
                byte0 = package.get_first_byte_num();
                session_id = package.get_session_id();
                gotRightPackage = true;
            }
        }
        std::mutex buffer_mutex;
        std::mutex empty_mutex;
        
        std::atomic_bool newSession(false);
        std::thread writerThread(writer, std::ref(buffer), std::ref(receiver), std::ref(buffer_mutex), std::ref(empty_mutex), std::ref(newSession), session_id, byte0);
        writerThread.join();        
    }

    while(true) {
        Package package = receiver.receive_package();
        if(package.get_first_byte_num() != INT_MAX) {
            fwrite(package.get_audio_data().data(), sizeof(uint8_t), package.get_audio_data().size(), stdout);
        }
    }
}