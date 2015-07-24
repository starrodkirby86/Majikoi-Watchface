/*
*    Day of the Week
*    Bitmap layer to draw the day of the week.
*/

/*
* TODO:
*/

// Include
#include <pebble.h>
  
// Define Constants
#define W_X    4
#define W_Y    149
#define W_SIZE 16

// Initial Declarations
GBitmap *w_day;
static BitmapLayer *ly_w;
  
// Functions
void w_update_proc(void) {
  // Time structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  // Make buffer
  switch(tick_time->tm_wday) {
    case 0:
      w_day = gbitmap_create_with_resource(RESOURCE_ID_W_00_WHITE);
      break;
    case 1:
      w_day = gbitmap_create_with_resource(RESOURCE_ID_W_01_WHITE);
      break;
    case 2:
      w_day = gbitmap_create_with_resource(RESOURCE_ID_W_02_WHITE);  
      break;
    case 3:
      w_day = gbitmap_create_with_resource(RESOURCE_ID_W_03_WHITE);    
      break;
    case 4:
      w_day = gbitmap_create_with_resource(RESOURCE_ID_W_04_WHITE);   
      break;
    case 5:
      w_day = gbitmap_create_with_resource(RESOURCE_ID_W_05_WHITE);    
      break;
    default:
      w_day = gbitmap_create_with_resource(RESOURCE_ID_W_06_WHITE);
      break;
  }
  
}
  
  // Change the resource ID based off buffer_w

static void w_tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  w_update_proc();
}
  
// Load/Unload
void load_w(Window *window) {
  // Define boundaries and other formal housekeeping
  GRect bounds = GRect(W_X, W_Y, W_SIZE, W_SIZE);
  w_update_proc();
  
  // Create layer
  ly_w = bitmap_layer_create(bounds);
  
  // Assign image resource into bitmap layer
  bitmap_layer_set_bitmap(ly_w,w_day);
  
  // Assign to the window
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(ly_w));
}

void unload_w(void) {
  bitmap_layer_destroy(ly_w);
  gbitmap_destroy(w_day);
}