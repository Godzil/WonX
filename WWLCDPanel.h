#ifndef _WWLCDPanel_h_INCLUDED_
#define _WWLCDPanel_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdlib.h>

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWLCDPanel * WWLCDPanel;

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

int WWLCDPanel_GetWidth( WWLCDPanel p);
int WWLCDPanel_GetHeight(WWLCDPanel p);
int WWLCDPanel_SetWidth( WWLCDPanel p, int n);
int WWLCDPanel_SetHeight(WWLCDPanel p, int n);
unsigned char * WWLCDPanel_GetPixelMap(WWLCDPanel p);
int WWLCDPanel_GetPixel(WWLCDPanel lcd_panel, int x, int y);
int WWLCDPanel_SetPixel(WWLCDPanel lcd_panel, int x, int y, int pixel);
WWLCDPanel WWLCDPanel_Create(int width, int height);
WWLCDPanel WWLCDPanel_Destroy(WWLCDPanel lcd_panel);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/