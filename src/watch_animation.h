/*
*    Watch Animation
*    This is specifically to create the watch portion
*    of the watchface.
*/

/*
* TODO:
* The animation currently works with only one circle.
* >> Make it generalized so that multiple circles can be drawn by this method.
* >> Organize and make the code PRETTY.
*/

// INCLUDE
#include <pebble.h>

    
// DEFINE CONSTANTS
#define WATCH_ANIM_DURATION 500
#define WATCH_ANIM_DELAY 300

#define MAIN_CIRCLE_X 8
#define MAIN_CIRCLE_Y 112
#define MAIN_CIRCLE_W 48
#define MAIN_CIRCLE_H 48  
  
// INITIAL DECLARATIONS
static Layer *ly_watch;
static PropertyAnimation *ani_circles;
  
// FUNCTIONS
void watch_interface_animation_started(Animation *animation, void *data) {
  
}

void watch_interface_animation_stopped(Animation *animation, bool finished, void *data) {
  property_animation_destroy(ani_circles);
}

void watch_interface_animation_go(void) {
  GRect from_frame = layer_get_frame(ly_watch);
  GRect to_frame = GRect(8, 112, MAIN_CIRCLE_W, MAIN_CIRCLE_H);
  
  ani_circles = property_animation_create_layer_frame(ly_watch, &from_frame, &to_frame);
  
  animation_set_handlers((Animation*) ani_circles, (AnimationHandlers) {
    .started = (AnimationStartedHandler) watch_interface_animation_started,
    .stopped = (AnimationStoppedHandler) watch_interface_animation_stopped,
  }, NULL);
  
  animation_set_duration((Animation*) ani_circles, WATCH_ANIM_DURATION);
  animation_set_curve((Animation*) ani_circles, AnimationCurveEaseInOut);
  animation_schedule((Animation*) ani_circles);
  
}

void watch_interface_draw_circle(GContext *ctx, GRect bounds) {
  graphics_context_set_fill_color(ctx, GColorBlack);
  int16_t half_h = bounds.size.h / 2;
  graphics_fill_circle(ctx, GPoint(half_h, half_h), half_h);
}

void watch_update(Layer *layer, GContext *ctx) {
  watch_interface_draw_circle(ctx, layer_get_bounds(layer));
}

void load_watch_interface(Window *window) {
  // This actually loads the drawing into existance.
  GRect grect_watch_base = GRect(MAIN_CIRCLE_X+MAIN_CIRCLE_W/2, MAIN_CIRCLE_Y+MAIN_CIRCLE_H/2, 0, 0);
  ly_watch = layer_create(grect_watch_base);
  layer_set_update_proc(ly_watch, watch_update);
  layer_add_child(window_get_root_layer(window), ly_watch);
}

void unload_watch_interface(void) {
  layer_destroy(ly_watch);
}