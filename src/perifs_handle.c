#include "perifs_handle.h"

#include "colors.h"
#include "text_display.h"

#define THRESHOLD 128

union pixel fb[LCD_WIDTH][LCD_HEIGHT]; //frame buffer

void *parlcd_base;
void *spiled_base;
uint32_t prev_rotate;

union rgb PRP={.r=255,.g=0,.b=255};
union rgb WHT={.r=255,.g=255,.b=255};
union rgb BLCK={.r=0,.g=0,.b=0};
union rgb GRN={.r=0,.g=255,.b=0};
union rgb RED={.r=255, .g=0, .b=0};
union rgb BLU={.r=0, .g=0, .b=255};


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
void lcdReset(union rgb color){
  //parlcd_hx8357_init(parlcd_base); //!
  int background_color=color.d;
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
  //fprintf(stderr,"DEBUG: refreshing LCD\n");
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
  prev_rotate=0x0;
  struct rotation_t knobs;//!
  /*
  do{  //flush the wrong values
    //sleep(1);
    knobs=updateKnobValues();
    printString("Loading! Please wait.",80,120,BLCK,scaling);
    printString("If it takes longer than 10s",20,220,BLCK,scaling);
    printString("move with the red knob.",20,260,BLCK,scaling);
    printf("r %d g %d b %d\n",knobs.r_knob_data,knobs.g_knob_data,knobs.b_knob_data);
  }while(knobs.r_knob_data!=0 || knobs.g_knob_data!=0 || knobs.b_knob_data!=0);
  */
  lcdReset(WHT);
}

/*updates all data related to knobs*/
struct rotation_t updateKnobValues(void){
  struct rotation_t output;
  defaultKnobs(&output);
  knob_t knobs; 

  uint32_t knobs_val=knobsVal();

  // previous values of rotation
  knobs.r_prev=(prev_rotate >> 16) & 0xFF;
  knobs.g_prev=(prev_rotate >> 8) & 0xFF;
  knobs.b_prev=(prev_rotate >> 0) & 0xFF;

  // current values of rotation
  knobs.r_cur=(knobs_val >> 16) & 0xFF;
  knobs.g_cur=(knobs_val >> 8) & 0xFF;
  knobs.b_cur=(knobs_val >> 0) & 0xFF;

  // clicks of knobs
  output.is_r_pressed=(knobs_val >> 26) & 0x1;
  output.is_g_pressed=(knobs_val >> 25) & 0x1;
  output.is_b_pressed=(knobs_val >> 24) & 0x1;

  //red knob
  if(knobs.r_cur > knobs.r_prev) //clockwise
    output.r_knob_data=(knobs.r_cur-knobs.r_prev <= THRESHOLD)? 1 : -1;
  else if(knobs.r_cur < knobs.r_prev) //counterclockwise
    output.r_knob_data=(knobs.r_prev-knobs.r_cur <= THRESHOLD)? -1 : 1;
  else //no rotation
    output.r_knob_data=0;

  prev_rotate +=(4 << 16) * output.r_knob_data;

  //green knob
  if(knobs.g_cur > knobs.g_prev)
    output.g_knob_data=(knobs.g_cur-knobs.g_prev <= THRESHOLD)? 1 : -1;
  else if(knobs.g_cur < knobs.g_prev)
    output.g_knob_data=(knobs.g_prev-knobs.g_cur <= THRESHOLD)? -1 : 1;
  else
    output.g_knob_data=0;

  prev_rotate +=(4 << 8) * output.g_knob_data;

  //blue knob
  if(knobs.b_cur > knobs.b_prev)
    output.b_knob_data=(knobs.b_cur-knobs.b_prev <= THRESHOLD)? 1 : -1;
  else if(knobs.b_cur < knobs.b_prev)
    output.b_knob_data=(knobs.b_prev-knobs.b_cur <= THRESHOLD)? -1 : 1;
  else
    output.b_knob_data=0;
    
  prev_rotate +=(4 << 0) * output.b_knob_data;
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
  //fprintf(stderr,"DEBUG: rgb1:%x\n",color.d);
  *ptr=color.d;
}

/*sets RGB2 to specified color*/
void rgb2(union rgb color){
  uint32_t *ptr=spiled_base+SPILED_REG_LED_RGB2_o;
  //fprintf(stderr,"DEBUG: rgb2:%x\n",color.d);
  *ptr=color.d;
}

void initRGBStrip(){
  uint32_t *ptr=spiled_base+SPILED_REG_LED_LINE_o;
  *ptr=0xFF;
}

void LEDStrip(uint32_t change){
  uint32_t *ptr=spiled_base+SPILED_REG_LED_LINE_o;
  *ptr=change;


  //*ptr=0xFFFFFFFF;
}
