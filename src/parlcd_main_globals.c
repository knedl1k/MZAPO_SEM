#include <stdint.h>

#define LCD_HEIGHT 320
#define LCD_WIDTH 480

void *parlcd_base;
union pixel{
  uint16_t d; //data
  struct{
    int b:5;
    int g:6;
    int r:5;
  };
}; 
union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer
