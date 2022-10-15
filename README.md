# Pipe Up

This program replicates the pipe operator found in shells and allows users to pipe together the inputs and outputs of executables.

## Building

The program is built by entering the lab1 directory, which must contain pipe.c and the Makefile, and executing the command "make".

## Running

An example command would be "./pipe ls cat wc". The expected output would be the output from the command "ls | cat | wc", which should be three numbers representing the number of lines, words, and characters in the output of "ls".

## Cleaning up

The lab1 directory can be cleaned up by entering the lab1 directory and executing the command "make clean", which will remove all binary files.
