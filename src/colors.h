#ifndef COLORS_H
#define COLORS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

union rgb{
  uint32_t d;
  struct{
    uint8_t b,g,r;
  };
};




#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*DRAWING_MAIN_H*/
