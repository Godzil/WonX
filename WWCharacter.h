#ifndef _WWCharacter_h_INCLUDED_
#define _WWCharacter_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WWCharacter * WWCharacter;

/*****************************************************************************/
/* ヘッダファイルのインクルード                                              */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "WWDisplay.h"
#include "wonx/libwwc.h"

/*****************************************************************************/
/* メンバ関数の宣言                                                          */
/*****************************************************************************/

/*===========================================================================*/
/* ナンバーの操作                                                            */
/*===========================================================================*/

int WWCharacter_GetNumber(WWCharacter c);
int WWCharacter_SetNumber(WWCharacter c, int n);

/*===========================================================================*/
/* ビットマップの操作                                                        */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* char 型として操作するための関数                                           */
/*---------------------------------------------------------------------------*/

unsigned char WWCharacter_GetBitmapAsChar(WWCharacter c, int n);
unsigned char WWCharacter_SetBitmapAsChar(WWCharacter c, int n,
					  unsigned char bitmap);

/*---------------------------------------------------------------------------*/
/* short int 型として操作するための関数                                      */
/*---------------------------------------------------------------------------*/

unsigned short int WWCharacter_GetBitmapAsShortInt(WWCharacter c, int n);
unsigned short int WWCharacter_SetBitmapAsShortInt(WWCharacter c, int n,
						   unsigned short int bitmap);

/*---------------------------------------------------------------------------*/
/* long int 型として操作するための関数                                       */
/*---------------------------------------------------------------------------*/

unsigned long int WWCharacter_GetBitmapAsLongInt(WWCharacter c, int n);
unsigned long int WWCharacter_SetBitmapAsLongInt(WWCharacter c, int n,
						 unsigned long int bitmap);

/*===========================================================================*/
/* オブジェクトの生成と削除                                                  */
/*===========================================================================*/

WWCharacter WWCharacter_Create(int number);
WWCharacter WWCharacter_Destroy(WWCharacter character);

/*===========================================================================*/
/* ピクセルの操作                                                            */
/*===========================================================================*/

int WWCharacter_GetPixel(WWCharacter character, int x, int y,
			 WWDisplay display);
int WWCharacter_ClearAllPixels(WWCharacter character);
int WWCharacter_CopyAllPixels(WWCharacter dst, WWCharacter src);

/*===========================================================================*/
/* 内部データ出力                                                            */
/*===========================================================================*/

int WWCharacter_PrintData(WWCharacter character, WWDisplay display, FILE * f);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
