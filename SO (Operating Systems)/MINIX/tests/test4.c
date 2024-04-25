# include <unistd.h>
# include <stdio.h>// test ma sprawdzić czy możliwe jest obudzenie procesu wykonującego wait_for_parent(); przy użyciu wait_for_sibling();
// (oczywiście nie powinno być)

int main() {
    int pid_1 = fork();
    if (pid_1 == 0) {
        //child process
        // wati for 1 second
        
        int pid_2 = fork();
        if (pid_2 == 0) {
            sleep(1);
            printf("1 ");
            
            wait_for_parent();
            return 0;
        } 
        wait_for_child();
        printf("2 ");
        wait_for_sibling();
        wait_for_parent();
        return 0;
    } 
    //parent process
    //wait for child
    wait_for_sibling();
    printf("3\n");
    wait_for_child();
    return 0;
}