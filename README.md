# A-Text-Editor

## Prerequisites
**Note: Not all of these are necessary, some are here purely for convenience.**

**Note: The program was not able to be tested on macOS so there is no guarantee that it will run smoothly. For the best experience, use Windows.**
### A Package Manager
To make downloading easy. In this guide [git (not a package manager)](https://github.com/git-guides/install-git) is used.
### A C Language Compiler
To compile and run C. In this guide [gcc](https://gcc.gnu.org/install/) is used.
### Administrator Privileges
This is needed to add an executable to the system files so that the program can be run globally by entering the 'ate' command. If this is not done, the program can only be run from its directory, however, the 'ate' command that allows the program to run globally will be created.

## Installation
### 1. Download the source files
The files can be downloaded directly

or

Clone the repo
```
git clone https://github.com/Fwaith/A-Text-Editor.git
```
### 2. Compile and run the code
In the terminal (administrator), go to the directory where the installed file is located and then run the commands.
```
cd A-Text-Editor
```
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

If the program runs without any issues but there are errors, simply ignore the errors

## Deletion

### 1. Delete the executable
On Windows: C:\\Windows\\ate.exe

On macOS: /usr/local/bin/ate
### 2. Delete the source files
Wherever you downloaded it

## Operations

ate (by itself) - Opens the editor

append <file name> - Specifies the file to append a line to

create <file name> - Creates a single file given that it doesn't already exist

copy <file name> - Creates a copy of a file

delete <file name> - Deletes the specified file

exit - Exits and ends the current running instance of the editor

help - Displays all the commands along with its description

insert <file name> - Specifies the file to insert a line of text

lndelete <file name> - Specifies the file to delete a particular line of text

lnshow <file name> - Specifies the file to show a particular line of text

log - Shows the change log; the actions performed by the editor in chronological order

show - Shows the contents of a file along with the line numbers

shownl - Shows the number of lines in a specified file

## Additional Operations
listf - Lists all files in the current directory along with other relevant information

search <file name> - Specifies the file to search for a string
