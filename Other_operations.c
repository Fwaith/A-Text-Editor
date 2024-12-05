#include "Other_operations.h"

void resolve_full_path(const char *filePath, char *resolvedPath, size_t size) {
#ifdef _WIN32
    // Use _fullpath for Windows
    if (_fullpath(resolvedPath, filePath, size) == NULL) {
        // Fallback: Copy filePath if _fullpath fails
        strncpy(resolvedPath, filePath, size - 1);
        resolvedPath[size - 1] = '\0';
    }
#else
    // Use realpath for Unix-like systems
    if (realpath(filePath, resolvedPath) == NULL) {
        // Fallback: Copy filePath if realpath fails
        strncpy(resolvedPath, filePath, size - 1);
        resolvedPath[size - 1] = '\0';
    }
#endif
}

void change_log(const char *operation, const char *filePath, const char *details) {
    char fullPath[1024];
    char changelogPath[1024];
    char currentDir[1024];
    // Resolve full path of the file being logged
    if (realpath(filePath, fullPath) == NULL) {
        // Fallback if realpath fails
        snprintf(fullPath, sizeof(fullPath), "%s", filePath);
    }
    // Get the current working directory
    if (getcwd(currentDir, sizeof(currentDir)) == NULL) {
        printf("Error: Unable to get the current working directory.\n");
        return;
    }
    // Construct path for changelog.txt in the A-Text-Editor folder
    snprintf(changelogPath, sizeof(changelogPath), "%s/A-Text-Editor/changelog.txt", currentDir);

    // Ensure the A-Text-Editor folder exists
#ifdef _WIN32
    _mkdir("A-Text-Editor");
#else
    mkdir("A-Text-Editor", 0777);
#endif

    // Open the changelog file in append mode
    FILE *logFile = fopen(changelogPath, "a");
    if (logFile == NULL) {
        printf("Error: Unable to open or create changelog file at '%s'.\n", changelogPath);
        return;
    }
    // Get the current timestamp
    time_t now = time(NULL);
    char timeStamp[20];
    strftime(timeStamp, sizeof(timeStamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    // Write the log entry
    fprintf(logFile, "[%s] Operation: %s, File: %s, Changes: %s\n", timeStamp, operation, fullPath, details);
    fclose(logFile);
    printf("Logged operation to '%s'.\n", changelogPath);
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