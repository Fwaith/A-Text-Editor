#ifndef OTHER_OPERATIONS_H
#define OTHER_OPERATIONS_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#ifdef _WIN32
#include <direct.h> // For _getcwd
#define getcwd _getcwd
#else
#include <unistd.h> // For getcwd
#endif

void change_log(const char *operation, const char *filePath, const char *details);

int number_of_lines(char arguments[]);

void listf();

#endif