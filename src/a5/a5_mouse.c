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

static ALLEGRO_THREAD * a5_mouse_thread = NULL;
static int a5_last_mouse_x = -1;
static int a5_last_mouse_y = -1;

static void * a5_mouse_thread_proc(ALLEGRO_THREAD * thread, void * data)
{
    ALLEGRO_EVENT_QUEUE * queue;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMEOUT timeout;

    queue = al_create_event_queue();
    if(!queue)
    {
        return NULL;
    }
    printf("mouse thread\n");
    al_register_event_source(queue, al_get_mouse_event_source());
    while(!al_get_thread_should_stop(thread))
    {
        al_init_timeout(&timeout, 1.0);
        if(al_wait_for_event_until(queue, &event, &timeout))
        {
            switch(event.type)
            {
                case ALLEGRO_EVENT_MOUSE_AXES:
                {
                    _mouse_x = event.mouse.x;
                    _mouse_y = event.mouse.y;
                    _mouse_z = event.mouse.z;
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                {
                    _mouse_b |= 1 << (event.mouse.button - 1);
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                {
                    _mouse_b &= ~(1 << (event.mouse.button - 1));
                    break;
                }
            }
            _handle_mouse_input();
        }
    }
    return NULL;
}

static int a5_mouse_init(void)
{
    printf("mouse init\n");
    if(!al_install_mouse())
    {
        return -1;
    }
    a5_mouse_thread = al_create_thread(a5_mouse_thread_proc, NULL);
    al_start_thread(a5_mouse_thread);
    return 0;
}

static void a5_mouse_exit(void)
{
    al_destroy_thread(a5_mouse_thread);
    a5_mouse_thread = NULL;
    al_uninstall_mouse();
}

static void a5_mouse_position(int x, int y)
{
    al_set_mouse_xy(_a5_display, x, y);
}

static void a5_mouse_get_mickeys(int * x, int * y)
{
    if(x)
    {
        if(a5_last_mouse_x < 0)
        {
            a5_last_mouse_x = _mouse_x;
        }
        *x = _mouse_x - a5_last_mouse_x;
        a5_last_mouse_x = _mouse_x;
    }
    if(y)
    {
        if(a5_last_mouse_y < 0)
        {
            a5_last_mouse_y = _mouse_y;
        }
        *y = _mouse_y - a5_last_mouse_y;
        a5_last_mouse_y = _mouse_y;
    }
}

MOUSE_DRIVER mouse_allegro_5 = {
   MOUSE_ALLEGRO_5,		// int id;
   empty_string,	// char *name;
   empty_string,	// char *desc;
   "Allegro 5 Mouse",		// char *ascii_name;
   a5_mouse_init, //be_mouse_init,	// AL_LEGACY_METHOD(int, init, (void));
   a5_mouse_exit, //be_mouse_exit,	// AL_LEGACY_METHOD(void, exit, (void));
   NULL,		// AL_LEGACY_METHOD(void, poll, (void));
   NULL,		// AL_LEGACY_METHOD(void, timer_poll, (void));
   a5_mouse_position, //be_mouse_position,	// AL_LEGACY_METHOD(void, position, (int x, int y));
   NULL, //be_mouse_set_range,	// AL_LEGACY_METHOD(void, set_range, (int x1, int y1, int x2, int y2));
   NULL, //be_mouse_set_speed,	// AL_LEGACY_METHOD(void, set_speed, (int xspeed, int yspeed));
   a5_mouse_get_mickeys, //be_mouse_get_mickeys,// AL_LEGACY_METHOD(void, get_mickeys, (int *mickeyx, int *mickeyy));
   NULL,                // AL_LEGACY_METHOD(int,  analyse_data, (const char *buffer, int size));
   NULL,                // AL_LEGACY_METHOD(void,  enable_hardware_cursor, (AL_LEGACY_CONST int mode));
   NULL                 // AL_LEGACY_METHOD(int,  select_system_cursor, (AL_LEGACY_CONST int cursor));
};
