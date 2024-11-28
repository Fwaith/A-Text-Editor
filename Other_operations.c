#include "Other_operations.h"

void show_change_log() {
    
}

void number_of_lines(char arguments[]) {
    
}

void listf() {
#ifdef _WIN32
    system("dir");
#else
    system("ls");
#endif
}