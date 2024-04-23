#include "communication.hpp"
#include "err.hpp"
#include "safe_fifo.hpp"
#include "safe_set.hpp"

#include <boost/program_options.hpp>
#include <iostream>
#include <ctime>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>

using namespace boost::program_options;

#define DEFAULT_PORT 20004
#define DEFAULT_CTRL_PORT 30004
void check_arguments(variables_map vm) {
    ENSURE(vm["MCAST_ADDR"].as<std::string>().size() <= 15);
    ENSURE(vm["CTRL_PORT"].as<uint64_t>() >= 0 && vm["CTRL_PORT"].as<uint64_t>() <= 65535);
    ENSURE(vm["DATA_PORT"].as<uint64_t>() >= 0 && vm["DATA_PORT"].as<uint64_t>() <= 65535);
    ENSURE(vm["PSIZE"].as<uint64_t>() >= 1);
    ENSURE(vm["FSIZE"].as<uint64_t>() >= 1);
    ENSURE(vm["RTIME"].as<uint64_t>() >= 1);
    ENSURE(vm["NAME"].as<std::string>().size() <= 64);
}
void send_rexmit(MulticastSender &multicastSender, SafeFifo &fifo, SafeSet& packets_to_rexmit, uint64_t rtime, uint64_t session_id, bool &stop, std::mutex& stop_mutex) {
    bool end = 0;
    while(!end) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rtime));
        std::vector<uint64_t> vec = packets_to_rexmit.getAndClear();
        for(auto it = vec.begin(); it != vec.end(); it++) {
            std::vector<uint8_t> bytes = fifo.getBytesByFirstByteNum(*it);
            //If requested package is not in fifo, skip it
            if(bytes.size() == 0) {
                continue;
            }
            Package package(session_id, *it, bytes);
            multicastSender.send_package(package);
        }
        std::lock_guard<std::mutex> lock(stop_mutex);
        end = stop;     
    }
}

void listen_for_ctrl(uint16_t ctrl_port, SafeFifo& fifo, SafeSet& packets_to_rexmit, variables_map vm, bool &stop, std::mutex& stop_mutex) {
    BroadcastReceiver broadcast_receiver(ctrl_port);
    bool end = 0;
    while(!end) {
        
        auto received = broadcast_receiver.receive_package();
        if(received.get_type() == CtrlPackage::Type::REXMIT) {
            std::vector<uint64_t> x = received.get_package_numbers();
            packets_to_rexmit.insert(x);
        }
        else if(received.get_type() == CtrlPackage::Type::LOOKUP) {
            Sender sender(received.get_client_address(), DEFAULT_CTRL_PORT);
            LookupResponsePackage lookup_response_package(vm["MCAST_ADDR"].as<std::string>(), vm["DATA_PORT"].as<uint64_t>(), vm["NAME"].as<std::string>());
            sender.send_lookup_response_package(lookup_response_package);
        }
        std::lock_guard<std::mutex> lock(stop_mutex);
        end = stop;
    }
}
int main(int argc, const char *argv[])
{
    options_description desc{"Options"};
    desc.add_options()
      ("MCAST_ADDR,a", value<std::string>()->required(), "Destination address")
      ("CTRL_PORT,C", value<uint64_t>()->default_value(DEFAULT_CTRL_PORT), "Control port")
      ("DATA_PORT,P", value<uint64_t>()->default_value(DEFAULT_PORT), "Data port")
      ("PSIZE,p", value<uint64_t>()->default_value(512), "Package size")
      ("FSIZE,f", value<uint64_t>()->default_value(131072), "FIFO size")
      ("RTIME, R", value<uint64_t>()->default_value(250), "Retransmission time")
      ("NAME,n", value<std::string>()->default_value("Nienazwany Nadajnik"));
    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);
    check_arguments(vm);
    bool read = true;
    std::uint8_t buffer[67557];
    uint64_t session_id = time(NULL);
    uint64_t first_byte_num = 0;
    std::string data_addr = vm["MCAST_ADDR"].as<std::string>();
    MulticastSender sender(data_addr, vm["DATA_PORT"].as<uint64_t>());
    auto fifo = SafeFifo(vm["FSIZE"].as<uint64_t>(), vm["PSIZE"].as<uint64_t>());
    auto packets_to_rexmit = SafeSet();
    bool end = 0;
    std::mutex stop_mutex;
    std::thread listen_for_ctrl_thread(listen_for_ctrl, vm["CTRL_PORT"].as<uint64_t>(), std::ref(fifo), std::ref(packets_to_rexmit), vm, std::ref(end), std::ref(stop_mutex));
    std::thread send_rexmit_thread(send_rexmit, std::ref(sender), std::ref(fifo), std::ref(packets_to_rexmit), vm["RTIME"].as<uint64_t>(), session_id, std::ref(end), std::ref(stop_mutex));
    while(read) {
        uint64_t read_len = fread(buffer, sizeof(uint8_t), vm["PSIZE"].as<uint64_t>(), stdin);
        for(uint64_t i = 0; i < read_len; i++) {
            fifo.write_byte(buffer[i]);
        }
        if(read_len != vm["PSIZE"].as<uint64_t>()) {
            read = false;
        }
        if(read_len == 0) {
            break;
        }
        Package package(session_id, first_byte_num, std::vector<uint8_t>(buffer, buffer + read_len));
        sender.send_package(package);
        first_byte_num += read_len;
    }
    stop_mutex.try_lock();
    end = 1;
    stop_mutex.unlock();
    listen_for_ctrl_thread.join();
    send_rexmit_thread.join();
}