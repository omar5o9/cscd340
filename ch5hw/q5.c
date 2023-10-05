#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();
    
    if (pid == 0) {
        // child process
        int wt = wait(NULL);
        printf("Child process running...\n");
        printf("Return code from wait() is %d\n", wt);
       
    }
    else if (pid > 0) {
        // parent process
        printf("Parent process running...\n");
        
    }
    else {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }
    
    return 0;
}
