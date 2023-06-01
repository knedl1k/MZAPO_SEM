#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "colors.h"
#include "drawing.h"
#include "perifs_handle.h"

union rgb color;
extern union pixel fb[LCD_WIDTH][LCD_HEIGHT];  // frame buffer


union rgb red={.r=255, .g=0, .b=0};
union rgb black={.r=0, .g=0, .b=0};
union rgb blue={.r=0, .g=0, .b=255};

void colorPixel(union rgb color, int x, int y){
  /*printf("%d %d\n",x,y);
  if(x<0 || x>=LCD_WIDTH || y<0 || y>=LCD_HEIGHT){
    fprintf(stderr,"ERROR: CP OUT OF LCD RANGE\n");
    return;
  }*/
  fb[y][x].r=color.r;
  fb[y][x].g=color.g;
  fb[y][x].b=color.b;
}

void colorPixelBlackHor(int x, int y){
  fb[x][y].r=0;
  fb[x][y+1].r=0;
  fb[x][y+1].r=0;
  fb[x][y+3].r=0;
  fb[x][y+4].r=0;
  fb[x][y].g=0;
  fb[x][y+1].g=0;
  fb[x][y+2].g=0;
  fb[x][y+3].g=0;
  fb[x][y+4].g=0;
  fb[x][y].b=0;
  fb[x][y+1].b=0;
  fb[x][y+2].b=0;
  fb[x][y+3].b=0;
  fb[x][y+4].b=0;
}

void colorPixelBlackVer(int x, int y){
  fb[x][y].r=0;
  fb[x+1][y].r=0;
  fb[x+2][y].r=0;
  fb[x+3][y].r=0;
  fb[x+4][y].r=0;
  fb[x][y].g=0;
  fb[x+1][y].g=0;
  fb[x+2][y].g=0;
  fb[x+3][y].g=0;
  fb[x+4][y].g=0;
  fb[x][y].b=0;
  fb[x+1][y].b=0;
  fb[x+2][y].b=0;
  fb[x+3][y].b=0;
  fb[x+4][y].b=0;
}

void drawRectangle(union rgb color, int x, int y, int width, int height){
  // left and right edge
  for(size_t i=x; i < x+width; ++i){
    colorPixel(color, i, y);
    colorPixel(color, i, y+1);
    colorPixel(color, i, y+2);
    colorPixel(color, i, y+3);
    colorPixel(color, i, y+4);

    colorPixel(color, i+4, y+height);
    colorPixel(color, i+4, y+height+1);
    colorPixel(color, i+4, y+height+2);
    colorPixel(color, i+4, y+height+3);
    colorPixel(color, i+4, y+height+4);
  }
  // top and bottom edge
  for(size_t i=y; i < y+height+5; ++i){
    colorPixel(color, x, i);
    colorPixel(color, x+1, i);
    colorPixel(color, x+2, i);
    colorPixel(color, x+3, i);
    colorPixel(color, x+4, i);

    colorPixel(color, x+width, i);
    colorPixel(color, x+width+1, i);
    colorPixel(color, x+width+2, i);
    colorPixel(color, x+width+3, i);
    colorPixel(color, x+width+4, i);
  }
}

int edge=33;

void drawSquare(union rgb color, int x, int y){
  // edge=hrana čtverečků, ze kterých budou sestávat dílky, asi se nastavi defaultne
  // left and right edge
  for(int i=x; i < x+edge; ++i){
    colorPixel(color, i, y);
    colorPixel(color, i, y+1);
    colorPixel(color, i, y+2);
    colorPixel(color, i, y+3);
    colorPixel(color, i, y+4);

    colorPixel(color, i+5, y+edge);
    colorPixel(color, i+5, y+edge+1);
    colorPixel(color, i+5, y+edge+2);
    colorPixel(color, i+5, y+edge+3);
    colorPixel(color, i+5, y+edge+4);
  }
  // top and bottom edge
  for(int i=y; i < y+edge+5; ++i){
    colorPixel(color, x, i);
    colorPixel(color, x+1, i);
    colorPixel(color, x+2, i);
    colorPixel(color, x+3, i);
    colorPixel(color, x+4, i);

    colorPixel(color, x+edge, i);
    colorPixel(color, x+edge+1, i);
    colorPixel(color, x+edge+2, i);
    colorPixel(color, x+edge+3, i);
    colorPixel(color, x+edge+4, i);
  }
}
/*
typedef struct {
  int posX;
  int posY;
  int shape[4][4];
} GetResult;
*/
// nakresli dilek zadany matici, coords urcuji pozici nejvyssiho ctverecku dilku nejvic vlevo
int* drawShape(int(*shapeMatrix)[4], int* y, int* x, int draw){ 
  printf("draw shape called with matrix: \n");
  int* result = malloc(2 * sizeof(int));
  result[0] = -1;  // posX
  result[1] = -1;  // posY
  for(int i=0; i < 4; ++i){
    for(int j=0; j < 4; ++j){
      //printf(" %d", shapeMatrix[i][j]);

      if(shapeMatrix[i][j] != 0){ 
        shapeMatrix[i][j] = 1;
        if (result[0] == -1 && result[1] == -1){
          result[0] = *x + i*edge; 
          result[1] = *y + j* edge; 
        }
        if (draw == 1){ 
          //printf("if draw == 1\n"); 
          drawSquare(black, *x+i*edge, *y+j*edge);

        }
        // printf("posX: %d, posY: %d\n", result[0], result[1]);      
      }
          printf(" %d", shapeMatrix[i][j]);

    }
        printf("\n");

  } 
  return result; 
}



GetResult rotateLeft2(int(*matrix)[4], int pos[2]){
    GetResult result;
  int(*rotatedShape)[4] = malloc(4 * sizeof(*rotatedShape));

  // Perform left rotation
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      rotatedShape[i][j] = matrix[j][3 - i];
    }
  }

  // Update position
  int* drawShapeResult = drawShape(rotatedShape, &pos[1], &pos[0], 1);
  pos[0] = drawShapeResult[0];
  pos[1] = drawShapeResult[1];
  free(drawShapeResult);

  // Set values in the result struct
  result.posX = pos[0];
  result.posY = pos[1];
  memcpy(result.shape, rotatedShape, 4 * 4 * sizeof(int));

  free(rotatedShape);
  return result;
}

GetResult rotateRight2(int(*matrix)[4], int pos[2]){ 
  GetResult result;
  int(*rotatedShape)[4] = malloc(4 * sizeof(*rotatedShape));

  // Perform right rotation
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      rotatedShape[i][j] = matrix[3 - j][i];

    colorPixel(color, x+edge, i);
    colorPixel(color, x+edge+1, i);
    colorPixel(color, x+edge+2, i);
    colorPixel(color, x+edge+3, i);
    colorPixel(color, x+edge+4, i);
  }
}

// nakresli dilek zadany matici, coords urcuji pozici nejvyssiho ctverecku dilku nejvic vlevo
void drawShape(int(*shapeMatrix)[4], int y, int x){
  // ex.: shapeMatrix=[[1, 1 , 0, 0], [0, 1, 0, 0], [0, 1, 0, 0], [0, 0, 0, 0]]
  for(int i=0; i < 4; ++i){
    for(int j=0; j < 4; ++j){
      if(shapeMatrix[i][j] == 1){
        drawSquare(black, x+i*edge, y+j*edge);
        printf("HERE");
      }
    }
  }

  lcdRefresh();


  // Update position
  int* drawShapeResult = drawShape(rotatedShape, &pos[1], &pos[0], 1);
  pos[0] = drawShapeResult[0];
  pos[1] = drawShapeResult[1];
  free(drawShapeResult);

  // Set values in the result struct
  result.posX = pos[0];
  result.posY = pos[1];
  memcpy(result.shape, rotatedShape, 4 * 4 * sizeof(int));

  free(rotatedShape);
  return result;
}

GetResult drawShapeBasedOnKnobs(int (*shape)[4], int *posX, int *posY, int knobLeftState, int knobRightState) {
  printf("posX: %d, posY: %d\n", *posX, *posY);      
  lcdRefresh();

  int pos[2]; 
  pos[0] = *posX; 
  pos[1] = *posY; 
  GetResult result; 

  int* drawShapeResult = drawShape(shape, &pos[1], &pos[0], 0);
  pos[0] = drawShapeResult[0]; 
  pos[1] = drawShapeResult[1]; 
  result.posX = pos[0]; 
  result.posY = pos[1];
  memcpy(result.shape, shape, 4 * 4 * sizeof(int));

  if (knobLeftState == 1) { 
    GetResult rotateResult = rotateLeft2(shape, pos);
    result.posX = rotateResult.posX;
    result.posY = rotateResult.posY; 
    memcpy(result.shape, rotateResult.shape, 4 * 4 * sizeof(int));
  }

  if (knobRightState == 1) {
    GetResult rotateResult = rotateRight2(shape, pos);
    result.posX = rotateResult.posX;
    result.posY = rotateResult.posY;
    memcpy(result.shape, rotateResult.shape, 4 * 4 * sizeof(int));

  }
 
  printf("posX: %d, posY: %d\n", drawShapeResult[0], drawShapeResult[1]);      


    free(drawShapeResult);
  return result; 

}

void drawShapeLARGE(int(*shapeMatrix)[6], int y, int x){
  // ex.: shapeMatrix=[[1, 1 , 0, 0], [0, 1, 0, 0], [0, 1, 0, 0], [0, 0, 0, 0]]
  for(int i=0; i < 6; ++i){
    for(int j=0; j < 6; ++j){
      if(shapeMatrix[i][j] == 1){
        drawSquare(red, x+i*edge, y+j*edge);
        printf("HERE 6 ");
      }
    }
  }
  lcdRefresh();
}

// DRAW BOARDS
int const t=5; // thickness
int SPx=20-t;  // starting point x
int SPy=30-t;

// BOARD 1
void drawBoard1(int edge){
  int background[6][6]={{1, 1, 1, 0, 0, 0},{1, 1, 1, 1, 1, 1},{0, 0, 1, 1, 1, 1},
                         {0, 0, 1, 1, 1, 0},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  for(int i=SPx; i < SPx+3*edge+3*t; ++i){  // 1-
    colorPixelBlackHor(i, SPy);
  }
  for(int i=SPy; i < SPy+2*edge+2*t; ++i){  // 1|
    colorPixelBlackVer(SPx, i);
  }
  for(int i=SPx; i < SPx+2*edge+t; ++i){  // 3-
    colorPixelBlackHor(i, SPy+2*edge+2*t);
  }
  for(int i=SPy; i < SPy+edge+t; ++i){  // 3|
    colorPixelBlackVer(SPx+3*edge+2*t, i);
  }
  for(int i=SPy+2*edge+2*t; i < SPy+4*edge+3*t; ++i){  // 2|
    colorPixelBlackVer(SPx+2*edge, i);
  }
  for(int i=SPx+3*edge+2*t; i < SPx+6*edge+3*t; ++i){  // 2-
    colorPixelBlackHor(i, SPy+edge);
  }
  for(int i=SPx+2*edge; i < SPx+5*edge+2*t; ++i){  // 5-
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  }
  for(int i=SPy+edge; i < SPy+3*edge+3*t; ++i){  // 5|
    colorPixelBlackVer(SPx+6*edge+2*t, i);
  }
  for(int i=SPx+5*edge+2*t; i < SPx+6*edge+2*t; ++i){  // 4-
    colorPixelBlackHor(i, SPy+3*edge+2*t);
  }
  for(int i=SPy+3*edge+2*t; i < SPy+4*edge+3*t; ++i){  // 4|
    colorPixelBlackVer(SPx+5*edge+2*t, i);
  }
  lcdRefresh();
}

// BOARD 2
void drawBoard2(int edge){
  int background[6][6]={{0, 1, 1, 0, 0, 0},{1, 1, 1, 0, 0, 0},{1, 1, 1, 1, 1, 0},
                         {1, 1, 1, 1, 1, 0},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  for(int i=SPx; i < SPx+edge; ++i){
    colorPixelBlackHor(i, SPy+edge);
  }
  for(int i=SPy; i < SPy+edge+t; ++i){
    colorPixelBlackVer(SPx+edge, i);
  }
  for(int i=SPx+edge; i < SPx+3*edge+3*t; ++i){  // 1 - USED
    colorPixelBlackHor(i, SPy);
  }
  for(int i=SPx+3*edge+2*t; i < SPx+5*edge+3*t; ++i){  // 2 - USED
    colorPixelBlackHor(i, SPy+2*edge);
  }
  for(int i=SPx; i < SPx+5*edge+2*t; ++i){  // 5 - USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  }
  for(int i=SPy+edge; i < SPy+4*edge+2*t; ++i){  // 1| USED
    colorPixelBlackVer(SPx, i);
  }
  for(int i=SPy; i < SPy+2*edge+t; ++i){  // 3| USED
    colorPixelBlackVer(SPx+3*edge+2*t, i);
  }
  for(int i=SPy+2*edge+t; i < SPy+4*edge+3*t; ++i){  // 4|
    colorPixelBlackVer(SPx+5*edge+2*t, i);
  }
  lcdRefresh();
}

// BOARD 3
void drawBoard3(int edge){
  int background[6][6]={{0, 1, 1, 1, 0, 0},{1, 1, 1, 1, 0, 0},{1, 1, 1, 1, 1, 0},
                         {1, 1, 1, 1, 1, 0},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  for(int i=SPx; i < SPx+edge; ++i){  // OK
    colorPixelBlackHor(i, SPy+edge);
  }
  for(int i=SPy; i < SPy+edge+t; ++i){  // OK
    colorPixelBlackVer(SPx+edge, i);
  }
  for(int i=SPx+edge; i < SPx+4*edge+3*t; ++i){  // 1- USED
    colorPixelBlackHor(i, SPy);
  }
  for(int i=SPx+4*edge+2*t; i < SPx+5*edge+3*t; ++i){  // 2- USED
    colorPixelBlackHor(i, SPy+2*edge);
  }
  for(int i=SPx; i < SPx+5*edge+2*t; ++i){  // 5- USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  }
  for(int i=SPy+edge; i < SPy+4*edge+2*t; ++i){  // 1| OK
    colorPixelBlackVer(SPx, i);
  }
  for(int i=SPy; i < SPy+2*edge+t; ++i){  // 3| USED
    colorPixelBlackVer(SPx+4*edge+2*t, i);
  }
  for(int i=SPy+2*edge+t; i < SPy+4*edge+3*t; ++i){  // 4|
    colorPixelBlackVer(SPx+5*edge+2*t, i);
  }
  lcdRefresh();
}

// BOARD 4
void drawBoard4(int edge){
  int background[6][6]={{1, 1, 0, 0, 0, 0},{1, 1, 0, 0, 0, 0},{1, 1, 1, 0, 1, 0},
                         {1, 1, 1, 1, 1, 0},{0, 0, 1, 1, 1, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  for(int i=SPx; i < SPx+2*edge+2*t; ++i){  // OK
    colorPixelBlackHor(i, SPy);
  }
  for(int i=SPy; i < SPy+2*edge+t; ++i){  // OK
    colorPixelBlackVer(SPx+2*edge+2*t, i);
  }
  for(int i=SPx+2*edge+2*t; i < SPx+3*edge+3*t; ++i){  // 1- USED
    colorPixelBlackHor(i, SPy+2*edge);
  }
  for(int i=SPx; i < SPx+2*edge+t; ++i){  // 5- USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  }
  for(int i=SPy; i < SPy+4*edge+2*t; ++i){  // 1| OK
    colorPixelBlackVer(SPx, i);
  }
  for(int i=SPy+2*edge; i < SPy+3*edge+t; ++i){  // 3| USED
    colorPixelBlackVer(SPx+3*edge+2*t, i);
  }
  for(int i=SPy+4*edge+2*t; i < SPy+5*edge+3*t; ++i){
    colorPixelBlackVer(SPx+2*edge, i);
  }
  for(int i=SPx+2*edge; i < SPx+5*edge+3*t; ++i){
    colorPixelBlackHor(i, SPy+5*edge+2*t);
  }
  for(int i=SPx+3*edge+2*t; i < SPx+4*edge+t; ++i){
    colorPixelBlackHor(i, SPy+3*edge);
  }
  for(int i=SPy+2*edge; i < SPy+3*edge; ++i){
    colorPixelBlackVer(SPx+4*edge, i);
  }
  for(int i=SPx+4*edge; i < SPx+5*edge+3*t; ++i){
    colorPixelBlackHor(i, SPy+2*edge);
  }
  for(int i=SPy+2*edge; i < SPy+5*edge+2*t; ++i){
    colorPixelBlackVer(SPx+5*edge+2*t, i);
  }
  lcdRefresh();
}

// BOARD 5
void drawBoard5(int edge){
  int background[6][6]={{0, 0, 1, 1, 0, 0},{1, 1, 1, 1, 0, 0},{1, 1, 1, 1, 0, 0},
                         {1, 1, 1, 1, 0, 0},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  for(int i=SPx; i < SPx+2*edge+t; ++i){  // OK
    colorPixelBlackHor(i, SPy+edge);
  }
  for(int i=SPy; i < SPy+edge+t; ++i){  // OK
    colorPixelBlackVer(SPx+2*edge, i);
  }
  for(int i=SPx+2*edge; i < SPx+4*edge+3*t; ++i){  // 1- USED
    colorPixelBlackHor(i, SPy);
  }
  for(int i=SPx; i < SPx+4*edge+2*t; ++i){  // 5- USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  }
  for(int i=SPy+edge; i < SPy+4*edge+2*t; ++i){  // 1| OK
    colorPixelBlackVer(SPx, i);
  }
  for(int i=SPy; i < SPy+4*edge+3*t; ++i){  // 3| USED
    colorPixelBlackVer(SPx+4*edge+2*t, i);
  }
  lcdRefresh();
}

// BOARD 6
void drawBoard6(int edge){
  int background[6][6]={{0, 1, 1, 1, 0, 0},{1, 1, 1, 1, 0, 0},{0, 1, 1, 1, 1, 1},
                         {0, 1, 1, 1, 1, 1},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  for(int i=SPx; i < SPx+edge; ++i){  //
    colorPixelBlackHor(i, SPy+edge);
  }
  for(int i=SPy; i < SPy+edge+t; ++i){  //
    colorPixelBlackVer(SPx+edge, i);
  }
  for(int i=SPx+edge; i < SPx+4*edge+3*t; ++i){  // 1- USED
    colorPixelBlackHor(i, SPy);
  }
  for(int i=SPx+4*edge+2*t; i < SPx+6*edge+3*t; ++i){  // 2- USED
    colorPixelBlackHor(i, SPy+2*edge);
  }
  for(int i=SPx+edge; i < SPx+6*edge+2*t; ++i){  // 5- USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  }
  for(int i=SPy+edge; i < SPy+2*edge+2*t; ++i){  // 1| OK
    colorPixelBlackVer(SPx, i);
  }
  for(int i=SPy; i < SPy+2*edge+t; ++i){  // 3| USED
    colorPixelBlackVer(SPx+4*edge+2*t, i);
  }
  for(int i=SPy+2*edge+t; i < SPy+4*edge+3*t; ++i){  // 4|
    colorPixelBlackVer(SPx+6*edge+2*t, i);
  }
  for(int i=SPx; i < SPx+edge+t; ++i){  //
    colorPixelBlackHor(i, SPy+2*edge+2*t);
  }
  for(int i=SPy+2*edge+2*t; i < SPy+4*edge+2*t; ++i){  //
    colorPixelBlackVer(SPx+edge, i);
  }
  lcdRefresh();
}

void drawFullRowBox(union rgb color, int x, int y){ 
  //for(int i=x) 
}
/*

  fb[y][x].r=color.r;
  fb[y][x].g=color.g;
  fb[y][x].b=color.b;
}

void colorPixelBlackHor(int x, int y){
  fb[x][y].r=0;
  fb[x][y+1].r=0;
  fb[x][y+1].r=0;
  fb[x][y+3].r=0;
  fb[x][y+4].r=0;
  fb[x][y].g=0;
  fb[x][y+1].g=0;
  fb[x][y+2].g=0;
  fb[x][y+3].g=0;
  fb[x][y+4].g=0;
  fb[x][y].b=0;
  fb[x][y+1].b=0;
  fb[x][y+2].b=0;
  fb[x][y+3].b=0;
  fb[x][y+4].b=0;
}

void colorPixelBlackVer(int x, int y){
  fb[x][y].r=0;
  fb[x+1][y].r=0;
  fb[x+2][y].r=0;
  fb[x+3][y].r=0;
  fb[x+4][y].r=0;
  fb[x][y].g=0;
  fb[x+1][y].g=0;
  fb[x+2][y].g=0;
  fb[x+3][y].g=0;
  fb[x+4][y].g=0;
  fb[x][y].b=0;
  fb[x+1][y].b=0;
  fb[x+2][y].b=0;
  fb[x+3][y].b=0;
  fb[x+4][y].b=0;
}

void drawRectangle(union rgb color, int x, int y, int width, int height){
  // left and right edge
  for(size_t i=x; i < x+width; ++i){
    colorPixel(color, i, y);
    colorPixel(color, i, y+1);
    colorPixel(color, i, y+2);
    colorPixel(color, i, y+3);
    colorPixel(color, i, y+4);

    colorPixel(color, i+4, y+height);
    colorPixel(color, i+4, y+height+1);
    colorPixel(color, i+4, y+height+2);
    colorPixel(color, i+4, y+height+3);
    colorPixel(color, i+4, y+height+4);
  }
  // top and bottom edge
  for(size_t i=y; i < y+height+5; ++i){
    colorPixel(color, x, i);
    colorPixel(color, x+1, i);
    colorPixel(color, x+2, i);
    colorPixel(color, x+3, i);
    colorPixel(color, x+4, i);

    colorPixel(color, x+width, i);
    colorPixel(color, x+width+1, i);
    colorPixel(color, x+width+2, i);
    colorPixel(color, x+width+3, i);
    colorPixel(color, x+width+4, i);
  }
}

int edge=40;

void drawSquare(union rgb color, int x, int y){
  // edge=hrana čtverečků, ze kterých budou sestávat dílky, asi se nastavi defaultne
  // left and right edge
  for(int i=x; i < x+edge; ++i){
    colorPixel(color, i, y);
    colorPixel(color, i, y+1);
    colorPixel(color, i, y+2);
    colorPixel(color, i, y+3);
    colorPixel(color, i, y+4);

    colorPixel(color, i+5, y+edge);
    colorPixel(color, i+5, y+edge+1);
    colorPixel(color, i+5, y+edge+2);
    colorPixel(color, i+5, y+edge+3);
    colorPixel(color, i+5, y+edge+4);
  }
  // top and bottom edge
  for(int i=y; i < y+edge+5; ++i){
    colorPixel(color, x, i);
    colorPixel(color, x+1, i);
    colorPixel(color, x+2, i);
    colorPixel(color, x+3, i);
    colorPixel(color, x+4, i);

    colorPixel(color, x+edge, i);
    colorPixel(color, x+edge+1, i);
    colorPixel(color, x+edge+2, i);
    colorPixel(color, x+edge+3, i);
    colorPixel(color, x+edge+4, i);
  }
}

// nakresli dilek zadany matici, coords urcuji pozici nejvyssiho ctverecku dilku nejvic vlevo
int* drawShape(int(*shapeMatrix)[4], int* y, int* x, int draw){
  int* result = malloc(2 * sizeof(int));
  result[0] = -1;  // posX
  result[1] = -1;  // posY
  for(int i=0; i < 4; ++i){
    for(int j=0; j < 4; ++j){
      if(shapeMatrix[i][j] == 1){ 
        if (result[0] == -1 && result[1] == -1){
          result[0] = *x + i*edge; 
          result[1] = *y + j* edge; 
        }
        if (draw == 1){ 
          drawSquare(black, *x+i*edge, *y+j*edge);

        }
        // printf("posX: %d, posY: %d\n", result[0], result[1]);      
      }
    }
  } 
  return result; 
}

int* rotateLeft2(int(*matrix)[4], int pos[2]){ 
  int(*result)[4]=malloc(4*sizeof(*result));
  for(int i=0; i < 4; ++i){
    for(int j=0; j < 4; ++j){
      result[i][j]=matrix[j][3-i];
    }
  }
  int* drawShapeResult = drawShape(result, &pos[1], &pos[0], 1);
  pos[0] = drawShapeResult[0]; 
  pos[1] = drawShapeResult[1];
  free(drawShapeResult); 
  return pos;
}

int* rotateRight2(int(*matrix)[4], int pos[2]){ 
  int(*result)[4]=malloc(4*sizeof(*result));
  for(int i=0; i < 4; ++i){
    for(int j=0; j < 4; ++j){
      result[i][j]=matrix[3-j][i];
    }
  }
  int* drawShapeResult = drawShape(result, &pos[1], &pos[0], 1);
  pos[0] = drawShapeResult[0]; 
  pos[1] = drawShapeResult[1];
  free(drawShapeResult); 
  return pos;
}

int* drawShapeBasedOnKnobs(int (*shape)[4], int *posX, int *posY, int knobLeftState, int knobRightState) {
  printf("posX: %d, posY: %d\n", *posX, *posY);      

  int* drawShapeResult = drawShape(shape, posX, posY, 1);


  if (knobLeftState == 1) {
    int* rotatedShape = rotateLeft2(shape, drawShapeResult);
    // free(drawShapeResult);
    drawShapeResult = rotatedShape;
  }
  
  if (knobRightState == 1) {
    int* rotatedShape = rotateRight2(shape, drawShapeResult);
    // free(drawShapeResult);
    drawShapeResult = rotatedShape;
  }
  printf("posX: %d, posY: %d\n", drawShapeResult[0], drawShapeResult[1]);      


  *posX = drawShapeResult[0];
  *posY = drawShapeResult[1];
  free(drawShapeResult); 
  return drawShapeResult; 
}

int(*rotateLeft(int(*matrix)[4]))[4]{
  int(*result)[4]=malloc(4*sizeof(*result));
  for(int i=0; i < 4; ++i){
    for(int j=0; j < 4; ++j){
      result[i][j]=matrix[j][3-i];
    }

int(*rotateLeft(int(*matrix)[4]))[4]{
  int(*result)[4]=malloc(4*sizeof(*result));
  for(int i=0; i < 4; ++i){
    for(int j=0; j < 4; ++j){
      result[i][j]=matrix[j][3-i];
    }

  }
  return result;
}

int(*rotateRight(int(*matrix)[4]))[4]{
  int(*result)[4]=malloc(4*sizeof(*result));
  for(int i=0; i < 4; ++i){
    for(int j=0; j < 4; ++j){
      result[i][j]=matrix[3-j][i];
    }
  }
  return result;
}


void drawShapeLARGE(int(*shapeMatrix)[6], int y, int x){
  // ex.: shapeMatrix=[[1, 1 , 0, 0], [0, 1, 0, 0], [0, 1, 0, 0], [0, 0, 0, 0]]
  for(int i=0; i < 6; ++i){
    for(int j=0; j < 6; ++j){
      if(shapeMatrix[i][j] == 1){
        drawSquare(red, x+i*edge, y+j*edge);
        printf("HERE 6 ");
      }
    }
  }
}

// DRAW BOARDS
int const t=5; // thickness
int SPx=20-t;  // starting point x
int SPy=30-t;

// BOARD 1
void drawBoard1(void){
  int background[6][6]={{1, 1, 1, 0, 0, 0},{1, 1, 1, 1, 1, 1},{0, 0, 1, 1, 1, 1},
                         {0, 0, 1, 1, 1, 0},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  for(int i=SPx; i < SPx+3*edge+3*t; ++i){  // 1-
    colorPixelBlackHor(i, SPy);
  }
  for(int i=SPy; i < SPy+2*edge+2*t; ++i){  // 1|
    colorPixelBlackVer(SPx, i);
  }
  for(int i=SPx; i < SPx+2*edge+t; ++i){  // 3-
    colorPixelBlackHor(i, SPy+2*edge+2*t);
  }
  for(int i=SPy; i < SPy+edge+t; ++i){  // 3|
    colorPixelBlackVer(SPx+3*edge+2*t, i);
  }
  for(int i=SPy+2*edge+2*t; i < SPy+4*edge+3*t; ++i){  // 2|
    colorPixelBlackVer(SPx+2*edge, i);
  }
  for(int i=SPx+3*edge+2*t; i < SPx+6*edge+3*t; ++i){  // 2-
    colorPixelBlackHor(i, SPy+edge);
  }
  for(int i=SPx+2*edge; i < SPx+5*edge+2*t; ++i){  // 5-
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  }
  for(int i=SPy+edge; i < SPy+3*edge+3*t; ++i){  // 5|
    colorPixelBlackVer(SPx+6*edge+2*t, i);
  }
  for(int i=SPx+5*edge+2*t; i < SPx+6*edge+2*t; ++i){  // 4-
    colorPixelBlackHor(i, SPy+3*edge+2*t);
  }
  for(int i=SPy+3*edge+2*t; i < SPy+4*edge+3*t; ++i){  // 4|
    colorPixelBlackVer(SPx+5*edge+2*t, i);
  }
  lcdRefresh();
}

// BOARD 2
void drawBoard2(void){
  int background[6][6]={{0, 1, 1, 0, 0, 0},{1, 1, 1, 0, 0, 0},{1, 1, 1, 1, 1, 0},
                         {1, 1, 1, 1, 1, 0},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  for(int i=SPx; i < SPx+edge; ++i){
    colorPixelBlackHor(i, SPy+edge);
  }
  for(int i=SPy; i < SPy+edge+t; ++i){
    colorPixelBlackVer(SPx+edge, i);
  }
  for(int i=SPx+edge; i < SPx+3*edge+3*t; ++i){  // 1 - USED
    colorPixelBlackHor(i, SPy);
  }
  for(int i=SPx+3*edge+2*t; i < SPx+5*edge+3*t; ++i){  // 2 - USED
    colorPixelBlackHor(i, SPy+2*edge);
  }
  for(int i=SPx; i < SPx+5*edge+2*t; ++i){  // 5 - USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  }
  for(int i=SPy+edge; i < SPy+4*edge+2*t; ++i){  // 1| USED
    colorPixelBlackVer(SPx, i);
  }
  for(int i=SPy; i < SPy+2*edge+t; ++i){  // 3| USED
    colorPixelBlackVer(SPx+3*edge+2*t, i);
  }
  for(int i=SPy+2*edge+t; i < SPy+4*edge+3*t; ++i){  // 4|
    colorPixelBlackVer(SPx+5*edge+2*t, i);
  }
  lcdRefresh();
}

// BOARD 3
void drawBoard3(void){
  int background[6][6]={{0, 1, 1, 1, 0, 0},{1, 1, 1, 1, 0, 0},{1, 1, 1, 1, 1, 0},
                         {1, 1, 1, 1, 1, 0},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  for(int i=SPx; i < SPx+edge; ++i){  // OK
    colorPixelBlackHor(i, SPy+edge);
  }
  for(int i=SPy; i < SPy+edge+t; ++i){  // OK
    colorPixelBlackVer(SPx+edge, i);
  }
  for(int i=SPx+edge; i < SPx+4*edge+3*t; ++i){  // 1- USED
    colorPixelBlackHor(i, SPy);
  }
  for(int i=SPx+4*edge+2*t; i < SPx+5*edge+3*t; ++i){  // 2- USED
    colorPixelBlackHor(i, SPy+2*edge);
  }
  for(int i=SPx; i < SPx+5*edge+2*t; ++i){  // 5- USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  }
  for(int i=SPy+edge; i < SPy+4*edge+2*t; ++i){  // 1| OK
    colorPixelBlackVer(SPx, i);
  }
  for(int i=SPy; i < SPy+2*edge+t; ++i){  // 3| USED
    colorPixelBlackVer(SPx+4*edge+2*t, i);
  }
  for(int i=SPy+2*edge+t; i < SPy+4*edge+3*t; ++i){  // 4|
    colorPixelBlackVer(SPx+5*edge+2*t, i);
  }
  lcdRefresh();
}

// BOARD 4
void drawBoard4(void){
  int background[6][6]={{1, 1, 0, 0, 0, 0},{1, 1, 0, 0, 0, 0},{1, 1, 1, 0, 1, 0},
                         {1, 1, 1, 1, 1, 0},{0, 0, 1, 1, 1, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  for(int i=SPx; i < SPx+2*edge+2*t; ++i){  // OK
    colorPixelBlackHor(i, SPy);
  }
  for(int i=SPy; i < SPy+2*edge+t; ++i){  // OK
    colorPixelBlackVer(SPx+2*edge+2*t, i);
  }
  for(int i=SPx+2*edge+2*t; i < SPx+3*edge+3*t; ++i){  // 1- USED
    colorPixelBlackHor(i, SPy+2*edge);
  }
  for(int i=SPx; i < SPx+2*edge+t; ++i){  // 5- USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  }
  for(int i=SPy; i < SPy+4*edge+2*t; ++i){  // 1| OK
    colorPixelBlackVer(SPx, i);
  }
  for(int i=SPy+2*edge; i < SPy+3*edge+t; ++i){  // 3| USED
    colorPixelBlackVer(SPx+3*edge+2*t, i);
  }
  for(int i=SPy+4*edge+2*t; i < SPy+5*edge+3*t; ++i){
    colorPixelBlackVer(SPx+2*edge, i);
  }

  for(int i=SPx+2*edge; i < SPx+5*edge+3*t; ++i){
    colorPixelBlackHor(i, SPy+5*edge+2*t);
  }
  for(int i=SPx+3*edge+2*t; i < SPx+4*edge+t; ++i){
    colorPixelBlackHor(i, SPy+3*edge);
  }
  for(int i=SPy+2*edge; i < SPy+3*edge; ++i){
    colorPixelBlackVer(SPx+4*edge, i);
  }
  for(int i=SPx+4*edge; i < SPx+5*edge+3*t; ++i){
    colorPixelBlackHor(i, SPy+2*edge);
  }
  for(int i=SPy+2*edge; i < SPy+5*edge+2*t; ++i){
    colorPixelBlackVer(SPx+5*edge+2*t, i);
  }
  lcdRefresh();
}

// BOARD 5
void drawBoard5(void){
  int background[6][6]={{0, 0, 1, 1, 0, 0},{1, 1, 1, 1, 0, 0},{1, 1, 1, 1, 0, 0},
                         {1, 1, 1, 1, 0, 0},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  for(int i=SPx; i < SPx+2*edge+t; ++i){  // OK
    colorPixelBlackHor(i, SPy+edge);
  }
  for(int i=SPy; i < SPy+edge+t; ++i){  // OK
    colorPixelBlackVer(SPx+2*edge, i);
  }
  for(int i=SPx+2*edge; i < SPx+4*edge+3*t; ++i){  // 1- USED
    colorPixelBlackHor(i, SPy);
  }
  for(int i=SPx; i < SPx+4*edge+2*t; ++i){  // 5- USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  }
  for(int i=SPy+edge; i < SPy+4*edge+2*t; ++i){  // 1| OK
    colorPixelBlackVer(SPx, i);
  }
  for(int i=SPy; i < SPy+4*edge+3*t; ++i){  // 3| USED
    colorPixelBlackVer(SPx+4*edge+2*t, i);
  }
  lcdRefresh();

}

// BOARD 6
void drawBoard6(void){
  int background[6][6]={{0, 1, 1, 1, 0, 0},{1, 1, 1, 1, 0, 0},{0, 1, 1, 1, 1, 1},
                         {0, 1, 1, 1, 1, 1},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  for(int i=SPx; i < SPx+edge; ++i){  //
    colorPixelBlackHor(i, SPy+edge);
  }
  for(int i=SPy; i < SPy+edge+t; ++i){  //
    colorPixelBlackVer(SPx+edge, i);
  }
  for(int i=SPx+edge; i < SPx+4*edge+3*t; ++i){  // 1- USED
    colorPixelBlackHor(i, SPy);
  }
  for(int i=SPx+4*edge+2*t; i < SPx+6*edge+3*t; ++i){  // 2- USED
    colorPixelBlackHor(i, SPy+2*edge);
  }
  for(int i=SPx+edge; i < SPx+6*edge+2*t; ++i){  // 5- USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  }
  for(int i=SPy+edge; i < SPy+2*edge+2*t; ++i){  // 1| OK
    colorPixelBlackVer(SPx, i);
  }
  for(int i=SPy; i < SPy+2*edge+t; ++i){  // 3| USED
    colorPixelBlackVer(SPx+4*edge+2*t, i);
  }
  for(int i=SPy+2*edge+t; i < SPy+4*edge+3*t; ++i){  // 4|
    colorPixelBlackVer(SPx+6*edge+2*t, i);
  }
  for(int i=SPx; i < SPx+edge+t; ++i){  //
    colorPixelBlackHor(i, SPy+2*edge+2*t);
  }
  for(int i=SPy+2*edge+2*t; i < SPy+4*edge+2*t; ++i){  //
    colorPixelBlackVer(SPx+edge, i);
  }
  lcdRefresh();

}

void drawFullRowBox(union rgb color, int x, int y){ 
  //for(int i=x) 
}


// board = number of board <1,6>
// piece = number of piece which is / is not in stack
// in_stack = determines if it's picked or in stack
// cursor = where the cursor in the stack is located
#define ROWS 4
#define COLS 4

#define MAPS 6
#define PIECES_PER_MAP 4
#define NUM_PIECES 12


int pieces[NUM_PIECES][ROWS][COLS]=
{

{{0,0,0,0},
 {1,1,0,0},
 {1,0,0,0},
 {1,0,0,0}}, 

{{1,1,0,0},
 {1,0,0,0},
 {1,0,0,0},
 {1,0,0,0}}, 

{{1,0,0,0},
 {1,1,0,0},
 {1,0,0,0},
 {1,0,0,0}},

{{0,0,0,0},
 {0,0,0,0},
 {1,1,0,0},
 {1,1,0,0}}, 

{{0,0,0,0},
 {0,1,0,0},
 {1,1,0,0},
 {1,0,0,0}},

{{0,0,0,0},
 {1,0,0,0},
 {1,1,0,0},
 {1,1,0,0}},

{{0,0,0,0},
 {1,1,0,0},
 {0,1,0,0},
 {0,1,1,0}},

{{0,0,0,0},
 {1,0,0,0},
 {1,1,0,0},
 {1,0,0,0}},

{{0,0,0,0},
 {1,0,0,0},
 {1,0,0,0},
 {1,0,0,0}},

{{0,0,0,0},
 {0,0,0,0},
 {1,0,0,0},
 {1,1,0,0}},

{{1,0,0,0},
 {1,0,0,0},
 {1,0,0,0},
 {1,0,0,0}}, 

{{0,0,0,0},
 {0,0,0,0},
 {1,0,0,0},
 {1,0,0,0}}

};

int combinations[MAPS][PIECES_PER_MAP]={
  {5,1,11,0}, {4,3,7,8}, {1,5,7,9},
  {5,4,6,11}, {2,4,8,11}, {10,5,0,7}
};

#define OFFSET_STACK edge*2

static void drawStack(uint8_t board){
  for(size_t i=0;i<PIECES_PER_MAP;++i){
    drawShape(pieces[combinations[board][i]],  250, 5+i*OFFSET_STACK);
    i+=1;
    drawShape(pieces[combinations[board][i]], 390, 93+i*OFFSET_STACK);
  }
  
}

void manageStack(uint8_t board, uint8_t piece, _Bool in_stack, uint8_t cursor){
  /*
  for(size_t i=0;i<6;++i){
    lcdReset(0xFFFF);
    drawStack(i);
    sleep(5);

  }
  */
  drawStack(board);

  /*
  switch(board){
    case 1:
      

      break;




  }
  */


}

