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
 *      Configuration file access routines.
 *
 *      By Shawn Hargreaves.
 *
 *      See readme.txt for copyright information.
 */


#ifndef ALLEGRO_LEGACY_CONFIG_H
#define ALLEGRO_LEGACY_CONFIG_H

#include "base.h"

#ifdef __cplusplus
   extern "C" {
#endif

AL_LEGACY_FUNC(void, set_config_file, (AL_LEGACY_CONST char *filename));
AL_LEGACY_FUNC(void, set_config_data, (AL_LEGACY_CONST char *data, int length));
AL_LEGACY_FUNC(void, override_config_file, (AL_LEGACY_CONST char *filename));
AL_LEGACY_FUNC(void, override_config_data, (AL_LEGACY_CONST char *data, int length));
AL_LEGACY_FUNC(void, flush_config_file, (void));
AL_LEGACY_FUNC(void, reload_config_texts, (AL_LEGACY_CONST char *new_language));

AL_LEGACY_FUNC(void, push_config_state, (void));
AL_LEGACY_FUNC(void, pop_config_state, (void));

AL_LEGACY_FUNC(void, hook_config_section, (AL_LEGACY_CONST char *section, AL_LEGACY_METHOD(int, intgetter, (AL_LEGACY_CONST char *, int)), AL_LEGACY_METHOD(AL_LEGACY_CONST char *, stringgetter, (AL_LEGACY_CONST char *, AL_LEGACY_CONST char *)), AL_LEGACY_METHOD(void, stringsetter, (AL_LEGACY_CONST char *, AL_LEGACY_CONST char *))));
AL_LEGACY_FUNC(int, config_is_hooked, (AL_LEGACY_CONST char *section));

AL_LEGACY_FUNC(AL_LEGACY_CONST char *, get_config_string, (AL_LEGACY_CONST char *section, AL_LEGACY_CONST char *name, AL_LEGACY_CONST char *def));
AL_LEGACY_FUNC(int, get_config_int, (AL_LEGACY_CONST char *section, AL_LEGACY_CONST char *name, int def));
AL_LEGACY_FUNC(int, get_config_hex, (AL_LEGACY_CONST char *section, AL_LEGACY_CONST char *name, int def));
AL_LEGACY_FUNC(float, get_config_float, (AL_LEGACY_CONST char *section, AL_LEGACY_CONST char *name, float def));
AL_LEGACY_FUNC(int, get_config_id, (AL_LEGACY_CONST char *section, AL_LEGACY_CONST char *name, int def));
AL_LEGACY_FUNC(char **, get_config_argv, (AL_LEGACY_CONST char *section, AL_LEGACY_CONST char *name, int *argc));
AL_LEGACY_FUNC(AL_LEGACY_CONST char *, get_config_text, (AL_LEGACY_CONST char *msg));

AL_LEGACY_FUNC(void, set_config_string, (AL_LEGACY_CONST char *section, AL_LEGACY_CONST char *name, AL_LEGACY_CONST char *val));
AL_LEGACY_FUNC(void, set_config_int, (AL_LEGACY_CONST char *section, AL_LEGACY_CONST char *name, int val));
AL_LEGACY_FUNC(void, set_config_hex, (AL_LEGACY_CONST char *section, AL_LEGACY_CONST char *name, int val));
AL_LEGACY_FUNC(void, set_config_float, (AL_LEGACY_CONST char *section, AL_LEGACY_CONST char *name, float val));
AL_LEGACY_FUNC(void, set_config_id, (AL_LEGACY_CONST char *section, AL_LEGACY_CONST char *name, int val));

AL_LEGACY_FUNC(int, list_config_entries, (AL_LEGACY_CONST char *section, AL_LEGACY_CONST char ***names));
AL_LEGACY_FUNC(int, list_config_sections, (AL_LEGACY_CONST char ***names));
AL_LEGACY_FUNC(void, free_config_entries, (AL_LEGACY_CONST char ***names));

#ifdef __cplusplus
   }
#endif

#endif          /* ifndef ALLEGRO_LEGACY_CONFIG_H */


