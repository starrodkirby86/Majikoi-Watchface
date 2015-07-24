/*
*    Background Layer
*    A bitmap layer that handles the background of the Majikoi app.
*    Comes from the game's CGs.
*/

/* 
* TODO:
* >> Add random background update
*
*/


// INCLUDE
#include <pebble.h>
#include <random_bg.h>

// DEFINE CONSTANTS
  
// INITIAL DECLARATIONS 
GBitmap *bg;
static BitmapLayer *ly_bg;
bool isNewBGHour;
  
// FUNCTIONS
void background_update_proc(void) {
  /// Time structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  if(tick_time->tm_min == 0 && !isNewBGHour)
  {
    bg = gbitmap_create_with_resource(randomize_bg());
    isNewBGHour = 1;
  }
  else if(tick_time->tm_min > 0 && isNewBGHour)
  {
    isNewBGHour = 0;
  }
}
  
// LOADING/UNLOADING
void load_background(Window *window) {
  // Define boundaries and other formal housekeeping
  GRect bounds = layer_get_bounds(window_get_root_layer(window));
  bg = gbitmap_create_with_resource(randomize_bg());
  isNewBGHour = 0;
  
  // Create layer
  ly_bg = bitmap_layer_create(bounds);
  
  // Assign image resource into bitmap layer
  bitmap_layer_set_bitmap(ly_bg,bg);
  
  // Assign to the window
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(ly_bg));
}

void unload_background(void) {
  bitmap_layer_destroy(ly_bg);
  gbitmap_destroy(bg);
}