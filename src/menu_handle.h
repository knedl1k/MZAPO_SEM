#ifndef RENDER_MENU_H
#define RENDER_MENU_H

#include <stdint.h>
#include "colors.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t renderMenu(void);
void menuReaction(_Bool red, _Bool green, _Bool blue);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif
