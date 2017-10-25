#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include "mergesort.h"

int dirTraversal(char* filename, char* headerTitle)
{
  pid_t myPID = getpid();
  pid_t childPid = 0;
  DIR * base = opendir(filename);
  struct dirent * entry = readdir(base);
  char nextDir[1000] = "\0";
  while( entry != NULL )
    {
      switch( (int)entry->d_type)
	{
	case 4:
	  memset( nextDir, '\0', 1000);
	  if ( strcmp( entry->d_name, ".\0")  != 0 &&
	       strcmp( entry->d_name, "..\0") != 0)
	    {
	      strcat( nextDir, filename);
	      strcat( nextDir, "/");
	      strcat( nextDir, entry->d_name);

	      childPid = fork();
	      if(childPid == 0)
		{
		  _exit(dirTraversal( nextDir, headerTitle));

		}
	      printf("PID: %d child:%d  file: %s\n",myPID,childPid, entry->d_name);

	    }
	  break;
	case 8:
	  
	    childPid = fork();
	    if( childPid == 0)
	      {
		node* head = (node*)malloc(sizeof(node));
		head->next = NULL;
		node* rows = (node*)malloc(sizeof(node));
		int numberOfHeaders = 0;
		int chosenField =0;
				
		strcat( nextDir, filename);
		strcat( nextDir, "/");
		strcat( nextDir, entry->d_name);
		char * extention = (char*)malloc(sizeof(char)*5);
		extention[4] = '\0';
		int i =0;
		int c =3;
		for ( i = sizeof(nextDir); i > 0; i--)
		  {
		    if ( nextDir[i] == '\0')
		      continue;
		    else
		      {
			extention[c] = nextDir[i];
			c--;
		      }
		    if ( c < 0)
		      break;
		  }
		
		printf("File: %s Extention:%s\n",nextDir,extention);
		if ( strcmp(extention,".csv") != 0 )
		  {
		    printf("File is not correct\n");
		    _exit(-4);
		  }
		chosenField = getHeader(head, headerTitle, &numberOfHeaders,filename);
		if ( numberOfHeaders > 27)
		  {
		    _exit(-2);//File not compatible
		  }

		readData( rows, numberOfHeaders, nextDir);
		mergeSort(&rows, chosenField, checkString); 
		head->next = rows;
		printData(head,numberOfHeaders);

		}
	    break;
	}
    
      entry = readdir(base);
    }  
  return 0;

}

int main( int argc, char ** argv )
{

  dirTraversal("nothing", "movie_title");

  return 0;
}
