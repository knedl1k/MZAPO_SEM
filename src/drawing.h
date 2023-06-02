#ifndef DRAWING_MAIN_H
#define DRAWING_MAIN_H

#include "colors.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  int posX;
  int posY;
  int shape[4][4];
} GetResult;

void colorPixel(union rgb color, int x, int y);
void colorPixelBlackHor(int x, int y); 
void colorPixelBlackVer(int x, int y); 
void drawRectangle(union rgb color, int x, int y, int width, int height);
void drawSquare(union rgb color, int x, int y);
int* drawShape(int (*shapeMatrix)[4], int* y, int* x, int draw);

GetResult rotateLeft2(int(*matrix)[4], int pos[2]);
GetResult rotateRight2(int(*matrix)[4], int pos[2]);
GetResult drawShapeBasedOnKnobs(int (*shape)[4], int *posX, int *posY, int knobLeftState, int knobRightState); 
void drawShapeLARGE(int (*shapeMatrix)[6], int y, int x); 


#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*DRAWING_MAIN_H*/
