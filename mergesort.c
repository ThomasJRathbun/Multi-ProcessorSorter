#include "mergesort.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int getHeader(node * head, char * headerTitle, int * numberOfHeaders, char * filename)
{
  FILE * file = fopen( filename, "r");
  char * line;
  char * orig = NULL;
  int chosenHeader =0;
  bool found=FALSE;
  fscanf(file,"%ms", &line);

  orig = (char*) malloc( sizeof(char) * strlen(line)+1);
  memcpy( orig, line, strlen(line)+1);
    while( line != NULL )
    {
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
	  break;
	}

      if ( strcmp(headerTitle,line) == 0)
	{
	  chosenHeader = *numberOfHeaders;
	  found = TRUE;
	}
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

int checkString( char* arg1, char* arg2 )
{
  int i = 0;
  for( i=0; i < strlen(arg1);i++)
    {
      arg1[i] = tolower( arg1[i]);
    }
  for( i=0; i < strlen(arg2);i++)
    {
      arg2[i] = tolower( arg2[i]);
    }
  i = 0;
  int j =0;
  char* c1;
  char* c2;
  while( i < strlen(arg1) || j < strlen(arg2) )
    {
      while(isspace(arg1[i]) || arg1[i] == '\"')
	{
	  i++;
	  if( i > strlen(arg1))
	    break;
	}
      while(isspace(arg2[j]) || arg2[j] == '\"')
	{
	  if( j > strlen(arg2))
	    break;
	  j++;
	}
      c1 = arg1[i];
      c2 = arg2[j];
      if(c1 == c2)
	{
	  i++;
	  j++;
	  continue;
	}
      else if( (int)c1 < (int)c2)
	{
	  return -1;
	}
      else
	{
	  return 1;
	}
      i++;
      j++;
    }
  return 0;
}

void readData( node * head, int _numHeaders, char* filename )
{
  char* line = NULL;
  size_t size;
  node * newNode = head;
  FILE* file = fopen(filename, "r");
  
  
  while( getline(&line, &size,file) != -1)
    {
      char * s = line;
      bool onlySpaces = FALSE;
      while( *s != '\0')
	{
	  if ( !isspace(*s))
	    break;
	  else
	    {
	      s++;
	    }
	  onlySpaces =TRUE;
	}
      if( onlySpaces)
	{
	  continue;
	}


      if (line == "")
	{
	  line = NULL;
	  continue;
	}
      if ( newNode->next == NULL && newNode->data == NULL )
	{
	  newNode->data = (char**)malloc(sizeof(char*) * _numHeaders);
	  newNode->next = NULL;
	}
      else
	{
	  while ( newNode->next != NULL )
	    {
	      node * prev = newNode;
	      newNode = newNode->next;
	      prev->next = newNode;
	    }
	  newNode->next = (node*)malloc(sizeof(node));
	  node * prev = newNode;
	  newNode = newNode->next;
	  prev->next = newNode;
	}

      newNode->data = (char**)malloc(sizeof(char*) * _numHeaders);
      newNode->next = NULL;

      int i = 0;
      char *tok = line;
      char *end = line;
      for (i=0; i<_numHeaders; i++)
	{
	  tok = strsep(&end, ",");
	  newNode->data[i] = (char*)malloc(sizeof(char) * strlen(line)+1);
	  newNode->data[i] = tok;

	}

      line = NULL;
    }
}


void printData( node * head, int _numHeaders)
{
  node * curr = head;
  int i = 0;
  int l = 0;
  while( curr != NULL)
    {
      for (i = 0 ; i< _numHeaders; i++)
	{ 
	  for ( l = 0; l < sizeof(curr->data[i]); l++)
	    {
	      if( curr->data[i][l] == '\n')
		{
		  curr->data[i][l] = '\0';
		}
	    }
	  if ( (_numHeaders - i) == 1)
	    {	     
	      printf("%s",curr->data[i]);
	    }
	  else
	    {
	      printf("%s,",curr->data[i]);
	    }
	}
      printf("\n");
      curr = curr->next;
    }

  return;
}


node* merge(node * leftList, node* rightList,int index, int (*comp)(void*,void*))
{
  if ( leftList == NULL)
    {
      return rightList;
    }
  if ( rightList == NULL)
    {
      return leftList;
    }
  node * result = NULL;

  if( (*comp)(strcat(leftList->data[index],"\0"),strcat(rightList->data[index],"\0")) <= 0)
      {
	result = leftList;
	result->next = merge(leftList->next,rightList,index,comp);
      }
      else
	{
	  result = rightList;
	  result->next = merge(leftList,rightList->next,index,comp);
      	}

      return result;
}

void subDivide( node * head, node** left, node** right )
{
  node * fast = head->next;
  node * slow = head;
  if ( head == NULL || head->next == NULL)
    {
      *left  = head;
      *right = NULL;
    }
  else
    {

      while( fast != NULL)
	{
	  fast = fast->next;
	  if ( fast != NULL )
	    {
	      fast = fast->next;
	      slow = slow->next;
	    }
	}
      *left  = head;
      *right = slow->next;
      slow->next = NULL;
    }
}

void mergeSort( node ** head, int index,  int (*comp)(void*,void*))
{
  node * left    = NULL;
  node * right   = NULL;
  node * result  = *head;
  if ( result == NULL || result->next == NULL)
    {
      return;
    }
    subDivide( result, &left, &right );
    mergeSort(&left, index, comp);
    mergeSort(&right, index, comp);

  *head = merge(left,right,index, comp);
}
