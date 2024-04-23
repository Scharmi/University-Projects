#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "err.h"


int main(int argc, char* argv[])
{
    int n_children = 5;
    if (argc > 2)
        fatal("Expected zero or one arguments, got: %d.", argc - 1);
    if (argc == 2)
        n_children = atoi(argv[1]);
    pid_t pid;
    ASSERT_SYS_OK(pid = fork());
    while (pid == 0) {
        // Child process
        printf("NUMBER: %d\n", n_children);
        n_children--;
        if(n_children == 0) exit(1);
        ASSERT_SYS_OK(pid = fork());
        
    }
    printf("My pid is %d, my parent's pid is %d\n", getpid(), getppid());
    ASSERT_SYS_OK(wait(0));
    return 0;
}
