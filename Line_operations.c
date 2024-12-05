#include "File_operations.h"
#include "Other_operations.h"

void append_line(char arguments[]) {
    printf("text: ");
    char line[1024];
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = '\0'; // Remove newline character
    FILE *file = fopen(arguments, "a");
    if (file == NULL) {
        printf("Error: Unable to open file '%s' for appending\n", arguments);
        return;
    }
    fprintf(file, "%s\n", line);
    fclose(file);
    // Log the change
    char logDetails[1100];
    snprintf(logDetails, sizeof(logDetails), "Appended line: '%s'", line);
    change_log("append", arguments, logDetails);
    printf("Line appended successfully to '%s'\n", arguments);
}

// Deletes a specific line from the file
void delete_line(char arguments[]) {
    printf("line: ");
    int lineNumber;
    scanf("%d", &lineNumber);
    getchar(); // Clear the newline character from the input buffer
    FILE *file = fopen(arguments, "r");
    if (file == NULL) {
        printf("Error: Unable to open file '%s' for deleting a line\n", arguments);
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        fclose(file);
        printf("Error: Unable to create temporary file.\n");
        return;
    }
    int currentLine = 1;
    char line[1024];
    int lineFound = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (currentLine == lineNumber) {
            lineFound = 1;
        } 
        else {
            fprintf(temp, "%s", line);
        }
        currentLine++;
    }
    fclose(file);
    fclose(temp);
    remove(arguments);
    rename("temp.txt", arguments);
    if (lineFound) {
        // Log the change
        char logDetails[100];
        snprintf(logDetails, sizeof(logDetails), "Deleted line %d", lineNumber);
        change_log("delete", arguments, logDetails);
        printf("Line %d deleted successfully from '%s'\n", lineNumber, arguments);
    }
    else {
        printf("Error: Line %d not found in the file.\n", lineNumber);
    }
}

// Inserts a line at a specific position in the file
void insert_line(char arguments[]) {
    printf("text: ");
    char newLine[1024];
    fgets(newLine, sizeof(newLine), stdin);
    newLine[strcspn(newLine, "\n")] = '\0'; // Remove newline character
    printf("line: ");
    int lineNumber;
    scanf("%d", &lineNumber);
    getchar(); // Clear the newline character from the input buffer
    FILE *file = fopen(arguments, "r");
    if (file == NULL) {
        printf("Error: Unable to open file '%s' for inserting a line\n", arguments);
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        fclose(file);
        printf("Error: Unable to create temporary file.\n");
        return;
    }
    int currentLine = 1;
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (currentLine == lineNumber) {
            fprintf(temp, "%s\n", newLine);
        }
        fprintf(temp, "%s", line);
        currentLine++;
    }
    if (currentLine <= lineNumber) {
        fprintf(temp, "%s\n", newLine);
    }
    fclose(file);
    fclose(temp);
    remove(arguments);
    rename("temp.txt", arguments);
    // Log the change
    char logDetails[1100];
    snprintf(logDetails, sizeof(logDetails), "Inserted line: '%s' at line %d", newLine, lineNumber);
    change_log("insert", arguments, logDetails);
    printf("Line inserted successfully into '%s'\n", arguments);
}

void show_line(char arguments[]) {
    printf("line: ");
    int lineNumber;
    if (scanf("%d", &lineNumber) != 1 || lineNumber <= 0) { // Validate input
        printf("Error: Invalid line number.\n");
        getchar(); // Clear invalid input from buffer
        return;
    }
    getchar(); // Clear the newline character from the input buffer
    FILE *file = fopen(arguments, "r");
    if (file == NULL) {
        printf("Error: Unable to open file '%s' to show line.\n", arguments);
        return;
    }
    int currentLine = 1;
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (currentLine == lineNumber) {
            line[strcspn(line, "\n")] = '\0'; // Remove newline character
            printf("Line %d: %s\n", lineNumber, line);
            // Log the change
            char logDetails[1024];
            snprintf(logDetails, sizeof(logDetails), "Viewed line %d: '%s'", lineNumber, line);
            change_log("view", arguments, logDetails);
            fclose(file);
            return;
        }
        currentLine++;
    }
    fclose(file);
    // If the specified line does not exist
    printf("Error: Line %d does not exist in the file.\n", lineNumber);
}