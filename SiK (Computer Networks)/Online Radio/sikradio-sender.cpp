#include "communication.hpp"

#include <boost/program_options.hpp>
#include <iostream>
#include <ctime>
#include <mutex>

using namespace boost::program_options;

#define DEFAULT_PORT 20004
int main(int argc, const char *argv[])
{
    options_description desc{"Options"};
    desc.add_options()
      ("DEST_ADDR,a", value<std::string>()->required(), "Destination address")
      ("DATA_PORT,P", value<int>()->default_value(DEFAULT_PORT), "Data port")
      ("PSIZE,p", value<int>()->default_value(512), "Package size")
      ("NAZWA,n", value<std::string>()->default_value("Nienazwany Nadajnik"));
    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);
    bool read = true;
    std::uint8_t buffer[67557];
    uint64_t session_id = time(NULL);
    uint64_t first_byte_num = 0;
    std::string data_addr = vm["DEST_ADDR"].as<std::string>();
    Sender sender(data_addr, vm["DATA_PORT"].as<int>());
    while(read) {
        ssize_t read_len = fread(buffer, sizeof(uint8_t), vm["PSIZE"].as<int>(), stdin);
        if(read_len != vm["PSIZE"].as<int>()) {
            read = false;
        }
        Package package(session_id, first_byte_num, std::vector<uint8_t>(buffer, buffer + read_len));
        sender.send_package(package);
        first_byte_num += read_len;
    }
}