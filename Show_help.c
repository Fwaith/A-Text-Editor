#include "Show_help.h"

void show_help() {
    printf("-------------------------\n");
    printf("| Full list of commands |\n");
    printf("-------------------------\n");
    printf("\nTo enter a command, type ate <command>.\n");
    printf("\tExample: ate help\n");
    printf("\nate (by itself) - Opens the editor\n");
    printf("exit - Exits and ends the current running instance of the editor\n");
    printf("help - Displays all the commands along with its description\n");
    printf("uninstall - Uninstalls the program and removes any directories made from the installation of the software\n");
}