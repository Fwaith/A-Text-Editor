#include "Other_operations.h"

void show_change_log() {
    
}

int number_of_lines(char arguments[]) {
    FILE *file = fopen(arguments, "r"); // Open the file in read mode
    if (file == NULL) {
        // Error opening the file
        printf("Error: Could not open file '%s'.\n", arguments);
        return -1; // Return -1 to indicate an error
    }

    int lineCount = 0;
    char ch;

    // Read the file character by character
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lineCount++; // Increment line count on every newline character
        }
    }

    fclose(file); // Close the file
    return lineCount; // Return the total number of lines
}

void listf() {
#ifdef _WIN32
    system("dir");
#else
    system("ls");
#endif
}