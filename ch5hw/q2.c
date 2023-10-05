#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/stat.h>


// Question 2

int main(){

    int fd = open("file.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    int pid = fork();

    if (pid == 0) {
        const char * childSTR = "Child process. Writing\n";
        
        printf("Child process\n");
        printf("Child File Description: (file handle): %d\n", fd);
        write(fd, childSTR, strlen(childSTR));
        
    } else if (pid > 0) {
        const char * parentSTR = "Parent process. Writing\n";
        printf("Parent process\n");
        printf("Parent File Description: (file handle): %d\n", fd);
        write(fd, parentSTR, strlen(parentSTR));

    } else {
        printf("Fork failed\n");
        exit(1);
    }
    close(fd);
    return 0;
}