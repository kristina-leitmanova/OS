#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
writeFile(char *path, char *message) {

    int file = open(path, O_WRONLY | O_CREATE);

        if(file < 0) {
            return -1;
        }

        int character = 0;
        char buf[1];
        int n = 1;

        while (message[character] != '\0') {

            buf[0] = message[character];

            write(file, buf, n);

            character++;
        }

        close(file);
        return 0;
}

int
main(int argc, char *argv[])
{
    char *message = argv[3];

    int pid = fork();

    if(pid == 0) {

        writeFile(argv[1], message);
    }

    else if(pid > 0) {

        writeFile(argv[2], message);
    }

    exit(0);
}
