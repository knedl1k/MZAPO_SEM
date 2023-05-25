#include "text_display.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "mzapo_parlcd.h"
#include "font_types.h"
#include "perifs_handle.h"
#include "drawing.h"
#include "colors.h"

union rgb PRP={.r=255,.g=0,.b=255};

//union rgb BLACK={.r=255,.g=255,.b=255};

/*draws a character 'c' onto a framebuffer 'fb' at position (x, y), with a scaling factor*/
void printChar(char c, int x, int y, union rgb color,unsigned char scale){
  printf("%d %d\n",x,y);
  if(x<0 || x>=LCD_WIDTH || y<0 || y>LCD_HEIGHT){
    fprintf(stderr,"ERROR: OUT OF LCD RANGE\n");
    return;
  }
  //int color=0xffff;
  //Check if the character 'c' is within the range of characters defined by the font set 'font_rom8x16'
  if (c<font_rom8x16.firstchar || c >= (font_rom8x16.size+font_rom8x16.firstchar))
    //If the character is out of range, use the default character defined by the font set
    c=font_rom8x16.defaultchar;
  
  //Calculate the offset of the character 'c' from the first character in the font set, and get a pointer 'cb' to the bit representation of the character
  const int off=c-font_rom8x16.firstchar;
  const uint16_t *cb=font_rom8x16.bits+(font_rom8x16.height * off); //char bits
  
  //Iterate over each row and column of the character's bit representation
  for (unsigned short i=0; i<font_rom8x16.height; i++){
    for (unsigned short j=0; j<font_rom8x16.maxwidth; j++){
      
      //Check if the corresponding bit in the character's bit representation is set
      if (cb[i] & (0x1 << (font_rom8x16.height-1-j)) ){
        
        //Calculate the position of the corresponding pixel in the framebuffer, taking into account the scaling factor 'scale'
        int px=x+(j * scale);
        int py=y+(i * scale);
        
        //Iterate over a square of size 'scale x scale' and set the color of each pixel to black (represented by the hexadecimal value '0x0')
        for (unsigned short xi=0; xi<scale; xi++)
          for (unsigned short xj=0; xj<scale; xj++)
            //fb[px+xj][py+xi].d=color;
            color_pixel(color,py+xi,px+xj);
        
      }
    }
  }
}
/*prints inputted string starting from the coords with scaling*/
void printString(char *word, int x, int y,union rgb color, unsigned char scale){
  size_t chars=strlen(word); //gets the exact amount of chars to print
  int x_off=0, y_off=0;
  for(size_t i=0;i<chars;++i){
    printChar(word[i],x+x_off,y+y_off,color,scale);
    x_off+= font_rom8x16.maxwidth*scale;
  }
  lcdFrame(); //write to panel all changes from frame_buffer
}

void drawRectangleWithText(char *str, int x, int y, union rgb color,unsigned char scale, _Bool selected){
  size_t cChars=strlen(str);
  int x_off=x+10;
  int y_off=-y+3;
  printString(str,x+12,y+4,color,scale);

  drawRectangle(color,y,x,scale*font_rom8x16.height,scale*font_rom8x16.maxwidth*(cChars+1)); //
  if(selected)
    drawRectangle(PRP,y-5,x-5,scale*font_rom8x16.height+10,scale*font_rom8x16.maxwidth*(cChars+1)+10);
  lcdFrame();
}
