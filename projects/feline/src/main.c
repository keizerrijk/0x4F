#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main (int argc, char* argv[]) {
    if (argc < 1) {
        printf("ERROR: Feline requires one argument.\n");
        return 1;
    }

    char buf[BUF_SIZE];

    int numRead;
    int fd = open(argv[1], O_RDONLY);

    if (fd) {
        while((numRead = read(fd, buf, BUF_SIZE)) != EOF)
            if (write(STDOUT_FILENO, buf, BUF_SIZE) != 0)
                return 1;
        return 0;
    } else {
        printf("ERROR: unable to open file for reading");
        return 1;
    }
}
