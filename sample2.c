#include "wonx_include/disp.h"
#include "wonx_include/key.h"

static unsigned char clear[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static unsigned char block[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

main()
{
  int x, y, f, k;

  display_control(DCM_SCR2 | DCM_SPR);

  lcd_set_color(0, 0xffff);
  palette_set_color(0, 0);
  palette_set_color(8, (0xf << 12));

  font_set_color(0x03);

  font_set_monodata(0, 1, clear);
  font_set_monodata(1, 1, block);

  sprite_set_char(0,
		  CFM_SPR_UPPER |
		  ((0 << 9) & CFM_SPR_PALETTE) |
		  (1 & CFM_FONT)
		  );

  sprite_set_range(0, 1); 

  x = 14;
  y = 9;
  f = 0;

  while (!f) {
    sprite_set_location(0, x * 8, y * 8);

    k = key_hit_check();
    if (k & KEY_START) f = 1;
    if (k & KEY_A) f = 1;
    if ((k & KEY_LEFT1) && (x > 0)) x--;
    if ((k & KEY_RIGHT1) && (x < LCD_PIXEL_WIDTH/8 - 1)) x++;
    if ((k & KEY_UP1) && (y > 0)) y--;
    if ((k & KEY_DOWN1) && (y < LCD_PIXEL_HEIGHT/8 - 1)) y++;
  }

  bios_exit();
}
