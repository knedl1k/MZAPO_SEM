/*******************************************************************
  Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

  change_me.c      - main file

  include your name there and license for distribution.

  Remove next text: This line should not appear in submitted
  work and project name should be change to match real application.
  If this text is there I want 10 points subtracted from final
  evaluation.

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

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
void fbchar(char c,int x, int y, int scale);


union pixel{
  uint16_t d; //data
  struct{
    int b:5;
    int g:6;
    int r:5;
  };
};

union pixel fb[480][320]; //frame buffer


// MOJE 


void color_pixel(union rgb color, int x, int y) {
  fb[y][x].r = color.r;
  fb[y][x].g = color.g;
  fb[y][x].b = color.b;
}

union rgb red = {.r = 255, .g = 0, .b = 0}; 
union rgb black = {.r = 0, .g = 0, .b = 0}; 

void drawRectangle(union rgb color, int x, int y, int width, int height){ 
    // top and bottom edge 
    for (int i = x; i < x + width; i++){ 
      color_pixel(color, i, y); 
      color_pixel(color, i, y+1); 
      color_pixel(color, i, y+2); 
      color_pixel(color, i, y+3); 
      color_pixel(color, i, y+4); 

      color_pixel(color, i+4, y + height); 
      color_pixel(color, i+4, y + height+1); 
      color_pixel(color, i+4, y + height+2); 
      color_pixel(color, i+4, y + height+3); 
      color_pixel(color, i+4, y + height+4); 

    }
    // left and right edge 
    for (int i = y; i < y + height; i++){ 
      color_pixel(color, x, i); 
      color_pixel(color, x+1, i); 
      color_pixel(color, x+2, i); 
      color_pixel(color, x+3, i); 
      color_pixel(color, x+4, i); 

      color_pixel(color, x + width, i); 
      color_pixel(color, x + width+1, i); 
      color_pixel(color, x + width+2, i); 
      color_pixel(color, x + width+3, i); 
      color_pixel(color, x + width+4, i); 

    }
}

int edge = 40; 

void drawSquare(int x, int y){
  // edge = hrana čtverečků, ze kterých budou sestávat dílky, asi se nastavi defaultne 
    // top and bottom edge 
    for (int i = x; i < x + edge; i++){ 
      color_pixel(black, i, y); 
      color_pixel(black, i, y+1); 
      color_pixel(black, i, y+2); 
      color_pixel(black, i, y+3); 
      color_pixel(black, i, y+4); 

      color_pixel(black, i, y + edge); 
      color_pixel(black, i, y + edge+1); 
      color_pixel(black, i, y + edge+2); 
      color_pixel(black, i, y + edge+3); 
      color_pixel(black, i, y + edge+4); 

    }
    // left and right edge 
    for (int i = y; i < y + edge; i++){ 
      color_pixel(black, x, i); 
      color_pixel(black, x+1, i); 
      color_pixel(black, x+2, i); 
      color_pixel(black, x+3, i); 
      color_pixel(black, x+4, i); 

      color_pixel(black, x + edge, i); 
      color_pixel(black, x + edge+1, i);
      color_pixel(black, x + edge+2, i);
      color_pixel(black, x + edge+3, i); 
      color_pixel(black, x + edge+4, i);
    }
}

// nakresli dilek zadany matici, coords urcuji pozici nejvyssiho ctverecku dilku nejvic vlevo 
void drawShape(int (*shapeMatrix)[4], int y, int x){ 
  //ex.: shapeMatrix = [[1, 1 , 0, 0], [0, 1, 0, 0], [0, 1, 0, 0], [0, 0, 0, 0]]
  for (int i = 0; i < 4; i++){
    for (int j =0; j < 4; j++){
      if (shapeMatrix[i][j] == 1){ 
        drawSquare(x + i * edge, y + j*edge); 
        printf("HERE");
      } 
    }
  }
}


int (*rotateLeft(int (*matrix)[4]))[4] {
    int (*result)[4] = malloc(4 * sizeof(*result));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = matrix[j][3 - i];
        }
    }
    return result;
}

int (*rotateRight(int (*matrix)[4]))[4] {
    int (*result)[4] = malloc(4 * sizeof(*result));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = matrix[3 - j][i];
        }
    }
    return result;
}



// ENDE 


int main(int argc, char *argv[]){

  /* Serialize execution of applications */

  /* Try to acquire lock the first */
  if (serialize_lock(1) <= 0) { //aby nam nekdo nevzal desku
    printf("System is occupied\n");

    if (1) {
      printf("Waitting\n");
      /* Wait till application holding lock releases it or exits */
      serialize_lock(0);
    }
  }


  parlcd_base=map_phys_address(PARLCD_REG_BASE_PHYS,PARLCD_REG_SIZE,0); //0=nechcem to cashovat  
  assert(parlcd_base !=NULL);
  parlcd_hx8357_init(parlcd_base);

  for(int i=0;i<320;i++){
    for(int j=0;j<480;j++){
      fb[j][i].d=0xffac;
    }
  }


  lcd_frame();

  spiled_base=map_phys_address(SPILED_REG_BASE_PHYS,SPILED_REG_SIZE,0); //0=nechcem to cashovat
  assert(spiled_base!=NULL);

  rgb1((union rgb){.g=255});

  printf("Hello world\n");

  while(1){
    rgb1((union rgb){.d=knobs()});
  }

  sleep(4);

  printf("Goodbye world\n");

  /* Release the lock */
  serialize_unlock();

  return 0;
}
void rgb1(union rgb color){
  uint32_t *ptr=spiled_base+SPILED_REG_LED_RGB1_o;
  printf("rgb:%x\n",color.d );
  *ptr=color.d;
}
uint32_t knobs(void){
  uint32_t *knobs=(spiled_base + SPILED_REG_KNOBS_8BIT_o);
  return *knobs;
}
void lcd_frame(void){
  parlcd_write_cmd(parlcd_base, 0x2c);
  for (int i = 0; i < 320 ; i++) {
    for (int j = 0; j < 480 ; j++) {
      parlcd_write_data(parlcd_base, fb[j][i].d);
    }
  }
}

void fbchar(char c,int x, int y, int scale){
  if(c<font_rom8x16.firstchar || c>=(font_rom8x16.size+font_rom8x16.firstchar))
    c=font_rom8x16.defaultchar;
  const int off=c-font_rom8x16.firstchar;
  const uint16_t *cb=font_rom8x16.bits+(font_rom8x16.height*off);//char bits  
  for(int i=0;i<font_rom8x16.height;i++){
    for(int j=0;j<font_rom8x16.maxwidth;j++){
      if(cb[i] & (0x1 << (16-1-j) )){ //prepsat 16
        int px=x+(j*scale);
        int py=y+(i*scale);
        for(int xi=0;xi<scale;xi++){
          for(int xj=0;xj<scale;xj++){
            fb[px+xj][py+xi].d=0x0;
          }
        }
      }
    }
  }
}

