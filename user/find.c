#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

int
find(char *path, char *fileName)
{
    struct stat st;
    int statStatus = stat(path, &st);

    if(statStatus == -1) {
        exit(1);
    }

    switch (st.type)
    {
    // name check
    case T_DEVICE:
    case T_FILE:
        if(strcmp(fmtname(path), fileName) == 32) 
        {
            printf("%s\n",path);
        }
        break;

    // search directory
    case T_DIR:
        int fd = open(path, O_RDONLY);
        struct dirent de;
        char buf [512];
        char *p;

        // set cursor to end of the fileName for direstory search/open
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';

        while(read(fd, &de, sizeof(de)) == sizeof(de)){

            // root check
            if(de.inum == 0)
                continue;
            
            // add name at the end of the path
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;

            if(strcmp(de.name, ".") == 0) 
                continue;
            
            if(strcmp(de.name, "..") == 0) 
                continue;

            find(buf, fileName);
        }
    }
    return 0;
}

int
main(int argc, char *argv[])
{
  find(argv[1], argv[2]);

  exit(0);
}