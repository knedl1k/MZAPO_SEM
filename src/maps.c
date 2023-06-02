#include "maps.h"

#include "drawing.h"
#include "colors.h"
#include "perifs_handle.h"
#include "text_display.h"

extern union rgb PRP;
extern union rgb WHT;
extern union rgb BLCK;
extern union rgb GRN;

#define edge 33
#define OFFSET_STACK edge*2
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

uint8_t combinations[MAPS][PIECES_PER_MAP]={
  {5,1,11,0}, {4,3,7,8}, {1,5,7,9},
  {5,4,6,11}, {2,4,8,11}, {10,5,0,7}
};


// DRAW BOARDS
int const t=5; // thickness
int SPx=20-t;  // starting point x
int SPy=30-t;

// BOARD 1
void drawBoard1(void){
  int background[6][6]={{1, 1, 1, 0, 0, 0},{1, 1, 1, 1, 1, 1},{0, 0, 1, 1, 1, 1},
                         {0, 0, 1, 1, 1, 0},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);
  
  for(int i=SPx; i < SPx+3*edge+3*t; ++i)  // 1-
    colorPixelBlackHor(i, SPy);
  for(int i=SPy; i < SPy+2*edge+2*t; ++i)  // 1|
    colorPixelBlackVer(SPx, i);
  for(int i=SPx; i < SPx+2*edge+t; ++i)  // 3-
    colorPixelBlackHor(i, SPy+2*edge+2*t);
  for(int i=SPy; i < SPy+edge+t; ++i)  // 3|
    colorPixelBlackVer(SPx+3*edge+2*t, i);
  for(int i=SPy+2*edge+2*t; i < SPy+4*edge+3*t; ++i)  // 2|
    colorPixelBlackVer(SPx+2*edge, i);
  for(int i=SPx+3*edge+2*t; i < SPx+6*edge+3*t; ++i)  // 2-
    colorPixelBlackHor(i, SPy+edge);
  for(int i=SPx+2*edge; i < SPx+5*edge+2*t; ++i)  // 5-
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  for(int i=SPy+edge; i < SPy+3*edge+3*t; ++i)  // 5|
    colorPixelBlackVer(SPx+6*edge+2*t, i);
  for(int i=SPx+5*edge+2*t; i < SPx+6*edge+2*t; ++i)  // 4-
    colorPixelBlackHor(i, SPy+3*edge+2*t);
  for(int i=SPy+3*edge+2*t; i < SPy+4*edge+3*t; ++i)  // 4|
    colorPixelBlackVer(SPx+5*edge+2*t, i);
  
  lcdRefresh();
}

// BOARD 2
void drawBoard2(void){
  int background[6][6]={{0, 1, 1, 0, 0, 0},{1, 1, 1, 0, 0, 0},{1, 1, 1, 1, 1, 0},
                         {1, 1, 1, 1, 1, 0},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);

  for(int i=SPx; i < SPx+edge; ++i)
    colorPixelBlackHor(i, SPy+edge);
  for(int i=SPy; i < SPy+edge+t; ++i)
    colorPixelBlackVer(SPx+edge, i);
  for(int i=SPx+edge; i < SPx+3*edge+3*t; ++i) // 1 - USED
    colorPixelBlackHor(i, SPy);
  for(int i=SPx+3*edge+2*t; i < SPx+5*edge+3*t; ++i) // 2 - USED
    colorPixelBlackHor(i, SPy+2*edge);
  for(int i=SPx; i < SPx+5*edge+2*t; ++i) // 5 - USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  for(int i=SPy+edge; i < SPy+4*edge+2*t; ++i)  // 1| USED
    colorPixelBlackVer(SPx, i);
  for(int i=SPy; i < SPy+2*edge+t; ++i)  // 3| USED
    colorPixelBlackVer(SPx+3*edge+2*t, i);
  for(int i=SPy+2*edge+t; i < SPy+4*edge+3*t; ++i)  // 4|
    colorPixelBlackVer(SPx+5*edge+2*t, i);

  lcdRefresh();
}

// BOARD 3
void drawBoard3(void){
  int background[6][6]={{0, 1, 1, 1, 0, 0},{1, 1, 1, 1, 0, 0},{1, 1, 1, 1, 1, 0},
                         {1, 1, 1, 1, 1, 0},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);

  for(int i=SPx; i < SPx+edge; ++i)  // OK
    colorPixelBlackHor(i, SPy+edge);
  for(int i=SPy; i < SPy+edge+t; ++i) // OK
    colorPixelBlackVer(SPx+edge, i);
  for(int i=SPx+edge; i < SPx+4*edge+3*t; ++i)  // 1- USED
    colorPixelBlackHor(i, SPy);
  for(int i=SPx+4*edge+2*t; i < SPx+5*edge+3*t; ++i)  // 2- USED
    colorPixelBlackHor(i, SPy+2*edge);
  for(int i=SPx; i < SPx+5*edge+2*t; ++i) // 5- USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  for(int i=SPy+edge; i < SPy+4*edge+2*t; ++i) // 1| OK
    colorPixelBlackVer(SPx, i);
  for(int i=SPy; i < SPy+2*edge+t; ++i)  // 3| USED
    colorPixelBlackVer(SPx+4*edge+2*t, i);
  for(int i=SPy+2*edge+t; i < SPy+4*edge+3*t; ++i)  // 4|
    colorPixelBlackVer(SPx+5*edge+2*t, i);
  
  lcdRefresh();
}

// BOARD 4
void drawBoard4(void){
  int background[6][6]={{1, 1, 0, 0, 0, 0},{1, 1, 0, 0, 0, 0},{1, 1, 1, 0, 1, 0},
                         {1, 1, 1, 1, 1, 0},{0, 0, 1, 1, 1, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);

  for(int i=SPx; i < SPx+2*edge+2*t; ++i) // OK
    colorPixelBlackHor(i, SPy);
  for(int i=SPy; i < SPy+2*edge+t; ++i)  // OK
    colorPixelBlackVer(SPx+2*edge+2*t, i);
  for(int i=SPx+2*edge+2*t; i < SPx+3*edge+3*t; ++i)  // 1- USED
    colorPixelBlackHor(i, SPy+2*edge);
  for(int i=SPx; i < SPx+2*edge+t; ++i)  // 5- USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  for(int i=SPy; i < SPy+4*edge+2*t; ++i)  // 1| OK
    colorPixelBlackVer(SPx, i);
  for(int i=SPy+2*edge; i < SPy+3*edge+t; ++i)  // 3| USED
    colorPixelBlackVer(SPx+3*edge+2*t, i);
  for(int i=SPy+4*edge+2*t; i < SPy+5*edge+3*t; ++i)
    colorPixelBlackVer(SPx+2*edge, i);
  for(int i=SPx+2*edge; i < SPx+5*edge+3*t; ++i)
    colorPixelBlackHor(i, SPy+5*edge+2*t);
  for(int i=SPx+3*edge+2*t; i < SPx+4*edge+t; ++i)
    colorPixelBlackHor(i, SPy+3*edge);
  for(int i=SPy+2*edge; i < SPy+3*edge; ++i)
    colorPixelBlackVer(SPx+4*edge, i);
  for(int i=SPx+4*edge; i < SPx+5*edge+3*t; ++i)
    colorPixelBlackHor(i, SPy+2*edge);
  for(int i=SPy+2*edge; i < SPy+5*edge+2*t; ++i)
    colorPixelBlackVer(SPx+5*edge+2*t, i);
  
  lcdRefresh();
}

// BOARD 5
void drawBoard5(void){
  int background[6][6]={{0, 0, 1, 1, 0, 0},{1, 1, 1, 1, 0, 0},{1, 1, 1, 1, 0, 0},
                         {1, 1, 1, 1, 0, 0},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);

  for(int i=SPx; i < SPx+2*edge+t; ++i)  // OK
    colorPixelBlackHor(i, SPy+edge);
  for(int i=SPy; i < SPy+edge+t; ++i)  // OK
    colorPixelBlackVer(SPx+2*edge, i);
  for(int i=SPx+2*edge; i < SPx+4*edge+3*t; ++i)  // 1- USED
    colorPixelBlackHor(i, SPy);
  for(int i=SPx; i < SPx+4*edge+2*t; ++i)  // 5- USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  for(int i=SPy+edge; i < SPy+4*edge+2*t; ++i) // 1| OK
    colorPixelBlackVer(SPx, i);
  for(int i=SPy; i < SPy+4*edge+3*t; ++i)  // 3| USED
    colorPixelBlackVer(SPx+4*edge+2*t, i);
  
  lcdRefresh();
}

// BOARD 6
void drawBoard6(void){
  int background[6][6]={{0, 1, 1, 1, 0, 0},{1, 1, 1, 1, 0, 0},{0, 1, 1, 1, 1, 1},
                         {0, 1, 1, 1, 1, 1},{0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0}};
  drawShapeLARGE(background, SPx+t, SPy+t);

  for(int i=SPx; i < SPx+edge; ++i)  //
    colorPixelBlackHor(i, SPy+edge);
  for(int i=SPy; i < SPy+edge+t; ++i)//
    colorPixelBlackVer(SPx+edge, i);
  for(int i=SPx+edge; i < SPx+4*edge+3*t; ++i)  // 1- USED
    colorPixelBlackHor(i, SPy);
  for(int i=SPx+4*edge+2*t; i < SPx+6*edge+3*t; ++i)  // 2- USED
    colorPixelBlackHor(i, SPy+2*edge);
  for(int i=SPx+edge; i < SPx+6*edge+2*t; ++i)  // 5- USED
    colorPixelBlackHor(i, SPy+4*edge+2*t);
  for(int i=SPy+edge; i < SPy+2*edge+2*t; ++i)  // 1| OK
    colorPixelBlackVer(SPx, i);
  for(int i=SPy; i < SPy+2*edge+t; ++i)  // 3| USED
    colorPixelBlackVer(SPx+4*edge+2*t, i);
  for(int i=SPy+2*edge+t; i < SPy+4*edge+3*t; ++i)  // 4|
    colorPixelBlackVer(SPx+6*edge+2*t, i);
  for(int i=SPx; i < SPx+edge+t; ++i)  //
    colorPixelBlackHor(i, SPy+2*edge+2*t);
  for(int i=SPy+2*edge+2*t; i < SPy+4*edge+2*t; ++i)  //
    colorPixelBlackVer(SPx+edge, i);
  
  lcdRefresh();
}

// nakresli dilek zadany matici, coords urcuji pozici nejvyssiho ctverecku dilku nejvic vlevo
static void drawShapeNormal(int(*shapeMatrix)[4], int y, int x){
  // ex.: shapeMatrix=[[1, 1 , 0, 0], [0, 1, 0, 0], [0, 1, 0, 0], [0, 0, 0, 0]]
  for(uint8_t i=0; i < 4; ++i)
    for(uint8_t j=0; j < 4; ++j)
      if(shapeMatrix[i][j] == 1)
        drawSquare(BLCK, x+i*edge, y+j*edge);
  
  lcdRefresh();
}
/* draw a stack in a stack area */
static void drawStack(uint8_t board){
  for(size_t i=0;i<PIECES_PER_MAP;++i){
    drawShapeNormal(pieces[combinations[board][i]], 250, 5+i*OFFSET_STACK);
    i+=1;
    drawShapeNormal(pieces[combinations[board][i]], 390, 93+i*OFFSET_STACK);
  }
}
/* function to print pieces in a stack, creates a cursor around them and manage them */
void manageStack(uint8_t board, uint8_t piece, _Bool in_stack, uint8_t cursor){

  drawStack(board);

  /*
  switch(board){
    case 1:
      

      break;




  }
  */


}
