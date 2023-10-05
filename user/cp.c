#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

#define BUFFER_SIZE 512

int
main(int argc, char *argv[]) {

    if (argc != 3)
    {
        fprintf(2, "Usage: cp <SOURCE> <DESTINATION>");
        exit(1);
    }

    int fd_src, fd_dest;

    fd_src = open(argv[1], O_RDONLY);
    fd_dest = open(argv[2], O_WRONLY | O_CREATE);

    if (fd_src < 0 || fd_dest < 0)
    {
        fprintf(2, "cp: cannot open");
        exit(1);
    }

    char buf[BUFFER_SIZE];
    int n = BUFFER_SIZE;

    while(read(fd_src, buf, n) != 0) {

        write(fd_dest, buf, n);
    }

    close(fd_src);
    close(fd_dest);

    exit(0);
}