#ifndef DRAWING_MAIN_H
#define DRAWING_MAIN_H

#include "colors.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void color_pixel(union rgb color, int x, int y);
void drawRectangle(union rgb color, int x, int y, int16_t width, uint16_t height);
void drawSquare(int x, int y);
void drawShape(int (*shapeMatrix)[4], int y, int x);
int (*rotateLeft(int (*matrix)[4]))[4];
int (*rotateRight(int (*matrix)[4]))[4];

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*DRAWING_MAIN_H*/
