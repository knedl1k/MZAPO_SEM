#ifndef SERIALIZE_LOCK_H
#define SERIALIZE_LOCK_H

#include <stdint.h>

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


#ifdef __cplusplus
extern "C" {
#endif

void prepare_lcd(void);
void lcd_frame(void);
void fbchar(char c,int x, int y, unsigned char scale);
void fontString(char *word, int x, int y, unsigned char scale);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*SERIALIZE_LOCK_H*/

