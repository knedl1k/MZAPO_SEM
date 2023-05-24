#include "perifs_handle.h"

union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer

void *parlcd_base;
void *spiled_base;

void lcdInit(void){
  parlcd_base=map_phys_address(PARLCD_REG_BASE_PHYS,PARLCD_REG_SIZE,0); //0=nechcem to cashovat  
  assert(parlcd_base !=NULL);
}

/*initializes/resets the LCD*/
void lcdReset(void){
  parlcd_hx8357_init(parlcd_base);
  int background_color=0x0000;
  for(unsigned short i=0;i<LCD_HEIGHT;++i)
    for(unsigned short j=0;j<LCD_WIDTH;++j)
      fb[j][i].d=background_color;
  lcdFrame();
}

/*writes all cached changes in frame buffer to LCD*/
void lcdFrame(void){
  parlcd_write_cmd(parlcd_base, 0x2c);
  for (unsigned short i=0; i<LCD_HEIGHT; ++i)
    for (unsigned short j=0; j<LCD_WIDTH; ++j)
      parlcd_write_data(parlcd_base, fb[j][i].d);

  fprintf(stderr,"refreshing LCD\n");
}

void knobInit(void){
  spiled_base=map_phys_address(SPILED_REG_BASE_PHYS,SPILED_REG_SIZE,0);
  assert(spiled_base!=NULL);
}


/*returns knobs combined value*/
uint32_t knobsVal(void){
  uint32_t *knobs=(spiled_base+SPILED_REG_KNOBS_8BIT_o);
  return *knobs;
}

/*returns red knob value*/
uint8_t redKnobVal(void){
  uint32_t knobs_val=knobsVal();
  uint32_t mask = ((1 << 8) - 1) << 17;
  return knobs_val & mask;
}
_Bool isRedPressed(void){
  uint32_t knobs_val=knobsVal();
  uint32_t mask = ((1 << 1) - 1) << 26;
  return knobs_val & mask;
}
/*returns green knob value*/
uint8_t greenKnobVal(void){
  uint32_t knobs_val=knobsVal();
  uint32_t mask = ((1 << 8) - 1) << 9;
  return knobs_val & mask;
}
_Bool isGreenPressed(void){
  uint32_t knobs_val=knobsVal();
  uint32_t mask = ((1 << 1) - 1) << 25;
  return knobs_val & mask;
}
/*returns blue knob value*/
uint8_t blueKnobVal(void){
  uint32_t knobs_val=knobsVal();
  uint32_t mask = ((1 << 8) - 1) << 0;
  return knobs_val & mask;
}
_Bool isBluePressed(void){
  uint32_t knobs_val=knobsVal();
  uint32_t mask = ((1 << 1) - 1) << 24;
  return knobs_val & mask;
}




/*sets RGB1 to specified color*/
void rgb1(union rgb color){
  uint32_t *ptr=spiled_base+SPILED_REG_LED_RGB1_o;
  printf("rgb:%x\n",color.d );
  *ptr=color.d;
}
