typedef unsigned int uint;

#include "u_assert.h"



int main(int argc, char *argv[])
{
  
  printf("Current UID is %d\n", getuid());
  

  //argument parsing
  switch(argc)
  {
    
  case 1:
  {
    setuid(1);
    printf("After setting the uid, the new UID is %d\nfor Help: processlimiter -h or processlimiter help\n", getuid());
  }
  break;

  case 2:
  if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "help"))
  {
    printf("Usage:\nprocesslimiter userID numProcs\nor for default behavior which will set the user id to 1 automatically (default non-root):\nprocesslimiter\n");
  }
  else
  {
    int userID = atoi(argv[1]);
    printf("user id: %d\n", userID);
    if(argv[1][0] == '-')
    {
      defineAssertFailureErrSpecfic(setuid, UID>0, uidstr2, uidstrN, User ID passed has to be positive)
      assert(userID > 0, uidstr2, uidstrN);
      goto erroneousArg; //jump
    }
    
    defineAssertFailureErrSpecfic(setuid, UID!=0, uidstr1, uidstrZ, Only the kernel can acess this process by default with UID=0)
    assert(userID != 0, uidstr1, uidstrZ);
    

    setuid(userID);  // this line used to set the uid 

  }
  break;
  
  default:
    goto erroneousArg; //jump
  break;
  }
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

  erroneousArg:
  printf("Erroneous arguments passed, exiting program.\n");
  exit(1);
}

