#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "err.h"
#include "common.h"

#define LINE_SIZE 100
#define BUFFER_SIZE 100
#define QUEUE_LENGTH 5
ssize_t
readn(int fd, void* buf, size_t n)
{
  char* b = buf;
  size_t left = n;

  while (left) {
    ssize_t res = read(fd, b, left);
    if (res == -1) {
      if (errno == EINTR)
        continue;
      return -1;
    } else if (res == 0) {
      break;
    }
    left -= res;
    b += res;
  }
  return n - left;
}

ssize_t
writen(int fd, const void* buf, size_t n)
{
  const char* b = buf;
  size_t left = n;

  while (left) {
    ssize_t res = write(fd, b, left);
    if (res == -1) {
      if (errno == EINTR)
        continue;
      return -1;
    }
    left -= res;
    b += res;
  }
  return n;
}

void *handle_connection(void *client_fd_ptr) {
    int client_fd = *(int *) client_fd_ptr;
    free(client_fd_ptr);

    char *ip = get_ip_from_socket(client_fd);
    int port = get_port_from_socket(client_fd);

    printf("[thread %lu, pid %d] %s:%d connected\n",
           (unsigned long) pthread_self(), getpid(), ip, port);

    int file_size;
    ssize_t read = readn(client_fd, &file_size, 4);
    file_size = ntohl(file_size);
    printf("SIZE: %d\n", file_size);
    int file_name_size;
    read = readn(client_fd, &file_name_size, 2);
    file_name_size = ntohs(file_name_size);
    printf("FILE NAME SIZE: %d\n", file_name_size);
    char file_name[file_name_size];
    memset(file_name, 0, sizeof(file_name));
    read = readn(client_fd, file_name, file_name_size);
    printf("FILE NAME: %s\n", file_name);
    FILE *fp;
    fp = fopen("TEST.txt", "w");
    printf("new client %s:%d size=%d file=%s\n", ip, port, file_size, file_name);
    sleep(1);
    char line[LINE_SIZE];
    for (;;) {
        memset(line, 0, sizeof(line));
        ssize_t read = receive_message(client_fd, line, sizeof(line) - 1, NO_FLAGS);
        if (read < 0)
            PRINT_ERRNO();
        if (read == 0)
            break;
        fprintf(fp, line);
    }
    fclose(fp);
    printf("client %s:%d has sent its file of size=%d\n", ip, port, file_size);
    CHECK_ERRNO(close(client_fd));
    return 0;
}

int main() {
    int socket_fd = open_socket();

    int port = bind_socket_to_any_port(socket_fd);
    printf("Listening on port %d\n", port);

    start_listening(socket_fd, QUEUE_LENGTH);

    for (;;) {
        struct sockaddr_in client_addr;

        int client_fd = accept_connection(socket_fd, &client_addr);

        // Arguments for the thread must be passed by pointer
        int *client_fd_pointer = malloc(sizeof(int));
        if (client_fd_pointer == NULL) {
            fatal("malloc");
        }
        *client_fd_pointer = client_fd;

        pthread_t thread;
        CHECK_ERRNO(pthread_create(&thread, 0, handle_connection, client_fd_pointer));
        CHECK_ERRNO(pthread_detach(thread));
    }
}

