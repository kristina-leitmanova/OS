#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pipe1[2];
  pipe(pipe1);

  int pipe2[2];
  pipe(pipe2);

  int pid = fork();

  if(pid < 0) {
    printf("fork error\n");
    exit(1);
  }

  if(pid > 0) {
    close(pipe1[0]);
    close(pipe2[1]);
    
    int fd = pipe1[1];
    char buf [1];
    int n = 1;

    write(fd, buf, n);

    close(pipe1[1]);

    fd = pipe2[0];

    read(fd, buf, n);

    printf("%d: received pong\n", getpid());
  }

  else {
    close(pipe1[1]);
    close(pipe2[0]);

    int fd = pipe1[0];
    char buf [1];
    int n = 1;

    read(fd, buf, n);

    printf("%d: received ping\n", getpid());

    close(pipe1[0]);

    fd = pipe2[1];

    write(fd, buf, n);

    close(pipe2[1]);

    exit(0);
  }

  exit(0);
}