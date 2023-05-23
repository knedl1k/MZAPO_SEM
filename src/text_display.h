#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "font_types.h"
#include "colors.h"

//#include "parlcd_main.h"
void fbchar(char c,int x, int y, union rgb color, unsigned char scale);
void printString(char *word, int x, int y,union rgb color, unsigned char scale);
void drawRectangleWithText(char *str, int x, int y, union rgb color,unsigned char scale);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*TEXT_DISPLAY_H*/
