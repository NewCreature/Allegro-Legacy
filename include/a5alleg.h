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
 *      The Be Allegro Header File.
 *
 *      Aren't you glad you used the BeOS header file?
 *      Don't you wish everybody did?
 *
 *      By Jason Wilkins.
 *
 *      See readme.txt for copyright information.
 */

#ifndef A5_ALLEGRO_LEGACY_H
#define A5_ALLEGRO_LEGACY_H

AL_VAR(ALLEGRO_DISPLAY *, _a5_display);
AL_FUNC(ALLEGRO_BITMAP *, allegro_get_a5_bitmap, (BITMAP * bp));
AL_FUNC(void, allegro_render_a5_bitmap, (BITMAP * bp, ALLEGRO_BITMAP * a5bp));
AL_FUNC(void, allegro_render_screen, (void));

#endif /* ifndef A5_ALLEGRO_LEGACY_H */
