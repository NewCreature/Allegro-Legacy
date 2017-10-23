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

DIGI_DRIVER digi_allegro_5 =
{
   DIGI_ALLEGRO_5,
   empty_string,
   empty_string,
   "Allegro 5 Sound",
   0,
   0,
   MIXER_MAX_SFX,
   MIXER_DEF_SFX,

   NULL, //be_sound_detect,
   NULL, //be_sound_init,
   NULL, //be_sound_exit,
   NULL, //be_sound_set_mixer_volume,
   NULL, //be_sound_get_mixer_volume,

   NULL, //be_sound_lock_voice,
   NULL, //be_sound_unlock_voice,
   NULL, //be_sound_buffer_size,
   NULL, //_mixer_init_voice,
   NULL, //_mixer_release_voice,
   NULL, //_mixer_start_voice,
   NULL, //_mixer_stop_voice,
   NULL, //_mixer_loop_voice,

   NULL, //_mixer_get_position,
   NULL, //_mixer_set_position,

   NULL, //_mixer_get_volume,
   NULL, //_mixer_set_volume,
   NULL, //_mixer_ramp_volume,
   NULL, //_mixer_stop_volume_ramp,

   NULL, //_mixer_get_frequency,
   NULL, //_mixer_set_frequency,
   NULL, //_mixer_sweep_frequency,
   NULL, //_mixer_stop_frequency_sweep,

   NULL, //_mixer_get_pan,
   NULL, //_mixer_set_pan,
   NULL, //_mixer_sweep_pan,
   NULL, //_mixer_stop_pan_sweep,

   NULL, //_mixer_set_echo,
   NULL, //_mixer_set_tremolo,
   NULL, //_mixer_set_vibrato,
   0, 0,
   0,
   0,
   0,
   0,
   0,
   0
};
