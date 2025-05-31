#ifndef U_ASSERT
#define U_ASSERT

#include "user.h"

#define NULL (void*)0

typedef unsigned char bool8;

#define defineAssertFailure(funcName, condition, errStrVar) \
    char errStrVar[] = "error - failure to execute: "#funcName"\non: ("#condition") - it yielded: ";

#define defineAssertFailureErrSpecfic(funcName, condition, errStrVar, errSpcfcVar, errString) \
    char errStrVar[] = "error - failure to execute: "#funcName"\non: ("#condition") - it yielded: ";   \
    char errSpcfcVar[] = #errString;

defineAssertFailure(assert, failurePrint != NULL, assertStringEqualNull)
defineAssertFailure(assert, strlen(failurePrint)>0, assertStringHasBytes)
//example of usage on user end:
//defineAssertFailure(setuid, x>0, setuidErrStr)
//then call it down at assert like: assert(x>0, setuidErrStr); in runtime

void assert(bool8 condition, char* failurePrint, char* failureSpecific)
{
    if(!failurePrint) { printf("%s%d\n", assertStringEqualNull, (failurePrint!=NULL) ); exit(1);}
    
    uint plen = strlen(failurePrint);

    if(plen <= 0) {printf("%s%d\n", assertStringHasBytes, (plen>0)); exit(1);}
    
    if(!(condition))
    {   if(failureSpecific && strlen(failureSpecific)>5)
        {
        printf("%s%d\n%s\n", failurePrint, condition, failureSpecific);    
        }
        else
        printf("%s%d\n", failurePrint, condition); 
    exit(1);
    }
    
    return;
}

#endif 