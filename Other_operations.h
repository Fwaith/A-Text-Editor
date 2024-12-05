#ifndef OTHER_OPERATIONS_H
#define OTHER_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <direct.h> // For _getcwd and _fullpath
#define getcwd _getcwd
#else
#include <unistd.h> // For getcwd and realpath
#include <limits.h> // For PATH_MAX
#endif

void change_log(const char *operation, const char *filePath, const char *details);

int number_of_lines(char arguments[]);

void listf();

void show_file(char arguments[]);

#endif