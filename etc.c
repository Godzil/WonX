#include "etc.h"

#include <ctype.h>

/*===========================================================================*/
/* "true", "false" ��ʸ������֤�                                            */
/*===========================================================================*/

char * wonx_true_false(int b)
{
  char * s[] = {"false", "true"};
  b = b ? 1 : 0;
  return (s[b]);
}

/*===========================================================================*/
/* ʸ���ν���                                                                */
/*===========================================================================*/

int wonx_print_character(FILE * fp, unsigned char c)
{
  if      (c == '\n') fprintf(fp, "\\n");
  else if (c == '\r') fprintf(fp, "\\r");
  else if (c == '\t') fprintf(fp, "\\t");
  else if (c == '\"') fprintf(fp, "\\\"");
  else if (c == '\'') fprintf(fp, "\\\'");
  else if (c == '\\') fprintf(fp, "\\\\");
  else if (c == ' ' ) fprintf(fp, "\\s");
  else if (isprint(c)) fputc(c, fp);
  else fprintf(fp, "^%02x", (int)c);
  fflush(fp);
  return (0);
}

/*===========================================================================*/
/* 10�ʢ�16��ʸ���ؤ��Ѵ�                                                    */
/*===========================================================================*/

char wonx_dec_to_hex(int dec)
{
  static char * dec2hex = "0123456789abcdef";
  return (dec2hex[dec]);
}

