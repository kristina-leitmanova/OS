#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
  for(;;) {

    int nextArgc = 0;
    char nextArgv[MAXARG][MAXARG];

    int argLength = 0;

    int fd = 0;
    char buf[1];
    int n = 1;

    // loop for reading characters
    while ( (read(fd, buf, n) > 0 ) && (buf[0] != '\n') )
    {

        if (buf[0] == ' ')
        {
            argLength = 0;
            nextArgc++;
            continue;
        }
        
        nextArgv[nextArgc][argLength] = buf[0];
        argLength++;
    }

    if (argLength != 0)
    {
        nextArgc++;
    }

    if(nextArgc == 0) 
    {
        break;
    }

    int pid = fork();

    if (pid < 0)
    {
        exit(1);
    }
    
    else if (pid > 0)
    {
        pid = wait(0);
    }

    else 
    {
        char *newArgv[MAXARG];
        int newArgc;
        
        for (newArgc = 0; newArgc < (argc - 1); newArgc++)
        {
            newArgv[newArgc] = argv[newArgc + 1];
        }

        for (int i = 0; i < nextArgc; i++)
        {
            newArgv[newArgc] = nextArgv[i];
            newArgc++;
        }
        
        newArgv[newArgc] = 0;

        exec(newArgv[0], newArgv);
    }   
  }

  exit(0);
}