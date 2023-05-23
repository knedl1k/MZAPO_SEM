#include "perifs_handle.h"

void *parlcd_base;

union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer

//union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer
void *parlcd_base;

/*initializes the LCD*/
void prepare_lcd(void){
  parlcd_base=map_phys_address(PARLCD_REG_BASE_PHYS,PARLCD_REG_SIZE,0); //0=nechcem to cashovat  
  assert(parlcd_base !=NULL);
  parlcd_hx8357_init(parlcd_base);
  int background_color=0x0000;
  for(unsigned short i=0;i<LCD_HEIGHT;++i)
    for(unsigned short j=0;j<LCD_WIDTH;++j)
      fb[j][i].d=background_color;
  lcd_frame();
}
/*writes all cached changes in frame buffer to LCD*/
void lcd_frame(void){
  parlcd_write_cmd(parlcd_base, 0x2c);
  for (unsigned short i=0; i<LCD_HEIGHT; ++i)
    for (unsigned short j=0; j<LCD_WIDTH; ++j)
      parlcd_write_data(parlcd_base, fb[j][i].d);

  fprintf(stderr,"refreshing LCD\n");
}
