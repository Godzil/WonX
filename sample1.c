#include "wonx_include/text.h"
#include "wonx_include/key.h"

main()
{
  text_screen_init();
  text_put_string(0,  1, "  WonX - WonderWitch on X.  ");
  text_put_string(0,  3, "    This is test program    ");
  text_put_string(0,  4, "          for WonX.         ");
  text_put_string(0,  6, "   WonX is an emulator for  ");
  text_put_string(0,  7, "  WonderWitch on X. It is   ");
  text_put_string(0,  8, "   linked to program for    ");
  text_put_string(0,  9, "  WonderWitch and behave as ");
  text_put_string(0, 10, "        WonderWitch.        ");
  text_put_string(0, 12, "WonX Copyright (c) 2000-2001");
  text_put_string(0, 13, "       Sakai Hiroaki.       ");
  text_put_string(0, 14, "    All Rights Reserved.    ");
  text_put_string(0, 16, "   Hit space key to exit.   ");

  key_wait();

  bios_exit();
}
