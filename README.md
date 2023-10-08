# Allegro Legacy

Port your Allegro 4 programs to modern systems using Allegro 5.

## Introduction

Allegro Legacy is a library that you can use in place of Allegro 4 to compile
your programs and run them on modern systems. It utilizes Allegro 5 to access
the system hardware, so it should theoretically run anywhere Allegro 5 can run.

## Features

* Full Allegro 4 API compatibility
* Additional functions to take advantage of Allegro 5 features

## How to Use

You will need to have Allegro 5 installed before you can build Allegro Legacy.
Your Allegro 5 build needs to have the audio add-on enabled. Once you have that
set up, you need to use CMake to generate the build scripts for your
development environment.

To build Allegro Legacy, you create a build directory somewhere and navigate to
it in the terminal. Then you type:

    cmake <path_to_allegro_legacy_source>
    make
    make install

Once you have Allegro Legacy installed, you can build your Allegro 4 program as
you normally would.

## API

Allegro Legacy exposes the entire Allegro 4 API and adds a few functions to
make it easier to upgrade your old projects. Below are all the additional
variables and functions that Allegro Legacy exposes:

* `ALLEGRO_LEGACY`  
  Defined so you can detect from your code whether or not it is being built
  with Allegro Legacy.
* `void all_disable_threaded_display(void)`  
  Disable the emulated display. Must be called before `set_gfx_mode()`. If you
  do this, you will need to add your own code to get graphics to render to the
  display.
* `ALLEGRO_DISPLAY * all_get_display(void)`  
  Get a pointer to the Allegro 5 display that is being used by Allegro Legacy.
  This variable is initialized during a call to `set_gfx_mode()`.
* `ALLEGRO_BITMAP * all_get_a5_bitmap(BITMAP * bp)`  
  Get an Allegro 5 `ALLEGRO_BITMAP * ` from an Allegro 4 `BITMAP *`.
* `void all_render_a5_bitmap(BITMAP * bp, ALLEGRO_BITMAP * a5bp)`  
  Render the Allegro 4 `BITMAP *` to the Allegro 5 `ALLEGRO_BITMAP *`.
* `void all_render_screen(void)`  
  Render the contents of `screen` to the display.
* `void all_set_display_transform(ALLEGRO_TRANSFORM * transform)`  
  Apply the transformation `transform` when rendering `screen` to the internal
  Allegro 5 display. Must be called after `set_gfx_mode()` for it to take
  effect. If you set the `ALLEGRO_FULLSCREEN_WINDOW` flag before setting the
  graphics mode, you can use this to inform Allegro Legacy how you want to scale
  `screen` to fill the display. Set the `ALLEGRO_MIN_LINEAR` and/or
  `ALLEGRO_MAG_LINEAR` new bitmap flags before calling `set_gfx_mode()` to
  enable bilinear filtering.
* `bool all_adjust_int(void * proc, double speed)`
  Adjust the speed of the underlying timer associated with `proc`. This makes
  it possible to take advantage of Allegro 5's more precise timer routines
  without requiring you to write a whole new timing loop. For example:

      intall_int_ex(increment_tick, BPS_TO_TIMER(60));
      #ifdef ALLEGRO_LEGACY
        all_adjust_int(increment_tick, 1.0 / 60.0);
      #endif

* `bool`` all_wait_for_int(void * proc)`
  Idle until the underlying timer associated with `proc` ticks. This makes it
  much easier to reduce CPU usage for Allegro 4 style timing loops since we can
  just add a call to this function to the top of the loop. For example:

      while(ticks > 0)
      {
        /* sleep until timer ticks */
        #ifdef ALLEGRO_LEGACY
          all_wait_for_int(increment_tick);
        #endif
        process_logic();
        ticks--;
        /* or yield when not using Allegro Legacy */
        #ifndef ALLEGRO_LEGACY
          yield_timeslice();
        #endif
      }

## Advanced Usage

Once you have your program up and running with Allegro Legacy, you may wish to
upgrade some aspects of it to take advantage of some of the enhancements that
Allegro 5 offers. Allegro Legacy lets you use both the Allegro 4 and Allegro 5
APIs at the same time.

One thing you may want to do is replace your old timing loops with Allegro 5
loops. This will allow your program to only use the amount of CPU time it
needs.

You can optimize your rendering if you are using a separate buffer instead of
rendering directly to `screen` using the following code:

    a5_backbuffer = al_get_backbuffer(all_get_display());
    all_render_a5_bitmap(a4_buffer, a5_backbuffer);
    al_flip_display();

## Compatibility Notes

Allegro Legacy does not support hacked graphics modes such as that used by the
ex12bit example. After looking into ex12bit not working, I decided the hacked
mode it uses is not officially part of the Allegro 4 API. The additional code to
support that specific mode could be added, but there may be other possible
hacked modes. There's no clean way to add support for these types of hacks.

## License

Allegro Legacy is licensed under the gift-ware license (see a4_readme.txt for
details). This means it can be used in any way that Allegro 4 can be used.
