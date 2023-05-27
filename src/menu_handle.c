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

union rgb RED = {.r=255, .g=0, .b=0};
union rgb GREEN = {.r=0, .g=255, .b=0};
union rgb BLUE = {.r=0, .g=0, .b=255};
union rgb WHITE={.r=255,.g=255,.b=255};
union rgb BLACK={.r=0,.g=0,.b=0};
//union rgb YLW={.r=255,.g=255,.b=0};

#define MAX_OPTIONS 2

extern struct rotation_t knobs;

<<<<<<< Updated upstream
void renderMenu(void){
  lcdReset();
  printString("APONGO",180,50,WHITE,3);
  printString("Navigate using red knob",60,220,WHITE,2);
  drawRectangleWithText("Play",30,150,RED,2,0);
  drawRectangleWithText("Settings",160,150,GREEN,2,1);
  drawRectangleWithText("Quit",360,150,BLUE,2,0);
  lcdFrame();
}

static uint8_t renderSettingsMenu(void){
  lcdReset();
  printString("APONGO",180,-300,WHITE,3);
  printString("Settings",60,-220,WHITE,2);
  drawRectangleWithText("Difficulty",30,-150,RED,2,0);
  drawRectangleWithText("Font",150,-150,GREEN,2,0);
  drawRectangleWithText("Back",350,-150,BLUE,2,0);
  lcdFrame();
  //wait for knob press
  return 0;
}

static void renderDiffMenu(void){
  lcdReset();
  printString("APONGO",180,-300,WHITE,3);
  printString("Choose your difficulty",60,-220,WHITE,2);
  drawRectangleWithText("Potato",30,-150,RED,2,0);
  drawRectangleWithText("Nightmare",150,-150,GREEN,2,0);
  drawRectangleWithText("Hell",350,-150,BLUE,2,0);
  lcdFrame();
  //wait for knob press
}

static uint8_t renderFontMenu(void){
  lcdReset();
  printString("APONGO",180,-300,WHITE,3);
  printString("Change font properties",60,-220,WHITE,2);
  drawRectangleWithText("Scaling",30,-150,RED,2,0);
  drawRectangleWithText("Type",150,-150,GREEN,2,0);
  drawRectangleWithText("Back",350,-150,BLUE,2,0);
  lcdFrame();
  //wait for knob press
  return 0;
=======
void renderMenu(uint8_t selected){
  if(selected>MAX_OPTIONS) return;
  //lcdReset();
  printString("APONGO",180,50,BLACK,3);
  printString("Navigate using green knob",40,220,BLACK,2);
  (selected==0)? drawRectangleWithText("Play",30,150,RED,2,1) : drawRectangleWithText("Play",30,150,RED,2,0);
  (selected==1)? drawRectangleWithText("Settings",160,150,GREEN,2,1) : drawRectangleWithText("Settings",160,150,GREEN,2,0);
  (selected==2)? drawRectangleWithText("Quit",360,150,BLUE,2,1) : drawRectangleWithText("Quit",360,150,BLUE,2,0);
  
  
  lcdRefresh();
}

static void renderSettingsMenu(uint8_t selected){
  if(selected>MAX_OPTIONS) return;
  //lcdReset();
  printString("APONGO",180,50,BLACK,3);
  printString("Settings",180,220,BLACK,2);
  (selected==0)? drawRectangleWithText("Difficulty",30,150,RED,2,1) : drawRectangleWithText("Difficulty",30,150,RED,2,0);
  (selected==1)? drawRectangleWithText("Font",230,150,GREEN,2,1) : drawRectangleWithText("Font",230,150,GREEN,2,0);
  (selected==2)? drawRectangleWithText("Back",350,150,BLUE,2,1) : drawRectangleWithText("Back",350,150,BLUE,2,0);
  lcdRefresh();
}

static void renderDiffMenu(uint8_t selected){
  if(selected>MAX_OPTIONS) return;
  //lcdReset();
  printString("APONGO",180,50,BLACK,3);
  printString("Choose your difficulty",80,220,BLACK,2);
  (selected==0)? drawRectangleWithText("Potato",30,150,RED,2,1) : drawRectangleWithText("Potato",30,150,RED,2,0);
  (selected==1)? drawRectangleWithText("Nightmare",170,150,GREEN,2,1) : drawRectangleWithText("Nightmare",170,150,GREEN,2,0);
  (selected==2)? drawRectangleWithText("Hell",350,150,BLUE,2,1) : drawRectangleWithText("Hell",350,150,BLUE,2,0);
  lcdRefresh();
}

static void renderFontMenu(uint8_t selected){
  if(selected>MAX_OPTIONS) return;
  //lcdReset();
  printString("APONGO",180,50,BLACK,3);
  printString("Font options",100,220,BLACK,2);
  (selected==0)? drawRectangleWithText("Scale 1",30,150,RED,2,1) : drawRectangleWithText("Scale 1",30,150,RED,2,0);
  (selected==1)? drawRectangleWithText("Scale 2",200,150,GREEN,2,1) : drawRectangleWithText("Scale 2",200,150,GREEN,2,0);
  (selected==2)? drawRectangleWithText("Back",350,150,BLUE,2,1) : drawRectangleWithText("Back",350,150,BLUE,2,0);
  lcdRefresh();
>>>>>>> Stashed changes
}

void menuReaction(void){
  //reacts on knob presses
  _Bool quit=0;
  renderMenu(0);
  int8_t rendered=0;
  int8_t selected=0;
  int8_t move;
  int8_t prev_move;
  
  
  while(! quit){
    prev_move=move;
    knobs=updateKnobValues();


    move=knobs.g_knob_data*(-1); //!ON OUR BOARD
    printf("move %d\n",move);
    if(prev_move!=move || move!=0){
      selected+= move; 
      if(selected>MAX_OPTIONS)
        selected=MAX_OPTIONS;
      else if(selected<0)
        selected=0;

      printf("selected%d\n",selected);
      switch(rendered){
        case 0:
          renderMenu(selected);
          break;
        case 1:
          renderSettingsMenu(selected);
          break;
        case 2:
          renderDiffMenu(selected);
          break;
        case 3:
          renderFontMenu(selected);
          break;
      }

    }
    

    //knobs=updateKnobValues();
    _Bool pressed=knobs.is_g_pressed;
    printf("pressed%d\n",pressed);
    int8_t new_selected=0;
    if(pressed){
      new_selected=0;
      if(rendered==0){ //main menu
        switch(selected){
          case 0:
            //start the game
            break;
          case 1:
            //render settings menu
            lcdReset();
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
            lcdReset();
            renderDiffMenu(new_selected);
            rendered=2;
            break;
          case 1:
            //render font menu
            lcdReset();
            renderFontMenu(new_selected);
            rendered=3;
            break;
          case 2:
            //back to main menu
            lcdReset();
            renderMenu(new_selected);
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
        lcdReset();
        renderMenu(selected); //return to main menu
        rendered=0;
      }else if(rendered==3){ //font menu
        switch(selected){
          case 0:
            //printString("Font options",100,220,BLACK,2);
            //drawFullRowBox(BLACK,30,150);
            //printString("Scaling level 1 set.",60,220,BLACK,2);
            break;
          case 1:
            //set scaling of all text to 2
            break;
          case 2:
            //back to main menu
            lcdReset();
            renderSettingsMenu(new_selected);
            rendered=1;
            break;
        }
      }
      selected=new_selected;
    }

    
    sleep(0.5);
  }
  

}

