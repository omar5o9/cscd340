#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = malloc(100 * sizeof(int)); // allocate memory for array of 100 integers
    free(arr); // free the memory allocated for the array
    printf("%d", arr[0]); // try to print the value of the first element of the array
    return 0;
}
