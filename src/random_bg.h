/*
*    Randomizer: BG
*    Randomizer for the character on the watchface.
*
*/

/*
* TODO:
* >>
*/

// INCLUDE
#include <pebble.h>

// CONSTANTS
#define MAX_BG_COUNT  5

// INITIAL DECLARATIONS  
  
// FUNCTIONS
uint32_t randomize_bg(void) {
  
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "random count: %d", rand() % 300);

  // Set seed
  srand(time(NULL));  
  
  // Switch
  switch(rand() % MAX_BG_COUNT) {
    case 0:
      return RESOURCE_ID_BG_01;
    case 1:
      return RESOURCE_ID_BG_02;
    case 2:
      return RESOURCE_ID_BG_03;
    case 3:
      return RESOURCE_ID_BG_04;
    case 4:
      return RESOURCE_ID_BG_05;  
    default:
      return RESOURCE_ID_BG_01;
  }
}