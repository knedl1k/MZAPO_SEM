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

void prepare_lcd(void);
void lcd_frame(void);


#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*PERIFS_HANDLE_H*/
