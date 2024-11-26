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
#define INSTALL_PATH "C:\\Windows\\ate.exe"
#else
#include <sys/stat.h>
#define INSTALL_PATH "/usr/local/bin/ate"
#endif

#ifdef _WIN32
    // Copy the executable to C:\Windows
    snprintf(command, sizeof(command), "copy \"%s\" \"%s\"", INSTALL_PATH);
    if (system(command) == 0) {
        printf("Successfully installed 'ate' command. You can now use it globally.\n");
    }
    else {
        printf("Error: Failed to install 'ate'. Try running as Administrator.\n");
    }
#else
    // Move the executable to /usr/local/bin
    snprintf(command, sizeof(command), "sudo mv \"%s\" \"%s\"", INSTALL_PATH);
    if (system(command) == 0) {
        printf("Successfully installed 'ate' command. You can now use it globally.\n");
    }
    else {
        printf("Error: Failed to install 'ate'. Try running with sudo.\n");
    }
#endif

int main() {
    char input[100];  // Buffer to store user input
    int running = 0;  // Control variable for the loop

    printf("Welcome to the A-Text-Editor Command-Line Editor\n");
    printf("Type 'ate help' for a full list of commands.\n");

    while (running == 0) {
        fgets(input ,sizeof(input) ,stdin);     
        if (strcmp(input, "ate exit")==0) {
            running = 1;
        } 
        else if (strcmp(input, "ate help")==0) {
            show_help();
        } 
        else {

        }
    }
    return 0;
}