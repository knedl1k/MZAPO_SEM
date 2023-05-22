#include "render_menu.h"

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parlcd_main_globals.h"
#include "drawing.h"
#include "text_display.h"
#include "colors.h"
#include "font_types.h"

//#define FONT_OFFSET_X 35
//#define FONT_OFFSET_Y 45

//union rgb color;
//union rgb black = {.r = 0, .g = 0, .b = 0}; 
extern union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer

void drawRectangleWithText(char *str, int x, int y, int height, int width){
  union rgb coloring={.r = 0, .g = 0, .b = 0};
  int scale=2;
  size_t cChars=strlen(str);
  int x_off=x+font_rom8x16.maxwidth*scale;
  for(size_t i=0;i<cChars;++i){
    fprintf(stderr,"pisu %c\n",str[i]);
    fbchar(str[i],x_off,y,scale);
    x_off+=font_rom8x16.maxwidth*scale;
    //y_off+=(-1)*y;
  }

  drawRectangle(coloring,x,y,scale*font_rom8x16.height,scale*font_rom8x16.maxwidth*cChars); //
  //fontString(str, (1), (-1)*(y+FONT_OFFSET_Y), 2); // 1 should be replaced with scale var
}

