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

/*LCD section*/
void lcdInit(void);
void lcdReset(void);
void lcdFrame(void);

/*knob section*/
void knobInit(void);
uint32_t knobsVal(void);
uint8_t redKnobVal(void);
_Bool isRedPressed(void);
uint8_t greenKnobVal(void);
_Bool isGreenPressed(void);
uint8_t blueKnobVal(void);
_Bool isBluePressed(void);

/*RGB LED section*/
void rgb1(union rgb color);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*PERIFS_HANDLE_H*/
