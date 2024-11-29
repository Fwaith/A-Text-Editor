#include "File_operations.h"
#include "Line_operations.h"
#include "Other_operations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    if (is_installed()) {
        return;
    }
    char command[512];

// For Windows devices
#ifdef _WIN32
    snprintf(command, sizeof(command), "copy \"%s\" \"%s\"", INSTALL_PATH_SRC, INSTALL_PATH);
    if (system(command) == 0) {
        printf("Successfully installed 'ate' command. You can now use it globally.\n");
    }
    else {
        printf("Error: Failed to install 'ate'. Try running as Administrator.\n");
    }
// For macOS devices
#else
    snprintf(command, sizeof(command), "sudo mv \"%s\" \"%s\"", INSTALL_PATH_SRC, INSTALL_PATH);
    if (system(command) == 0) {
        printf("Successfully installed 'ate' command. You can now use it globally.\n");
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
    printf("create <file name> - Creates a single file given that it doesn't already exist\n");
    printf("copy <file name> - Creates a copy of a file\n");
    printf("delete <file name> - Deletes a file\n");
    printf("exit - Exits and ends the current running instance of the editor\n");
    printf("help - Displays all the commands along with its description\n");
    printf("listf - Lists all files in the current directory along with other relevant information\n");
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
        // To help see what the command and argument is (will remove later)
        printf("Command: %s\n", command);
        printf("Arguments: %s\n", arguments);   
        // Checks the command
        if (strcmp(command, "exit")==0) {
            running = 1;
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
        else if (strcmp(command, "show")==0) {
            show_file(arguments);
        }
        else if (strcmp(command, "shownl")==0) {
            int lines = number_of_lines(arguments); // Call the function to get the number of lines
            if (lines >= 0) {
                printf("The file '%s' contains %d line(s).\n", arguments, lines);
            } else {
                printf("Error: Could not determine the number of lines in the file.\n");
            }
        }
        else if (strcmp(command, "help")==0) {
            help();
        }
        else if (strcmp(command, "listf")==0) {
            listf();
        }
        else {
            printf("Error: Invalid command\n");
        }
    }
    return 0;
}