/*         ______   ___    ___
 *        /\  _  \ /\_ \  /\_ \
 *        \ \ \L\ \\//\ \ \//\ \      __     __   _ __   ___
 *         \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\
 *          \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \L\ \ \ \//\ \L\ \
 *           \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/
 *            \/_/\/_/\/____/\/____/\/____/\/___L\ \/_/ \/___/
 *                                           /\____/
 *                                           \_/__/
 *
 *      Stuff for BeOS.
 *
 *      By Jason Wilkins.
 *
 *      See readme.txt for copyright information.
 */

#include "allegro.h"
#include "allegro/internal/aintern.h"
#include "allegro/platform/ainta5.h"
#include "allegro/platform/ala5.h"


KEYBOARD_DRIVER keyboard_allegro_5 = {
   KEYBOARD_ALLEGRO_5,
   empty_string,
   empty_string,
   "Allegro 5 Keyboard",
   TRUE,
   NULL, //be_key_init,
   NULL, //be_key_exit,
   NULL,
   NULL, //be_key_set_leds,
   NULL, //be_key_set_rate,
   NULL, //be_key_wait_for_input,
   NULL, //be_key_stop_waiting_for_input,
   NULL,
   NULL
};
