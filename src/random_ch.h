/*
*    Randomizer: Character
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
#define MAX_COUNT  8

// INITIAL DECLARATIONS  
  
// FUNCTIONS
  void randomize_ch(uint32_t *ch_white, uint32_t *ch_black) {
  
  // Set seed
  srand(time(NULL));  
  
  // Switch
  switch(rand() % MAX_COUNT) {
    case 0:
      *ch_white = RESOURCE_ID_CH_01_MOMO01_WHITE;
      *ch_black = RESOURCE_ID_CH_01_MOMO01_BLACK;
      break;
    case 1:
      *ch_white = RESOURCE_ID_CH_02_KAZUKO01_WHITE;
      *ch_black = RESOURCE_ID_CH_02_KAZUKO01_BLACK;
      break;
    case 2:
      *ch_white = RESOURCE_ID_CH_03_MIYAKO01_WHITE;
      *ch_black = RESOURCE_ID_CH_03_MIYAKO01_BLACK;
      break;
    case 3:
      *ch_white = RESOURCE_ID_CH_04_YUKIE01_WHITE;
      *ch_black = RESOURCE_ID_CH_04_YUKIE01_BLACK;
      break;
    case 4:
      *ch_white = RESOURCE_ID_CH_05_CHRIS01_WHITE;
      *ch_black = RESOURCE_ID_CH_05_CHRIS01_BLACK;
      break;
    case 5:
      *ch_white = RESOURCE_ID_CH_06_SHOU01_WHITE;
      *ch_black = RESOURCE_ID_CH_06_SHOU01_BLACK;
      break;
    case 6:
      *ch_white = RESOURCE_ID_CH_07_GAKU01_WHITE;
      *ch_black = RESOURCE_ID_CH_07_GAKU01_BLACK;
      break;
    case 7:
      *ch_white = RESOURCE_ID_CH_08_MORO01_WHITE;
      *ch_black = RESOURCE_ID_CH_08_MORO01_BLACK;
      break;
    default:
      *ch_white = RESOURCE_ID_CH_01_MOMO01_WHITE;
      *ch_black = RESOURCE_ID_CH_01_MOMO01_BLACK;
      break;
  }
  
  return;
}