#include "menu_handle.h"

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "perifs_handle.h"
#include "drawing.h"
#include "text_display.h"
#include "colors.h"
#include "font_types.h"
#include "game_handle.h"

#define MAX_OPTIONS 2
uint8_t scaling=2;

extern union rgb PRP;
extern union rgb WHT;
extern union rgb BLCK;
extern union rgb GRN;
extern union rgb RED;
extern union rgb BLU;


static void renderMainMenu(uint8_t selected){
  if(selected>MAX_OPTIONS) return;
  //lcdReset(WHT);
  printString("APONGO",180,50,BLCK,scaling+1);
  printString("Navigate using green knob",40,220,BLCK,scaling);
  (selected==0)? drawRectangleWithText("Play",30,150,RED,scaling,1) : drawRectangleWithText("Play",30,150,RED,scaling,0);
  (selected==1)? drawRectangleWithText("Settings",160,150,GRN,scaling,1) : drawRectangleWithText("Settings",160,150,GRN,scaling,0);
  (selected==2)? drawRectangleWithText("Quit",360,150,BLU,scaling,1) : drawRectangleWithText("Quit",360,150,BLU,scaling,0); 
  lcdRefresh();
}

static void renderSettingsMenu(uint8_t selected){
  if(selected>MAX_OPTIONS) return;
  //lcdReset(WHT);
  printString("APONGO",180,50,BLCK,scaling+1);
  printString("Settings",180,220,BLCK,scaling);
  (selected==0)? drawRectangleWithText("Difficulty",30,150,RED,scaling,1) : drawRectangleWithText("Difficulty",30,150,RED,scaling,0);
  (selected==1)? drawRectangleWithText("Font",230,150,GRN,scaling,1) : drawRectangleWithText("Font",230,150,GRN,scaling,0);
  (selected==2)? drawRectangleWithText("Back",350,150,BLU,scaling,1) : drawRectangleWithText("Back",350,150,BLU,scaling,0);
  lcdRefresh();
}

static void renderDiffMenu(uint8_t selected){
  if(selected>MAX_OPTIONS) return;
  //lcdReset(WHT);
  printString("APONGO",180,50,BLCK,scaling+1);
  printString("Choose your difficulty",80,220,BLCK,scaling);
  (selected==0)? drawRectangleWithText("Potato",30,150,RED,scaling,1) : drawRectangleWithText("Potato",30,150,RED,scaling,0);
  (selected==1)? drawRectangleWithText("Nightmare",170,150,GRN,scaling,1) : drawRectangleWithText("Nightmare",170,150,GRN,scaling,0);
  (selected==2)? drawRectangleWithText("Hell",350,150,BLU,scaling,1) : drawRectangleWithText("Hell",350,150,BLU,scaling,0);
  lcdRefresh();
}

static void renderFontMenu(uint8_t selected, uint8_t rerender){
  if(selected>MAX_OPTIONS) return;
  //lcdReset(WHT);
  printString("APONGO",180,50,BLCK,scaling+1);
  if(rerender!=0){
    if(rerender==1)
      printString("Font scale has been set to 1.",30,220,BLCK,scaling);
    else if(rerender==2)
      printString("Font scale has been set to 2.",30,220,BLCK,scaling);
  }else
    printString("Font options",100,220,BLCK,scaling);
  
  (selected==0)? drawRectangleWithText("Scale 1",30,150,RED,scaling,1) : drawRectangleWithText("Scale 1",30,150,RED,scaling,0);
  (selected==1)? drawRectangleWithText("Scale 2",200,150,GRN,scaling,1) : drawRectangleWithText("Scale 2",200,150,GRN,scaling,0);
  (selected==2)? drawRectangleWithText("Back",350,150,BLU,scaling,1) : drawRectangleWithText("Back",350,150,BLU,scaling,0);
  lcdRefresh();
}

static void endScreen(void){
  lcdReset(BLCK);
}

void menuReaction(void){

  struct rotation_t knobs;

  _Bool quit=0;
  renderMainMenu(0);
  int8_t rendered=0;
  int8_t selected=0;
  int8_t move=0;
  int8_t prev_move=0;


  while(! quit){
    /* knob move response section */
    prev_move=move;
    knobs=updateKnobValues();

    move=knobs.g_knob_data*(-1); //!ON OUR BOARD
    printf("move %d\n",move);
    printf("r %d g %d b %d\n",knobs.r_knob_data,knobs.g_knob_data,knobs.b_knob_data);
    if(move!=0 || prev_move!=move){
      selected+= move; 
      if(selected>MAX_OPTIONS)
        selected=MAX_OPTIONS;
      else if(selected<0)
        selected=0;

      printf("selected%d\n",selected);
      switch(rendered){
        case 0:
          renderMainMenu(selected);
          break;
        case 1:
          renderSettingsMenu(selected);
          break;
        case 2:
          renderDiffMenu(selected);
          break;
        case 3:
          renderFontMenu(selected,0);
          break;
      }
    }
    /* knob press response section */
    _Bool pressed=knobs.is_g_pressed;
    printf("pressed%d\n",pressed);
    int8_t new_selected=0;
    if(pressed){
      new_selected=0;
      if(rendered==0){ //main menu
        switch(selected){
          case 0:
            //start the game
            gameReaction();
            //quit=1;
            break;
          case 1:
            //render settings menu
            lcdReset(WHT);
            renderSettingsMenu(new_selected);
            rendered=1;
            break;
          case 2:
            //quit the program
            quit=1;
            break;
        }
      }else if(rendered==1){ //settings menu
        switch(selected){
          case 0:
            //render diff menu
            lcdReset(WHT);
            renderDiffMenu(new_selected);
            rendered=2;
            break;
          case 1:
            //render font menu
            lcdReset(WHT);
            renderFontMenu(new_selected,0);
            rendered=3;
            break;
          case 2:
            //back to main menu
            lcdReset(WHT);
            renderMainMenu(new_selected);
            rendered=0;
            break;
        }
      }else if(rendered==2){ //difficulty menu
        switch(selected){
          case 0:
             //set difficulty to Potato
            break;
          case 1:
             //set difficulty to Nightmare
            break;
          case 2:
             //set difficulty to Hell
            break;
        }
        lcdReset(WHT);
        renderMainMenu(new_selected); //return to main menu
        rendered=0;
      }else if(rendered==3){ //font menu
        switch(selected){
          case 0:
            //set scaling of all text to 1
            scaling=1;
            lcdReset(WHT);
            renderFontMenu(new_selected,scaling);
            break;
          case 1:
            //set scaling of all text to 2
            scaling=2;
            lcdReset(WHT);
            renderFontMenu(new_selected,scaling);
            break;
          case 2:
            //back to main menu
            lcdReset(WHT);
            renderSettingsMenu(new_selected);
            rendered=1;
            break;
        }
      }
      selected=new_selected;
    } //knob response section end

    
    sleep(0.5);
  } //end while
  if(quit){
    endScreen();
    rgb1(BLCK);
    rgb2(BLCK);
  }
} //end of function

