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

void *spiled_base;

void rgb1(union rgb color);
uint32_t knobs(void);

int main(void){
  /* Serialize execution of applications */
  if(serialize_lock(1) <= 0){ /* Try to acquire lock the first */
    printf("System is occupied\n");
    if(1){ /* Wait till application holding lock releases it or exits */
      printf("Waitting\n");
      serialize_lock(0);
    }
  }

  prepare_lcd(); //starts up LCD and sets default background
  
  _Bool red=0;
  _Bool green=0;
  _Bool blue=0;

  /* LCD SECTION */
  renderMenu();
  int num;
  scanf("%d",&num);
  if(num==1) red=1;
  else if(num==2) green=1;
  else blue=1;
  menuReaction(red,green,blue);
  
  //drawSquare(-200, 200);
  lcd_frame();
  //union rgb blue = {.r=0, .g=0, .b=255};
  //drawRectangle(blue,50,-200,50,70);
  //lcd_frame();
  //drawRectangle(blue,-200, 150, 200, 30);
  //lcd_frame();
  //drawRectangleWithText("Play",200, -150,blue,2);
  //lcd_frame();

  
  //fontString("Volba 1",-200,200,2);
  /*
    if you want to write on LCD display, change colors of pixels in fb[LCD_WIDTH][LCD_HEIGHT].d
    after that call lcd_frame(); which will write those changes onto the display
    example of it is in text_display.c file.
  */
  
  
  /* KNOBS SECTION */
  //spiled_base=map_phys_address(SPILED_REG_BASE_PHYS,SPILED_REG_SIZE,0); //0=nechcem to cashovat
  //assert(spiled_base!=NULL);
  //rgb1((union rgb){.b=255});
  //while(1){
    //rgb1((union rgb){.d=knobs()});
  //}
  //printf("%d",font_rom8x16.maxwidth);

  sleep(4);
  printf("Goodbye world\n");
  serialize_unlock(); /* Release the lock */
  return 0;
}

/*sets RGB1 to specified color*/
void rgb1(union rgb color){
  uint32_t *ptr=spiled_base+SPILED_REG_LED_RGB1_o;
  printf("rgb:%x\n",color.d );
  *ptr=color.d;
}
/*reteurns knobs value*/
uint32_t knobs(void){
  uint32_t *knobs=(spiled_base+SPILED_REG_KNOBS_8BIT_o);
  return *knobs;
}
