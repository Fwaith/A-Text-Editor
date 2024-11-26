#include "Append_file.h"
#include "Copy_file.h"
#include "Create_file.h"
#include "Delete_file.h"
#include "Delete_line.h"
#include "Insert_line.h"
#include "Show_change_log.h"
#include "Show_file.h"
#include "Show_help.h"
#include "Show_line.h"
#include "Show_number_of_lines.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#include <aclapi.h>
#define INSTALL_PATH_SRC "ate.exe"
#define INSTALL_PATH "C:\\Windows\\ate.exe"
#else
#include <sys/stat.h>
#include <limits.h>
#define INSTALL_PATH_SRC "./ate"
#define INSTALL_PATH "/usr/local/bin/ate"
#endif

// Function to get the directory of the currently running executable
void get_executable_directory(char *buffer, size_t size) {
#ifdef _WIN32
    if (GetModuleFileName(NULL, buffer, (DWORD)size) == 0) {
        fprintf(stderr, "Error: Unable to get executable path.\n");
        exit(1);
    }
    // Remove the executable name to get the directory
    char *last_slash = strrchr(buffer, '\\');
    if (last_slash) {
        *last_slash = '\0';
    }
#else
    ssize_t len = readlink("/proc/self/exe", buffer, size - 1);
    if (len == -1) {
        perror("Error: Unable to get executable path");
        exit(1);
    }
    buffer[len] = '\0';
    // Remove the executable name to get the directory
    char *last_slash = strrchr(buffer, '/');
    if (last_slash) {
        *last_slash = '\0';
    }
#endif
}

// Function to check if the program is installed
int is_installed() {
#ifdef _WIN32
    FILE *file = fopen(INSTALL_PATH, "r");
    if (file) {
        fclose(file);
        return 1; // File exists
    }
#else
    if (access(INSTALL_PATH, F_OK) == 0) {
        return 1; // File exists
    }
#endif
    return 0; // File does not exist
} 

// Function to delete a directory and its contents recursively
int delete_directory(const char *path) {
#ifdef _WIN32
    char command[512];
    snprintf(command, sizeof(command), "rmdir /S /Q \"%s\"", path);
    return system(command) == 0; // Use rmdir command on Windows
#else
    DIR *dir = opendir(path);
    if (!dir) return -1;

    struct dirent *entry;
    char filepath[512];
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);
        if (entry->d_type == DT_DIR) {
            if (delete_directory(filepath) != 0) {
                closedir(dir);
                return -1; // Recursively delete subdirectories
            }
        } else {
            if (remove(filepath) != 0) {
                closedir(dir);
                return -1; // Delete file
            }
        }
    }
    closedir(dir);
    return rmdir(path); // Delete the directory itself
#endif
}

// Installs ate
void install() {
    if (is_installed()) {
        return;
    }
    char command[512];

#ifdef _WIN32
    snprintf(command, sizeof(command), "copy \"%s\" \"%s\"", INSTALL_PATH_SRC, INSTALL_PATH);
    if (system(command) == 0) {
        printf("Successfully installed 'ate' command. You can now use it globally.\n");
    }
    else {
        printf("Error: Failed to install 'ate'. Try running as Administrator.\n");
    }
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

// Uninstalls ate
void uninstall() {
    if (!is_installed()) {
        printf("'ate' is not installed. Nothing to uninstall.\n");
        return;
    }
    printf("Uninstalling 'ate' from %s...\n", INSTALL_PATH);

    int executable_removed = 0; // Track if the executable is successfully removed

#ifdef _WIN32
    printf("Uninstalling 'ate' from %s...\n", INSTALL_PATH);

    // Attempt to delete the executable directly
    if (DeleteFile(INSTALL_PATH)) {
        printf("Successfully uninstalled 'ate'.\n");
        executable_removed = 1; // Mark as successfully removed
    } else {
        // Retrieve and print the error code
        DWORD error_code = GetLastError();

        switch (error_code) {
            case ERROR_FILE_NOT_FOUND:
                printf("Error: 'ate.exe' not found at %s. It may already be uninstalled.\n", INSTALL_PATH);
                break;
            case ERROR_ACCESS_DENIED:
                printf("Error: Access denied. Try running the program as Administrator.\n");
                break;
            case ERROR_SHARING_VIOLATION:
                printf("Error: File is being used by another process. Ensure no other application is using 'ate.exe' and try again.\n");
                break;
            default:
                printf("Error: Failed to uninstall 'ate'. Error code: %lu.\n", error_code);
        }
    }
#else
    if (remove(INSTALL_PATH) == 0) {
        printf("Successfully uninstalled 'ate'.\n");
        executable_removed = 1;
    } else {
        printf("Error: Failed to uninstall 'ate'. Try running with sudo.\n");
    }
#endif

    // Only remove source files if the executable was removed
    if (executable_removed) {
        char source_directory[512];
        get_executable_directory(source_directory, sizeof(source_directory));
        
        // Ensure the directory is appended only once
#ifdef _WIN32
        snprintf(source_directory, sizeof(source_directory), "%s\\A-Text-Editor", source_directory);
#else
        snprintf(source_directory, sizeof(source_directory), "%s/A-Text-Editor", source_directory);
#endif

        printf("Removing source files from %s...\n", source_directory);
        if (delete_directory(source_directory) == 0) {
            printf("Successfully removed source files.\n");
        } else {
            printf("Error: Failed to remove source files. Ensure you have the necessary permissions.\n");
        }
    }
}

int main() {
    install();
    char input[100];
    int running = 0;

    printf("Welcome to the A-Text-Editor Command-Line Editor\n");
    printf("Type 'ate help' for a full list of commands.\n");

    while (running == 0) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;    
        if (strcmp(input, "ate exit")==0) {
            running = 1;
        }
        else if (strcmp(input, "ate help")==0) {
            show_help();
        }
        else if (strcmp(input, "ate uninstall")==0){
            uninstall();
        }
        else {
            printf("Error: Invalid command\n");
        }
    }
    return 0;
}