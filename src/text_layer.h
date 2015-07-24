/*
*    Text Layer
*    This creates the text layer components of the watchface.
*    This pretty much helps us tell the time. WOW SO MODERN
*/

/*
* TODO:
* >> Perfect the coordinates, I guess.
*/

// INCLUDE
#include <pebble.h>

// DEFINE CONSTANTS AND STUFF 
#define TEXT_BOUND_X_H 2
#define TEXT_BOUND_Y_H 105
#define TEXT_BOUND_X_M 20
#define TEXT_BOUND_Y_M 123
#define TEXT_BOUND_W   42
#define TEXT_BOUND_H   42

// INITIAL DECLARATIONS  
TextLayer *text_clock_h;
TextLayer *text_clock_m;

// FUNKY FUNCTIONS
// LOL THE ALLITERATION

// update functions
void text_update_proc_time(void) {
  // Time structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  // Make buffer
  static char buffer_h[] = "00";
  static char buffer_m[] = "00";
  
  // In the buffer, we write the time (in separate strings of course)
  if(clock_is_24h_style()) {
    // 24hr format
    strftime(buffer_h, sizeof("00"), "%H", tick_time);
  } else {
    // 12hr format
    strftime(buffer_h, sizeof("00"), "%I", tick_time);
  }
  strftime(buffer_m, sizeof("00"), "%M", tick_time);
  
  // OK, now let's send this into the respective text layers.
  text_layer_set_text(text_clock_h, buffer_h);
  text_layer_set_text(text_clock_m, buffer_m);
}

// SOME TICK TOCK STUFF
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  text_update_proc_time();
  /*if(tick_time->tm_min == 0)
  {
    w_update_proc();
    ch_update_proc();
  }*/
}

// loading/unloading
void load_text_clock(Window *window) {
  // Bounds should be the same except for X, Y.
  GRect bounds_h = GRect(TEXT_BOUND_X_H,TEXT_BOUND_Y_H,TEXT_BOUND_W,TEXT_BOUND_H);
  GRect bounds_m = GRect(TEXT_BOUND_X_M,TEXT_BOUND_Y_M,TEXT_BOUND_W,TEXT_BOUND_H);
  GSize bounds_size = GSize(TEXT_BOUND_W, TEXT_BOUND_H);
  // Create layers
  text_clock_h = text_layer_create(bounds_h);
  text_clock_m = text_layer_create(bounds_m);
  // Properties
  // By nature, text properties should be the same too.
  text_layer_set_text_color(text_clock_h, GColorWhite);
  text_layer_set_text_color(text_clock_m, GColorWhite);
  text_layer_set_background_color(text_clock_h, GColorClear);
  text_layer_set_background_color(text_clock_m, GColorClear);
  text_layer_set_text_alignment(text_clock_h, GTextAlignmentCenter);
  text_layer_set_text_alignment(text_clock_m, GTextAlignmentCenter);
  text_layer_set_size(text_clock_h, bounds_size);
  text_layer_set_size(text_clock_m, bounds_size);
  text_layer_set_font(text_clock_h, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_font(text_clock_m, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  // Set Text
  // Will be in the update procedure, right?
  // Assign child
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_clock_h));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_clock_m));
}

void unload_text_clock(void) {
  text_layer_destroy(text_clock_h);
  text_layer_destroy(text_clock_m);
}