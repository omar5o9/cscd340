#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("This is child process\n");
        printf("hello\n");
        exit(0);
    } else {
        while(waitpid(pid, NULL, WNOHANG) == 0) {
            // do nothing
        }
        printf("This is parent process\n");
        printf("goodbye\n");
    }
    return 0;
}
