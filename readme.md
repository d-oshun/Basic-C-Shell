NAME & AUTHOR

    Shell name : myshell 
    Author Name: Diana Williams Oshun
DESCRIPTION

    I made a basic command-line shell written in C called 'myshell'. The shell supports interanl and external commands, i/o redirection, bacground execution, batchfile execution ect.
START

    1. Make sure you are in the same folder as myshell.c, utility.c and myshell.h files.
    2. Run the command 'make myshell' to compile the shell.
    3. Run the command './myshell' to run the shell.
COMMANDS

    A Unix command is an instruction that is typed into the terminal of the myshell programme.
    ```
    HELP
        DESCRIPTION
            This outputs a user manual for the user to better understand how to use and navigate through the commands built in the shell.
        EXECUTION
            help
    CD
        DESCRIPTION
            This changes the directory of the user to the specified directory or if no directory has been specified the command will output the current working directory.
        EXECUTION
            cd <arg1>
                or
            cd
    CLR
        DESCRIPTION
            This clears any previous commands and outputs from the screen.
        EXECUTION
            clr
    DIR
        DESCRIPTION
            This list all the files in the specified directory or if no directory is specified it lists all the files in the current working directory.
        EXECUTION
            dir <arg1>
                or
            ls
                or
            ls -l
    ENVIRON
        DESCRIPTION
            This outputs all of the environment strings to the user.
        EXECUTION
            environ
    ECHO
        DESCRIPTION
            This outputs the arguments following the command on a seperate line, regardless of tabs and extra spaces.
        EXECUTION
            echo <arg1> <arg2> ... <argn-1>
    PAUSE
        DESCRIPTION
            This pauses all function and running commands on the shell until the enter button has been pressed.
        EXECUTION
            pause
    FORK
        DESCRIPTION
            This creates a fork of the parent process resulting in a child process.
        EXECUTION
            fork
    EXEC
        DESCRIPTION
            This runs a command on the child independant to the parent process.
        EXECUTION
            exec <command>
                or
            exec
    QUIT
        DESCRIPTION
            This exits the shell programme.
        EXECUTION
            quit

    ```
ENVIRONMENT CONCEPTS

    In my shell, Environment concepts refer to the environment variables that are usually set by the OS/Shell already. The string values are composed by 'name=/value' . The 'environ' command can be run to output all the environment strings to the user.
    ```
        ENVIRON
        EXECUTION
            environ

    ```

    
I/O REDIRECTION

    In  my shell, I/O redirection refers to input and output redirection.
    INPUT REDIRECTION (<)
        DESCRIPTION
            Input redirection instructs myshell to take input for a command from a file instead of the keyboard. Input redirection uses the '<' symbol as an indicator that it's input redirection from a file.
        EXECUTION
            ```
            ./myshell <arg1> <arg2> < 'input_file'
                or
            ./myshell <arg1> < 'input_file'
            ```
    OUTPUT REDIRECTION (> and >>)
        DESCRIPTION
             Output redirection instructs myshell to send the output of a command to a file instead of displaying it the terminal. Output redirection uses the '>' symbol if the output file hasn't been created yet or to overwrite the information already in the file and the '>>' symbol to append the output to the end of an already existing file.
        EXECUTION
            ```
            ./myshell <arg1> <arg2> > 'output_file'
                or
            ./myshell <arg1> > 'output_file'
                or
            ./myshell <arg1> <arg2> >> 'output_file'
                or
            ./myshell <arg1> >> 'output_file'
            ```
    INPUT AND OUTPUT REDIRCECTION
        DESCRIPTION
            You can use both input and output redirection simultaneously to redirect input from a file and send the output to another file.
        EXECUTION
            ```
            ./myshell <arg1> <arg2> < 'input_file' > 'output_file' 
                or
            ./myshell <arg1> < 'input_file' > 'output_file'
                or
            ./myshell <arg1> <arg2> < 'input_file' >> 'output_file'
                or
            ./myshell <arg1> < 'input_file' >> 'output_file'
            ```
PROCESS CONCEPT

    In my shell, there are two differnt ways a command can be run that is either in the foreground or background.
    FOREGROUND
        DESCRIPTION
            This is when the command is running in the terminal like usual. The shell will wait for the command to finish before a new command can be run.
        EXECUTION
            ```
            <command> <args>
                or
            <command>
            ```
    BACKGROUND
        DESCRIPTION
            This is when the command is run in the background of the shell. After the command is entered the command prompt shows up immediately. Following this, the command runs in the background. My shell knows that the command is meant ot be run in the background when the end of the command has an "&" symbol after it.
        EXECUTION
            ```
            <command>& <args>
                or
            <command>&
            ```
BATCHFILE MODE

    DESCRIPTION
        In my shell, Batchfile mode consists of a batchfile that can be a ".txt" or ".sh" where pre-written commands are. The shell will take the commands from the batch file and run them all sequentially.
    EXECUTION
        ```
        ./myshell batchfile.txt
            or
        ./myshell batchfile.sh
        ```
REFERENCES

    These are the references that I used to create my shell:
    1. Silberschatz, Abraham, et al. Operating System Concepts: Essentials. John Wiley & Sons, Incorporated, 2018.
    2. Bach, Maurice J. The Design of the UNIX Operating System. Pearson Education, 2016.
    3. Robbins, Kenneth A., and Michael M. Dieter. UNIX Systems Programming: Communication, Interprocess Synchronization, and Dynamic Memory Allocation. Pearson Education Limited, 2012.
    4. Stevens, W. Richard. Advanced Programming in the Unix Environment, Third Edition. Addison-Wesley Professional, 2013.
    5. Arpaci-Dusseau, Remzi H., and Andrea C. Arpaci-Dusseau. Operating Systems: Three Easy Pieces. Arpaci-Dusseau Books, 2014.
    6. McKusick, Michael K., et al. The Design and Implementation of the 4.4BSD Operating System. Addison-Wesley Longman Publishing Co.,        Incorporated, 1996.


<!-- My name is Diana Williams Oshun, my student number is 23101961. I acknowlege the DCU Academic 
Integrity Policy -->

