/*
*    Character Sprite
*    Character sprite management and animation.
*    Handles the character sprite.
*/

/*
* TODO:
*/

// INCLUDE
#include <pebble.h>

// DEFINE CONSTANTS
  
// INITIAL DECLARATIONS
GBitmap *ch_white;
GBitmap *ch_black;
BitmapLayer *ly_white;
BitmapLayer *ly_black;
  
// FUNCTIONS
  
// ANIMATION PROPERTIES  
  
// LOAD/UNLOAD
void load_ch_sprite(Window *window) {
  
  // Create white/black images
  ch_white = gbitmap_create_with_resource(RESOURCE_ID_S01_MIYAKO01_WHITE);
  ch_black = gbitmap_create_with_resource(RESOURCE_ID_S01_MIYAKO01_BLACK);
  //ly_white = bitmap_layer_create(GRect(0, 0, 208, 346));
  //bitmap_layer_set_bitmap(ly_white, ch_white);
    
  //layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(ly_white));
  
  // G Shape delcarations
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);    
  GPoint center = grect_center_point(&bounds);    
  GSize image_size = ch_white->bounds.size;
  GRect image_frame = GRect(center.x, center.y, image_size.w, image_size.h);
  image_frame.origin.x -= image_size.w / 2;
  image_frame.origin.y -= image_size.h / 2;
    
  // OK
  // Use GCompOpOr to display the white portions of the image
  ly_white = bitmap_layer_create(image_frame);
  bitmap_layer_set_bitmap(ly_white, ch_white);
  bitmap_layer_set_compositing_mode(ly_white, GCompOpOr);
  layer_add_child(window_layer, bitmap_layer_get_layer(ly_white));

  // Use GCompOpClear to display the black portions of the image
  ly_black = bitmap_layer_create(image_frame);
  bitmap_layer_set_bitmap(ly_black, ch_black);
  bitmap_layer_set_compositing_mode(ly_black, GCompOpClear);
  layer_add_child(window_layer, bitmap_layer_get_layer(ly_black));  
}

void unload_ch_sprite(void) {
    gbitmap_destroy(ch_white);
    bitmap_layer_destroy(ly_white);
    gbitmap_destroy(ch_black);
    bitmap_layer_destroy(ly_black);  
}