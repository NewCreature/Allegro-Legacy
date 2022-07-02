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
#include "allegro/platform/ala5.h"

static ALLEGRO_THREAD * a5_timer_thread;

static double a5_get_timer_speed(long speed)
{
    return (double)speed / (float)TIMERS_PER_SECOND;
}

static void * a5_timer_proc(ALLEGRO_THREAD * thread, void * unused)
{
    double cur_time, prev_time, diff_time;

    prev_time = al_get_time();
    while(!al_get_thread_should_stop(thread))
    {
        cur_time = al_get_time();
        diff_time = cur_time - prev_time;
        prev_time = cur_time;
        double delay = a5_get_timer_speed(_handle_timer_tick(MSEC_TO_TIMER(diff_time * 1000.0)));
        if (delay < .001) {
            delay = .001;
        }
        al_rest(delay);
    }
    return NULL;
}

static int a5_timer_init(void)
{
    a5_timer_thread = al_create_thread(a5_timer_proc, NULL);
    al_start_thread(a5_timer_thread);
    return 0;
}

static void a5_timer_exit(void)
{
    al_destroy_thread(a5_timer_thread);
}

static void a5_timer_rest(unsigned int time, void (*callback)(void))
{
    double start_time = al_get_time();
    double current_time = start_time;
    if(callback)
    {
        while(current_time - start_time < (double)time / 1000.0)
        {
            callback();
        }
    }
    else
    {
        al_rest((double)time / 1000.0);
    }
}

TIMER_DRIVER timer_allegro5 = {
   TIMERDRV_ALLEGRO_5,		// int id;
   empty_string,	// char *name;
   empty_string,	// char *desc;
   "Allegro 5 Timer",		// char *ascii_name;
   a5_timer_init,	// AL_LEGACY_METHOD(int, init, (void));
   a5_timer_exit,	// AL_LEGACY_METHOD(void, exit, (void));
   NULL, 			// AL_LEGACY_METHOD(int, install_int, (AL_LEGACY_METHOD(void, proc, (void)), long speed));
   NULL,			// AL_LEGACY_METHOD(void, remove_int, (AL_LEGACY_METHOD(void, proc, (void))));
   NULL,			// AL_LEGACY_METHOD(int, install_param_int, (AL_LEGACY_METHOD(void, proc, (void *param)), void *param, long speed));
   NULL,			// AL_LEGACY_METHOD(void, remove_param_int, (AL_LEGACY_METHOD(void, proc, (void *param)), void *param));
   NULL,			// AL_LEGACY_METHOD(int, can_simulate_retrace, (void));
   NULL,			// AL_LEGACY_METHOD(void, simulate_retrace, (int enable));
   a5_timer_rest,	// AL_LEGACY_METHOD(void, rest, (long time, AL_LEGACY_METHOD(void, callback, (void))));
};

_DRIVER_INFO _timer_driver_list[] = {
   {TIMERDRV_ALLEGRO_5, &timer_allegro5, TRUE},
   {0, NULL, 0}
};
