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
 *      Configuration defines for use with MacOS X.
 *
 *      By Angelo Mottola.
 *
 *      See readme.txt for copyright information.
 */


#ifndef ALOSXCFG_H
#define ALOSXCFG_H

/* Provide implementations of missing functions */
#define ALLEGRO_LEGACY_NO_STRICMP
#define ALLEGRO_LEGACY_NO_STRLWR
#define ALLEGRO_LEGACY_NO_STRUPR

/* Override default definitions for this platform */
#define AL_RAND()    ((rand() >> 16) & 0x7fff)

/* A static auto config */
#define ALLEGRO_LEGACY_HAVE_LIBPTHREAD 1
#define ALLEGRO_LEGACY_HAVE_DIRENT_H   1
#define ALLEGRO_LEGACY_HAVE_INTTYPES_H 1
#define ALLEGRO_LEGACY_HAVE_STDINT_H   1
#define ALLEGRO_LEGACY_HAVE_SYS_TIME_H 1
#define ALLEGRO_LEGACY_HAVE_SYS_STAT_H 1
#define ALLEGRO_LEGACY_HAVE_MKSTEMP    1

/* Describe this platform */
#define ALLEGRO_LEGACY_PLATFORM_STR  "MacOS X"
#define ALLEGRO_LEGACY_CONSOLE_OK
#define ALLEGRO_LEGACY_USE_CONSTRUCTOR
#define ALLEGRO_LEGACY_MULTITHREADED

/* Endianesse - different between Intel and PPC based Mac's */
#ifdef __LITTLE_ENDIAN__
   #define ALLEGRO_LEGACY_LITTLE_ENDIAN
#endif
#ifdef __BIG_ENDIAN__
   #define ALLEGRO_LEGACY_BIG_ENDIAN
#endif

/* Exclude ASM */

#ifndef ALLEGRO_LEGACY_NO_ASM
	#define ALLEGRO_LEGACY_NO_ASM
#endif

/* Arrange for other headers to be included later on */
#define ALLEGRO_LEGACY_EXTRA_HEADER     "allegro/platform/alosx.h"


#endif
