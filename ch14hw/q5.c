#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int*) malloc(100 * sizeof(int)); // allocate memory for 100 integers
    data[100] = 0; // set the last element to zero
    // do something with the array
    free(data); // free the memory
    return 0;
}
