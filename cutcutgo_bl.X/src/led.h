#ifndef __INC_LED_H
#define __INC_LED_H

#include "configuration.h"
#include "definitions.h"

/*
 * Front-panel LEDs, Cricut Maker 3 main board (SCM-84-100-X7,
 * PIC32MK1024MCF100). Found by driving each candidate pin in turn.
 * All are ACTIVE HIGH (pin driven high = LED on).
 *
 *   Power ring, white   RB7
 *   Power ring, red     RC10
 *   Power ring, blue    RD15
 *   Load/Unload, white  RD12
 *   Cricut logo, white  RD13
 *   Pause, blue         RD14
 *
 * Not used here: the white carriage light is on RG7 (on when driven LOW).
 *
 * DO NOT DRIVE RB10: it moves the blade-down actuator. (It was the
 * "pause LED" in the original Cricut Maker / PIC32MX pin map.)
 */
#define     LED_PWR_WHITE   GPIO_PIN_RB7
#define     LED_PWR_RED     GPIO_PIN_RC10
#define     LED_PWR_BLUE    GPIO_PIN_RD15
#define     LED_UPDOWN      GPIO_PIN_RD12     /* Load/Unload button LED */
#define     LED_LOGO        GPIO_PIN_RD13     /* Cricut logo button LED */
#define     LED_PAUSE       GPIO_PIN_RD14


/**
 * Exported functions
 **/

/* LED initialization. */
void led_init(void);

/* LED switch on/off. */
void led_set_logo(bool enable);
void led_set_pause(bool enable);
void led_set_power(bool blue, bool white, bool red);
void led_set_updown(bool enable);
void led_toggle_updown(void);


#endif /* __INC_LED_H */
