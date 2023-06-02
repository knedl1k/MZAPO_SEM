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
#include "game_handle.h"

//union rgb WHITE={.r=255,.g=255,.b=255};
struct rotation_t knobs;
extern union rgb PRP;
extern union rgb WHT;
extern union rgb BLCK;
extern union rgb GRN;


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
  lcdReset(WHT);
  knobInit();
  LEDStrip(0);
  rgb1((union rgb){.r=0,.g=0,.b=0});
  rgb2((union rgb){.r=0,.g=0,.b=0});
  
  printf("Init completed.\n");

  
  menuReaction();

  //gameReaction();

  lcdRefresh();

  sleep(4);
  printf("The end of APONGO has come.\n");

  serialize_unlock(); /* Release the lock */
  return 0;
}
