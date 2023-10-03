#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pipe1[2];
  pipe(pipe1);

  int pid = fork();

  if (pid < 0)
  {
    exit(1);
  }

  else if (pid > 0) 
  {
    close(pipe1[0]);

    for (int i = 2; i < 36; i++)
    {
        write(pipe1[1], &i, sizeof(int));
    }

    close(pipe1[1]);
    wait(0);
  }

  else 
  {
    close(pipe1[1]);

    int primeNumber = 0;
    int number = 0;

    int pipe2[2];

    while (read(pipe1[0], &primeNumber, sizeof(int)))
    {
        printf("prime %d\n", primeNumber);

        // read from left until pipe is empty
        while (read(pipe1[0], &number, sizeof(int))) {

            if ((number % primeNumber) != 0)
            {
                if (pid == 0) {

                    pipe(pipe2);
                    pid = fork();

                    if (pid < 0)
                    {
                        exit(1);
                    }
                    
                    else if(pid > 0) 
                    {
                        close(pipe2[0]);
                    }

                    else {
                        close(pipe2[1]);
                        pipe1[0] = pipe2[0];
                        break;
                    }
                }

                write(pipe2[1], &number, sizeof(int));
            }
        }
    }
    close(pipe1[0]);
    close(pipe2[1]);

    wait(0);
  }

  exit(0);
}