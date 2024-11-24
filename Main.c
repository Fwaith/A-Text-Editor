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
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

// GitHub repository link
#define GITHUB_REPO "https://github.com/Fwaith/A-Text-Editor"
#define GITHUB_ZIP_URL "https://github.com/Fwaith/A-Text-Editor/archive/refs/heads/main.zip"
#define INSTALL_DIR "/usr/local/bin/"
#define COMMAND_NAME "ate"
#define TMP_FOLDER "A-Text-Editor-tmp"

// Function to check if a command exists
int command_exists(const char *cmd) {
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "command -v %s >/dev/null 2>&1", cmd);
    return system(buffer) == 0;
}

// Function to download the latest release
void download_latest_release() {
    char command[512];
#ifdef _WIN32
    // Use PowerShell or curl to download on Windows
    snprintf(command, sizeof(command), "curl -L -o main.zip %s", GITHUB_ZIP_URL);
#else
    // Use curl to download the zip file
    snprintf(command, sizeof(command), "curl -L -o main.zip %s", GITHUB_ZIP_URL);
#endif

    printf("Downloading the latest release from %s...\n", GITHUB_REPO);
    if (system(command) != 0) {
        fprintf(stderr, "Error: Failed to download the latest release.\n");
        exit(1);
    }
}

// Function to extract the zip file
void extract_zip_file() {
#ifdef _WIN32
    // Use PowerShell to extract on Windows
    if (system("powershell -Command \"Expand-Archive -Path main.zip -DestinationPath .\"") != 0) {
        fprintf(stderr, "Error: Failed to extract main.zip on Windows.\n");
        exit(1);
    }
#else
    // Use unzip to extract on macOS/Linux
    if (system("unzip -o main.zip > /dev/null") != 0) {
        fprintf(stderr, "Error: Failed to extract main.zip on macOS/Linux.\n");
        exit(1);
    }
#endif
}

// Function to install the latest version
void install_latest_version() {
    char install_path[512];
    snprintf(install_path, sizeof(install_path), "%s%s", INSTALL_DIR, COMMAND_NAME);

#ifdef _WIN32
    // Copy the executable to C:\Windows
    if (system("copy A-Text-Editor-main\\Main.exe C:\\Windows\\ate.exe") != 0) {
        fprintf(stderr, "Error: Failed to install 'ate' on Windows. Try running as Administrator.\n");
        exit(1);
    }
#else
    // Move the executable to /usr/local/bin and make it executable
    if (system("cp A-Text-Editor-main/Main ./ate && chmod +x ./ate && mv ./ate /usr/local/bin/") != 0) {
        fprintf(stderr, "Error: Failed to install 'ate' on macOS/Linux. Try running with sudo.\n");
        exit(1);
    }
#endif

    printf("Successfully installed the latest version of 'ate'. You can now use it globally.\n");
}

// Function to check the current version
void check_and_update() {
    printf("Checking for an existing version of 'ate'...\n");

    // Check if 'ate' already exists
    if (command_exists(COMMAND_NAME)) {
        printf("'ate' is already installed. Updating to the latest version...\n");
    } else {
        printf("'ate' is not installed. Installing now...\n");
    }

    // Download the latest release
    download_latest_release();

    // Extract the downloaded zip file
    extract_zip_file();

    // Install the latest version
    install_latest_version();

    // Cleanup temporary files
    printf("Cleaning up temporary files...\n");
    system("rm -rf A-Text-Editor-main main.zip");
}

int main() {
    printf("Starting the installation process for 'A-Text-Editor'...\n");
    check_and_update();
    printf("Installation complete. You can now use 'ate' globally!\n");
    return 0;
}
