#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();
    
    if (pid == 0) {
        // child process
        
        printf("Child process running..., My PID is %d\n", getpid());
        exit(0);
       
    }
    else if (pid > 0) {
        // parent process
        int stat;
        waitpid(pid, &stat, 0);
        printf("Parent process running..., My PID is %d\n", getpid());
        
    }
    else {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }
    
    return 0;
}
