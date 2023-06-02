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
    (*boards[i])(); //!EXAMPLE  
    manageStack(i,1,1,1);

    rgb1(PRP);
    rgb2(BLCK);
    sleep(6);
    rgb2(GRN);
    rgb1(BLCK);
  }


  while(! quit){
    knobs=updateKnobValues();
    quit=knobs.is_b_pressed;
    LEDStrip(1);

    sleep(0.8);
    LEDStrip(-1);
  }
  

}
