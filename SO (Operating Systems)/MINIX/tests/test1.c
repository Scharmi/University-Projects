# include <unistd.h>
# include <stdio.h>
// Podstawowy test sprawdzający poprawność wait_for_child/parent
// include fork
# include <unistd.h>

int main() {
    //create another process
    int pid = fork();
    if (pid == 0) {
        //child process
        // wati for 1 second
        sleep(1);
        fprintf(stderr,"1 ");
        wait_for_parent();
    } else {
        //parent process
        //wait for child
        wait_for_child();
        fprintf(stderr, "2\n");
        
    }
    sleep(1);
    return 0;
}