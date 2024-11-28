#include "File_operations.h"

void create_file(char arguments[]) {  
    FILE *file = fopen(arguments, "r");
    if (file != NULL) {
        fclose(file);
        printf("Warning: file '%s' already exists, making a new file will overwrite the old one\n", arguments);
        printf("Proceed to overwrite file ? (y/n)\n");
        printf(">>");
        printf(" ");
        char conformation[10];
        fgets(conformation, sizeof(conformation), stdin);
        // Remove the newline character from the input
        conformation[strcspn(conformation, "\n")] = '\0';
        if (strcmp(conformation, "y") == 0) {
            // Removes the old file and create a new one
            fopen(arguments, "w");
            printf("'%s' created successfully\n", arguments);
            fclose();
        }
        else if (strcmp(conformation, "n") == 0) {
            printf("File creation cancelled\n");
        }
        else {
            printf("Invalid input\n");
            printf("File creation cancelled\n");
        }
    }
    else {
        fopen(arguments, "w");
        printf("'%s' created successfully\n", arguments);
        fclose();
    } 
}

void copy_file() { 
}

void delete_file() {
}

void show_file() { 
}