/*
* Maji de Watashi ni Koishinasai! Watchface
* Version 0.9
*
* Utilizes sprites from Majikoi to make
* a fun and cute watchface for the Pebble.
*
*/

/* TODO:
* >> character updating
*
*/

#include <pebble.h>
#include "background.h"
#include "ch_sprite.h"
#include "watch_animation.h"
#include "text_layer.h"
#include "week.h"

    
/*
* Define constants
*/
    
/*
* DECLARATIONS
* Declaring layers...
*/
    
Window *my_window;


/*
* FUNCTIONS HERE
*/

// SOME TICK TOCK STUFF
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  text_update_proc_time();
  if(tick_time->tm_min == 0)
  {
    w_update_proc();
    background_update_proc();
    //ch_update_proc(my_window);
  }
}

void main_window_load(void) {     
  
  // Load background here
  load_background(my_window);
  background_update_proc();
  
  // Load ch_sprite here
  load_ch_sprite(my_window);
  
  // Include watch interface now...
  load_watch_interface(my_window);
  load_w(my_window);
  
  // Timer stuff
  load_text_clock(my_window);
  text_update_proc_time();
}

void main_window_unload(void) {
    unload_watch_interface();
    unload_background();
    unload_ch_sprite();
    unload_w();
    unload_text_clock();
}

void handle_init(void) {
  
  // Main window load
  my_window = window_create();
  main_window_load();
  window_stack_push(my_window, true);
  
  
  // Interface load
  watch_interface_animation_go();
  //ch_animation_go();
  
  // Load tick timers
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

void handle_deinit(void) {  
  main_window_unload();
  window_destroy(my_window);  
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}