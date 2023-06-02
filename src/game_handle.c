#include "game_handle.h"

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "colors.h"
#include "drawing.h"
#include "perifs_handle.h"
#include "text_display.h"
#include "maps.h"

extern struct rotation_t knobs;

extern union rgb PRP;
extern union rgb WHT;
extern union rgb BLCK;
extern union rgb GRN;

/* after quit from the game loop, return to the main menu. */
void gameReaction(void){
  _Bool quit=0;
  lcdReset(WHT);
  void (*boards[6])() = {drawBoard1, drawBoard2, drawBoard3,drawBoard4,drawBoard5,drawBoard6};  
 
  //knobs=updateKnobValues();
  for(uint8_t i=0;i<6;++i){
    lcdReset(WHT);
    (*boards[i])();
    manageStack(i,1,1,1);

    rgb1(PRP);
    rgb2(BLCK);
    
    sleep(3);
    (i%2)? LEDStrip(0xFF00FF00) : LEDStrip(0x00FF00FF);
    rgb2(GRN);
    rgb1(BLCK);
  }

  lcdReset(WHT);

  // in the while loop, draws rotated shape according to which knob is being turned 
  int knobLeftState = 0; 
  int knobRightState = 1; 
  int shape[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}};
  int posX = 100; 
  int posY = 60; 
  int i = 0; 
  int* update = malloc(2 * sizeof(int)); 
  update[0] = posX; 
  update[1] = posY;  

  while ( i < 3){
    lcdReset(WHT);
    GetResult result = drawShapeBasedOnKnobs(shape, &posX, &posY, knobLeftState, knobRightState);
    
    lcdRefresh();
    posX = result.posX; 
    posY = result.posY; 
    memcpy(shape, result.shape, 4*4*sizeof(int));
    i+=1;
    
    sleep(3);
    (i%2)? LEDStrip(0x0F0F0F0F) : LEDStrip(0xF0F0F0F0);
  }

  lcdReset(BLCK);

  printString("Press blue knob to leave.",30,150,WHT,2);

  while(! quit){
    knobs=updateKnobValues();
    quit=knobs.is_b_pressed;


    sleep(0.8);
  }
  

}
