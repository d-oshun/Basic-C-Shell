/*My name is Diana Williams Oshun, my student number is 23101961. I acknowlege the DCU Academic 
Integrity Policy*/

/* 
strtokeg - skeleton shell using strtok to parse command line
usage:
strtokeg
reads in a line of keyboard input at a time, parsing it into
tokens that are separated by white spaces (set by #define SEPARATORS).
can use redirected input if the first token is a recognised internal command, 
then that command is executed. otherwise the tokens are printed on the display.
internal commands:
clear - clears the screen
quit - exits from the program
********************************************************************
version: 1.0
date:    December 2003
author:  Ian G Graham
School of Information Technology
Griffith University, Gold Coast
ian.graham@griffith.edu.au
copyright (c) Ian G Graham, 2003. All rights reserved.
This code can be used for teaching purposes, but no warranty,
explicit or implicit, is provided.
*******************************************************************/     

// Function prototypes

//it parces the commands entered in the buffer
int parse_commands(char *buffer, char *args[], char **input_file, char **output_file, int *append);
//runns the commands that the user enters when the shell is running
int run_commands(char *args[], char *input_file, char *output_file, int append);
//clears the screen
void screen_clear();
//lists the files in the current directory
void list_dir(char *dir);
//prints all of the enviroment strings
void print_environ();
//changes the directory and outputs the current directory
void change_dir(char *dir);
//echos info to the user where its one word per line
void echo_args(char *args[]);
//outputs to the user the user help manual
void help_user_manual();
//forks the parent process to make a child process
int make_fork(char *args[]);
//changes the program running on the child process to another command
int run_exec(char *args[]);
//executes commands that are stored in a batchfile
void batch_mode(char *file_name); 