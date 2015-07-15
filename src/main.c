/*
* Maji de Watashi ni Koishinasai! Watchface
*
* Utilizes sprites from Majikoi to make
* a fun and cute watchface for the Pebble.
*
*/

#include <pebble.h>
#include "watch_animation.h"

    
/*
* Define constants
*/
#define BOX_SIZE 20
#define ANIM_DURATION 500
#define ANIM_DELAY 300
    
/*
* DECLARATIONS
* Declaring layers...
*/
    
Window *my_window;
TextLayer *text_layer;
GBitmap *ch_white;
GBitmap *ch_black;
BitmapLayer *ly_white;
BitmapLayer *ly_black;

static Layer *s_box_layer;
static PropertyAnimation *s_box_animation;

static int s_current_stage = 0;

/*
* Animation function prototypes
*/
static void next_animation();

static void anim_stopped_handler(Animation *animation, bool finished, void *context) {
#ifdef PBL_PLATFORM_APLITE
  // Free the animation
  property_animation_destroy(s_box_animation);
#endif

  // Schedule the next one, unless the app is exiting
  if (finished) {
    next_animation();
  }
    
}

/* Defining next animation... */ 
static void next_animation() {
  // Determine start and finish positions
  GRect start, finish;
  switch (s_current_stage) {
    case 0:
      start = GRect(0, 0, BOX_SIZE, BOX_SIZE);
      finish = GRect(144 - BOX_SIZE, 0, BOX_SIZE, BOX_SIZE);
      break;
    case 1:
      start = GRect(144 - BOX_SIZE, 0, BOX_SIZE, BOX_SIZE);
      finish = GRect(144 - BOX_SIZE, 168 - BOX_SIZE, BOX_SIZE, BOX_SIZE);
      break;
    case 2:
      start = GRect(144 - BOX_SIZE, 168 - BOX_SIZE, BOX_SIZE, BOX_SIZE);
      finish = GRect(0, 168 - BOX_SIZE, BOX_SIZE, BOX_SIZE);
      break;
    case 3:
      start = GRect(0, 168 - BOX_SIZE, BOX_SIZE, BOX_SIZE);
      finish = GRect(0, 0, BOX_SIZE, BOX_SIZE);
      break;
    default:
      start = GRect(0, 0, BOX_SIZE, BOX_SIZE);
      finish = GRect(0, 0, BOX_SIZE, BOX_SIZE);
      break;
  }

  // Schedule the next animation
  s_box_animation = property_animation_create_layer_frame(s_box_layer, &start, &finish);
  animation_set_duration((Animation*)s_box_animation, ANIM_DURATION);
  animation_set_delay((Animation*)s_box_animation, ANIM_DELAY);
  animation_set_curve((Animation*)s_box_animation, AnimationCurveEaseInOut);
  animation_set_handlers((Animation*)s_box_animation, (AnimationHandlers) {
    .stopped = anim_stopped_handler
  }, NULL);
  animation_schedule((Animation*)s_box_animation);

  // Increment stage and wrap
  s_current_stage = (s_current_stage + 1) % 4;
}

/*
* FUNCTIONS HERE
*/

static void update_proc(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 4, GCornersAll);
}

void main_window_load(void) {        

  // Create white/black images
  ch_white = gbitmap_create_with_resource(RESOURCE_ID_S01_MIYAKO01_WHITE);
  ch_black = gbitmap_create_with_resource(RESOURCE_ID_S01_MIYAKO01_BLACK);
  //ly_white = bitmap_layer_create(GRect(0, 0, 208, 346));
  //bitmap_layer_set_bitmap(ly_white, ch_white);
    
  //layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(ly_white));
  
  // G Shape delcarations
  Layer *window_layer = window_get_root_layer(my_window);
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
    
  // Create Layer
  s_box_layer = layer_create(GRect(0, 0, BOX_SIZE, BOX_SIZE));
  layer_set_update_proc(s_box_layer, update_proc);
  layer_add_child(window_layer, s_box_layer);    
  
  // Include watch interface now...
  load_watch_interface(my_window);
}

void main_window_unload(void) {
    gbitmap_destroy(ch_white);
    bitmap_layer_destroy(ly_white);
    gbitmap_destroy(ch_black);
    bitmap_layer_destroy(ly_black);
    unload_watch_interface();
}

void handle_init(void) {
  my_window = window_create();
  main_window_load();
  window_stack_push(my_window, true);
  next_animation();
  watch_interface_animation_go();
}

void handle_deinit(void) {
  animation_unschedule_all();
  main_window_unload();
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}