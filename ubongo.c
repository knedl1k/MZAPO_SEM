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

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "serialize_lock.h"
#include "font_types.h"
#include "parlcd_main.h"
#include "text_display.h"

void *spiled_base;

union rgb{
  uint32_t d;
  struct{
    uint8_t b,g,r;
  };
};

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
  
  spiled_base=map_phys_address(SPILED_REG_BASE_PHYS,SPILED_REG_SIZE,0); //0=nechcem to cashovat
  assert(spiled_base!=NULL);
  rgb1((union rgb){.b=255});

  printf("Hello world\n");
  fontString("World Hello", 0, -200, 1);
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

