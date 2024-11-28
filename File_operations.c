#include "File_operations.h"

void create_file(char arguments[]) {  
    FILE *file;
    file = fopen(arguments, "w"); 
    fclose(file);
}

void copy_file() { 
}

void delete_file() {
}

void show_file() { 
}