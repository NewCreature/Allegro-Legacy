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


MOUSE_DRIVER mouse_allegro_5 = {
   MOUSE_ALLEGRO_5,		// int id;
   empty_string,	// char *name;
   empty_string,	// char *desc;
   "Allegro 5 Mouse",		// char *ascii_name;
   NULL, //be_mouse_init,	// AL_METHOD(int, init, (void));
   NULL, //be_mouse_exit,	// AL_METHOD(void, exit, (void));
   NULL,		// AL_METHOD(void, poll, (void));
   NULL,		// AL_METHOD(void, timer_poll, (void));
   NULL, //be_mouse_position,	// AL_METHOD(void, position, (int x, int y));
   NULL, //be_mouse_set_range,	// AL_METHOD(void, set_range, (int x1, int y1, int x2, int y2));
   NULL, //be_mouse_set_speed,	// AL_METHOD(void, set_speed, (int xspeed, int yspeed));
   NULL, //be_mouse_get_mickeys,// AL_METHOD(void, get_mickeys, (int *mickeyx, int *mickeyy));
   NULL,                // AL_METHOD(int,  analyse_data, (const char *buffer, int size));
   NULL,                // AL_METHOD(void,  enable_hardware_cursor, (AL_CONST int mode));
   NULL                 // AL_METHOD(int,  select_system_cursor, (AL_CONST int cursor));
};
