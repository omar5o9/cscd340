#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> 


void listFiles(const char* directory, int detailed) {
    DIR* dir = opendir(directory);
    if (dir == NULL) {
        printf("Error opening directory: %s\n", directory);
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (detailed) {
            struct stat fileStat;
            char filePath[256];
            snprintf(filePath, sizeof(filePath), "%s/%s", directory, entry->d_name);
            if (stat(filePath, &fileStat) == -1) {
                printf("Error getting file information: %s\n", entry->d_name);
                continue;
            }
            printf("File: %s\n", entry->d_name);
            printf("Owner: %d\n", fileStat.st_uid);
            printf("Group: %d\n", fileStat.st_gid);
            printf("Permissions: %o\n", fileStat.st_mode & 0777);
            // Print other file information as needed
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main(int argc, char* argv[]) {
    int detailed = 0;
    const char* directory;

    if (argc == 2 && strcmp(argv[1], "-l") == 0) {
        detailed = 1;
        directory = getcwd(NULL, 0);
    } else if (argc == 3 && strcmp(argv[1], "-l") == 0) {
        detailed = 1;
        directory = argv[2];
    } else if (argc == 2) {
        directory = argv[1];
    } else {
        directory = getcwd(NULL, 0);
    }

    listFiles(directory, detailed);

    return 0;
}
