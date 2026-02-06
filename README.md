# Implemented barebones cp command which copies the data of a src file to a dest file

- Developed on Linux, (Fedora 43)
- Implemented in C using only syscalls
- Copys the contents of {src_file} to {dest_file}
- To compile and run:
    1. Either run 'gcc -Wall -Werror -o cp cp.c'
    2. Or run 'make' to build using the Makefile

- To execute the program and utilize the functionality: run './cp ${src_file} ${dest_file}'

# Notes
- This is just a fun little mini project I decided to do to learn more about linux system calls and the process in how bytes are read, written and files are opened and handled using linux-kernel calls.
