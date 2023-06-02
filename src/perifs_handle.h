#ifndef PERIFS_HANDLE_H
#define PERIFS_HANDLE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "colors.h"

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

extern struct rotation_t{
  _Bool is_r_pressed;
  int8_t r_knob_data; //-1 left backwards, 0 no change, +1 right forward
  _Bool is_g_pressed;
  int8_t g_knob_data;
  _Bool is_b_pressed;
  int8_t b_knob_data;
}rotation_t;

typedef struct{
  uint8_t r_cur; //red
  uint8_t r_prev;
  uint8_t g_cur; //green
  uint8_t g_prev;
  uint8_t b_cur; //blue
  uint8_t b_prev;
}knob_t;

extern union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer
extern uint8_t scaling;

void initMemory(void);

/*LCD section*/
void lcdReset(union rgb color);
void lcdRefresh(void);

/*knob section*/
void knobInit(void);
struct rotation_t updateKnobValues(void);

/*RGB LED section*/
void rgb1(union rgb color);
void rgb2(union rgb color);
void LEDStrip(int8_t change);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*PERIFS_HANDLE_H*/
