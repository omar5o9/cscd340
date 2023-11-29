#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h> // Include the <string.h> header
#include <limits.h> // Include the <limits.h> header

void listFiles(const char *dirPath, int showDetails) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    // Open the directory
    dir = opendir(dirPath);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Get the file path
                char filePath[PATH_MAX];
                snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, entry->d_name);

                // Get file information
                if (showDetails) {
                    if (stat(filePath, &fileStat) == -1) {
                        perror("stat");
                        exit(EXIT_FAILURE);
                    }

                    // Print file details
                    printf("File: %s\n", entry->d_name);
                    printf("Owner: %d\n", fileStat.st_uid);
                    printf("Group: %d\n", fileStat.st_gid);
                    printf("Permissions: %o\n", fileStat.st_mode & 0777);
                    printf("Size: %ld bytes\n", fileStat.st_size);
                    printf("Last modified: %s", ctime(&fileStat.st_mtime));
                }
            }
            closedir(dir);
        }

        int main(int argc, char *argv[]) {
            const char *dirPath;
            int showDetails = 0;

            if (argc == 3 && strcmp(argv[1], "-l") == 0) {
                showDetails = 1;
                dirPath = argv[2];
            } else if (argc == 2) {
                // Directory path provided
                dirPath = argv[1];
            } else {
                fprintf(stderr, "Usage: %s [-l] [directory]\n", argv[0]);
                exit(EXIT_FAILURE);
            }

            // List files in the directory
            listFiles(dirPath, showDetails);

            return 0;
        }
    // Check if directory path is provided
    if (argc == 1) {
        // No directory path provided, use current working directory
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd");
            exit(EXIT_FAILURE);
        }
        dirPath = cwd;
    } else if (argc == 2) {
        // Directory path provided
        dirPath = argv[1];
    } else {
        fprintf(stderr, "Usage: %s [-l] [directory]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Check if -l flag is provided
    int showDetails = 0;
    if (argc == 3 && strcmp(argv[1], "-l") == 0) {
        showDetails = 1;
    }

    // List files in the directory
    listFiles(dirPath, showDetails);

    return 0;
}
