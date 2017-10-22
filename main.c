#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>


int main( int argc, char ** argv )
{

  DIR * base = opendir("test");
  struct dirent * fileOrDirectory = readdir(base);
  
  while( fileOrDirectory != NULL )
    {

      printf("name: %s type: %d \n",fileOrDirectory->d_name,fileOrDirectory->d_type);

      switch( (int)fileOrDirectory->d_type)
	{
	case 4:
	  if(
	  strcmp( (fileOrDirectory->d_name), ".")  != 0 &&
	  strcmp( (fileOrDirectory->d_name), "..") != 0)
	    {
	      fork();
	      
	    }
	  break;

	case 8:
	  

	  break;

	}




	}



      
      fileOrDirectory = readdir(base);


    }
  /*
  pid_t mypid;
  
  printf( "Starting\n");
  mypid = fork();


  printf("%d\n", (int)mypid );
  */
  return 0;
}
