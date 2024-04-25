#include "communication.hpp"
#include "err.hpp"
#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>


Package::Package(std::vector<uint8_t> serialized_data) {
    this->session_id = __builtin_bswap64(*((uint64_t*)serialized_data.data()));
    this->first_byte_num = __builtin_bswap64(*((uint64_t*)(serialized_data.data() + 8)));
    this->audio_data = std::vector<uint8_t>(serialized_data.begin() + 16, serialized_data.end());
}
Package::Package(uint64_t session_id, uint64_t first_byte_num, std::vector<uint8_t> audio_data) {
    this->session_id = session_id;
    this->first_byte_num = first_byte_num;
    this->audio_data = audio_data;
}
std::vector<uint8_t> Package::serialize() {
    std::vector<uint8_t> serialized_data;
    uint64_t session_id_n = __builtin_bswap64(this->session_id);
    uint64_t first_byte_num_n = __builtin_bswap64(this->first_byte_num);
    serialized_data.insert(serialized_data.end(), (uint8_t*)&session_id_n, (uint8_t*)&session_id_n + 8);
    serialized_data.insert(serialized_data.end(), (uint8_t*)&first_byte_num_n, (uint8_t*)&first_byte_num_n + 8);
    serialized_data.insert(serialized_data.end(), this->audio_data.begin(), this->audio_data.end());
    return serialized_data;
}
uint64_t Package::get_session_id() {
    return this->session_id;
}
uint64_t Package::get_first_byte_num() {
    return this->first_byte_num;
}
std::vector<uint8_t> Package::get_audio_data() {
    return this->audio_data;
}
void Package::set_first_byte_num(uint64_t first_byte_num) {
    this->first_byte_num = first_byte_num;
}

Sender::Sender(std::string client_address, uint16_t client_port) {
    this->client_address = client_address;
    this->client_port = client_port;
    this->socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    this->server_address.sin_family = AF_INET;
    this->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    this->server_address.sin_port = htons(this->client_port);

}
void Sender::send_package(Package package) {
    std::vector<uint8_t> serialized_package = package.serialize();
    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(this->client_address.c_str());
    client_address.sin_port = htons(this->client_port);
    if(sendto(this->socket_fd, serialized_package.data(), serialized_package.size(), 0, (struct sockaddr*)&client_address, sizeof(client_address)) < 0) {
        fatal("sendto");
    }
}
Receiver::Receiver(std::string address, uint16_t port) {
    this->socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(this->socket_fd < 0) {
        fatal("socket");
    }
    this->server_address.sin_family = AF_INET;
    this->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    this->server_address.sin_port = htons(port);
    this->server_ip = address;
    if(bind(this->socket_fd, (struct sockaddr*)&this->server_address, sizeof(this->server_address)) < 0) {
        fatal("bind");
    }
}
Package Receiver::receive_package() {
    std::vector<uint8_t> buffer(1024);
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    ssize_t received_bytes = recvfrom(this->socket_fd, buffer.data(), buffer.size(), 0, (struct sockaddr*)&client_address, &client_address_len);
    if(received_bytes < 0) {
        fatal("recvfrom");
    }
    buffer.resize(received_bytes);
    Package package = Package(buffer);
    if(inet_ntoa(client_address.sin_addr) != this->server_ip) {
        package.set_first_byte_num(INT_MAX);
    }
    return package;
}





