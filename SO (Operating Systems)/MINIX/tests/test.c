#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;
    // Create a child process
    if (!fork()) {
        sleep(4);
        wait_for_parent();
        sleep(1);
        wait_for_parent();
    } else {
        wait_for_child();
        printf("WAITED");
    }
    sleep(10);
    return 0;
}
