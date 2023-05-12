#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
//#include "serialize_lock.h"
#include "font_types.h"
#include "parlcd_main.h"
//#include "text_display.h"




/*initializes the LCD*/
void prepare_lcd(void){
  parlcd_base=map_phys_address(PARLCD_REG_BASE_PHYS,PARLCD_REG_SIZE,0); //0=nechcem to cashovat  
  assert(parlcd_base !=NULL);
  parlcd_hx8357_init(parlcd_base);
  int background_color=0xffff;
  for(unsigned short i=0;i<LCD_HEIGHT;i++)
    for(unsigned short j=0;j<LCD_WIDTH;j++)
      fb[j][i].d=background_color;
  lcd_frame();
}
/*writes all cached changes in frame buffer to LCD*/
void lcd_frame(void){
  parlcd_write_cmd(parlcd_base, 0x2c);
  for (unsigned short i=0; i<LCD_HEIGHT; i++)
    for (unsigned short j=0; j<LCD_WIDTH; j++)
      parlcd_write_data(parlcd_base, fb[j][i].d);

  printf("zapisuju\n");
}
