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

static ALLEGRO_BITMAP * _a5_screen = NULL;

static BITMAP * a5_display_init(int w, int h, int vw, int vh, int color_depth)
{
    BITMAP * bp;

    bp = create_bitmap(w, h);
    if(bp)
    {
        _a5_display = al_create_display(w, h);
        if(_a5_display)
        {
            _a5_screen = al_create_bitmap(w, h);
            if(_a5_screen)
            {
                display_allegro_5.w = w;
                display_allegro_5.h = h;
                return bp;
            }
        }
        al_destroy_display(_a5_display);
        _a5_display = NULL;
    }
    return NULL;
}

static void a5_display_exit(BITMAP * bp)
{
    al_destroy_bitmap(_a5_screen);
    _a5_screen = NULL;
    al_destroy_display(_a5_display);
    _a5_display = NULL;
}

static void a5_display_vsync(void)
{
    al_wait_for_vsync();
}

static void a5_display_set_palette(const struct RGB * palette, int from, int to, int vsync)
{
}

static ALLEGRO_COLOR a5_get_color(PALETTE palette, int depth, int color)
{
    int r, g, b, a;

    if(palette)
    {
        return al_map_rgba_f((float)palette[color].r / 63.0, (float)palette[color].g / 63.0, (float)palette[color].b / 63.0, 1.0);
    }
    else
    {
        switch(depth)
        {
            case 15:
            {
                r = getr15(color);
                g = getg15(color);
                b = getb15(color);
                a = 0xFF;
                break;
            }
            case 16:
            {
                r = getr16(color);
                g = getg16(color);
                b = getb16(color);
                a = 0xFF;
                break;
            }
            case 24:
            {
                r = getr24(color);
                g = getg24(color);
                b = getb24(color);
                a = 0xFF;
                break;
            }
            case 32:
            {
                r = getr32(color);
                g = getg32(color);
                b = getb32(color);
                a = geta32(color);
                a = 0xFF;
                break;
            }
        }
    }

    return al_map_rgba(r, g, b, a);
}

void allegro_render_a5_bitmap(BITMAP * bp, ALLEGRO_BITMAP * a5bp)
{
    ALLEGRO_STATE old_state;
    PALETTE palette;
    int depth;
    int i, j;

    depth = bitmap_color_depth(bp);
    if(depth == 8)
    {
        get_palette(palette);
    }
    al_store_state(&old_state, ALLEGRO_STATE_TARGET_BITMAP);
    al_set_target_bitmap(a5bp);
    al_lock_bitmap(a5bp, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
    for(i = 0; i < bp->h; i++)
    {
        for(j = 0; j < bp->w; j++)
        {
            switch(depth)
            {
                case 8:
                {
                    al_put_pixel(j, i, a5_get_color(depth == 8 ? palette : NULL, depth, bp->line[i][j]));
                    break;
                }
                case 15:
                case 16:
                {
                    al_put_pixel(j, i, a5_get_color(depth == 8 ? palette : NULL, depth, ((short *)bp->line[i])[j]));
                    break;
                }
                case 24:
                case 32:
                {
                    al_put_pixel(j, i, a5_get_color(depth == 8 ? palette : NULL, depth, ((long *)bp->line[i])[j]));
                    break;
                }
            }
        }
    }
    al_unlock_bitmap(a5bp);
    al_restore_state(&old_state);
}

ALLEGRO_BITMAP * allegro_get_a5_bitmap(BITMAP * bp)
{
    ALLEGRO_BITMAP * bitmap;

    bitmap = al_create_bitmap(bp->w, bp->h);
    if(bitmap)
    {
        allegro_render_a5_bitmap(bp, bitmap);
        return bitmap;
    }
    return NULL;
}

void allegro_render_screen(void)
{
    allegro_render_a5_bitmap(screen, _a5_screen);
    al_draw_bitmap(_a5_screen, 0, 0, 0);
    al_flip_display();
}

GFX_DRIVER display_allegro_5 = {
   GFX_ALLEGRO_5,                     // int id;
   empty_string,                      // char *name;
   empty_string,                      // char *desc;
   "Allegro 5 Display",               // char *ascii_name;
   a5_display_init,   // AL_LEGACY_METHOD(struct BITMAP *, init, (int w, int h, int v_w, int v_h, int color_depth));
   a5_display_exit, //be_gfx_bwindowscreen_exit,         // AL_LEGACY_METHOD(void, exit, (struct BITMAP *b));
   NULL, //be_gfx_bwindowscreen_scroll,       // AL_LEGACY_METHOD(int, scroll, (int x, int y));
   a5_display_vsync, //be_gfx_vsync,                      // AL_LEGACY_METHOD(void, vsync, (void));
   a5_display_set_palette,  // AL_LEGACY_METHOD(void, set_palette, (struct RGB *p, int from, int to, int vsync));
   NULL, //be_gfx_bwindowscreen_request_scroll,// AL_LEGACY_METHOD(int, request_scroll, (int x, int y));
   NULL, //be_gfx_bwindowscreen_poll_scroll,  // AL_LEGACY_METHOD(int, poll_scroll, (void));
   NULL,                              // AL_LEGACY_METHOD(void, enable_triple_buffer, (void));
   NULL,                              // AL_LEGACY_METHOD(struct BITMAP *, create_video_bitmap, (int width, int height));
   NULL,                              // AL_LEGACY_METHOD(void, destroy_video_bitmap, (struct BITMAP *bitmap));
   NULL,                              // AL_LEGACY_METHOD(int, show_video_bitmap, (struct BITMAP *bitmap));
   NULL, //be_gfx_bwindowscreen_request_video_bitmap,// AL_LEGACY_METHOD(int, request_video_bitmap, (struct BITMAP *bitmap));
   NULL,                              // AL_LEGACY_METHOD(struct BITMAP *, create_system_bitmap, (int width, int height));
   NULL,                              // AL_LEGACY_METHOD(void, destroy_system_bitmap, (struct BITMAP *bitmap));
   NULL,                              // AL_LEGACY_METHOD(int, set_mouse_sprite, (struct BITMAP *sprite, int xfocus, int yfocus));
   NULL,                              // AL_LEGACY_METHOD(int, show_mouse, (struct BITMAP *bmp, int x, int y));
   NULL,                              // AL_LEGACY_METHOD(void, hide_mouse, (void));
   NULL,                              // AL_LEGACY_METHOD(void, move_mouse, (int x, int y));
   NULL,                              // AL_LEGACY_METHOD(void, drawing_mode, (void));
   NULL,                              // AL_LEGACY_METHOD(void, save_state, (void));
   NULL,                              // AL_LEGACY_METHOD(void, restore_state, (void));
   NULL,                              // AL_LEGACY_METHOD(void, set_blender_mode, (int mode, int r, int g, int b, int a));
   NULL, //be_gfx_bwindowscreen_fetch_mode_list,// AL_LEGACY_METHOD(int, fetch_mode_list, (void));
   0, 0,                              // int w, h;  /* physical (not virtual!) screen size */
   TRUE,                              // int linear;  /* true if video memory is linear */
   0,                                 // long bank_size;  /* bank size, in bytes */
   0,                                 // long bank_gran;  /* bank granularity, in bytes */
   0,                                 // long vid_mem;  /* video memory size, in bytes */
   0,                                 // long vid_phys_base;  /* physical address of video memory */
   FALSE                              // int windowed;  /* true if driver runs windowed */
};
