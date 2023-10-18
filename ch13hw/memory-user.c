#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    
    if(argc != 3) {
        printf("Usage: %s <memory size in MB> <time in seconds>\n", argv[0]);
        return 1;
    }

    printf("Current PID = %d\n", getpid());
    long long int size = ((long long int)atoi(argv[1]))*1024*1024/sizeof(int); //in number of integers
    int* buffer = (int*)malloc(size*sizeof(int));

    if(buffer == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    time_t endwait, seconds, start;
    seconds=atoi(argv[2]);
    start=time(NULL);
    endwait = start + seconds;
    
    printf("Using %11lld bytes in %ld seconds\n", size*sizeof(int), seconds);

    while(start < endwait) {
   
        for(long long int i=0; i<size; i++) {
            buffer[i] = i;
        }
        start = time(NULL);
    }
    printf("(done)\n");
    free(buffer);
    return 0;
}
