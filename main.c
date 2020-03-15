#define ADC_VAL_1 256
#define ADC_VAL_2 512
#define ADC_VAL_3 768
#define ADC_VAL_4 1013
#define ADC_HYSTERESIS 10

#include "mcu_os.h"
#include "config.h"

void button1_task(void);
void button2_task(void);
void adc_task(void);
bool getButton1(void);
bool getButton2(void);
void setLed1(bool b);
void setLed2(bool b);
void setLed3(bool b);
void setLed4(bool b);
void increase_pwm(void);
void decrease_pwm(void);
uint16_t getAdcVal(void);

// var to store current pwm value
static uint16_t pwm_val=0;

int main( void )
{
  // LED init
  GPIO_Init(LED1_PORT, LED1_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(LED2_PORT, LED2_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(LED3_PORT, LED3_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(LED4_PORT, LED4_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  
  // buttons init
  GPIO_Init(BUTTON1_PORT, BUTTON1_PIN, GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(BUTTON2_PORT, BUTTON2_PIN, GPIO_MODE_IN_FL_NO_IT);  

  // ADC init
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_3, ADC1_PRESSEL_FCPU_D8, ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_ALL, DISABLE);
  ADC1_Cmd(ENABLE);
  ADC1_StartConversion();
  
  // PWM init
  TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, 4095, 0);
  TIM1_OC2Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE, 2050,
             TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET, 
             TIM1_OCNIDLESTATE_RESET);
  TIM1_Cmd(ENABLE);
  TIM1_CtrlPWMOutputs(ENABLE);
  
  mcu_os_add_task(button1_task, 10);
  mcu_os_add_task(button2_task, 10);
  mcu_os_add_task(adc_task, 500);
  
  mcu_os_init();
  return 0;
}

void button1_task(void)
{
  static uint8_t cnt=0;
  static bool state = FALSE;
  bool state_current = getButton1();
  if(state_current != state)
  {
    if(cnt++ == 5)
    {
      state=state_current;
      cnt=0;
      if(state)
      {
        increase_pwm();
      }
    }
  }
  else
  {
    cnt=0;
  }
}

void button2_task(void)
{
  static uint8_t cnt=0;
  static bool state = FALSE;
  bool state_current = getButton2();
  if(state_current != state)
  {
    if(cnt++ == 5)
    {
      state=state_current;
      cnt=0;
      if(state)
      {
        decrease_pwm();
      }
    }
  }
  else
  {
    cnt=0;
  }
}

void adc_task(void)
{
  uint16_t adc_val = getAdcVal();
  if(adc_val<(ADC_VAL_1-ADC_HYSTERESIS)) setLed1(FALSE);
  if(adc_val>(ADC_VAL_1+ADC_HYSTERESIS)) setLed1(TRUE);
  if(adc_val<(ADC_VAL_2-ADC_HYSTERESIS)) setLed2(FALSE);
  if(adc_val>(ADC_VAL_2+ADC_HYSTERESIS)) setLed2(TRUE);
  if(adc_val<(ADC_VAL_3-ADC_HYSTERESIS)) setLed3(FALSE);
  if(adc_val>(ADC_VAL_3+ADC_HYSTERESIS)) setLed3(TRUE);
  if(adc_val<(ADC_VAL_4-ADC_HYSTERESIS)) setLed4(FALSE);
  if(adc_val>(ADC_VAL_4+ADC_HYSTERESIS)) setLed4(TRUE);
}

bool getButton1(void)
{
  return (bool)GPIO_ReadInputPin(BUTTON1_PORT, BUTTON1_PIN);
}

bool getButton2(void)
{
  return (bool)GPIO_ReadInputPin(BUTTON2_PORT, BUTTON2_PIN);
}

void setLed1(bool b)
{
  if(b)
  {
    GPIO_WriteHigh(LED1_PORT, LED1_PIN);
  }
  else
  {
    GPIO_WriteLow(LED1_PORT, LED1_PIN);
  }
}
void setLed2(bool b)
{
  if(b)
  {
    GPIO_WriteHigh(LED2_PORT, LED2_PIN);
  }
  else
  {
    GPIO_WriteLow(LED2_PORT, LED2_PIN);
  }  
}
void setLed3(bool b)
{
  if(b)
  {
    GPIO_WriteHigh(LED3_PORT, LED3_PIN);
  }
  else
  {
    GPIO_WriteLow(LED3_PORT, LED3_PIN);
  }  
}
void setLed4(bool b)
{
  if(b)
  {
    GPIO_WriteHigh(LED4_PORT, LED4_PIN);
  }
  else
  {
    GPIO_WriteLow(LED4_PORT, LED4_PIN);
  }  
}

void increase_pwm(void)
{
  if(pwm_val<=4085)
  {
    pwm_val+=10;
  }
  else
  {
    pwm_val=4095;
  }
  TIM1_SetCompare2(pwm_val);  
}

void decrease_pwm(void)
{
  if(pwm_val>=10)
  {
    pwm_val-=10;
  }
  else
  {
    pwm_val=0;
  }
  TIM1_SetCompare2(pwm_val);
}

uint16_t getAdcVal(void)
{
  uint16_t val;
  while(ADC1_GetFlagStatus(ADC1_FLAG_EOC) == RESET); // be sure that conversion is complete
  val=ADC1_GetConversionValue();
  ADC1_StartConversion();
  return val;
}
