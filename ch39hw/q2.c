#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void printFileInfo(const char* filename) {
    struct stat fileStat;
    if (stat(filename, &fileStat) == -1) {
        perror("stat");
        return;
    }

    printf("File: %s\n", filename);
    printf("Owner: %d\n", fileStat.st_uid);
    printf("Group: %d\n", fileStat.st_gid);
    printf("Permissions: %o\n", fileStat.st_mode & 0777);
    printf("Size: %ld bytes\n", fileStat.st_size);
    printf("Last modified: %s", ctime(&fileStat.st_mtime));
    printf("\n");
}

void listFiles(const char* directory, int showFileInfo) {
    DIR* dir;
    struct dirent* entry;

    if ((dir = opendir(directory)) == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (showFileInfo) {
            char path[PATH_MAX];
            snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);
            printFileInfo(path);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main(int argc, char* argv[]) {
    const char* directory;

    if (argc == 1) {
        directory = getcwd(NULL, 0);
    } else if (argc == 3 && strcmp(argv[1], "-l") == 0) {
        directory = argv[2];
    } else {
        printf("Usage: %s [-l] [directory]\n", argv[0]);
        return 1;
    }

    listFiles(directory, argc == 3 && strcmp(argv[1], "-l") == 0);

    return 0;
}
