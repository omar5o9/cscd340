#include <stdlib.h>

int main() {
    int* ptr = (int*) malloc(sizeof(int)); // allocate memory
    // do something with ptr
    // ...
    // forget to free memory
    return 0;
}
