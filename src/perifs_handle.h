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

extern _Bool is_r_pressed;
extern _Bool is_g_pressed;
extern _Bool is_b_pressed;
extern uint8_t knob_data;
extern uint8_t r_knob_data;
extern uint8_t g_knob_data;
extern uint8_t b_knob_data;

/*LCD section*/
void lcdInit(void);
void lcdReset(void);
void lcdFrame(void);

/*knob section*/
void knobInit(void);
uint32_t knobsVal(void);
void updateKnobValues(void);

/*RGB LED section*/
void rgb1(union rgb color);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*PERIFS_HANDLE_H*/
