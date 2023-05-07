#ifndef PARLCD_MAIN_H
#define PARLCD_MAIN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void *parlcd_base; 

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
union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer

void prepare_lcd(void);
void lcd_frame(void);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*PARLCD_MAIN_H*/
