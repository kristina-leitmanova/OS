#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int number = square(atoi(argv[1]));

  printf("%d\n", number);

  exit(0);
}