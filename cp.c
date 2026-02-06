#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_SIZE 1024

/*
    Recreate the cp command from scratch
    Need to accept commandline arguments
    Copy an input file(s) to an output destination
    only use syscalls: open, read, write
*/

int main(int argc, char** argv)
{
    printf("Copying file...\n");

    if (argc == 1)
    {
        printf("{%s}: missing file operand\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // ensure the argument count is correct
    if (argc == 2)
    {
        printf("{%s}: missing destination file operand after {%s}\n", argv[0], argv[1]);
        exit(EXIT_FAILURE);
    }

    int src_fd;
    char src_buffer[MAX_SIZE];

    // obtain the src file file descriptor, ensure it exists, this is done by open
    if ((src_fd = open(argv[1], O_RDONLY)) == -1)
    {
        fprintf(stderr, "File {%s} doesn't exist, ERROR: %s\n", argv[1], strerror(errno));    
        exit(EXIT_FAILURE);
    }

    printf("src_fd=%d\n", src_fd);

    // to copy the src file to a destination file, we must read the bytes of the src file and then write them to the destination file at dest_fd
    int dest_fd;

    if ((dest_fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
    {
        fprintf(stderr, "An error has occurred opening the dest file: {%s}, ERROR: %s\n", argv[2], strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("dest_fd=%d\n", dest_fd);
    
    // now we must write the src_buffer to the destination file
    ssize_t bytes_read;

    while ((bytes_read = read(src_fd, src_buffer, MAX_SIZE)) > 0)
    {
        if (write(dest_fd, src_buffer, bytes_read) != bytes_read)
        {
            fprintf(stderr, "An error has occured write to the src_buffer, ERROR: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    if (close(src_fd) == -1)
    {
        fprintf(stderr, "An error has occured closing the src file: {%s}, ERROR: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (close(dest_fd) == -1)
    {
        fprintf(stderr, "An error has occured closing the dest file: {%s}, ERROR: %s\n", argv[2], strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    printf("Copy successful\n");        

    return EXIT_SUCCESS;
}
