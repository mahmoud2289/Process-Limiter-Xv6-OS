typedef unsigned int uint;
#include "user.h"


int main(int argc, char *argv[])
{
  printf("Current UID is %d\n", getuid());
  // this line used to set the uid 
  setuid(1);
  printf("After setting the uid, the new UID is %d\n", getuid());

  int i, status;

  for(i = 0; i < 5; i++)
  {
    int pid = fork();
    
    if(pid == 0) {
    printf("Child %d created with UID: %d\n", i, getuid());
    sleep(10);
    exit(0);
    } 
    else if(pid < 0) {
    printf("fork() failed at i=%d\n", i);
    }
    
    sleep(1);
  }
     
  for(i = 0; i < 5; i++)
  {
    wait(&status);
  }

  exit(0);
}

