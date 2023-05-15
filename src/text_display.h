#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

//#include "parlcd_main.h"
void fbchar(char c,int x, int y, unsigned char scale);
void fontString(char *word, int x, int y, unsigned char scale);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*TEXT_DISPLAY_H*/
