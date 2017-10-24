#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>

typedef struct _Proc
{
  pid_t pid;
  char  * file;
  struct _Proc * c_pid;
}proc;



/*
  
  procTree->pid = getpid()
  
  fork()


 */

int main( int argc, char** argv )
{

  return 0;

}
