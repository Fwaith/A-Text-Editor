#include "Other_operations.h"

void show_change_log() {
    
}

void show_number_of_lines() {
    
}

void listf() {
#ifdef _WIN32
    system("dir");
#else
    system("ls");
#endif
}