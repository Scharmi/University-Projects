# include <unistd.h>
# include <stdio.h>// Test sprawdzający cy proces wywołujący wait_for_sibling może być wzbudzony przez proces, który nie jest jego bezpośrednim rodzeństwem
// (oczywiście nie powinno być)


int main() {
    int pid_1 = fork();
    if (pid_1 == 0) {
        int pid_11 = fork();
        if (pid_11 == 0) {
            sleep(1);
            wait_for_sibling();
            return 0;
        }
        int pid_12 = fork();
        if(pid_12 == 0) {
            wait_for_sibling();
            fprintf(stderr, "1 ");
            wait_for_parent();
            return 0;
        }
        wait_for_child();
        fprintf(stderr, "2 ");
        wait_for_sibling();
        return 0;
    }
    int pid_2 = fork();
    if (pid_2 == 0) {
        wait_for_sibling();
        fprintf(stderr, "3\n");
        wait_for_parent();
        return 0;
    }
    wait_for_child();
    return 0;
}