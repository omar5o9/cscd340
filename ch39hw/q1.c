#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // Check if the file path is provided as a command-line argument
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    // Declare a struct stat variable
    struct stat fileStat;

    // Call the stat function to retrieve file information
    if (stat(argv[1], &fileStat) == -1) {
        perror("Error");
        return 1;
    }

    // Print the file information
    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("Blocks Allocated: %ld\n", fileStat.st_blocks);
    printf("Reference Count: %ld\n", fileStat.st_nlink);
    // Add more file information as needed

    return 0;
}
