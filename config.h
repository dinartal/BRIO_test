/*
 * config.h
 *
 * Created: 15.03.2020
 * Author: Dinar Talibullin
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

// leds
#define LED1_PORT GPIOC // 25
#define LED2_PORT GPIOC // 50
#define LED3_PORT GPIOC // 75
#define LED4_PORT GPIOC // 100

#define LED1_PIN GPIO_PIN_3
#define LED2_PIN GPIO_PIN_4
#define LED3_PIN GPIO_PIN_5
#define LED4_PIN GPIO_PIN_6

// buttons
#define BUTTON1_PORT GPIOD // -
#define BUTTON2_PORT GPIOD // +

#define BUTTON1_PIN GPIO_PIN_6
#define BUTTON2_PIN GPIO_PIN_5

#endif /* CONFIG_H_ */