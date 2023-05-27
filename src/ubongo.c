/*******************************************************************
  Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

  ubongo.c     -main file


 (C) Copyright 2023 by SomiLotr & knedl1k
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include "perifs_handle.h"
#include "menu_handle.h"
#include "text_display.h"
#include "drawing.h"
#include "serialize_lock.h"
#include "colors.h"

//union rgb WHITE={.r=255,.g=255,.b=255};
struct rotation_t knobs;


int main(void){
  /* Serialize execution of applications */
  if(serialize_lock(1) <= 0){ /* Try to acquire lock the first */
    printf("System is occupied\n");
    if(1){ /* Wait till application holding lock releases it or exits */
      printf("Waitting\n");
      serialize_lock(0);
    }
  }

  initMemory();
  lcdReset();
  knobInit();
  //_Bool quit = 0;
  menuReaction();

  /* LCD SECTION */
  //printf("Hello world\n");
  //fontString("World Hello", 0, -200, 1);
  //drawSquare(-200, 200);
  //lcd_frame();
  // union rgb blue = {.r=0, .g=0, .b=255};
  //drawRectangle(blue,-100, 50, 200, 30); 
  // drawBoard1(40);

  //drawBoard4(40); 

<<<<<<< Updated upstream
  //lcd_frame();
  /*
    if you want to write on LCD display, change colors of pixels in fb[LCD_WIDTH][LCD_HEIGHT].d
    after that call lcd_frame(); which will write those changes onto the display
    example of it is in text_display.c file.
  */
=======
  //drawBoard4(40); 

  lcdRefresh();
>>>>>>> Stashed changes

  //renderMenu();
  
  
  /* KNOBS SECTION */
  
  fprintf(stderr,"red%hhd blue%hhd green%hhd\n",knobs.is_r_pressed,knobs.is_g_pressed,knobs.is_b_pressed);
  rgb1((union rgb){.g=255});
  sleep(4);
  while(1){
    knobs=updateKnobValues();
    printf("r %d, g %d, b %d\n", knobs.is_r_pressed,knobs.is_g_pressed,knobs.is_b_pressed);
    //rgb1((union rgb){.d=r_knob_data});
    sleep(1);
  }
  
  sleep(4);
  printf("Goodbye world\n");
  serialize_unlock(); /* Release the lock */
  return 0;
}


