#include "perifs_handle.h"

union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer

void *parlcd_base;
void *spiled_base;
uint32_t last_rotation;

void initMemory(void){
  parlcd_base=map_phys_address(PARLCD_REG_BASE_PHYS,PARLCD_REG_SIZE,0); //0=nechcem to cashovat  
  assert(parlcd_base !=NULL);

  spiled_base=map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  assert(spiled_base!=NULL);
}

/* 
*
* LCD section
*
*/

/*initializes/resets the LCD*/
void lcdReset(void){
  //parlcd_hx8357_init(parlcd_base); //!
  int background_color=0xFFFF;
  for(unsigned short i=0;i<LCD_HEIGHT;++i)
    for(unsigned short j=0;j<LCD_WIDTH;++j)
      fb[j][i].d=background_color;
  lcdRefresh();
}

/*writes all cached changes in frame buffer to LCD*/
void lcdRefresh(void){
  parlcd_write_cmd(parlcd_base, 0x2c);
  for(unsigned short i=0; i<LCD_HEIGHT; ++i)
    for(unsigned short j=0; j<LCD_WIDTH; ++j)
      parlcd_write_data(parlcd_base, fb[j][i].d);

  //fprintf(stderr,"refreshing LCD\n");
}

/*
* 
* knobs section
*
*/

static void defaultKnobs(struct rotation_t *knobs){
  knobs->r_knob_data=0;
  knobs->is_r_pressed=0;
  knobs->g_knob_data=0;
  knobs->is_g_pressed=0;
  knobs->b_knob_data=0;
  knobs->is_b_pressed=0;
}

static uint32_t knobsVal(void){  
  volatile uint32_t* knobs=(volatile uint32_t*)(spiled_base + SPILED_REG_KNOBS_8BIT_o);
  return *knobs;
}

void knobInit(void){
  last_rotation=0x0;
}

/*updates all data related to knobs*/
struct rotation_t updateKnobValues(void){
  struct rotation_t output;
  defaultKnobs(&output);
  knob_t knob; 

  uint32_t knobs_val=knobsVal();

  //Previous values of knobs.
  knob.r_prev=(last_rotation >> 16) & 0xFF;
  knob.g_prev=(last_rotation >> 8) & 0xFF;
  knob.b_prev=(last_rotation >> 0) & 0xFF;

  //Current values of knobs.
  knob.r_cur=(knobs_val >> 16) & 0xFF;
  knob.g_cur=(knobs_val >> 8) & 0xFF;
  knob.b_cur=(knobs_val >> 0) & 0xFF;

  //Clicks of knobs.
  output.is_r_pressed=(knobs_val >> 26) & 0x1;
  output.is_g_pressed=(knobs_val >> 25) & 0x1;
  output.is_b_pressed=(knobs_val >> 24) & 0x1;

  // Red knob
  if(knob.r_cur > knob.r_prev){
    output.r_knob_data=(knob.r_cur-knob.r_prev <= 128)? 1 : -1;
    last_rotation +=(4 << 16) * output.r_knob_data;
  }else if(knob.r_cur < knob.r_prev){
    output.r_knob_data=(knob.r_prev-knob.r_cur <= 128)? -1 : 1;
    last_rotation +=(4 << 16) * output.r_knob_data;
  }else
    output.r_knob_data=0;

  // Green knob
  if(knob.g_cur > knob.g_prev){
    output.g_knob_data=(knob.g_cur-knob.g_prev <= 128)? 1 : -1;
    last_rotation +=(4 << 8) * output.g_knob_data;
  }else if(knob.g_cur < knob.g_prev){
    output.g_knob_data=(knob.g_prev-knob.g_cur <= 128)? -1 : 1;
    last_rotation +=(4 << 8) * output.g_knob_data;
  }else
    output.g_knob_data=0;

  // Blue knob
  if(knob.b_cur > knob.b_prev){
    output.b_knob_data=(knob.b_cur-knob.b_prev <= 128)? 1 : -1;
    last_rotation +=(4 << 0) * output.b_knob_data;
  }else if(knob.b_cur < knob.b_prev){
    output.b_knob_data=(knob.b_prev-knob.b_cur <= 128)? -1 : 1;
    last_rotation +=(4 << 0) * output.b_knob_data;
  }else
    output.b_knob_data=0;

  return output;
}

/*
*
* RGB LED section
*
*/

/*sets RGB1 to specified color*/
void rgb1(union rgb color){
  uint32_t *ptr=spiled_base+SPILED_REG_LED_RGB1_o;
  printf("rgb:%x\n",color.d);
  *ptr=color.d;
}
