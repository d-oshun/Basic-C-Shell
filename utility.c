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

#include <string.h>    //the string library
#include <stdio.h>     //the standard in out library
#include <stdlib.h>    //the standard library
#include <unistd.h>    //provides functions to interact with the operating system
#include <sys/wait.h>  // Include header for waitpid
#include "myshell.h"   //connects the myshell.h file

//defining global values so that they can be used throughout the programme
#define MAX_BUFFER 1024
#define MAX_ARGS 64
#define SEPARATORS " \t\n"

//it parces the commands entered in the buffer
int parse_commands(char *buffer, char *args[], char **input_file, char **output_file, int *append) 
{
    //initialising variables
    int i = 0;
    char *item;
    char *pbuffer = buffer; //made a pointer to the buffer

    //checks the argument for special characters so that the program can remove and redirect to an 
    //input or output file
    while (*pbuffer != '\0') 
    {
        //checks if a less than bracket is prestent
        if (*pbuffer == '<') 
        {
            //If it is present then that means input redirection
            pbuffer++;
            //this skips any spaces present to help the shell run properly
            while (*pbuffer == ' ') 
            { 
                pbuffer++;
            }#
            //the input_file now points to the buffer command without the less than bracket
            *input_file = pbuffer;
        } 
        //checks if a more than bracket is prestent
        else if (*pbuffer == '>') 
        {
            //If it is present then that means output redirection
            pbuffer++;
            //if it shows up twice then that means its output redirection to a file that already exists
            //it would append to the end of the output file
            if (*pbuffer == '>') 
            {
                pbuffer++;
                *append = 1;
            }
            //skips the extra spaces that arent needed
            while (*pbuffer == ' ') 
            {
                pbuffer++;
            }
            //the output_file now points towards the command without the more than bracket(s)
            *output_file = pbuffer;
            break; //So that there is only one output redircetions
        } 
        else 
        {
            //moves the buffer pointer to point at the next item
            pbuffer++;
        }
    }

    //Gets the first argument 
    item = strtok(buffer, SEPARATORS);
    if (item == NULL) 
    {  
        //if the argument is empty it returns an empty line
        return -1;
    }

    //Puts the first item in an array
    args[i++] = item;
    //puts the rest of the items in the array
    while ((item = strtok(NULL, SEPARATORS)) != NULL) 
    {
        args[i++] = item;
    }

    //When the list reaches a value that is NULL it terminates
    args[i] = NULL;

    
    return 0; //exits the function correctly
}

//runs the commands that the user enters when the shell is running
int run_commands(char *args[], char *input_file, char *output_file, int append) 
{
    //intitailising the variables
    int i, j = 0;
    int in_background = 0; //to be able to travk what command is to run in the background

    //checks if an argument has been given
    if (args[0] == NULL) 
    {
        return 0; //If its empty just exit the function
    }

    //this records all the commands given and checks for the less than and more than brackets if a bracket 
    //is found it is skipped and whatever else was part of the argument is placed into the args[j] array
    //for the program to process
    for (i = 0; args[i] != NULL; i++) 
    {
        if (strcmp(args[i], "<") != 0 && strcmp(args[i], ">") != 0 && strcmp(args[i], ">>") != 0) 
        {
            args[j++] = args[i];
        }
    }
    args[j] = NULL; //If the args array is null it terminates it

    //Checks if the & symbol is present at the end of the first argument to that the program knows the 
    //command is to be run in the background
    if (args[0] != NULL && strlen(args[0]) > 1 && args[0][strlen(args[0]) - 1] == '&') 
    { 
        in_background = 1; //change the value so that the command can run in the background
        args[0][strlen(args[0]) - 1] = '\0'; //Gets rid of the & symbol at the end of the first argument
    }

    //Checks if a registered internal command has been enetered
    //checks for the cd commadand to change directories
    if (strcmp(args[0], "cd") == 0) 
    {
        change_dir(args[1]);//calls upon the change_dir function with an arguemnt if one is given
        return 0;//exits the function
    }
    //checks for the clr command to clear the screen
    else if (strcmp(args[0], "clr") == 0) 
    {
        screen_clear();//calls upon the scree_clear function
        return 0;//exits the function
    } 
    //checks if the dir command was entered to list the files in the directory
    else if (strcmp(args[0], "dir") == 0) 
    {
        //if no second argument is given it defaulst to the current directory
        if (args[1] == NULL) 
        {
            list_dir("."); //calls upon the list_dir function for the current
            //directory
        } 
        //if an argument was given it lists the items in that directory
        else 
        {
            list_dir(args[1]);//calls upon the list_dir function for that 
            //mentioned directory
        }
        return 0; //exits the function
    } 
    //checks if the environ command was entered to lis all the enviroment strings
    else if (strcmp(args[0], "environ") == 0) 
    {
        print_environ();//calls upon the print_environ function
        return 0;//exits the function
    }
    //checks if the echo command was entered to output the folling arguments on separate lines
    else if (strcmp(args[0], "echo") == 0) 
    {
        echo_args(args + 1); //Inputs the secon argument and up into the echo_args function
        return 0;//exits the function
    } 
    //checks if the help command was entered to output the user manual
    else if (strcmp(args[0], "help") == 0) 
    {
        help_user_manual();//calls upon the help_user_manual function
        return 0;//exist teh function
    }
    //checks if the pause command was entered to pause all programs running in the shell
    if (strcmp(args[0], "pause") == 0) 
    {
        //waits for th user to press the enter button befor the shell unpauses
        getchar(); //gets any characters enetered before the enter button is pressed
        return 0;//exist the function
    } 
    //checks if the fork command was entered to create a fork of the parent process
    else if (strcmp(args[0], "fork") == 0) 
    {
        make_fork(args + 1); //calls upon the make_fork function without the first argument
        return 0;//exits the function
    } 
    //checks if the exec command was enetered to give a different commadn to the child process
    else if (strcmp(args[0], "exec") == 0) 
    {
        run_exec(args + 1); //calls upon the run_exec function without the first arguemnt
        return 0;//exits the function
    }
    //checks if the quit command was entered to close the programme
    else if (strcmp(args[0], "quit") == 0) 
    {
        exit(0); //This terminates the programme
    }
    

    //The external command use system call with redirection
    pid_t child_process_id = fork();
    if (child_process_id == -1) 
    {
        //prints out an error message if the fork is unsuccsessful
        perror("fork");
        return -1;
    }

    //a child process is created 
    if (child_process_id == 0) 
    {
        //if the input file isnt empty redirect to the input file
        if (input_file != NULL) 
        {
            //starts the redirection to the the input_file
            if (freopen(input_file, "r", stdin) == NULL) 
            {   
                //error message if teh redirect is unsucsessful
                perror("freopen (stdin)");
                exit(1);
            }
        }
        //if the output file isnt empty redirect to the outputfile
        if (output_file != NULL) 
        {
            //initialising the pointer to append to the output file
            //a stands for append and w stands for overwrite
            char *pappend = (append) ? "a" : "w"; 
            //redirecting the output to append to the end of the output file
            if (freopen(output_file, pappend, stdout) == NULL) 
            {
                //prints out an error mesaage if the redirections fails
                perror("freopen (stdout)");
                exit(1);
            }
        }

        //checks if there was an error replacing the child process command
        if (execvp(args[0], args) == -1) 
        {
            //error message is output if it was a failure
            perror("execvp");
            exit(1); //exits the child process with an error due to it being unsucsessful
        }
    } 
    else 
    { 
        //checks if the value of the in_background variable has been changed
        //it it was changed to 1 that measn this command is meant to be processed in teh background
        if (in_background == 1) 
        {
            //message output so that it is known that the command is running in the background
            printf("[%d] Process has started in the background\n", child_process_id);

        } 
        //if background execution is enabled this code runs instead
        else 
        {
            
            //intitialising the variable
            int state;
            // Wait for the child process
            if (waitpid(child_process_id, &state, 0) == -1) 
            {
                //prints out error if the the wait fails
                perror("waitpid");
            }
        }
    }

    //Exits the function properly
    return 0;
}

//clears the screen
void screen_clear() 
{
    //uses an inbuilt system function to clear the screen
    system("clear");
}

//lists the files in the current directory
void list_dir(char *dir) 
{
    //when the user inputs dir it asks them to input a command like ls -l to output all of the files
    //in the directory, ls on its own can also be inputted
    printf("ls -l %s\n", dir);
}

//prints all of the enviroment strings
void print_environ() 
{
    //Gets access to the enviroment variables
    extern char **environ;

    //uses a for loop to output all of the enviroment strings on a separate line
    for (int i = 0; environ[i] != NULL; i++) 
    {
        printf("%s\n", environ[i]);
    }
}

//changes the directory and outputs the current directory
void change_dir(char *dir) 
{
    //initialise the current_dir variable
    char current_dir[MAX_BUFFER];

    //if no directory to change to was given by the user it prints out the current working directory
    if (dir == NULL) 
    {
        //Print out the current directory if no other agument was given but cd
        if ( getcwd(current_dir, sizeof(current_dir)) == NULL) 
        {   
            //print out an error messege if it cant get the current working directory and return
            perror("getcwd");
            return;
        }
        //the line to print out the current directory the user is in
        printf("This is the current directory: %s\n", current_dir);
        return; //return to the shell programme
    }
    // Update current working directory for prompt and environment
    if (getcwd(current_dir, sizeof(current_dir)) == NULL) 
    {
        //print out an error message if it cant get the current working directory and return
        perror("getcwd");
        return;
    }
    //Change the directory to the one specified by the user
    if (chdir(dir) != 0) 
    {   
        //output an error message if it cant change the directory or if the directory the user wants 
        //to change to doesnt exist and return
        perror("chdir");
        return;
    }
    //Updates the PWD enviroment variable to match with the curretn working directory
    setenv("PWD", current_dir, 1);
}

//echos info to the user where its one word per line
void echo_args(char *args[]) 
{
    //for every argument in the args list output them one line at a time until the list is empty
    for (int i = 0; args[i] != NULL; i++) 
    {
        printf("%s\n", args[i]); //prints out the current argument with a newline after it
    }
}

//outputs to the user the user help manual
void help_user_manual() 
{
    //outputs the infomation in the readme.md to the user using the more command
    system("more manual.txt");  
}

//forks the parent process to make a child process
int make_fork(char *args[])
{
    //inistialises the process_id as a pid_t variable
    pid_t process_id;

    //usimng the inbuilt function we assign the result of the form to the process_id variable
    process_id = fork();
    //it checks if the fork failed
    if (process_id == -1) 
    {
        //if it was unable to fork output an error message to the user
        perror("fork");
        return -1;
    }
    //if the process_id is 0 a child process is created
    else if (process_id == 0) 
    {
        //Child process prints out a message to the user so they know it has been created
        fprintf(stderr, "A Child process with Process ID (%d) has been created\n", getpid());
        exit(0); //The child process has been sucessfully created it exits the function successfully
    }
    //this just shows that a child process was created after the parent process 
    else 
    {
        //Parent process has a fork for the child process
        fprintf(stderr, "Made a fork for the child process with the Process ID (%d)\n", process_id);
        return 0; //shows that the fork was successful and exits the function
    }  
}

//changes the program running on the child process to another command
int run_exec(char *args[]) 
{
    //inistialises the process_id as a pid_t variable
    pid_t process_id;

    //usimng the inbuilt function we assign the result of the form to the process_id variable
    process_id = fork();

    //it checks if the fork failed
    if (process_id == -1) 
    {
        //if it was unable to fork output an error message to the user
        perror("fork");
        return -1;
    } 
    //if the process_id is 0 a child process is created
    else if (process_id == 0) 
    {
        //Checks if the child process was made
        if (execvp(args[0], args) == -1) 
        {
            //Error message is output to the if it was unable to create the child process
            perror("execvp");
            exit(1); //Exits the child process with an error
        }
    } 
    //this just shows that a child process was created after the parent process 
    else 
    {
        //The parent process waits for the child process to recieve a command 
        int state;
        if (waitpid(process_id, &state, 0) == -1) 
        {
            //error message is oytput to the user if the parent process is unable to wait for 
            //the child process even though it is necessary
            perror("waitpid");
        }

        return 0; //exits the function correctly, shows that the exec command was sucssesful
    }
    //exits the function correctly
    return 0;
}

//executes commands that are stored in a batchfile
void batch_mode(char *file_name) 
{
    //initialises a pointer to file_name and initialise buffer
    FILE *pfile_name;
    char buffer[MAX_BUFFER];

    //Make the point equal the information in the file_name
    pfile_name = fopen(file_name, "r"); //fopen opens the file

    //if the file is empty return
    if (pfile_name == NULL) 
    {
        perror("fopen");
        return;
    }

    //While there is still information in the file read the lines of commands and execute them
    while (fgets(buffer, MAX_BUFFER, pfile_name) != NULL) 
    {
        //initialise variable
        char *args[MAX_ARGS];

        //Remove any traling newline charcters if there are any
        buffer[strcspn(buffer, "\n")] = '\0';

        // Declare variables for redirection so that i can use the parce_commands 
        //and run_commands functions
        char *input_file = NULL;
        char *output_file = NULL;
        int append = 0;

        //Parce the current line in the batchfile file and run the commands
        if (parse_commands(buffer, args, &input_file, &output_file, &append) == -1) 
        {
            //print error message if parcing the ciommand in the bactchile isnt successful
            fprintf(stderr, "There was an error parsing the command in batch file\n");
            continue;
        }
        //calling upon the run_commands function to run the command
        run_commands(args, input_file, output_file, append);
    }

    // Closes the file_name 
    fclose(pfile_name);
}
