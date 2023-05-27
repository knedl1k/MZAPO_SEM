#include "drawing.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "perifs_handle.h"
#include "colors.h"

union rgb color;
extern union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer

union rgb red = {.r = 255, .g = 0, .b = 0}; 
union rgb black = {.r = 0, .g = 0, .b = 0}; 
union rgb blue = {.r=0, .g=0, .b=255};

void color_pixel(union rgb color, int x, int y) {
  /*printf("%d %d\n",x,y);
  if(x<0 || x>=LCD_WIDTH || y<0 || y>=LCD_HEIGHT){
    fprintf(stderr,"ERROR: CP OUT OF LCD RANGE\n");
    return;
  }*/
  fb[y][x].r = color.r;
  fb[y][x].g = color.g;
  fb[y][x].b = color.b;
} 

void color_pixel_black_hor(int x, int y){ 
  fb[x][y].r = 0; 
  fb[x][y+1].r = 0; 
  fb[x][y+1].r = 0; 
  fb[x][y+3].r = 0; 
  fb[x][y+4].r = 0; 
  fb[x][y].g = 0; 
  fb[x][y+1].g = 0; 
  fb[x][y+2].g = 0; 
  fb[x][y+3].g = 0; 
  fb[x][y+4].g = 0; 
  fb[x][y].b = 0; 
  fb[x][y+1].b = 0; 
  fb[x][y+2].b = 0; 
  fb[x][y+3].b = 0; 
  fb[x][y+4].b = 0; 
}


void color_pixel_black_ver(int x, int y){ 
  fb[x][y].r = 0; 
  fb[x+1][y].r = 0; 
  fb[x+2][y].r = 0; 
  fb[x+3][y].r = 0; 
  fb[x+4][y].r = 0; 
  fb[x][y].g = 0; 
  fb[x+1][y].g = 0; 
  fb[x+2][y].g = 0; 
  fb[x+3][y].g = 0; 
  fb[x+4][y].g = 0; 
  fb[x][y].b = 0; 
  fb[x+1][y].b = 0; 
  fb[x+2][y].b = 0; 
  fb[x+3][y].b = 0; 
  fb[x+4][y].b = 0; 
}

void drawRectangle(union rgb color, int x, int y, int16_t height, uint16_t width){ 
    // left and right edge 
    for (size_t i = x; i < x + width; i++){ 
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
    // top and bottom edge 
    for (size_t i = y; i < y + height +5; i++){ 
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

void drawSquare(union rgb color, int x, int y){
  // edge = hrana čtverečků, ze kterých budou sestávat dílky, asi se nastavi defaultne 
  
    // left and right edge 
    for (int i = x; i < x + edge; i++){ 
      color_pixel(color, i, y); 
      color_pixel(color, i, y+1); 
      color_pixel(color, i, y+2); 
      color_pixel(color, i, y+3); 
      color_pixel(color, i, y+4); 

      color_pixel(color, i+5, y + edge); 
      color_pixel(color, i+5, y + edge+1); 
      color_pixel(color, i+5, y + edge+2); 
      color_pixel(color, i+5, y + edge+3); 
      color_pixel(color, i+5, y + edge+4); 

    }
    // top and bottom edge 
    for (int i = y; i < y + edge + 5; i++){ 
      color_pixel(color, x, i); 
      color_pixel(color, x+1, i); 
      color_pixel(color, x+2, i); 
      color_pixel(color, x+3, i); 
      color_pixel(color, x+4, i); 

      color_pixel(color, x + edge, i); 
      color_pixel(color, x + edge+1, i);
      color_pixel(color, x + edge+2, i);
      color_pixel(color, x + edge+3, i); 
      color_pixel(color, x + edge+4, i);
    }
}

// nakresli dilek zadany matici, coords urcuji pozici nejvyssiho ctverecku dilku nejvic vlevo 
void drawShape(int (*shapeMatrix)[4], int y, int x){ 
  //ex.: shapeMatrix = [[1, 1 , 0, 0], [0, 1, 0, 0], [0, 1, 0, 0], [0, 0, 0, 0]]
  for (int i = 0; i < 4; i++){
    for (int j =0; j < 4; j++){
      if (shapeMatrix[i][j] == 1){ 
        drawSquare(black, x + i * edge, y + j*edge); 
        printf("HERE");
      } 
    }
  }
}

void drawShapeLARGE(int (*shapeMatrix)[6], int y, int x){ 
  //ex.: shapeMatrix = [[1, 1 , 0, 0], [0, 1, 0, 0], [0, 1, 0, 0], [0, 0, 0, 0]]
  for (int i = 0; i < 6; i++){
    for (int j =0; j < 6; j++){
      if (shapeMatrix[i][j] == 1){ 
        drawSquare(red, x + i * edge, y + j*edge); 
        printf("HERE 6 ");
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

// DRAW BOARDS 
int const t = 5; // thickness 
int SPx = 20 - t; // starting point x 
int SPy = 30 - t; 

// BOARD 1 
void drawBoard1(int edge){ 
  int background[6][6] = {{1,1,1,0,0,0},{1,1,1,1,1,1},{0,0,1,1,1,1},{0,0,1,1,1,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
  drawShapeLARGE(background, SPx, SPy); 
  for (int i = SPx; i < SPx + 3*edge + 3* t; i++){ // 1- 
    color_pixel_black_hor(i, SPy);   
  }
  for (int i = SPy; i < SPy + 2*edge + 2* t ; i++){ // 1|
    color_pixel_black_ver(SPx, i);
  }
  for (int i = SPx; i < SPx + 2*edge + t ; i++){ // 3- 
    color_pixel_black_hor(i, SPy + 2 * edge + 2 * t); 
  }
  for (int i = SPy; i < SPy + edge + t ; i++){ // 3| 
    color_pixel_black_ver(SPx + 3*edge + 2 * t, i); 
  }
  for (int i = SPy + 2 * edge + 2*t; i < SPy + 4*edge + 3*t; i++){ // 2| 
    color_pixel_black_ver(SPx + 2*edge, i);
  }
  for (int i = SPx + 3 * edge + 2*t; i < SPx + 6*edge + 3*t ; i++){ // 2- 
    color_pixel_black_hor(i, SPy + edge); 
  }
  for (int i = SPx + 2 * edge; i < SPx + 5 * edge + 2 *t; i++){ // 5-
    color_pixel_black_hor(i, SPy + 4 * edge + 2*t); 
  }
  for (int i = SPy + edge; i <SPy + 3* edge + 3*t ; i++){ // 5| 
    color_pixel_black_ver(SPx + 6 * edge + 2*t, i); 
  }
  for (int i = SPx + 5 * edge + 2 * t; i <SPx + 6 * edge + 2 * t; i++){ // 4- 
    color_pixel_black_hor(i, SPy + 3* edge + 2 * t); 
  }
  for (int i = SPy + 3 * edge + 2 * t; i <SPy + 4 * edge + 3*t; i++){ // 4| 
    color_pixel_black_ver(SPx + 5 * edge + 2 * t, i);
  }
  
}

// BOARD 2 
void drawBoard2(int edge){ 
  int background[6][6] = {{0, 1 , 1, 0, 0,0}, {1,1,1,0,0,0}, {1,1,1,1,1,0}, {1,1,1,1,1,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}};
  drawShapeLARGE(background, SPx + t, SPy + t);
  for (int i = SPx; i < SPx + edge; i++){ 
    color_pixel_black_hor(i, SPy + edge);
  } 
  for (int i = SPy; i < SPy + edge+ t; i++){ 
    color_pixel_black_ver(SPx + edge, i);
  }
  for (int i = SPx + edge; i <SPx + 3*edge + 3* t; i++){ // 1- USED 
    color_pixel_black_hor(i, SPy);   
  }
  for (int i = SPx + 3 * edge + 2*t; i < SPx + 5*edge + 3*t; i++){ // 2- USED 
    color_pixel_black_hor(i, SPy + 2*edge); 
  }
  for (int i = SPx; i < SPx + 5 * edge + 2 *t; i++){ // 5- USED
    color_pixel_black_hor(i, SPy + 4 * edge + 2*t); 
  }
  for (int i = SPy + edge; i < SPy + 4*edge + 2* t; i++){ // 1| USED
    color_pixel_black_ver(SPx, i);
  }
  for (int i = SPy; i <SPy + 2*edge + t; i++){ // 3| USED 
    color_pixel_black_ver(SPx + 3*edge + 2 * t, i); 
  } 
  for (int i = SPy + 2 * edge + t; i < SPy + 4 * edge + 3*t; i++){ // 4| 
    color_pixel_black_ver(SPx + 5 * edge + 2 * t, i);
  }  
}

// BOARD 3 
void drawBoard3(int edge){ 
  int background[6][6] = {{0,1,1,1,0,0}, {1,1,1,1,0,0}, {1,1,1,1,1,0}, {1,1,1,1,1,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}};
  drawShapeLARGE(background, SPx + t, SPy + t);
  for (int i = SPx; i < SPx + edge; i++){ // OK 
    color_pixel_black_hor(i, SPy + edge);
  } 
  for (int i = SPy; i < SPy + edge+ t; i++){ // OK 
    color_pixel_black_ver(SPx + edge, i);
  }
  for (int i = SPx + edge; i <SPx + 4*edge + 3* t; i++){ // 1- USED 
    color_pixel_black_hor(i, SPy);   
  }
  for (int i = SPx + 4 * edge + 2*t; i < SPx + 5*edge + 3*t; i++){ // 2- USED 
    color_pixel_black_hor(i, SPy + 2*edge); 
  }
  for (int i = SPx; i < SPx + 5 * edge + 2 *t; i++){ // 5- USED
    color_pixel_black_hor(i, SPy + 4 * edge + 2*t); 
  }
  for (int i = SPy + edge; i < SPy + 4*edge + 2* t; i++){ // 1| OK
    color_pixel_black_ver(SPx, i);
  }
  for (int i = SPy; i <SPy + 2*edge + t; i++){ // 3| USED 
    color_pixel_black_ver(SPx + 4*edge + 2 * t, i); 
  } 
  for (int i = SPy + 2 * edge + t; i < SPy + 4 * edge + 3*t; i++){ // 4| 
    color_pixel_black_ver(SPx + 5 * edge + 2 * t, i);
  }  
}

// BOARD 4 
void drawBoard4(int edge){ 
  int background[6][6] = {{1,1,0,0,0,0}, {1,1,0,0,0,0}, {1,1,1,0,1,0}, {1,1,1,1,1,0}, {0,0,1,1,1,0}, {0,0,0,0,0,0}};
  drawShapeLARGE(background, SPx + t, SPy + t);
  for (int i = SPx; i < SPx + 2* edge + 2*t; i++){ // OK 
    color_pixel_black_hor(i, SPy);
  } 
  for (int i = SPy; i < SPy + 2*edge+ t; i++){ // OK 
    color_pixel_black_ver(SPx + 2*edge + 2 * t, i);
  }
  for (int i = SPx +2* edge+ 2 * t; i <SPx + 3*edge + 3* t; i++){ // 1- USED 
    color_pixel_black_hor(i, SPy+2*edge);   
  }
  for (int i = SPx; i < SPx + 2 * edge + t; i++){ // 5- USED
    color_pixel_black_hor(i, SPy + 4 * edge + 2*t); 
  }
  for (int i = SPy; i < SPy + 4*edge + 2* t; i++){ // 1| OK
    color_pixel_black_ver(SPx, i);
  }
  for (int i = SPy + 2 * edge; i <SPy + 3*edge + t; i++){ // 3| USED 
    color_pixel_black_ver(SPx + 3*edge + 2 * t, i); 
  } 
  for (int i = SPy + 4 * edge + t; i < SPy + 5 * edge + 3*t; i++){ 
    color_pixel_black_ver(SPx + 2 * edge, i);
  } 
  for ( int i = SPx + 2 * edge; i < SPx + 5 * edge + 3* t; i++){ 
    color_pixel_black_hor(i, SPy + 5 * edge + 2*t);
  } 
  for (int i = SPx + 3*edge + t; i < SPx + 4 * edge + t; i++){ 
    color_pixel_black_hor(i,SPy + 3*edge);
  } 
  for (int i = SPy + 2 * edge; i <SPy + 3*edge; i++){ 
    color_pixel_black_ver(SPx + 4 * edge, i);
  } 
  for (int i = SPx + 4 * edge; i < SPx + 5 * edge + 3 * t; i++){ 
    color_pixel_black_hor(i, SPy + 2 * edge);
  } 
  for (int i = SPy + 2 * edge; i < SPy + 5*edge + 2 * t; i++){ 
    color_pixel_black_ver(SPx + 5 * edge+2*t, i); 
  }
}

// BOARD 5
void drawBoard5(int edge){ 
  int background[6][6] = {{0,0,1,1,0,0}, {1,1,1,1,0,0}, {1,1,1,1,0,0}, {1,1,1,1,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}};
  drawShapeLARGE(background, SPx + t, SPy + t);
  for (int i = SPx; i < SPx + 2* edge + t; i++){ // OK 
    color_pixel_black_hor(i, SPy + edge);
  } 
  for (int i = SPy; i < SPy + edge+ t; i++){ // OK 
    color_pixel_black_ver(SPx + 2*edge, i);
  }
  for (int i = SPx +2* edge; i <SPx + 4*edge + 3* t; i++){ // 1- USED 
    color_pixel_black_hor(i, SPy);   
  }
  for (int i = SPx; i < SPx + 4 * edge + 2 *t; i++){ // 5- USED
    color_pixel_black_hor(i, SPy + 4 * edge + 2*t); 
  }
  for (int i = SPy + edge; i < SPy + 4*edge + 2* t; i++){ // 1| OK
    color_pixel_black_ver(SPx, i);
  }
  for (int i = SPy; i <SPy + 4*edge + 3*t; i++){ // 3| USED 
    color_pixel_black_ver(SPx + 4*edge + 2 * t, i); 
  } 
}

// BOARD 6 
void drawBoard6(int edge){ 
  int background[6][6] = {{0,1,1,1,0,0}, {1,1,1,1,0,0}, {0,1,1,1,1,1}, {0, 1,1,1,1,1}, {0,0,0,0,0,0}, {0,0,0,0,0,0}};
  drawShapeLARGE(background, SPx + t, SPy + t);
  for (int i = SPx; i < SPx + edge; i++){ //  
    color_pixel_black_hor(i, SPy + edge);
  } 
  for (int i = SPy; i < SPy + edge+ t; i++){ //  
    color_pixel_black_ver(SPx + edge, i);
  }
  for (int i = SPx + edge; i <SPx + 4*edge + 3* t; i++){ // 1- USED 
    color_pixel_black_hor(i, SPy);   
  }
  for (int i = SPx + 4 * edge + 2*t; i < SPx + 6*edge + 3*t; i++){ // 2- USED 
    color_pixel_black_hor(i, SPy + 2*edge); 
  }
  for (int i = SPx + edge; i < SPx + 6 * edge + 2 *t; i++){ // 5- USED
    color_pixel_black_hor(i, SPy + 4 * edge + 2*t); 
  }
  for (int i = SPy + edge; i < SPy + 2*edge + 2* t; i++){ // 1| OK
    color_pixel_black_ver(SPx, i);
  }
  for (int i = SPy; i <SPy + 2*edge + t; i++){ // 3| USED 
    color_pixel_black_ver(SPx + 4*edge + 2 * t, i); 
  } 
  for (int i = SPy + 2 * edge + t; i < SPy + 4 * edge + 3*t; i++){ // 4| 
    color_pixel_black_ver(SPx + 6 * edge + 2 * t, i);
  }  
    for (int i = SPx; i < SPx + edge + t; i++){ //  
    color_pixel_black_hor(i, SPy + 2*edge+2*t);
  }
    for (int i = SPy + 2* edge+2*t; i < SPy + 4*edge+ 2*t; i++){ //  
    color_pixel_black_ver(SPx + edge, i);
  } 
}

void drawFullRowBox(union rgb color, int x, int y_end){
  for (int i=x;i<LCD_WIDTH;++i){
    for(int j=0;j<y_end;++j){
      color_pixel(color,j,i);
    }
  }
}
