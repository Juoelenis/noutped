#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_TEXT_LENGTH 1024


void createFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error creating file");
        return;
    }
    printf("File '%s' created successfully.\n", filename);
    fclose(file);
}


void writeFile(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    char text[MAX_TEXT_LENGTH];
    printf("Enter text to write to the file (type ':wq' to save and quit):\n");


    while (1) {
        fgets(text, sizeof(text), stdin);


        if (strcmp(text, ":wq\n") == 0) {
            break;
        }


        fputs(text, file);
    }


    printf("Text saved to '%s'.\n", filename);
    fclose(file);
}


void readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error reading file");
        return;
    }
    
    char text[MAX_TEXT_LENGTH];
    printf("Contents of '%s':\n", filename);
    
    while (fgets(text, sizeof(text), file)) {
        printf("%s", text);
    }
    
    fclose(file);
}


int main() {
    char filename[100];
    int choice;


    printf("Simple Notepad Program\n");
    printf("Enter filename: ");
    scanf("%s", filename);
    getchar(); // Clear newline from input buffer


    while (1) {
        printf("\nOptions:\n");
        printf("1. Create New File\n");
        printf("2. Write to File\n");
        printf("3. Read File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from input buffer


        switch (choice) {
            case 1:
                createFile(filename);
                break;
            case 2:
                writeFile(filename);
                break;
            case 3:
                readFile(filename);
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }


    return 0;
}

