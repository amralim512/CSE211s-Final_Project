#ifndef MFSHIELD_H
#define MFSHIELD_H

#include "mbed.h"

/* SHIELD HARDWARE PIN DEFINITIONS */
#define MFS_PIN_DISP_CK PA_7  // Example mbed pin
#define MFS_PIN_DISP_CS PA_4  // Example mbed pin
#define MFS_PIN_DISP_DO PA_5  // Example mbed pin
#define MFS_PIN_TRIMMER A0    // Analog pin
#define MFS_PIN_BUZZER PB_3   // Example mbed pin

/* SYSTEM CONSTANTS (Adjust as needed) */
#define MFS_DISP_SCAN_INTERVAL_MS 1
#define MFS_BUTTONS_POLLING_INTERVAL_MS 20

/* CLASS DEFINITION */
class MFShield {
public:
    MFShield();

    void onKeyPress(Callback<void(uint8_t)> func);

    uint16_t trimmer();                // Read onboard potentiometer value
    uint16_t getTrimmerValue();        // Alias for trimmer()

    void setLed(uint8_t led, bool state);
    bool getLed(uint8_t led);

    void beep(uint16_t ms = 100);      // Emit a sound for a specific duration

    void display(int16_t val, bool leading_zero = false);  // Show the number on display
    void showDisplay(bool visible = true);                // Turns on and off the numeric display

    void loop();                       // Main loop to handle updates

private:
    Callback<void(uint8_t)> onKeyPress_func;

    uint8_t key_mask_pre;

    uint32_t t_disp;
    uint32_t t_buttons;
    uint32_t t_beep;

    uint8_t raw_segment[4];
    uint8_t current_segment;
    bool disp_enable;
    bool disp_leading_zero;

    DigitalOut led_pins[4];            // Array of DigitalOut for LEDs
    DigitalIn key_pins[3];             // Array of DigitalIn for buttons
    AnalogIn trimmer_pin;              // AnalogIn for potentiometer
    DigitalOut buzzer_pin;
    SPI spi;                           // SPI for 7-segment control
};

#endif