#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_PATH 1024
#define MAX_FILE_CONTENT 1024

// Function to list files in a directory
void list_files(char *path) {
    DIR *dir;
    struct dirent *ent;

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        printf("Error: Unable to open directory %s\n", path);
        return;
    }

    // Traverse the directory and print file names
    printf("Files in directory %s:\n", path);
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG) {
            printf("%s\n", ent->d_name);
        }
    }

    // Close the directory
    closedir(dir);
}

// Function to create a file with user input
void create_file(char *path) {
    char filename[MAX_PATH], content[MAX_FILE_CONTENT];
    FILE *fp;

    // Get the file name and content from the user
    printf("Enter file name: ");
    scanf("%s", filename);
    printf("Enter file content: ");
    scanf("%s", content);

    // Create the file in the specified directory
    char filepath[MAX_PATH];
    sprintf(filepath, "%s/%s", path, filename);
    fp = fopen(filepath, "w");
    if (fp == NULL) {
        printf("Error: Unable to create file %s\n", filepath);
        return;
    }

    // Write the content to the file
    fprintf(fp, "%s", content);

    // Close the file
    fclose(fp);

    printf("File %s created successfully.\n", filepath);
}

// Function to print the content of a file
void print_file(char *path) {
    char filename[MAX_PATH], c;
    FILE *fp;

    // Get the file name from the user
    printf("Enter file name: ");
    scanf("%s", filename);

    // Open the file in the specified directory
    char filepath[MAX_PATH];
    sprintf(filepath, "%s/%s", path, filename);
    fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file %s\n", filepath);
        return;
    }

    // Print the content of the file
    printf("Content of file %s:\n", filepath);
    while ((c = fgetc(fp)) != EOF) {
        printf("%c", c);
    }

    // Close the file
    fclose(fp);
}
int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *ent;
    char directory_name[256];
    char file_name[256];
    char file_content[1024];
    char ch;
    char choice;



        dir = opendir(argv[1]);
        if (dir == NULL) {
            perror("opendir");
            exit(EXIT_FAILURE);
        }


    // check if a directory name was provided as an argument
    if (argc < 2) {
        printf("Please provide a directory name as an argument.\n");
        return 1;
    }

    // copy the directory name from the command line argument to a variable
    strcpy(directory_name, argv[1]);

    // open the directory
    dir = opendir(directory_name);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    // display menu of operations to choose from
    printf("Please select an operation:\n");
    printf("1. List files in directory\n");
    printf("2. Create a new file in directory\n");
    printf("3. Print the contents of a file in directory\n");

    // get user's choice
    scanf("%d", &choice);

    // perform operation based on user's choice
    switch (choice) {
        case 1:
            // list files in directory
            while ((entry = readdir(dir)) != NULL) {
                   if (entry->d_type == DT_REG) {
                       printf("%s\n", entry->d_name);
                   }
               }
            closedir(dir);
            break;

        case 2:
            // create a new file in directory
            printf("Please enter a name for the new file: ");
            scanf("%s", file_name);

            // create and open the file for writing
            FILE *file = fopen(file_name, "w");
            if (file == NULL) {
                perror("Error creating file");
                return 1;
            }

            // get content of new file from user input
            printf("Please enter the content of the file:\n");
            getchar(); // consume newline character from previous scanf
            fgets(file_content, 1024, stdin);

            // write the content to the file
            fprintf(file, "%s", file_content);

            // close the file
            fclose(file);
            printf("File created successfully.\n");
            break;

        case 3:
            // print contents of a file in directory
            printf("Please enter the name of the file to print: ");
            scanf("%s", file_name);

            // create and open the file for reading
            FILE *file_to_read = fopen(file_name, "r");
            if (file_to_read == NULL) {
                perror("Error opening file");
                return 1;
            }

            // read and print the contents of the file
            printf("Contents of %s:\n", file_name);
            while ((ch = fgetc(file_to_read)) != EOF) {
                printf("%c", ch);
            }

            // close the file
            fclose(file_to_read);
            break;

        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}



/*
int main(int argc, char *argv[]) {
    DIR *dir;
        struct dirent *entry;

        if (argc != 2) {
            printf("Usage: %s <directory>\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        dir = opendir(argv[1]);
        if (dir == NULL) {
            perror("opendir");
            exit(EXIT_FAILURE);
        }

    // Print the files in the directory
    printf("Files in directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            printf("%s\n", entry->d_name);
        }
    }

    // Create a file in the directory
    char filename[256], content[256];
    printf("Enter filename: ");
    scanf("%s", filename);
    printf("Enter file content: ");
    scanf("%s", content);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", argv[1], filename);
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s\n", content);
    fclose(file);
    printf("File created: %s\n", path);

    // Print the contents of a file in the directory
    printf("Enter filename to display contents: ");
    scanf("%s", filename);
    snprintf(path, sizeof(path), " %s/%s ", argv[1], filename);
    file = fopen(path, "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    printf("File contents:\n");
    char c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    closedir(dir);
    return 0;
}
*/