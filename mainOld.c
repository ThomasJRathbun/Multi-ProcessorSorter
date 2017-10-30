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
  int childStatus[255];
  pid_t childProcess[255];
  int processCounter = 0;
  pid_t myPID = getpid();

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

	      childProcess[processCounter] = fork();

	      if( childProcess[processCounter] == 0)
		{
		  _exit(dirTraversal( nextDir, headerTitle));

		}
	      printf("PID: %d child:%d  file: %s\n",myPID,childProcess[processCounter], entry->d_name);
	      processCounter++;
	    }
	  break;
	case 8:
	  
	  childProcess[processCounter] = fork();
	   
	  if( childProcess[processCounter] == 0)
	    {
	      myPID = getpid();
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
		
	      FILE * unSorted = fopen(nextDir,"r");
	      printf("PID: %d finding Field: %s\n",myPID,headerTitle);
	      chosenField = getHeader(head, headerTitle, &numberOfHeaders,&unSorted);
	      printf("Field:%d NumberOf Fields:%d\n",chosenField,numberOfHeaders);
	      if ( numberOfHeaders != 28)
		{
		  printf("PID: % number of headers wrong\n",myPID);
		  _exit(-2);//File not compatible
		}
	      printf("readingData\n");
	      readData( rows, numberOfHeaders, chosenField, &unSorted);
	      mergeSort(&rows, chosenField, checkString); 
	      head->next = rows;
	      FILE * sorted = fopen("./Sorted.csv","w");
	      printData(head,numberOfHeaders,&sorted);
	      freeNode(head);
	      _exit(1);
	    }
	  break;
	    
	}
      processCounter++;


      entry = readdir(base);
    }
  /*  int k = 0;
  for (k=0; k<processCounter; k++)
    {
      printf("Process ID:%d Child ID: %d, Filename: %s\n",myPID,childProcess[k], filename);
    }
  */
  waitpid(-1,NULL,0);


  return 0;

}

int main( int argc, char ** argv )
{

  dirTraversal("nothing", "movie_title");

  return 0;
}
