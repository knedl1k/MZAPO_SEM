#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "colors.h"
#include "drawing.h"
#include "perifs_handle.h"
#include "maps.h"

#define EDGE 33 //edge of the squares that will make up the pieces

union rgb color;
extern union pixel fb[LCD_WIDTH][LCD_HEIGHT];  // frame buffer
extern union rgb PRP;
extern union rgb WHT;
extern union rgb BLCK;
extern union rgb GRN;
extern union rgb RED;
extern union rgb BLU;

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
  fb[x][y+0].d=0;
  fb[x][y+1].d=0;
  fb[x][y+1].d=0;
  fb[x][y+3].d=0;
  fb[x][y+4].d=0;
}

void colorPixelBlackVer(int x, int y){
  fb[x+0][y].d=0;
  fb[x+1][y].d=0;
  fb[x+2][y].d=0;
  fb[x+3][y].d=0;
  fb[x+4][y].d=0;
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
          drawSquare(BLCK, *x+i*edge, *y+j*edge);

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

  result.posX = pos[0];
  result.posY = pos[1];

  // Perform right rotation
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      rotatedShape[i][j] = matrix[3 - j][i];
    }
  }

  // Update position
  int* drawShapeResult = drawShape(rotatedShape, &pos[1], &pos[0], 1);
  pos[0] = drawShapeResult[0];
  pos[1] = drawShapeResult[1];
  free(drawShapeResult);

  // Set values in the result struct
  /*
  result.posX = pos[0];
  result.posY = pos[1];
  */
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
        drawSquare(RED, x+i*edge, y+j*edge);
      }
    }
  }
  lcdRefresh();
}
