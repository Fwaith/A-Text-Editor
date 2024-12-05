#include "File_operations.h"
#include "Line_operations.h"
#include "Other_operations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <direct.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#define INSTALL_PATH_SRC "ate.exe"
#define INSTALL_PATH "C:\\Windows\\ate.exe"
#else
#include <sys/stat.h>
#define INSTALL_PATH_SRC "./ate"
#define INSTALL_PATH "/usr/local/bin/ate"
#endif

// Function to check if the program is installed
int is_installed() {
// For Windows devices
#ifdef _WIN32
    FILE *file = fopen(INSTALL_PATH, "r");
    if (file) {
        fclose(file);
        return 1;
    }
// For macOS devices
#else
    if (access(INSTALL_PATH, F_OK) == 0) {
        return 1;
    }
#endif
    return 0;
}

// Installs ate
void install() {
    char installDir[1024];
    char changelogPath[1024];
    char configFilePath[1024];
    char command[512];
    FILE *logFile = NULL;
    FILE *configFile = NULL;
    // Get the current working directory
    if (getcwd(installDir, sizeof(installDir)) == NULL) {
        perror("Error: Unable to get the current working directory");
        return;
    }
    // Append the subdirectory for the installation if not already present
#ifdef _WIN32
    if (!strstr(installDir, "A-Text-Editor")) {
        snprintf(installDir, sizeof(installDir), "%s\\A-Text-Editor", installDir);
    }
#else
    if (!strstr(installDir, "A-Text-Editor")) {
        snprintf(installDir, sizeof(installDir), "%s/A-Text-Editor", installDir);
    }
#endif
    // Construct paths for changelog.txt and install_path.txt
    snprintf(changelogPath, sizeof(changelogPath), "%s/changelog.txt", installDir);
    snprintf(configFilePath, sizeof(configFilePath), "%s/install_path.txt", installDir);
    // Notify about the directory assumption
    printf("Directory exists or assumed to exist: %s\n", installDir);
    // Create or verify the changelog.txt file
    logFile = fopen(changelogPath, "a");
    if (logFile == NULL) {
        printf("Error: Could not create or open changelog file at '%s'. Check your permissions.\n", changelogPath);
    } 
    else {
        fclose(logFile);
        printf("Changelog file ready at '%s'.\n", changelogPath);
    }
    // Save the installation path in install_path.txt
    configFile = fopen(configFilePath, "w");
    if (configFile == NULL) {
        printf("Error: Unable to save installation path configuration at '%s'.\n", configFilePath);
    } 
    else {
        fprintf(configFile, "%s\n", installDir); // Save the installation directory path
        fclose(configFile);
        printf("Installation directory saved to '%s'.\n", configFilePath);
    }
    // Install the ate executable (DO NOT MODIFY THIS PART)
#ifdef _WIN32
    snprintf(command, sizeof(command), "copy \"%s\" \"%s\"", INSTALL_PATH_SRC, INSTALL_PATH);
    if (system(command) == 0) {
        printf("Successfully installed 'ate' command to '%s'. You can now use it globally.\n", INSTALL_PATH);
    } 
    else {
        printf("Error: Failed to install 'ate'. Try running as Administrator.\n");
    }
#else
    snprintf(command, sizeof(command), "sudo mv \"%s\" \"%s\"", INSTALL_PATH_SRC, INSTALL_PATH);
    if (system(command) == 0) {
        printf("Successfully installed 'ate' command to '%s'. You can now use it globally.\n", INSTALL_PATH);
    } 
    else {
        printf("Error: Failed to install 'ate'. Try running with sudo.\n");
    }
#endif
}

void split_input(char *input, char *command, char *arguments) {
    // Remove the "ate " prefix
    if (strncmp(input, "ate ", 4) == 0) {
        input += 4; // Move the pointer to skip "ate "
    }
    // Find the first space in the remaining input
    char *space = strchr(input, ' ');
    if (space != NULL) {
        // Split into command and arguments
        size_t command_length = space - input;
        strncpy(command, input, command_length);
        command[command_length] = '\0'; 
        // Copy the remaining part as arguments
        strcpy(arguments, space + 1);
    } 
    else {
        // No space found, the entire input is the command
        strcpy(command, input);
        arguments[0] = '\0'; // No arguments
    }
}

void help() {
    printf("-------------------------\n");
    printf("| Full list of commands |\n");
    printf("-------------------------");
    printf("\nTo enter a command, type ate <command>\n");
    printf("\tExample: ate help\n");
    printf("\nate (by itself) - Opens the editor\n");
    printf("append <file name> - Specifies the file to append a line to\n");
    printf("create <file name> - Creates a single file given that it doesn't already exist\n");
    printf("copy <file name> - Creates a copy of a file\n");
    printf("delete <file name> - Deletes the specified file\n");
    printf("exit - Exits and ends the current running instance of the editor\n");
    printf("help - Displays all the commands along with its description\n");
    printf("insert <file name> - Specifies the file to insert a line of text\n");
    printf("listf - Lists all files in the current directory along with other relevant information\n");
    printf("lndelete <file name> - Specifies the file to delete a particular line of text\n");
    printf("lnshow <file name> - Specifies the file to show a particular line of text\n");
    printf("log - Shows the change log; the actions performed by the editor in chronological order\n");
    printf("search <file name> - Specifies the file to be searched for a string\n");
    printf("show - Shows the contents of a file along with the line numbers\n");
    printf("shownl - Shows the number of lines in a specified file\n");
}

int main() {
    install();
    int running = 0;
    printf("Welcome to the A-Text-Editor Command-Line Editor\n");
    printf("Type 'ate help' for a full list of commands.\n");
    while (running == 0) {
        // Input buffers
        char input[256];
        char command[56];
        char arguments[200];
        // Prompt
        printf(">>");
        printf(" ");
        fgets(input, sizeof(input), stdin);
        // Removes newline character
        input[strcspn(input, "\n")] = 0;
        // Splits input to its 'command' and 'argument'
        split_input(input, command, arguments);   
        // Checks the command
        if (strcmp(command, "exit")==0) {
            running = 1;
        }
        else if (strcmp(command, "append")==0) {
            append_line(arguments);
        }
        else if (strcmp(command, "create")==0) {
            create_file(arguments);
        }
        else if (strcmp(command, "copy")==0) {
            copy_file(arguments);
        }
        else if (strcmp(command, "delete")==0) {
            delete_file(arguments);
        }
        else if (strcmp(command, "help")==0) {
            help();
        }
        else if (strcmp(command, "insert")==0) {
            insert_line(arguments);
        }
        else if (strcmp(command, "listf")==0) {
            listf();
        }
        else if (strcmp(command, "lndelete")==0) {
            delete_line(arguments);
        }
        else if (strcmp(command, "lnshow")==0) {
            show_line(arguments);
        }
        else if (strcmp(command, "log") == 0) {
            char changelogPath[1024];
            FILE *logFile = NULL;
            // Construct the path for changelog.txt in the current working directory
        #ifdef _WIN32
            snprintf(changelogPath, sizeof(changelogPath), ".\\changelog.txt");
        #else
            snprintf(changelogPath, sizeof(changelogPath), "./changelog.txt");
        #endif
            // Attempt to open the changelog file
            logFile = fopen(changelogPath, "r");
            if (logFile == NULL) {
                // If the changelog file doesn't exist, create it
                printf("No changelog found. Creating a new changelog file at '%s'.\n", changelogPath);
                logFile = fopen(changelogPath, "w");
                if (logFile == NULL) {
                    printf("Error: Unable to create changelog file at '%s'. Check your permissions.\n", changelogPath);
                } 
                else {
                    printf("Changelog file created successfully at '%s'.\n", changelogPath);
                    fclose(logFile);
                    logFile = NULL;
                }
            } 
            else {
                // Read and display the contents of the existing changelog
                printf("Change Log:\n");
                char line[1024];
                while (fgets(line, sizeof(line), logFile) != NULL) {
                    printf("%s", line); // Print each line from the changelog
                }
                fclose(logFile); // Close the changelog file
                logFile = NULL;
            }
        }
        else if (strcmp(command, "search")==0) {
            search_file(arguments);
        }
        else if (strcmp(command, "show")==0) {
            show_file(arguments);
        }
        else if (strcmp(command, "shownl")==0) {
            int lines = number_of_lines(arguments); // Call the function to get the number of lines
            if (lines >= 0) {
                printf("The file '%s' contains %d line(s).\n", arguments, lines);
            } 
            else {
                printf("Error: Could not determine the number of lines in the file.\n");
            }
        }
        else {
            printf("Error: Invalid command\n");
        }
    }
    return 0;
}