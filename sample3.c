#include "wonx/text.h"
#include "wonx/fcntl.h"
#include "wonx/key.h"

#ifdef _WONX_
#include "wonx/wonx.h"
#endif

main()
{
  char * p;
  int x, y, i;

  text_screen_init();
  p = mmap("COPYING");

#ifdef _WONX_
  wonx_lcddraw_level_down();
#endif

  i = 0;
  for (y = 0; y < TEXT_SCREEN_HEIGHT; y++) {
    for (x = 0; x < TEXT_SCREEN_WIDTH; x++) {
      text_put_char(x, y, p[i++]);
    }
  }

#ifdef _WONX_
  wonx_lcddraw_level_up();
#endif

  key_wait();

  bios_exit();
}
