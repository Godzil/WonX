#include "etc.h"

#include <ctype.h>

/*===========================================================================*/
/* "true", "false" の文字列を返す                                            */
/*===========================================================================*/

char * wonx_true_false(int b)
{
  char * s[] = {"false", "true"};
  b = b ? 1 : 0;
  return (s[b]);
}

/*===========================================================================*/
/* 文字の出力                                                                */
/*===========================================================================*/

int wonx_print_character(FILE * fp, unsigned char c)
{
  if      (c == '\n') fprintf(fp, "\\n");
  else if (c == '\r') fprintf(fp, "\\r");
  else if (c == '\t') fprintf(fp, "\\t");
  else if (c == ' ' ) fprintf(fp, "\\s");
  else if (isprint(c)) fputc(c, fp);
  else fprintf(fp, "^%02x", (int)c);
  fflush(fp);
  return (0);
}
