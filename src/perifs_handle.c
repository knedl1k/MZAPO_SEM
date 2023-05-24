#include "perifs_handle.h"

union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer

void *parlcd_base;
void *spiled_base;

_Bool is_r_pressed=0;
_Bool is_g_pressed=0;
_Bool is_b_pressed=0;
uint8_t knob_data;
uint8_t r_knob_data;
uint8_t g_knob_data;
uint8_t b_knob_data;


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
  is_r_pressed=0;
  is_g_pressed=0;
  is_b_pressed=0;
}


/*returns knobs combined value*/
uint32_t knobsVal(void){
  uint32_t *knobs=(spiled_base+SPILED_REG_KNOBS_8BIT_o);
  return *knobs;
}

void updateKnobValues(void){
  char red_knob_value = knob_data & 0b100;
  char green_knob_value = knob_data & 0b010;
  char blue_knob_value = knob_data & 0b001;

  is_r_pressed = 0;
  is_g_pressed = 0;
  is_b_pressed = 0;

  uint32_t knobs_value=knobsVal();

  knob_data = (knobs_value) >> 24;
  r_knob_data = (knobs_value >> 16) & 0xFF;
  g_knob_data = (knobs_value >> 8) & 0xFF;
  b_knob_data = (knobs_value) & 0xFF;

  if (red_knob_value - (knob_data & 0b100) == 0b100)
    is_r_pressed = 1;
  if (green_knob_value - (knob_data & 0b010) == 0b010)
    is_g_pressed = 1;
  if (blue_knob_value - (knob_data & 0b001) == 0b001)
    is_b_pressed = 1;
}




/*sets RGB1 to specified color*/
void rgb1(union rgb color){
  uint32_t *ptr=spiled_base+SPILED_REG_LED_RGB1_o;
  printf("rgb:%x\n",color.d );
  *ptr=color.d;
}
