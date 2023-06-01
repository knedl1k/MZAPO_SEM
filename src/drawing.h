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

void colorPixelBlackHor(int x, int y); 
void colorPixelBlackVer(int x, int y); 
void drawShapeLARGE(int (*shapeMatrix)[6], int y, int x); 
void drawBoard1(void); 
void drawBoard2(void); 
void drawBoard3(void); 
void drawBoard4(void); 
void drawBoard5(void); 
void drawBoard6(void); 

void drawFullRowBox(union rgb color, int x, int y);

//int (*)[4]map1_combi[2][PIECES_PER_MAP]={{piece6,piece2,piece12,piece1},{piece6,piece9,piece1,piece5}};

void manageStack(uint8_t board, uint8_t piece, _Bool in_stack, uint8_t cursor);



#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*DRAWING_MAIN_H*/
