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
  // menuReaction();

  /* LCD SECTION */
  printf("Hello world\n");


  // in the while loop, draws rotated shape according to which knob is being turned 
  int knobLeftState = 0; 
  int knobRightState = 1; 
  int shape[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}};
  int posX = 100; 
  int posY = 100; 
  int i = 0; 
  int* update = malloc(2 * sizeof(int)); 
  update[0] = posX; 
  update[1] = posY;  

  while ( i < 5){


    GetResult result = drawShapeBasedOnKnobs(shape, &posX, &posY, knobLeftState, knobRightState); 
    lcdRefresh();
    posX = result.posX; 
    posY = result.posY; 
    memcpy(shape, result.shape, 4 * 4 * sizeof(int));

    i++;
    
  }



  lcdRefresh();

  //renderMenu();
  
  
  /* KNOBS SECTION */
  /*
  fprintf(stderr,"red%hhd blue%hhd green%hhd\n",knobs.is_r_pressed,knobs.is_g_pressed,knobs.is_b_pressed);
  rgb1((union rgb){.g=255});
  sleep(4);
  while(1){
    knobs=updateKnobValues();
    printf("r %d, g %d, b %d\n", knobs.is_r_pressed,knobs.is_g_pressed,knobs.is_b_pressed);
    //rgb1((union rgb){.d=r_knob_data});
    sleep(1);
  }
  */
  sleep(4);
  printf("\nGoodbye world\n");
  serialize_unlock(); /* Release the lock */
  return 0;
}


