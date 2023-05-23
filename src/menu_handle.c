#include "menu_handle.h"

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

_Bool red_pressed=0;
_Bool green_pressed=0;
_Bool blue_pressed=0;


uint8_t renderMenu(void){
  prepare_lcd();
  fontString("APONGO",110,-300,WHITE,3);
  fontString("Press the knob to select",20,-220,WHITE,2);
  drawRectangleWithText("Play",30,-150,RED,2);
  drawRectangleWithText("Settings",140,-150,GREEN,2);
  drawRectangleWithText("Quit",350,-150,BLUE,2);
  lcd_frame();
  //wait for knob press
  return 0;
}

static uint8_t renderSettingsMenu(void){
  prepare_lcd();
  fontString("APONGO",110,-300,WHITE,3);
  fontString("Settings",20,-220,WHITE,2);
  drawRectangleWithText("Difficulty",30,-150,RED,2);
  drawRectangleWithText("Font",150,-150,GREEN,2);
  drawRectangleWithText("Back",350,-150,BLUE,2);
  lcd_frame();
  //wait for knob press
  return 0;
}

static void renderDiffMenu(void){
  prepare_lcd();
  fontString("APONGO",110,-300,WHITE,3);
  fontString("Choose your difficulty",20,-220,WHITE,2);
  drawRectangleWithText("Potato",30,-150,RED,2);
  drawRectangleWithText("Nightmare",150,-150,GREEN,2);
  drawRectangleWithText("Hell",350,-150,BLUE,2);
  lcd_frame();
  //wait for knob press
}

static uint8_t renderFontMenu(void){
  prepare_lcd();
  fontString("APONGO",110,-300,WHITE,3);
  fontString("Change font properties",20,-220,WHITE,2);
  drawRectangleWithText("Scaling",30,-150,RED,2);
  drawRectangleWithText("Type",150,-150,GREEN,2);
  drawRectangleWithText("Back",350,-150,BLUE,2);
  lcd_frame();
  //wait for knob press
  return 0;
}

void menuReaction(_Bool red, _Bool green, _Bool blue){
  //reacts on knob presses
  _Bool quit=0;
  _Bool start=0;
  uint8_t reaction=renderMenu();
  while(! quit){
    switch(reaction){
      case 0: break; //nothing is pressed, no reaction
      case 1:
        //start the game with set difficulty and font
        break;
      case 2:
        reaction=renderSettingsMenu();
        break;
      case 3:
        //quit the program
        break;
      case 11:
        renderDiffMenu();
        reaction=renderMenu();
        break;
      case 12:
        reaction=renderFontMenu();
      case 13:
        reaction=renderMenu();
        break;
      case 21:
        break;
      case 22:
        break;
      case 23:
        break;
    }

    
  }

}

