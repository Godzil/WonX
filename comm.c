/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <sys/comm.h>

#include "wonx.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

void comm_open(void)
{}

void comm_close(void)
{}

int comm_send_char(unsigned char byte)
{
  return (0);
}

int comm_receive_char(void)
{
  return (0);
}

int comm_receive_with_timeout(int timeout)
{
  return (0);
}

int comm_send_string(char * string)
{
  return (0);
}

int comm_send_block(void * buffer, int size)
{
  return (0);
}

int comm_receive_block(void * buffer, int size)
{
  return (0);
}

void comm_set_timeout(int receive_timeout, int send_timeout)
{
}

void comm_set_baudrate(int speed)
{
}

int comm_get_baudrate(void)
{
  return (0);
}

void comm_set_cancel_key(unsigned int pattern)
{
}

unsigned int comm_get_cancel_key(void)
{
  return (0);
}

/*
int comm_xmodem(void * xmodem)
{
  return (0);
}
*/
