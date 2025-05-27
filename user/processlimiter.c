
typedef int unsigned uint;

#include "u_assert.h"


#define MAX_ARGS 6 //maximum number of arguments the program can properly handle in console
int min(int a, int b) 
{
  return a <= b ? a : b;
}

bool8 c_lock = 0;

int main(int argc, char *argv[])
{
  

  uint nProcs = 5; /*the number of processes (forks) that will get EXECUTED not the cap*/
  bool8 timingEn = 0;
  printf("Current UID is %d\n", getuid());
  //argument parsing
if(argc == 1)
{
    setuid(1);
    printf("After setting the uid, the new UID is %d\n(TIP: for Help: processlimiter -h or processlimiter help)\n", getuid());
    sleep(1);
  }

else if(argc > 1)
{
  if(argc >= 2)
  {
  if( (!strcmp(argv[1], "-h") || !strcmp(argv[1], "help")) && argc==2)
  {
    printf("Usage:\nprocesslimiter userID numProcs enablePerformanceMeasurement\n(or for default behavior which will set the user id to 1 automatically (default non-root) and test on 5 procs.):\nprocesslimiter\n");
    exit(0);
  }
  
  else //uid setting
  {
    int userID = atoi(argv[1]);
    printf("user id: %d\n", userID);
    if(argv[1][0] == '-')
    {
      defineAssertFailureErrSpecfic(setuid, UID>0, uidstr2, uidstrN, User ID passed has to be positive)
      assert(userID > 0, uidstr2, uidstrN);
    }
    
    defineAssertFailureErrSpecfic(setuid, UID!=0, uidstr1, uidstrZ, Only the kernel can acess this process by default with UID=0)
    assert(userID != 0, uidstr1, uidstrZ);
    

    setuid(userID);  // this line used to set the uid 

  }
  if(argc >= 3) //numProcs
  {
    nProcs = (uint)atoi(argv[2]);
    if(argv[2][0] == '-')
    {
      defineAssertFailureErrSpecfic(processNumberParser, nProcs>0, procStr1, procStr2, Process Number passed has to be positive)
      assert(nProcs > 0, procStr1, procStr2);
    }
    if(nProcs == 0) 
    printf("Number of processes passed was zero, either erroneously entered or on purpose - the program will set the limit to ZERO processes.\n");
    
  }
  bool8 atleastOne = 0;
  if(argc >= 4) //time measurement and setting the maximum limit of procs manually
  {
    
    for(int i = 3; i < min(argc, MAX_ARGS); ++i)
    {
      char* it = argv[i];
      if(*it == '-') //-t for time measurement and -pMax for setting the max num of processes
      {
      
      if(*(++it) == 't')
        { atleastOne = 1;
          timingEn = 1;
          continue;
        }
      else if(*it == 'p' && !strcmp("pMax", it))
      { 
        int temp = atoi(argv[++i]); //accessing the maxprocesses set by the user in the console
        if(argv[i][0] == '-') //checking for the negative sign, since xv6's atoi is too stupid to differentiate between 0 and negative nums (in the return value)
        {
          defineAssertFailureErrSpecfic(setuid, maxProcesses>0, pmax1, pmax2, Cannot Set a Negative Max Of Processes)
          assert(temp > 0, pmax1, pmax2);
        }
        if(temp == 0 && (argv[i][0] != '0')) goto erroneousArg; 
        //again, user can set the maximum num of procs to zero but only if it was deliberately passed as zero. Since atoi returns 0 for both the digit 0 and any erroneous input... we have to do this check

        setProcCap(temp); //setting the max processes
        atleastOne = 1;
      }

      }

    else if(!atleastOne)
      goto erroneousArg;
    }
    
  }
  }
  else goto erroneousArg;
}
    
    //the actual program
  int i, status, START;

  if(timingEn)
   START = uptime();

  for(i = 0; i < nProcs; i++)
  {
    int pid = fork();
    
    if(pid == 0) 
    {
    //printf("Child %d created with UID: %d\n", i, getuid());
    write(1, "Child Created\n", 15); //just using write for now as an easier solution to the concurrency issues with printf's thread unsafety
    exit(0);
    } 
    else if(pid < 0) {
    printf("fork() failed at i=%d\n", i);
    }
    
    sleep(1);
  }
  

  for(i = 0; i < nProcs; i++)
  {
    wait(&status);
  }

  
  if(timingEn)
  {
    int END = uptime();
    int t = END - START;
    int fp = t%1000; //extract the decimal part after the radix (fixed-point math)
    t /= 1000;
    if(t < 10)
    printf("Process executed in: %d.00%d (s)\n", t, fp);
    else if(t < 100)
    printf("Process executed in: %d.0%d (s)\n", t, fp);
    else
    printf("Process executed in: %d.%d (s)\n", t, fp);
  }
  exit(0);

  erroneousArg:
  printf("Erroneous arguments passed, exiting program.\n");
  exit(1);
}

