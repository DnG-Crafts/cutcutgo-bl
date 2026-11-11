#include "buttons.h"

/*
 * Front-panel buttons (see buttons.h for the pin map).
 * Active low with external pull-ups, so we don't touch the internal
 * pull-ups/pull-downs: we only make each pin a digital input.
 */

/* ANSELx (and its CLR alias at +4 bytes); ports repeat every 0x100 bytes. */
static void button_make_digital_input(GPIO_PIN pin)
{
    uint32_t port = ((uint32_t)pin) >> 4;
    uint32_t bit = ((uint32_t)pin) & 0x0FU;
    volatile uint32_t *anselclr =
        (volatile uint32_t *)((uint32_t)&ANSELA + (port * 0x100U) + 0x04U);

    *anselclr = (1UL << bit);       /* digital (harmless if the pin has no analog function) */
    GPIO_PinInputEnable(pin);
}

void buttons_init(void)
{
    button_make_digital_input(BTN_POWER);
    button_make_digital_input(BTN_LOADUNLOAD);
    button_make_digital_input(BTN_LOGO);
    button_make_digital_input(BTN_PAUSE);
}

/* No debounce here: callers time how long a button is held. */
bool is_pause_button_pressed(void)
{
    return !GPIO_PinRead(BTN_PAUSE);
}

bool is_power_button_pressed(void)
{
    return !GPIO_PinRead(BTN_POWER);
}

bool is_logo_button_pressed(void)
{
    return !GPIO_PinRead(BTN_LOGO);
}

bool is_loadunload_button_pressed(void)
{
    return !GPIO_PinRead(BTN_LOADUNLOAD);
}
