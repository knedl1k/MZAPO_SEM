#include "game_handle.h"

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "colors.h"
#include "drawing.h"
#include "perifs_handle.h"
#include "text_display.h"


extern struct rotation_t knobs;


// infinity while loop that will check the movement of the knobs (R for x, G for y). B press = if piece is picked, 
// give it back to the pack.

/* after quit from the game loop, return to the main menu. */
void gameReaction(void){
  _Bool quit=0;
  lcdReset(0xFFFF);
  drawBoard4(); //!EXAMPLE  
  manageStack(4,1,1,1);
  //knobs=updateKnobValues();

  while(! quit){
    knobs=updateKnobValues();
    quit=knobs.is_b_pressed;


    sleep(0.8);
  }
  






}
