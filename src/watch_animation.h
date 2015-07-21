/*
*    Watch Animation
*    This is specifically to create the circular portions
*    of the watchface.
*/

/*
* TODO:
* >> Organize and make the code PRETTY.
* >> There's like three circles and tons of functions that do the same thing but have subtle name changes...
* >> >> Can't we do something about that?
*/

// INCLUDE
#include <pebble.h>

    
// DEFINE CONSTANTS
#define WATCH_ANIM_DURATION 500
#define WATCH_ANIM_DELAY 300

#define MAIN_CIRCLE_X 3
#define MAIN_CIRCLE_Y 105
#define MAIN_CIRCLE_W 42
#define MAIN_CIRCLE_H 42
  
#define SUB_CIRCLE_X  18
#define SUB_CIRCLE_Y  120
#define SUB_CIRCLE_W  42
#define SUB_CIRCLE_H  42
  
#define KO_CIRCLE_X   4
#define KO_CIRCLE_Y   149
#define KO_CIRCLE_W   16
#define KO_CIRCLE_H   16
  
// INITIAL DECLARATIONS
static Layer *ly_watch;
static Layer *ly_sub_watch;
static Layer *ly_ko_watch;

static PropertyAnimation *ani_circles;
static PropertyAnimation *ani_sub_circles;
static PropertyAnimation *ani_ko_circles;
  
// FUNCTIONS

// ANIMATION BASED FUNCTIONS
void watch_interface_animation_started(Animation *animation, void *data) {
  
}

void watch_interface_animation_stopped(Animation *animation, bool finished, void *data) {
  property_animation_destroy(ani_circles);
}

void sub_watch_interface_animation_started(Animation *animation, void *data) {
  
}

void sub_watch_interface_animation_stopped(Animation *animation, bool finished, void *data) {
  property_animation_destroy(ani_sub_circles);
}

void ko_watch_interface_animation_started(Animation *animation, void *data) {
  
}

void ko_watch_interface_animation_stopped(Animation *animation, bool finished, void *data) {
  property_animation_destroy(ani_ko_circles);
}

void watch_interface_animation_go(void) {
  // This portion of code is the BEFORE->AFTER
  // for the circle shape.
  GRect from_frame = layer_get_frame(ly_watch);
  GRect to_frame = GRect(MAIN_CIRCLE_X, MAIN_CIRCLE_Y, MAIN_CIRCLE_W, MAIN_CIRCLE_H);
  
  // The command itself
  ani_circles = property_animation_create_layer_frame(ly_watch, &from_frame, &to_frame);
  
  animation_set_handlers((Animation*) ani_circles, (AnimationHandlers) {
    .started = (AnimationStartedHandler) watch_interface_animation_started,
    .stopped = (AnimationStoppedHandler) watch_interface_animation_stopped,
  }, NULL);
  
  animation_set_duration((Animation*) ani_circles, WATCH_ANIM_DURATION);
  animation_set_curve((Animation*) ani_circles, AnimationCurveEaseInOut);
  animation_schedule((Animation*) ani_circles);
  
  // That was for the first one though.
  // Let's do the sub-circle.
  from_frame = layer_get_frame(ly_sub_watch);
  to_frame = GRect(SUB_CIRCLE_X, SUB_CIRCLE_Y, SUB_CIRCLE_W, SUB_CIRCLE_H);
  
  // The command itself.
  ani_sub_circles = property_animation_create_layer_frame(ly_sub_watch, &from_frame, &to_frame);
  
  animation_set_handlers((Animation*) ani_sub_circles, (AnimationHandlers) {
    .started = (AnimationStartedHandler) sub_watch_interface_animation_started,
    .stopped = (AnimationStoppedHandler) sub_watch_interface_animation_stopped,
  }, NULL);
  
  animation_set_duration((Animation*) ani_sub_circles, WATCH_ANIM_DURATION);
  animation_set_curve((Animation*) ani_sub_circles, AnimationCurveEaseInOut);
  animation_schedule((Animation*) ani_sub_circles);  
  
  // Now this one is for the kawaii circle.
  from_frame = layer_get_frame(ly_ko_watch);
  to_frame = GRect(KO_CIRCLE_X, KO_CIRCLE_Y, KO_CIRCLE_W, KO_CIRCLE_H);
  
  // The command itself.
  ani_ko_circles = property_animation_create_layer_frame(ly_ko_watch, &from_frame, &to_frame);
  
  animation_set_handlers((Animation*) ani_ko_circles, (AnimationHandlers) {
    .started = (AnimationStartedHandler) ko_watch_interface_animation_started,
    .stopped = (AnimationStoppedHandler) ko_watch_interface_animation_stopped,
  }, NULL);
  
  animation_set_duration((Animation*) ani_ko_circles, WATCH_ANIM_DURATION);
  animation_set_curve((Animation*) ani_ko_circles, AnimationCurveEaseInOut);
  animation_schedule((Animation*) ani_ko_circles);    
  
}

// OTHER FUNCTIONS I GUESS LOL

void watch_interface_draw_circle(GContext *ctx, GRect bounds) {
  graphics_context_set_fill_color(ctx, GColorBlack);
  int16_t half_h = bounds.size.h / 2;
  graphics_fill_circle(ctx, GPoint(half_h, half_h), half_h);
}

void watch_update(Layer *layer, GContext *ctx) {
  watch_interface_draw_circle(ctx, layer_get_bounds(layer));
}

// LOADING/UNLOADING

void load_watch_interface(Window *window) {
  // This actually loads the drawing into existance.
  // Loading main circle
  GRect grect_watch_base = GRect(MAIN_CIRCLE_X+MAIN_CIRCLE_W/2, MAIN_CIRCLE_Y+MAIN_CIRCLE_H/2, 0, 0);
  ly_watch = layer_create(grect_watch_base);
  layer_set_update_proc(ly_watch, watch_update);
  layer_add_child(window_get_root_layer(window), ly_watch);
  // Loading sub circle
  grect_watch_base = GRect(SUB_CIRCLE_X+SUB_CIRCLE_W/2, SUB_CIRCLE_Y+SUB_CIRCLE_H/2, 0, 0);
  ly_sub_watch = layer_create(grect_watch_base);
  layer_set_update_proc(ly_sub_watch, watch_update);
  layer_add_child(window_get_root_layer(window), ly_sub_watch);
  // Loading ko circle
  grect_watch_base = GRect(KO_CIRCLE_X+KO_CIRCLE_W/2, KO_CIRCLE_Y+KO_CIRCLE_H/2, 0, 0);
  ly_ko_watch = layer_create(grect_watch_base);
  layer_set_update_proc(ly_ko_watch, watch_update);
  layer_add_child(window_get_root_layer(window), ly_ko_watch);
}

void unload_watch_interface(void) {
  layer_destroy(ly_watch);
  layer_destroy(ly_sub_watch);
  layer_destroy(ly_ko_watch);
}