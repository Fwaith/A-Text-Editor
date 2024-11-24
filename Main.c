#include "Append_file.h"
#include "Copy_file.h"
#include "Create_file.h"
#include "Delete_file.h"
#include "Delete_line.h"
#include "Insert_line.h"
#include "Show_change_log.h"
#include "Show_file.h"
#include "Show_line.h"
#include "Show_number_of_lines.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <mach-o/dyld.h>  // For _NSGetExecutablePath
#include <unistd.h>       // For exec permissions
#endif

// Define the folder name and target command name
#define FOLDER_NAME "A-Text-Editor"
#define COMMAND_NAME "ate"

void install_self(const char *self_path) {
    char install_path[512];
    char command[1024];

#ifdef _WIN32
    // On Windows, install to C:\Windows\ate.exe
    snprintf(install_path, sizeof(install_path), "C:\\Windows\\%s.exe", COMMAND_NAME);

    // Copy file to the install location
    snprintf(command, sizeof(command), "copy \"%s\" \"%s\"", self_path, install_path);
    if (system(command) != 0) {
        fprintf(stderr, "Error: Failed to copy the file to %s. Try running as Administrator.\n", install_path);
        exit(1);
    }

    printf("Successfully installed '%s' command on Windows! You can now use it globally.\n", COMMAND_NAME);

#elif __APPLE__
    // On macOS, install to /usr/local/bin/ate
    snprintf(install_path, sizeof(install_path), "/usr/local/bin/%s", COMMAND_NAME);

    // Copy file to install location
    snprintf(command, sizeof(command), "cp \"%s\" \"%s\"", self_path, install_path);
    if (system(command) != 0) {
        fprintf(stderr, "Error: Failed to copy the file to %s. Try running with sudo.\n", install_path);
        exit(1);
    }

    // Make the file executable
    snprintf(command, sizeof(command), "chmod +x \"%s\"", install_path);
    if (system(command) != 0) {
        fprintf(stderr, "Error: Failed to set executable permissions on %s.\n", install_path);
        exit(1);
    }

    printf("Successfully installed '%s' command on macOS! You can now use it globally.\n", COMMAND_NAME);

#else
    fprintf(stderr, "Error: Unsupported platform.\n");
    exit(1);
#endif
}

void get_self_path(char *buffer, size_t size) {
#ifdef _WIN32
    // Windows: Use GetModuleFileName to get the path of the current executable
    if (!GetModuleFileName(NULL, buffer, (DWORD)size)) {
        fprintf(stderr, "Error: Unable to determine the executable path.\n");
        exit(1);
    }
#elif __APPLE__
    // macOS: Use _NSGetExecutablePath to get the path of the current executable
    uint32_t buffer_size = (uint32_t)size;
    if (_NSGetExecutablePath(buffer, &buffer_size) != 0) {
        fprintf(stderr, "Error: Path buffer too small.\n");
        exit(1);
    }
#else
    fprintf(stderr, "Error: Unsupported platform.\n");
    exit(1);
#endif
}

int main(int argc, char *argv[]) {
    char self_path[512];

    // Get the current executable's path
    get_self_path(self_path, sizeof(self_path));

    // Check if the executable is in the A-Text-Editor folder
    if (strstr(self_path, FOLDER_NAME) == NULL) {
        fprintf(stderr, "Error: The executable must be in the '%s' folder.\n", FOLDER_NAME);
        exit(1);
    }

    // Install this executable globally as 'ate'
    install_self(self_path);

    printf("Installation complete. You can now use the '%s' command globally!\n", COMMAND_NAME);
    return 0;
}