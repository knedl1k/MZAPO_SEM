#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>


#include "text_display.h"
#include "font_types.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

/*initializes the LCD*/
void prepare_lcd(void){
  parlcd_base=map_phys_address(PARLCD_REG_BASE_PHYS,PARLCD_REG_SIZE,0); //0=nechcem to cashovat  
  assert(parlcd_base !=NULL);
  parlcd_hx8357_init(parlcd_base);
  int background_color=0xffff;
  for(unsigned short i=0;i<LCD_HEIGHT;i++)
    for(unsigned short j=0;j<LCD_WIDTH;j++)
      fb[j][i].d=background_color;
  lcd_frame();
}
/*writes all cached changes in frame buffer to LCD*/
void lcd_frame(void){
  parlcd_write_cmd(parlcd_base, 0x2c);
  for (unsigned short i=0; i<LCD_HEIGHT; i++)
    for (unsigned short j=0; j<LCD_WIDTH; j++)
      parlcd_write_data(parlcd_base, fb[j][i].d);

  printf("zapisuju\n");
}
/*draws a character 'c' onto a framebuffer 'fb' at position (x, y), with a scaling factor*/
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
/*prints inputted string starting from the coords with scaling*/
void fontString(char *word, int x, int y, unsigned char scale){
  size_t chars=strlen(word); //gets the exact amount of chars to print
  int x_off=0, y_off=0;
  for(size_t i=0;i<chars;++i){
    printf("pisu pismeno %c\n",word[i]);
    fbchar(word[i],x+x_off,y+y_off,scale);
    x_off+= font_rom8x16.maxwidth*scale;
    y_off+= 0;
  }
  lcd_frame(); //write to panel all changes from frame_buffer
}

