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
    /*char buffer[10];
    int ret = snprintf(buffer, sizeof buffer, "%d", n_children);
    if (ret < 0 || ret >= (int)sizeof(buffer))
        fatal("snprintf failed");*/
    pid_t pid;
    printf("NUMBER: %d\n", n_children);
    if(n_children != 0) {
        fork();
        execlp("./line_exec", "./line_exec", n_children - 1, NULL);
    }
    wait(0);
    printf("My pid is %d, my parent's pid is %d\n", getpid(), getppid());

    return 0;
}
