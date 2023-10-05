#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
    int pid = fork();

    if(pid < 0) {

        printf("fork error\n");
        exit(1);
    }

    else if(pid > 0) {

        int status;

        wait(&status);

        if(status == 0) {

            printf("OK\n");
        }
        else {
            printf("error\n");
        }
    }

    else {

        char *arg[MAXARG];

        for(int i = 0; i == (argc - 1); i++) {

            arg[i] = argv[i + 1]; 
        }

        arg[argc - 1] = 0;

        exec(argv[1], arg);
        printf("exec error\n");
    }

    exit(0);
}
