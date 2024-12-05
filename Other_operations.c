#include "Other_operations.h"

// Cross-platform function to resolve the full path of a file
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

// Change log function
void change_log(const char *operation, const char *filePath, const char *details) {
    char installDir[1024];
    char changelogPath[1024];
    // Read the installation path from install_path.txt
    FILE *configFile = fopen("C:\\Users\\imana\\A-Text-Editor\\install_path.txt", "r");
    if (configFile == NULL) {
        printf("Error: Configuration file not found. Please reinstall 'ate'.\n");
        return;
    }
    if (fgets(installDir, sizeof(installDir), configFile) == NULL) {
        printf("Error: Could not read installation path from configuration.\n");
        fclose(configFile);
        return;
    }
    fclose(configFile);
    // Remove newline character from the installation path (if any)
    installDir[strcspn(installDir, "\n")] = '\0';
    // Construct the path for changelog.txt
    snprintf(changelogPath, sizeof(changelogPath), "%s\\changelog.txt", installDir);
    // Open the changelog file in append mode
    FILE *logFile = fopen(changelogPath, "a");
    if (logFile == NULL) {
        printf("Error: Unable to open changelog file at '%s'.\n", changelogPath);
        return;
    }
    // Get the current timestamp
    time_t now = time(NULL);
    char timeStamp[20];
    strftime(timeStamp, sizeof(timeStamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    // Write the log entry
    fprintf(logFile, "[%s] Operation: %s, File: %s, Changes: %s\n", timeStamp, operation, filePath, details);
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

void search_file(char arguments[]) {
    char searchTerm[256];
    // Prompt for the search term
    printf("text: ");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    searchTerm[strcspn(searchTerm, "\n")] = '\0'; // Remove newline character
    // Open the file for reading
    FILE *file = fopen(arguments, "r");
    if (file == NULL) {
        printf("Error: Unable to open file '%s'.\n", arguments);
        return;
    }
    // Search for the term in the file
    char line[1024];
    int lineNumber = 1;
    int found = 0;
    printf("Searching for '%s' in file '%s':\n", searchTerm, arguments);
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, searchTerm) != NULL) {
            printf("Line %d: %s", lineNumber, line);
            found = 1;
        }
        lineNumber++;
    }
    fclose(file);
    if (!found) {
        printf("No occurrences of '%s' found in the file.\n", searchTerm);
    }
}