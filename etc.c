#include "etc.h"

#include <stdio.h>
#include <stdlib.h>

/*===========================================================================*/
/* ���顼����                                                                */
/*===========================================================================*/

int Error(char * funcname, char * message)
{
  fprintf(stderr, "%s(): %s\n", funcname, message);
  exit (1);
}
