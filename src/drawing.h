#ifndef DRAWING_MAIN_H
#define DRAWING_MAIN_H

#include "colors.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void colorPixel(union rgb color, int x, int y);
void drawRectangle(union rgb color, int x, int y, int width, int height);
void drawSquare(union rgb color, int x, int y);
int* drawShape(int (*shapeMatrix)[4], int* y, int* x, int draw);


typedef struct {
  int posX;
  int posY;
  int shape[4][4];
} GetResult;


GetResult drawShapeBasedOnKnobs(int (*shape)[4], int *posX, int *posY, int knobLeftState, int knobRightState); 
GetResult rotateLeft2(int(*matrix)[4], int pos[2]);
GetResult rotateRight2(int(*matrix)[4], int pos[2]);

void colorPixel_black_hor(int x, int y); 
void colorPixel_black_ver(int x, int y); 
void drawShapeLARGE(int (*shapeMatrix)[6], int y, int x); 
void drawBoard1(int edge); 
void drawBoard2(int edge); 
void drawBoard3(int edge); 
void drawBoard4(int edge); 
void drawBoard5(int edge); 
void drawBoard6(int edge); 

void drawFullRowBox(union rgb color, int x, int y);



#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*DRAWING_MAIN_H*/
