# My name is Diana Williams Oshun, my student number is 23101961. I acknowlege the DCU Academic 
# Integrity Policy

# Joe Citizen, s1234567 - Operating Systems Project 1
# ca216/myshell

# /* 
# strtokeg - skeleton shell using strtok to parse command line
# usage:
# strtokeg
# reads in a line of keyboard input at a time, parsing it into
# tokens that are separated by white spaces (set by #define SEPARATORS).
# can use redirected input if the first token is a recognised internal command, 
# then that command is executed. otherwise the tokens are printed on the display.
# internal commands:
# clear - clears the screen
# quit - exits from the program
# ********************************************************************
# version: 1.0
# date:    December 2003
# author:  Ian G Graham
# School of Information Technology
# Griffith University, Gold Coast
# ian.graham@griffith.edu.au
# copyright (c) Ian G Graham, 2003. All rights reserved.
# This code can be used for teaching purposes, but no warranty,
# explicit or implicit, is provided.
# *******************************************************************/

#When 'make myshell' is entered it retrieves the data from the 'myshell.c', 'utility.c' and 'myshell.h'
#files it then compiles it into a single myshell file which can then be run by typing in typing 
#./myshell
myshell: myshell.c utility.c myshell.h
	gcc -Wall myshell.c utility.c -o myshell
