#ifndef DRAWING_MAPS_H
#define DRAWING_MAPS_H

#include "colors.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif



void drawBoard1(void);
void drawBoard2(void);
void drawBoard3(void);
void drawBoard4(void);
void drawBoard5(void);
void drawBoard6(void);

void manageStack(uint8_t board, uint8_t piece, _Bool in_stack, uint8_t cursor);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*DRAWING_MAPS_H*/
