#include <stdio.h>
#include <stdlib.h>

#include <sys/key.h>

#include "wonx.h"

#include "WonxDisplay.h"

int key_press_check(void)
{
  XDisplay x_display;
  int ret;

  printf("call : key_press_check() : "); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  x_display = WonxDisplay_GetXDisplay(wonx_display);
  XDisplay_Sync(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  return (ret);
}

int key_hit_check(void)
{
  XDisplay x_display;
  int ret;

  printf("call : key_hit_check() : "); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  x_display = WonxDisplay_GetXDisplay(wonx_display);
  XDisplay_Sync(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  return (ret);
}

int key_wait(void)
{
  XDisplay x_display;
  int ret;

  printf("call : key_wait() : "); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  x_display = WonxDisplay_GetXDisplay(wonx_display);

  ret = 0;
  do {
    XDisplay_Sync(x_display);
    ret = XDisplay_GetKeyPress(x_display);
  } while (ret == 0);

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  return (ret);
}

void key_set_repeat(int rate, int delay)
{
  printf("call : key_set_repeat() : rate = %d, delay = %d, ", rate, delay);
  fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  printf("return value = none\n"); fflush(stdout);
}

int key_get_repeat(void)
{
  int ret;

  printf("call : key_get_repeat() : "); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  ret = 0;

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  return (ret);
}

int key_hit_check_with_repeat(void)
{
  XDisplay x_display;
  int ret;

  printf("call : key_hit_check_with_repeat() : "); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  x_display = WonxDisplay_GetXDisplay(wonx_display);
  XDisplay_Sync(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  return (ret);
}

