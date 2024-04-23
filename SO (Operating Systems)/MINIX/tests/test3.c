# include <unistd.h>
# include <stdio.h>
int main() {

    for (int i = 0; i < 10; i++) {
        int pid = fork();
        if (pid == 0) {
            //child process
            wait_for_parent();
            fprintf(stderr, "this should be printed later 10 times\n");
            
            return 0;
        }
    }
    sleep(1);
    printf("this should be printed first\n");
    for (int i = 0; i < 10; i++) {
        fprintf(stderr, "%d ", i);
        wait_for_child();
        sleep(1);
    }
    return 0;
}