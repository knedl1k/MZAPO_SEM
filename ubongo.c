/*******************************************************************
  Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

  ubongo.c     -main file


  (C) Copyright 2023 by SomiLotr & knedl1k
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "serialize_lock.h"
#include "font_types.h"

void *spiled_base;
void *parlcd_base;

union rgb{
  uint32_t d;
  struct{
    uint8_t b,g,r;
  };
};

void rgb1(union rgb color);
uint32_t knobs(void);
void lcd_frame(void);
void fbchar(char c,int x, int y, unsigned char scale);
void fontString(char *word, int x, int y, unsigned char scale);
void prepare_lcd(void);

#define LCD_HEIGHT 320
#define LCD_WIDTH 480

union pixel{
  uint16_t d; //data
  struct{
    int b:5;
    int g:6;
    int r:5;
  };
};

union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer




int main(int argc, char *argv[]){
  /* Serialize execution of applications */
  if (serialize_lock(1) <= 0){ /* Try to acquire lock the first */
    printf("System is occupied\n");
    if (1){ /* Wait till application holding lock releases it or exits */
      printf("Waitting\n");
      serialize_lock(0);
    }
  }
  
  parlcd_base=map_phys_address(PARLCD_REG_BASE_PHYS,PARLCD_REG_SIZE,0); //0=nechcem to cashovat  
  assert(parlcd_base !=NULL);
  parlcd_hx8357_init(parlcd_base);


  
  spiled_base=map_phys_address(SPILED_REG_BASE_PHYS,SPILED_REG_SIZE,0); //0=nechcem to cashovat
  assert(spiled_base!=NULL);

  rgb1((union rgb){.g=255});

  printf("Hello world\n");
  fontString("Hello World", 0, -200, 1);
  //while(1){
    //rgb1((union rgb){.d=knobs()});
  //}
  //printf("%d",font_rom8x16.maxwidth);
  sleep(4);

  printf("Goodbye world\n");

  
  serialize_unlock(); /* Release the lock */

  return 0;
}
/*initializes the LCD*/
void prepare_lcd(void){
  int background_color=0xffff;
  for(unsigned short i=0;i<LCD_HEIGHT;i++)
    for(unsigned short j=0;j<LCD_WIDTH;j++)
      fb[j][i].d=background_color;
  lcd_frame();
}
/*sets RGB1 to specified color*/
void rgb1(union rgb color){
  uint32_t *ptr=spiled_base+SPILED_REG_LED_RGB1_o;
  printf("rgb:%x\n",color.d );
  *ptr=color.d;
}
/*reteurns knobs value*/
uint32_t knobs(void){
  uint32_t *knobs=(spiled_base+SPILED_REG_KNOBS_8BIT_o);
  return *knobs;
}
/*writes all cached changes in frame buffer to LCD*/
void lcd_frame(void){
  parlcd_write_cmd(parlcd_base, 0x2c);
  for (unsigned short i=0; i<LCD_HEIGHT; i++){
    for (unsigned short j=0; j<LCD_WIDTH; j++){
      parlcd_write_data(parlcd_base, fb[j][i].d);
    }
  }
}
/*prints inputted string starting from the coords with scaling*/
void fontString(char *word, int x, int y, unsigned char scale){
  size_t chars=strlen(word); //gets the exact amount of chars to print
  int x_off=0, y_off=0;
  for(size_t i=0;i<chars;++i){
    fbchar(word[i],x+x_off,y+y_off,scale);
    x_off+= font_rom8x16.maxwidth*scale;
    y_off+= 0;
  }
  lcd_frame(); //write to panel all changes from frame_buffer
}


//This function draws a character 'c' onto a framebuffer 'fb' at position (x, y), with a scaling factor of 'scale'
void fbchar(char c, int x, int y, unsigned char scale){
  if(x<0 || x>=LCD_WIDTH || y>0 || y<-LCD_HEIGHT){
    printf("ERROR: OUT OF LCD RANGE");
    return;
  }
  int char_color=0x0;
  //Check if the character 'c' is within the range of characters defined by the font set 'font_rom8x16'
  if (c<font_rom8x16.firstchar || c >= (font_rom8x16.size+font_rom8x16.firstchar)){
    //If the character is out of range, use the default character defined by the font set
    c=font_rom8x16.defaultchar;
  }
  
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
        for (unsigned short xi=0; xi<scale; xi++){
          for (unsigned short xj=0; xj<scale; xj++){
            fb[px+xj][py+xi].d=char_color;
          }
        }
      }
    }
  }
}
