#include "Other_operations.h"

void change_log(const char *operation, const char *filePath, const char *details) {
    FILE *logFile = fopen("changelog.txt", "a");
    if (logFile == NULL) {
        printf("Error: Unable to open changelog file.\n");
        return;
    }
    // Get the current timestamp
    time_t now = time(NULL);
    char timeStamp[20];
    strftime(timeStamp, sizeof(timeStamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    // Get the full directory path
    char fullPath[1024];
    realpath(filePath, fullPath); // Resolves the full directory path
    // Write the log entry
    fprintf(logFile, "[%s] Operation: %s, File: %s, Changes: %s\n", timeStamp, operation, fullPath, details);
    fclose(logFile);
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