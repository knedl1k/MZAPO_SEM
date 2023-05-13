#ifndef PARLCD_MAIN_H
#define PARLCD_MAIN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void prepare_lcd(void);
void lcd_frame(void);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*PARLCD_MAIN_H*/