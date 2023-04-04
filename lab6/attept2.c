#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

// function declarations
void print_regular_file_info(const char* filepath);
void print_symbolic_link_info(const char* filepath);

int main(int argc, char** argv) {
    // check for correct usage
    if (argc < 2) {
        printf("Use the code like this: %s [filepath1] [filepath2] ...\n", argv[0]);
        exit(1);
    }

    // iterate through all files in the arguments
    for (int i = 1; i < argc; i++) {
        struct stat statbuf;
        if (lstat(argv[i], &statbuf) == -1) {
            printf("Error: could not access file %s\n", argv[i]);
            continue;
        }

        // print file info based on file type
        if (S_ISREG(statbuf.st_mode)) {
            printf("Regular file: %s\n", argv[i]);
            print_regular_file_info(argv[i]);
        }
        else if (S_ISLNK(statbuf.st_mode)) {
            printf("Symbolic link: %s\n", argv[i]);
            print_symbolic_link_info(argv[i]);
        }
        else if (S_ISDIR(statbuf.st_mode)) {
            printf("Directory: %s\n", argv[i]);
            // add options for directory
        }
        else {
            printf("Unknown file type: %s\n", argv[i]);
        }
    }

    return 0;
}

void print_regular_file_info(const char* filepath) {
    // print regular file info
    printf("Options:\n");
    printf("-n: name\n");
    printf("-d: size\n");
    printf("-h: hard link count\n");
    printf("-m: time of last modification\n");
    printf("-a: access rights\n");
    printf("-I: create symbolic link\n");

    // get user input for options
    char input;
    printf("Enter option: ");
    scanf(" %c", &input);

    // process option
    switch (input) {
        case 'n':
            printf("Name: %s\n", filepath);
            break;
        case 'd': {
            struct stat statbuf;
            if (stat(filepath, &statbuf) == 0) {
                printf("Size: %ld bytes\n", statbuf.st_size);
            } else {
                printf("Error: could not access file %s\n", filepath);
            }
            break;
        }
        case 'h': {
            struct stat statbuf;
            if (stat(filepath, &statbuf) == 0) {
                printf("Hard link count: %ld\n", statbuf.st_nlink);
            } else {
                printf("Error: could not access file %s\n", filepath);
            }
            break;
        }
        case 'm': {
            struct stat statbuf;
            if (stat(filepath, &statbuf) == 0) {
                printf("Time of last modification: %ld\n", statbuf.st_mtime);
            } else {
                printf("Error: could not access file %s\n", filepath);
            }
            break;
        }
        case 'a':struct stat statbuf;
                     if (stat(filepath, &statbuf) == 0) {
                         printf("Access rights: ");
                         printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");
                         printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
                         printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
                         printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
                         printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
                         printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
                         printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
                         printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
                         printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
                         printf((statbuf.st_mode & S_IXOTH) ? "x" : "-");
                         printf("\n");
                     } else {
                         printf("Error: could not access file %s\n", filepath);
                     }
                     break;
        case 'I':case 'I': {
                     char link_path[100];
                     printf("Enter path for symbolic link: ");
                     scanf("%s", link_path);
                     if (symlink(filepath, link_path) == 0) {
                         printf("Symbolic link created successfully at %s\n", link_path);
                     } else {
                         printf("Error creating symbolic link\n");
                     }
                     break;
                 }

        default:
            printf("Invalid option\n");
            break;
    }
}

void print_symbolic_link_info(const char* filepath) {
    // print symbolic link info
    printf("Options:\n");
    printf("-n: name\n");
    printf("-l: delete symbolic link\n");
    printf("-d: size of symbolic link\n");
    printf("-t: size of target file\n");
    printf("-a: access rights\n");

    // get user input for options
    char input;
    printf("Enter option: ");
    scanf(" %c", &input);

    // process option
    switch (input) {
        case 'n':
            printf("Name: %s\n", filepath);
            break;
        case 'l':
            if (unlink(filepath) == 0) {
                printf("Symbolic link deleted successfully\n");
            } else {
                printf("Error deleting symbolic link\n");
            }
            break;
        case 'd': {
            struct stat statbuf;
            if (lstat(filepath, &statbuf) == 0) {
                printf("Size of symbolic link: %ld bytes\n", statbuf.st_size);
            } else {
                printf("Error: could not access file %s\n", filepath);
            }
            break;
        }
        case 't': {
            char target_path[256];
            if (readlink(filepath, target_path, sizeof(target_path)) == -1) {
                printf("Error: could not read target path of symbolic link %s\n", filepath);
            } else {
                struct stat statbuf;
                if (lstat(target_path, &statbuf) == 0) {
                    printf("Size of target file: %ld bytes\n", statbuf.st_size);
                } else {
                    printf("Error: could not access target file %s\n", target_path);
                }
            }
            break;
        }
        case 'a':struct stat statbuf;
                     if (stat(filepath, &statbuf) == 0) {
                         printf("Access rights: ");
                         printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");
                         printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
                         printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
                         printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
                         printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
                         printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
                         printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
                         printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
                         printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
                         printf((statbuf.st_mode & S_IXOTH) ? "x" : "-");
                         printf("\n");
                     } else {
                         printf("Error: could not access file %s\n", filepath);
                     }
                     break;
        default:
            printf("Invalid option\n");
            break;
    }
}
