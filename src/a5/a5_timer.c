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

#define _A5_MAX_TIMERS 32

static ALLEGRO_THREAD * a5_timer_thread = NULL;
static ALLEGRO_EVENT_SOURCE a5_timer_event_source;
static volatile bool a5_timer_thread_ready = false;

static ALLEGRO_TIMER * a5_timer[_A5_MAX_TIMERS] = {NULL};
static void (*a5_timer_proc[_A5_MAX_TIMERS])(void) = {NULL};
static int a5_timers = 0;

static ALLEGRO_TIMER * a5_param_timer[_A5_MAX_TIMERS] = {NULL};
static void (*a5_param_timer_proc[_A5_MAX_TIMERS])(void * data) = {NULL};
static void * a5_param_timer_data[_A5_MAX_TIMERS] = {NULL};
static int a5_param_timers = 0;

static ALLEGRO_MUTEX * a5_timer_mutex = NULL;

static void * a5_timer_thread_proc(ALLEGRO_THREAD * thread, void * data)
{
    ALLEGRO_EVENT_QUEUE * queue;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMEOUT timeout;
    double cur_time, prev_time = 0.0, diff_time;
    int i;

    queue = al_create_event_queue();
    if(!queue)
    {
        return NULL;
    }
    al_init_user_event_source(&a5_timer_event_source);
    al_register_event_source(queue, &a5_timer_event_source);
    a5_timer_thread_ready = true;
    while(!al_get_thread_should_stop(thread))
    {
        al_init_timeout(&timeout, 0.1);
        if(al_wait_for_event_until(queue, &event, &timeout))
        {
            al_lock_mutex(a5_timer_mutex);
            if(event.any.source == &a5_timer_event_source)
            {
                for(i = 0; i < a5_timers; i++)
                {
                    al_register_event_source(queue, al_get_timer_event_source(a5_timer[i]));
                }
                for(i = 0; i < a5_param_timers; i++)
                {
                    al_register_event_source(queue, al_get_timer_event_source(a5_param_timer[i]));
                }
            }
            else
            {
                cur_time = al_get_time();
                diff_time = cur_time - prev_time;
                prev_time = al_get_time();
                for(i = 0; i < a5_timers; i++)
                {
                    if(al_get_timer_event_source(a5_timer[i]) == event.any.source)
                    {
                        a5_timer_proc[i]();
                    }
                }
                for(i = 0; i < a5_param_timers; i++)
                {
                    if(al_get_timer_event_source(a5_param_timer[i]) == event.any.source)
                    {
                        a5_param_timer_proc[i](a5_param_timer_data[i]);
                    }
                }
                _handle_timer_tick(MSEC_TO_TIMER(diff_time * 1000.0));
            }
            al_unlock_mutex(a5_timer_mutex);
        }
    }
    al_destroy_event_queue(queue);
    return NULL;
}

static int a5_timer_init(void)
{
    a5_timer_thread = al_create_thread(a5_timer_thread_proc, NULL);
    if(a5_timer_thread)
    {
        a5_timer_mutex = al_create_mutex();
        if(!a5_timer_mutex)
        {
            al_destroy_thread(a5_timer_thread);
            a5_timer_thread = NULL;
        }
        al_start_thread(a5_timer_thread);
        while(!a5_timer_thread_ready);
        return 0;
    }
    return -1;
}

static void a5_timer_exit(void)
{
    al_destroy_thread(a5_timer_thread);
    a5_timer_thread = NULL;
    a5_timer_thread_ready = false;
    al_destroy_mutex(a5_timer_mutex);
    a5_timer_mutex = NULL;
}

static double a5_get_timer_speed(long speed)
{
    return (double)speed / 1193181.0;
}

static int a5_timer_install_int(void (*proc)(void), long speed)
{
    ALLEGRO_EVENT event;
    int i;

    if(a5_timers < _A5_MAX_TIMERS)
    {
        al_lock_mutex(a5_timer_mutex);
        for(i = 0; i < a5_timers; i++)
        {
            if(proc == a5_timer_proc[i])
            {
                al_set_timer_speed(a5_timer[i], a5_get_timer_speed(speed));
                al_unlock_mutex(a5_timer_mutex);
                return 0;
            }
        }

        a5_timer[a5_timers] = al_create_timer(a5_get_timer_speed(speed));
        if(a5_timer[a5_timers])
        {
            al_start_timer(a5_timer[a5_timers]);
            a5_timer_proc[a5_timers] = proc;
            a5_timers++;
            al_emit_user_event(&a5_timer_event_source, &event, NULL);
            al_unlock_mutex(a5_timer_mutex);
            return 0;
        }
    }
    return -1;
}

static void a5_timer_remove_int(void (*proc)(void))
{
    ALLEGRO_EVENT event;
    int i, j;

    al_lock_mutex(a5_timer_mutex);
    for(i = 0; i < a5_timers; i++)
    {
        if(proc == a5_timer_proc[i])
        {
            al_destroy_timer(a5_timer[i]);
            for(j = i; j < a5_timers - 1; j++)
            {
                a5_timer[j] = a5_timer[j + 1];
                a5_timer_proc[j] = a5_timer_proc[j + 1];
            }
            a5_timers--;
            al_emit_user_event(&a5_timer_event_source, &event, NULL);
            break;
        }
    }
    al_unlock_mutex(a5_timer_mutex);
}

static int a5_timer_install_param_int(void (*proc)(void * data), void * param, long speed)
{
    ALLEGRO_EVENT event;
    int i;

    if(a5_param_timers < _A5_MAX_TIMERS)
    {
        al_lock_mutex(a5_timer_mutex);
        for(i = 0; i < a5_param_timers; i++)
        {
            if(proc == a5_param_timer_proc[i])
            {
                al_set_timer_speed(a5_param_timer[i], a5_get_timer_speed(speed));
                al_unlock_mutex(a5_timer_mutex);
                return 0;
            }
        }

        a5_param_timer[a5_param_timers] = al_create_timer(a5_get_timer_speed(speed));
        if(a5_param_timer[a5_param_timers])
        {
            al_start_timer(a5_param_timer[a5_param_timers]);
            a5_param_timer_proc[a5_param_timers] = proc;
            a5_param_timer_data[a5_param_timers] = param;
            a5_param_timers++;
            al_emit_user_event(&a5_timer_event_source, &event, NULL);
            al_unlock_mutex(a5_timer_mutex);
            return 0;
        }
    }
    return -1;
}

static void a5_timer_remove_param_int(void (*proc)(void * data), void * param)
{
    ALLEGRO_EVENT event;
    int i, j;

    al_lock_mutex(a5_timer_mutex);
    for(i = 0; i < a5_param_timers; i++)
    {
        if(param == a5_param_timer_data[i])
        {
            al_destroy_timer(a5_param_timer[i]);
            for(j = i; j < a5_param_timers - 1; j++)
            {
                a5_param_timer[j] = a5_param_timer[j + 1];
                a5_param_timer_proc[j] = a5_param_timer_proc[j + 1];
            }
            a5_param_timers--;
            al_emit_user_event(&a5_timer_event_source, &event, NULL);
            break;
        }
    }
    al_unlock_mutex(a5_timer_mutex);
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
   a5_timer_install_int, 		// AL_LEGACY_METHOD(int, install_int, (AL_LEGACY_METHOD(void, proc, (void)), long speed));
   a5_timer_remove_int,		// AL_LEGACY_METHOD(void, remove_int, (AL_LEGACY_METHOD(void, proc, (void))));
   a5_timer_install_param_int,		// AL_LEGACY_METHOD(int, install_param_int, (AL_LEGACY_METHOD(void, proc, (void *param)), void *param, long speed));
   a5_timer_remove_param_int,		// AL_LEGACY_METHOD(void, remove_param_int, (AL_LEGACY_METHOD(void, proc, (void *param)), void *param));
   NULL,		// AL_LEGACY_METHOD(int, can_simulate_retrace, (void));
   NULL,		// AL_LEGACY_METHOD(void, simulate_retrace, (int enable));
   a5_timer_rest,	// AL_LEGACY_METHOD(void, rest, (long time, AL_LEGACY_METHOD(void, callback, (void))));
};

_DRIVER_INFO _timer_driver_list[] = {
   {TIMERDRV_ALLEGRO_5, &timer_allegro5, TRUE},
   {0, NULL, 0}
};
