#ifndef _WONX_SYS_WONX_H_
#define _WONX_SYS_WONX_H_

#include "service.h"

/*****************************************************************************/
/* 外部に公開する WonX のサービス関数                                        */
/*****************************************************************************/

/* カラーマップ情報の出力 */
void wonx_print_colormap_data(void);

/* パレット情報の出力 */
void wonx_print_palette_data(int n);

/* すべてのパレット情報を出力 */
void wonx_print_all_palette_data(void);

/* キャラクタ情報の出力 */
void wonx_print_character_data(int n);

/* すべてのキャラクタ情報を出力 */
void wonx_print_all_character_data(void);

/* スプライト情報の出力 */
void wonx_print_sprite_data(int n);

/* すべてのスプライト情報を出力 */
void wonx_print_all_sprite_data(void);

/* 現在の表示/非表示のレベルの取得．(1以上で表示，0以下で非表示) */
int wonx_get_lcddraw_level(void);

/* 現在の表示/非表示のレベルの設定 */
int wonx_set_lcddraw_level(int level);

/* 表示レベルを下げる */
int wonx_lcddraw_level_down(void);

/* 表示レベルを上げる */
int wonx_lcddraw_level_up(void);

#endif
