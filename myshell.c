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

//the main function of myshell programme
int main(int argc, char *argv[]) 
{
    //initialising variables for my programme to use
    char buffer[MAX_BUFFER];
    char *args[MAX_ARGS];
    char *prompt = "(;-;)==>"; //prompt so that the user knows it can input a command

    //If there is more than one argument that means that there is a batchfile includes
    if (argc > 1) 
    {
        //calls upon the batch_mode function to process the commands given in the batchfile
        batch_mode(argv[1]);
    }
    //if there is one or less arguments it prompts the user to input a command 
    else 
    { 
        while (1) 
        {
            //Outputs the prompt to the user
            fputs(prompt, stdout);

            //Removes any trailing newline charaters at the end of arguments 
            buffer[strcspn(buffer, "\n")] = '\0';

            //initialises variables incase i/o redirection needs to be implemented
            char *input_file = NULL;
            char *output_file = NULL;
            int append = 0; // Default to overwrite

            //Reads the input to check if its empty
            if (fgets(buffer, MAX_BUFFER, stdin) == NULL) 
            {
                //if the argument is empty the programme exits
                break;
            }

            //parces the command given by the user and checks if there was an error parcing
            if (parse_commands(buffer, args, &input_file, &output_file, &append) == -1) 
            {   
                //outputs this line if there was an error parcing the command
                fprintf(stderr, "There was an error parsing the command\n");
                continue;
            }

            //execued the command and has measures in place incase i need to use redirection
            if (run_commands(args, input_file, output_file, append) == -1) 
            {
                //outputs this line if there was an error executing a command
                fprintf(stderr, "There was an error executing the command\n");
                continue;
            }

        }
    }
    //returns 0 to properly exit the programme
    return 0;
}
