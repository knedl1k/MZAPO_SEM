#include "game_handle.h"

#include <stdint.h>
#include <stdio.h>

#include "colors.h"
#include "drawing.h"
#include "perifs_handle.h"
#include "text_display.h"


extern struct rotation_t knobs;

// function to render all available pieces for the given map

// infinity while loop that will check the movement of the knobs (R for x, G for y). B press = if piece is picked, 
// give it back to the pack.

void gameReaction(void){
  _Bool quit=0;
  lcdReset(0xFFFF);
  drawBoard1(); //!EXAMPLE  
  manageStack(4,1,1,1);
  





}
