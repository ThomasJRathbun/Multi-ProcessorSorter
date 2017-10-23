#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>


typedef struct _procList
{
  pid_t pid_p;
  struct _procList *  next;
} procList;

procList * Proccess = NULL;

//is the PID already in the list?//
int procSearch( procList * head ,pid_t PID )
{
  printf("procSearch\n");
  procList * curr = head;
  if ( curr == NULL )
    {
      printf("procSearch NEW NODE\n");
      curr = (procList*)malloc(sizeof(procList));
      curr->pid_p = PID;
      curr->next  = NULL;
      return 1;
    }
  else if ( curr->pid_p == PID )
    {
      return PID; //found
    }
  else
    {
      curr = curr->next;
      procSearch(curr, PID);
    }
  return -1;//ERROR

}

void printProc( procList * head )
{
  procList * curr = head;
  while ( curr != NULL)
    {
      printf("PID: %d\n", curr->pid_p);
      curr = curr->next;
    }
  return;
}


int dirTraversal(char* filename)
{
  printf("PID: %d\n",  procSearch( Proccess, getpid()));
  printf( "starting DirTraversal\n");
  pid_t myPID = getpid();
  pid_t childPid = 0;
  DIR * base = opendir(filename);
  struct dirent * entry = readdir(base);
  char nextDir[1000] = "\0";
  printf( "Entering While\n");
  while( entry != NULL )
    {
      printf("Enterint While PID: %d\n", myPID);
      switch( (int)entry->d_type)
	{
	case 4:
	  memset( nextDir, '\0', 1000);
	  if ( strcmp( entry->d_name, ".\0")  != 0 &&
	       strcmp( entry->d_name, "..\0") != 0)
	    {
	      printf("PID: %d name: %s type: %d \n",myPID,entry->d_name,entry->d_type);
	      strcat( nextDir, filename);
	      strcat( nextDir, "/");
	      strcat( nextDir, entry->d_name);

	      childPid = fork();
	      if(childPid == 0)
		dirTraversal( nextDir);
	    }
	  break;
	case 8:
	  printf("PID: %d name: %s type: %d \n",myPID,entry->d_name,entry->d_type);
     	  break;
	}
      
      entry = readdir(base);
      
    }
  wait(&childPid);
  return 0;

}



int main( int argc, char ** argv )
{


  dirTraversal("nothing");
  printProc(Proccess);
  printf("printed\n");

  return 0;
}
