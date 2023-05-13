#include "drawing.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parlcd_main_globals.h"
#include "colors.h"

union rgb color;
extern union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer

union rgb red = {.r = 255, .g = 0, .b = 0}; 
union rgb black = {.r = 0, .g = 0, .b = 0}; 
union rgb blue = {.r=0, .g=0, .b=255};

void color_pixel(union rgb color, int x, int y) {
  fb[y][x].r = color.r;
  fb[y][x].g = color.g;
  fb[y][x].b = color.b;
}

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
