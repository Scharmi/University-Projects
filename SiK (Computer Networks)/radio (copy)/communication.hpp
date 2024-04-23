#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include <iostream>
#include <vector>
#include <netinet/in.h>
#include <mutex>

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
class LookupPackage : public Package {
    public:
        LookupPackage(std::vector<uint8_t> serialized_data);
        LookupPackage(uint64_t session_id, uint64_t first_byte_num, std::string name);
        std::string get_name();
    private:
        std::string name;
};
class LookupResponsePackage {
    public:
        LookupResponsePackage(std::vector<uint8_t> serialized_data);
        LookupResponsePackage(std::string mcast_addr, uint16_t data_port, std::string name);
        std::vector<uint8_t> serialize();
    private:
        std::string mcast_addr;
        uint16_t data_port;
        std::string station_name;
};
class Sender {
    public:
        Sender(std::string address, uint16_t port);
        void send_package(Package package);
        void send_lookup_response_package(LookupResponsePackage package);
    private:
        std::string client_address;
        uint16_t client_port;
        int socket_fd;
        struct sockaddr_in server_address;

};
class TwoWayCommunication {
    public:
        TwoWayCommunication(std::string address, uint16_t port);
        Package receive_package();
        void send_package(Package package);
    private:
        int socket_fd;
        std::string server_ip;
        struct sockaddr_in server_address;
};
class CtrlPackage {
    public:
        CtrlPackage(std::vector<uint8_t> serialized_data);
        CtrlPackage(std::vector<uint8_t> serialized_data, std::string client_address);
        enum class Type {
            LOOKUP,
            REXMIT,
            UNKNOWN
        };
        Type get_type();
        std::string get_client_address();
        std::vector<uint64_t> get_package_numbers();
        void print_data();
    private:
        Type type;
        std::vector<uint64_t> package_numbers;
        std::string client_address;
};
class BroadcastReceiver {
    public:
        BroadcastReceiver(uint16_t port);
        CtrlPackage receive_package();
    private:
        int socket_fd;
        std::string server_ip;
        struct sockaddr_in server_address;
};

class MulticastSender {
    public:
        MulticastSender(std::string address, uint16_t port);
        void send_package(Package package);
    private:
        std::string client_address;
        uint16_t client_port;
        int socket_fd;
        struct sockaddr_in server_address;
        std::mutex mutex;

};


#endif
