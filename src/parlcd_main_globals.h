#ifndef PARLCD_MAIN_GLOBALS_H
#define PARLCD_MAIN_GLOBALS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_HEIGHT 320
#define LCD_WIDTH 480

union pixel{
  uint16_t d; //data
  struct{
    int b:5;
    int g:6;
    int r:5;
  };
}; 

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*DRAWING_MAIN_H*/

