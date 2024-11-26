# A-Text-Editor

## Prerequisites
**Note: Not all of these are necessary, some are here purely for convenience.**
### A Package Manager
To make downloading easy. In this guide [git (not a package manager)](https://github.com/git-guides/install-git) is used.
### A C Language Compiler
To compile and run C. In this guide [gcc](https://gcc.gnu.org/install/) is used.
### Administrator Privileges
This is needed to add an executable to the system files so that the program can be run globally by entering the 'ate' command. If this is not done, the program can only be run from its directory, however, the 'ate' command that allows the program to run globally will not work. 

## Installation
### 1. Download the source files
The files can be downloaded directly

or

Clone the repo
```
git clone https://github.com/Fwaith/A-Text-Editor.git
```
### 2. Compile and run the code
In the terminal (administrator), go to the directory where the installed file is located and run the commands.
```
gcc -o ate *.c
```
```
./ate
```
### 3. Testing
In the terminal (any directory) enter.
```
ate
```
The program should launch without any errors.

If this error occurs,

```
ate: The term 'ate' is not recognized as a name of a cmdlet, function, script file, or executable program.
Check the spelling of the name, or if a path was included, verify that the path is correct and try again.
```

Then that means step 2 was done incorrectly.

## Deletion
