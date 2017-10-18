#include "mergesort.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
      //      printf("[checkstring]str1:%s str2:%s\n:",arg1,arg2);
      while(isspace(arg1[i]) || arg1[i] == '\"')
	{
	  //	  printf("[checkstring]Space1\n:");
	  i++;
	  if( i > strlen(arg1))
	    break;
	}
      while(isspace(arg2[j]) || arg2[j] == '\"')
	{
	  //	  printf("[checkstring]Space2\n:");
	  if( j > strlen(arg2))
	    break;
	  j++;
	}
      //      printf("[checkstring]BeforeChar\n");
      //      printf("[checkstring]c1:%c c2:%c\n",arg1[i],arg2[j]);
      c1 = arg1[i];
      c2 = arg2[j];
      //      printf("[checkstring]AfterChar c1:%c c2:%c\n ",c1,c2);
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

//Read in data and insert nodes into Linked List
void readData( node * head, int _numHeaders )
{
  //  printf("[readData]:Entered\n");
  char* line = NULL;
  size_t size;
  node * newNode = head;
  //  printf("[readData]:Initialized\n");
  //  while ( scanf("%ms", &line ) != EOF )
  while( getline(&line, &size,stdin) != -1)
    {
      //      printf("[READDATA]::line:\n%s\n",line);
      //      printf("[readData]:Scanned\n");

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
	  //  printf("[READDATA]::lineEMPTY:\n%s\n",line);
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


      //      printf(" NUMBER OF HEADERS: %d\n", _numHeaders);


      int i = 0;
      char *tok = line;
      char *end = line;
      for (i=0; i<_numHeaders; i++)
	{
	  /*
	  printf(" NUMBER OF HEADERS: %d\n", _numHeaders);
	  printf("i:%d\n",i);
	  if( i == 0)
	    {
	      printf("[READDATA]:First Run\n");
	      line = strtok( &line, ",");
	    }
	  else
	    {
	      printf("[READDATA]:Second run\n");
	      line = strsep( &line, ",");
	    }
	  //	  if ( line == "" || line == NULL )
	  //	    {
	  //	      newNode->data[i] = "";
	  //	      continue;
	  }*/
	  tok = strsep(&end, ",");
	  
	  //  printf("line : %s\n",tok);
	  newNode->data[i] = (char*)malloc(sizeof(char) * strlen(line)+1);
	  newNode->data[i] = tok;
	  //	  printf("[readData]:data at node[%d]= %s\n",i,newNode->data[i]);
	}
      
      line = NULL;
    }
}


void printData( node * head, int _numHeaders)
{
  //  printf("[PRINTDATA]:Entering\n");
  node * curr = head;
  int i = 0;
  while( curr != NULL)
    {
      for (i = 0 ; i< _numHeaders; i++)
	{
	  if ( (_numHeaders - i) == 1)
	    printf("%s",curr->data[i]);
	  else
	    printf("%s,",curr->data[i]);
	}
      printf("\n");  
      curr = curr->next;
    }

  return;
}


node* merge(node * leftList, node* rightList,int index, int (*comp)(void*,void*))
{
  //  printf( "[merge]:ENTERING \n");
  //  printf("[merge]:Is left or right NULL\n");
  if ( leftList == NULL)
    {
      //      printf("[merge]:Left NULL return Right\n");
      return rightList;
    }
  if ( rightList == NULL)
    {
      //      printf("[merge]:Right NULL return Left\n");
      return leftList;
    }
  node * result = NULL;
  //  printf("[merge]:leftList:%s\n",leftList->data[index]);
  //  printf("[merge]:rightList:%s\n",rightList->data[index]);
  //  printf("[merge]:SWITCH. index:%d\n", index);
  if( (*comp)(strcat(leftList->data[index],"\0"),strcat(rightList->data[index],"\0")) <= 0)
      {
	//	printf( "[merge]:Less than 1 \n");
	result = leftList;
	//	printf( "[merge]:Less than 1 \n");
	result->next = merge(leftList->next,rightList,index,comp);
      }
      else
	{
	  //	  printf( "[merge]:More than 1 \n");
	  result = rightList;
	  //	  printf("[merge]:leftList:%s\n",leftList->data[index]);
	  result->next = merge(leftList,rightList->next,index,comp);
      	}
      
      return result;
}

void subDivide( node * head, node** left, node** right )
{
  //  printf("[subDivide]:ENtering\n");
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
      /*
      printf("[subDivide]: left:\n");
      printData(*left,4);
      printf("[subDivide]: right:\n");
      printData(*right,4);*/
    }
}

void mergeSort( node ** head, int index,  int (*comp)(void*,void*))
{
  //  printf("[mergeSort]:Initializing\n");
  node * left    = NULL;
  node * right   = NULL;
  node * result  = *head;
  if ( result == NULL || result->next == NULL)
    {
      //      printf("[mergeSort]:Result NULL?\n");
      return;
    }
  //  printf("[mergeSort]:Subdivide List\n");
    subDivide( result, &left, &right );
    //  printf("[mergeSort]:Recursive Left\n");
    mergeSort(&left, index, comp);
    //  printf("[mergeSort]:Recursive Right\n");
    mergeSort(&right, index, comp);

    //  printf("[mergeSort]:Merge\n");
  /*  
  printf("[MERGESORT]: left:\n");
  printData(left,4);
  printf("[MERGESORT]: right:\n");
  printData(right,4);
  */
    //  printf("[MERGESORT]:LEFTLIST:%s\n", left->data[index]);
  *head = merge(left,right,index, comp);
}
