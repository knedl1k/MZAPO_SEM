#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "colors.h"
#include "drawing.h"
#include "perifs_handle.h"

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
  // left and right EDGE
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
  // top and bottom EDGE
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

void drawSquare(union rgb color, int x, int y){
  // left and right EDGE
  for(int i=x; i < x+EDGE; ++i){
    colorPixel(color, i, y);
    colorPixel(color, i, y+1);
    colorPixel(color, i, y+2);
    colorPixel(color, i, y+3);
    colorPixel(color, i, y+4);

    colorPixel(color, i+5, y+EDGE);
    colorPixel(color, i+5, y+EDGE+1);
    colorPixel(color, i+5, y+EDGE+2);
    colorPixel(color, i+5, y+EDGE+3);
    colorPixel(color, i+5, y+EDGE+4);
  }
  // top and bottom EDGE
  for(int i=y; i < y+EDGE+5; ++i){
    colorPixel(color, x, i);
    colorPixel(color, x+1, i);
    colorPixel(color, x+2, i);
    colorPixel(color, x+3, i);
    colorPixel(color, x+4, i);

    colorPixel(color, x+EDGE, i);
    colorPixel(color, x+EDGE+1, i);
    colorPixel(color, x+EDGE+2, i);
    colorPixel(color, x+EDGE+3, i);
    colorPixel(color, x+EDGE+4, i);
  }
}

// draw a piece of the specified matrix, the coords determine the position of the leftmost square of the piece
int* drawShape(_Bool(*shapeMatrix)[4], int* y, int* x, int draw){ 
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
          result[0] = *x + i*EDGE; 
          result[1] = *y + j* EDGE; 
        }
        if (draw == 1){ 
          //printf("if draw == 1\n"); 
          drawSquare(BLCK, *x+i*EDGE, *y+j*EDGE);

        }
        // printf("posX: %d, posY: %d\n", result[0], result[1]);      
      }
      printf(" %d", shapeMatrix[i][j]);

    }
    printf("\n");

  } 
  return result; 
}

GetResult rotateLeft2(_Bool(*matrix)[4], int pos[2]){
  GetResult result;
  _Bool(*rotatedShape)[4] = malloc(4 * sizeof(*rotatedShape));

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
  memcpy(result.shape, rotatedShape, 4 * 4 * sizeof(_Bool));

  free(rotatedShape);
  return result;
}

GetResult rotateRight2(_Bool(*matrix)[4], int pos[2]){ 
  GetResult result;
  _Bool(*rotatedShape)[4] = malloc(4 * sizeof(*rotatedShape));

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
  result.posX = pos[0];
  result.posY = pos[1];
  memcpy(result.shape, rotatedShape, 4 * 4 * sizeof(_Bool));

  free(rotatedShape);
  return result;
}

GetResult drawShapeBasedOnKnobs(_Bool (*shape)[4], int *posX, int *posY, int knobLeftState, int knobRightState) {
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

void drawShapeLARGE(_Bool(*shapeMatrix)[6], int y, int x){
  // ex.: shapeMatrix=[[1, 1 , 0, 0], [0, 1, 0, 0], [0, 1, 0, 0], [0, 0, 0, 0]]
  for(int i=0; i < 6; ++i){
    for(int j=0; j < 6; ++j){
      if(shapeMatrix[i][j] == 1){
        drawSquare(RED, x+i*EDGE, y+j*EDGE);
        //printf("HERE 6 ");
      }
    }
  }
  lcdRefresh();
}
