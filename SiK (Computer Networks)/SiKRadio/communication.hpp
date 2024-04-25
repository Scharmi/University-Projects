#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include <iostream>
#include <vector>
#include <netinet/in.h>

class Package {
    public:
        Package(std::vector<uint8_t> serialized_data);
        Package(uint64_t session_id, uint64_t first_byte_num, std::vector<uint8_t> audio_data);
        std::vector<uint8_t> serialize();
        uint64_t get_session_id();
        uint64_t get_first_byte_num();
        std::vector<uint8_t> get_audio_data(); 
        void set_first_byte_num(uint64_t first_byte_num);
    private:
        std::vector<uint8_t> audio_data;
        uint64_t session_id;
        uint64_t first_byte_num;
};

class Receiver {
    public:
        Receiver(std::string address, uint16_t port);
        Package receive_package();
    private:
        int socket_fd;
        std::string server_ip;
        struct sockaddr_in server_address;

};
class Sender {
    public:
        Sender(std::string address, uint16_t port);
        void send_package(Package package);
    private:
        std::string client_address;
        uint16_t client_port;
        int socket_fd;
        struct sockaddr_in server_address;

};



#endif
