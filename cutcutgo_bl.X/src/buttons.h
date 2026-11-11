/*
 * File:   buttons.h
 * Author: virtualabs
 *
 * Created on 22 septembre 2023, 01:14
 */
#include "configuration.h"
#include "definitions.h"

/*
 * Front-panel buttons, Cricut Maker 3 main board (SCM-84-100-X7,
 * PIC32MK1024MCF100). Found by watching each input pin while pressing:
 * all are active low, with external pull-ups on the board.
 *
 *   Power           RF13
 *   Load/Unload     RF12
 *   Cricut logo     RE15
 *   Pause           RE14
 *
 * buttons.c derives everything (port, analog select) from these values.
 */
#define     BTN_POWER       GPIO_PIN_RF13
#define     BTN_LOADUNLOAD  GPIO_PIN_RF12
#define     BTN_LOGO        GPIO_PIN_RE15
#define     BTN_PAUSE       GPIO_PIN_RE14

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif

void buttons_init(void);
bool is_pause_button_pressed(void);
bool is_power_button_pressed(void);
bool is_logo_button_pressed(void);
bool is_loadunload_button_pressed(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */
