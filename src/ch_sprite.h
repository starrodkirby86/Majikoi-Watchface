/*
*    Character Sprite
*    Character sprite management and animation.
*    Handles the character sprite.
*/

/*
* TODO:
* >> Animation doesn't work.
* >> The reasoning is a bit hazy. Maybe there isn't enough space?
*/

// INCLUDE
#include <pebble.h>
#include <random_ch.h>

// DEFINE CONSTANTS
#define CH_HORZOFFSET    0  
#define CH_VERTOFFSET    8
#define CH_ANIM_DURATION 500
  
// INITIAL DECLARATIONS
GBitmap *ch_white;
GBitmap *ch_black;
BitmapLayer *ly_white;
BitmapLayer *ly_black;

static PropertyAnimation *ani_wh;
static PropertyAnimation *ani_bl;

uint32_t wh_id;
uint32_t bl_id;

GRect bounds;

  
// FUNCTIONS
  
// ANIMATION PROPERTIES  
void wh_animation_started(Animation *animation, void *data) {
  
}

void wh_animation_stopped(Animation *animation, bool finished, void *data) {
  property_animation_destroy(ani_wh);
}

void bl_animation_started(Animation *animation, void *data) {
  
}

void bl_animation_stopped(Animation *animation, bool finished, void *data) {
  property_animation_destroy(ani_bl);
}

void ch_animation_go() {
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "begin animation jinkela");
  
  // Get information of bounds  
  GPoint center = grect_center_point(&bounds);    
  GSize image_size = ch_white->bounds.size;
  GRect image_frame = GRect(center.x, center.y, image_size.w, image_size.h);
  image_frame.origin.x -= image_size.w / 2;
  image_frame.origin.y -= image_size.h / 2;
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Got the bounds info");
  
  // White
  
  // This portion of code is the BEFORE->AFTER
  // for the character sprite.
  GRect from_frame = layer_get_frame(bitmap_layer_get_layer(ly_white));
  GRect to_frame = GRect(center.x, center.y, image_size.w, image_size.h);
  
  // The command itself
  ani_wh = property_animation_create_layer_frame(bitmap_layer_get_layer(ly_white), &from_frame, &to_frame);
  
  animation_set_handlers((Animation*) ani_wh, (AnimationHandlers) {
    .started = (AnimationStartedHandler) wh_animation_started,
    .stopped = (AnimationStoppedHandler) wh_animation_stopped,
  }, NULL);
  
  animation_set_duration((Animation*) ani_wh, CH_ANIM_DURATION);
  animation_set_curve((Animation*) ani_wh, AnimationCurveEaseInOut);
  animation_schedule((Animation*) ani_wh);
  
  // Black
  from_frame = layer_get_frame(bitmap_layer_get_layer(ly_black));
  to_frame = GRect(center.x, center.y, image_size.w, image_size.h);
  
  ani_bl = property_animation_create_layer_frame(bitmap_layer_get_layer(ly_black), &from_frame, &to_frame);
  
  animation_set_handlers((Animation*) ani_bl, (AnimationHandlers) {
    .started = (AnimationStartedHandler) bl_animation_started,
    .stopped = (AnimationStoppedHandler) bl_animation_stopped,
  }, NULL);
  
  animation_set_duration((Animation*) ani_bl, CH_ANIM_DURATION);
  animation_set_curve((Animation*) ani_bl, AnimationCurveEaseInOut);
  animation_schedule((Animation*) ani_bl);
}

  
// LOAD/UNLOAD
void load_ch_sprite(Window *window) {
  
  // Create white/black images
  randomize_ch(&wh_id,&bl_id);
  
  ch_white = gbitmap_create_with_resource(wh_id);
  ch_black = gbitmap_create_with_resource(bl_id);
  
  // G Shape delcarations
  Layer *window_layer = window_get_root_layer(window);
  bounds = layer_get_bounds(window_layer);    
  GPoint center = grect_center_point(&bounds);    
  GSize image_size = ch_white->bounds.size;
  GRect image_frame = GRect(center.x+CH_HORZOFFSET, center.y+CH_VERTOFFSET, image_size.w, image_size.h);
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