#ifndef RENDER_MENU_H
#define RENDER_MENU_H

#include <stdint.h>
#include "colors.h"

#ifdef __cplusplus
extern "C" {
#endif

void renderMenu(uint8_t selected);
void menuReaction(void);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif
