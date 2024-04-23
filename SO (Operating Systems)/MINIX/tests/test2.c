# include <unistd.h>
# include <stdio.h>// Podstawowy test sprawdzający poprawność wait_for_child/parent

int main() {
    //create another process
    int pid = fork();
    if (pid == 0) {
        //child process
        // wati for 1 second
        
        wait_for_parent();
        fprintf(stderr, "2 \n");
        return 0;
    } 
    //parent process
    //wait for child
    sleep(1);
    fprintf(stderr, "1 ");
    wait_for_child();
        
    return 0;
}