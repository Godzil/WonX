#include <stdio.h>
#include <stdlib.h>

#include "wonx/wonx.h"

#include "WonX.h"
#include "WonXDisplay.h"
#include "WWDisplay.h"
#include "XDisplay.h"

#include "WWColorMap.h"
#include "WWPalette.h"
#include "WWCharacter.h"
#include "WWSprite.h"

/*****************************************************************************/
/* 外部に公開する WonX のサービス関数                                        */
/*****************************************************************************/

/*
 * Xサーバとの同期の整合性がとれなくなるなどの問題が考えられるので，
 * 互換関数の内部は UNIXTimer_Pause(), UNIXTimer_Unpause() でくくり，
 * タイマ割り込みを一時停止して処理を行う．また，unpause するまえに，
 * かならず sync するようにする．
 */

/*
 * タイマの一時停止の２重解除の問題が出てくるので，
 * 互換関数から互換関数を呼んではいけない．
 * (一時停止はネストされるが，いちおう)
 * 似たような処理をする関数の場合は，必ず static な別関数に処理をまとめ，
 * そっちを呼び出すようにすること．
 * 引数の表示の問題もあるしね．
 */

/* カラーマップ情報の出力 */
void wonx_print_colormap_data(void)
{
  WWDisplay ww_display;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_colormap_data() : \n");
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  WWColorMap_PrintData(WWDisplay_GetColorMap(ww_display), stdout);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_colormap_data() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* パレット情報の出力用内部関数 */
static void _print_palette_data(int n)
{
  WWDisplay ww_display;
  WWPalette ww_palette;
  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_palette = WWDisplay_GetPalette(ww_display, n);
  WWPalette_PrintData(ww_palette, ww_display, stdout);
  return;
}

/* パレット情報の出力 */
void wonx_print_palette_data(int n)
{
  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_palette_data() : number = %d\n", n);
  fflush(stdout);

  if ((n < 0) || (n > 16 - 1))
    WonX_Error("wonx_print_palette_data", "number is out of range.");
  _print_palette_data(n);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_palette_data() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* すべてのパレット情報を出力 */
void wonx_print_all_palette_data(void)
{
  int n;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_all_palette_data() : \n");
  fflush(stdout);

  for (n = 0; n < 16; n++) _print_palette_data(n);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_all_palette_data() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* キャラクタ情報の出力用内部関数 */
static void _print_character_data(int n)
{
  WWDisplay ww_display;
  WWCharacter ww_character;
  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_character = WWDisplay_GetCharacter(ww_display, n);
  WWCharacter_PrintData(ww_character, ww_display, stdout);
  return;
}

/* キャラクタ情報の出力 */
void wonx_print_character_data(int n)
{
  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_character_data() : number = %d\n", n);
  fflush(stdout);

  if ((n < 0) || (n > 512 - 1))
    WonX_Error("wonx_print_character_data", "number is out of range.");
  _print_character_data(n);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_character_data() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* すべてのキャラクタ情報を出力 */
void wonx_print_all_character_data(void)
{
  int n;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_all_character_data() : \n");
  fflush(stdout);

  for (n = 0; n < 512; n++) _print_character_data(n);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_all_character_data() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* スプライト情報の出力用内部関数 */
static void _print_sprite_data(int n)
{
  WWDisplay ww_display;
  WWSprite ww_sprite;
  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_sprite = WWDisplay_GetSprite(ww_display, n);
  WWSprite_PrintData(ww_sprite, stdout);
  return;
}

/* スプライト情報の出力 */
void wonx_print_sprite_data(int n)
{
  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_sprite_data() : number = %d\n", n);
  fflush(stdout);

  if ((n < 0) || (n > 128 - 1))
    WonX_Error("wonx_print_sprite_data", "number is out of range.");
  _print_sprite_data(n);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_sprite_data() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* すべてのスプライト情報を出力 */
void wonx_print_all_sprite_data(void)
{
  int n;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_all_sprite_data() : \n");
  fflush(stdout);

  for (n = 0; n < 128; n++) _print_sprite_data(n);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_all_sprite_data() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* 現在の表示/非表示のレベルの取得．(1以上で表示，0以下で非表示) */
int wonx_get_lcddraw_level(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_get_lcddraw_level() : \n");
  fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  ret = XDisplay_GetLCDDrawLevel(x_display);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_get_lcddraw_level() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/* 現在の表示/非表示のレベルの設定 */
int wonx_set_lcddraw_level(int level)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_set_lcddraw_level() : level = %d\n", level);
  fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  ret = XDisplay_SetLCDDrawLevel(x_display, level);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : wonx_set_lcddraw_level() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/* 表示レベルを下げる */
int wonx_lcddraw_level_down(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_lcddraw_level_down() : \n");
  fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  ret = XDisplay_LCDDrawLevelDown(x_display);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : wonx_lcddraw_level_down() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/* 表示レベルを上げる */
int wonx_lcddraw_level_up(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_lcddraw_level_up() : \n");
  fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  ret = XDisplay_LCDDrawLevelUp(x_display);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : wonx_lcddraw_level_up() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
