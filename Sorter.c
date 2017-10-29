#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mergesort.h"

int getHeader(node * head, char * headerTitle, int * numberOfHeaders)//take a head of list
{
  //  printf("[ENTERING][getHeader] \n");
  char * line;
  char * orig = NULL;
  int chosenHeader =0;
  bool found=FALSE;
  scanf("%ms", &line);
  
  //  printf("[getHeader]:gotline\n");
  
  orig = (char*) malloc( sizeof(char) * strlen(line)+1);
  memcpy( orig, line, strlen(line)+1);

  //  printf("[getHeader:Before While]:%s \n",line);
  //    printf("[getHeader:Before While]:headerTitle %s \n",headerTitle);
    while( line != NULL )
    {
      //      printf("[getHeader:Inside While]: first Print %s\n",line);      
      if(*numberOfHeaders ==0 )
	{
	  line = strtok( line, ",");
	}
      else
	{
	  line = strtok(NULL,",");
	}

      if ( line == NULL)
	{
	  //	  printf("[getHeader:Inside While]: BREAKING\n");
	  break;
	}
      
      if ( strcmp(headerTitle,line) == 0)
	{
	  chosenHeader = *numberOfHeaders;
	  found = TRUE;
	}
      //      printf("[getHeader:Inside While]: increment: %d\n",*numberOfHeaders);
      (*numberOfHeaders)++;
      
    }
    head->data = (char**)malloc(sizeof(char*) * *numberOfHeaders);
    int i;
    for (i =0; i < *numberOfHeaders; i++)
      {
	if( i == 0 )
	  orig = strtok(orig, ",");
	else
	  orig = strtok(NULL, ",");
	
	head->data[i] = (char*)malloc(sizeof(char) * strlen(orig)+1);
	head->data[i] = orig;
      }
  
  if ( found )
    return chosenHeader;
  else
    return -1;
}
/* ADDED FREE FUNCTION */
void freeLinkedList( struct _node* head){
  struct _node* cur = *head;
  struct _node* next;
  while( current != NULL){
    next = cur->next;
    free(cur);
    cur = next;
  }
  *head = NULL; 
}

int main(int argc, char *argv[])
 {
   //check flags
   int options;
   int cFlag =0;
   char * headerTitle = "deault_header";
   while( (options = getopt(argc, argv,"c:")) != -1 )
     {
       switch (options)
	 {
	 case 'c':
	   {
	     headerTitle = optarg;
	     cFlag = 1;
	     break; 
	   }
	 }
     }
 
     if ( cFlag == 0 )
     {
       printf("No -c option: Please try again with a header selected to sort by\n");
       return -1;
     }

    
     node * head = (node*)malloc(sizeof(node));
     head->next =NULL;
     int chosenColumn=0;
     int numOfHeaders=0;
     chosenColumn = getHeader(head, headerTitle, &numOfHeaders);

     node * data = (node*)malloc(sizeof(node));
     //     printf("[MAIN]:before Read\n");
     readData( data, numOfHeaders);

     //     head->next = data;
     //     printData( head, numOfHeaders);

     if(chosenColumn != -1)
       {
	 //	 printf("chosenColumn: %d\n",chosenColumn);
       }
     else
       {
	 //	 printf("header: %s does not exist\n",headerTitle);
	 return -1;
       }
     
     //     printf("[MAIN]:Before Merge\n");
     mergeSort( &data, chosenColumn ,checkString);
     head->next = data;
     //     printf("---***---\n");
     printData(head, numOfHeaders);
     freeLinkedList(head);
     return 0;
 }

     /*
     char * inputStr;
     char ** headers = NULL;
     char * secondRead = (char*) malloc(1000* sizeof(char));
     int numHeaders = 1;

     scanf( "%ms", &inputStr);
     memcpy( secondRead, inputStr, strlen(inputStr)+1);
     printf("%s \n",inputStr);

     char * test;
     test = strtok(inputStr,",");
     while (test != NULL)
       {
	 printf("input:%s\n %d\n",test,numHeaders);
	 test = strtok(NULL,",");
	 ++numHeaders;
       }
     printf("inputFile After initial read %s\n",inputStr);
     printf("inputFile After initial read %s\n",secondRead);
     headers = (char**)malloc(numHeaders *  sizeof(char*));
     int headerIndex = 0;
     for ( headerIndex; headerIndex < numHeaders-1; ++headerIndex)
       {
	 printf("headerIndex: %d\n",headerIndex);
	 headers[headerIndex] = (char*)malloc(100 * sizeof(char));

	 if ( headerIndex == 0 )
	   headers[headerIndex * 100] = strtok(secondRead,",");
	 else
	   headers[headerIndex * 100] = strtok(NULL,",");
	        
       }
     printf("secondread After initial read %s\n",secondRead);
     int i = 0;
     for( i; i < numHeaders-1; ++i)
       {
	 printf( "%d : %s\n",i,headers[i*(100)]);
       }

     return 0;
 }
*/
