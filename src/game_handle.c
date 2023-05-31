#include "game_handle.h"

#include <stdint.h>
#include <stdio.h>
#include "colors.h"
#include "drawing.h"

int board[6][6];
#define MAX_X 4
#define MAX_Z 4

// function to render all available pieces for the given map

// infinity while loop that will check the movement of the knobs (R for x, G for y). B press = if piece is picked, 
// give it back to the pack.

void gameReaction(void){
  _Bool quit=0;
  renderMenu(0);
  int8_t rendered=0;
  int8_t move_x=0;
  int8_t prev_x=0;
  int8_t val_x=0;

  int8_t move_y=0;
  int8_t prev_y=0;
  int8_t val_y=0;

  int8_t rotate_z=0;
  int8_t prev_Z=0;
  int8_t val_z=0;
  
  
  while(! quit){
    /* knob move response section */
    //prev_move=move;
    knobs=updateKnobValues();

    move_x=knobs.r_knob_data;
    if(move_x!=0 || prev_x!=move_x){
      
      
      
    }
    prev_x=move_x;

    move_y=knobs.g_knob_data;
    if(move_y!=0 || prev_y!=move_y){
      
      if()
    }

    rotate_z=knobs.b_knob_data;
    if(rotate_z!=0 || prev_z!=rotate_z){
      val_z=(val_z+rotate_z)%MAX_Z; //values between 0-3 for rotation encode
      if()
    }

  }






}
