#ifndef _WONX_SYS_COMM_H_
#define _WONX_SYS_COMM_H_

#include "service.h"

/*****************************************************************************/
/* 定数の定義                                                                */
/*****************************************************************************/

#define COMM_SPEED_9600  0
#define COMM_SPEED_38400 1

#define XMODE_SEND              0
#define XMODE_RECEIVE           1
#define XMODE_SEND_ENCRYPTED    2
#define XMODE_RECEIVE_ENCRYPTED 3
#define XMODE_AUTO_ERASE        4

#define ERR_SIO_OK        0x0000
#define ERR_SIO_BUSY      0x8100
#define ERR_SIO_TIMEOUT   0x8101
#define ERR_SIO_OVERRUN   0x8102
#define ERR_SIO_CANCEL    0x8103
#define ERR_XM_STATECODE  0x8104
#define ERR_XM_CANCELED   0x8105
#define ERR_XM_BLOCK_LOST 0x8106
#define ERR_XM_TOO_LARGE  0x8107

enum {
  XM_START = 1,
  XM_NEGO,
  XM_BLOCK,
  XM_BLOCK_RETRY,
  XM_CLOSE,
  XM_ABORT,
  XM_DONE,
  XM_ERASE_BANK
};

typedef struct {
  int  state;
  char mode;
  char retry_c;
  int  block_c;
  int  block_max;
  int  block_size;
  int  bank;
  int  offset;
  int  timeout_c;
} xmodeminfo;

/*****************************************************************************/
/* 互換関数の宣言                                                            */
/*****************************************************************************/

void comm_open(void);
void comm_close(void);
int comm_send_char(unsigned char c);
int comm_receive_char(void);
int comm_receive_with_timeout(int timeout);
int comm_send_string(char * string);
int comm_send_block(void * buffer, int size);
int comm_receive_block(void * buffer, int size);
void comm_set_timeout(int recv_timeout, int send_timeout);
void comm_set_baudrate(int baudrate);
int comm_get_baudrate(void);
void comm_set_cancel_key(unsigned int pattern);
unsigned int comm_get_cancel_key(void);
int comm_xmodem(void * xmodem);

#endif
