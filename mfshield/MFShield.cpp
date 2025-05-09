#include "MFShield.h"

MFShield::MFShield() :
    led_pins{DigitalOut(PA_13), DigitalOut(PA_12), DigitalOut(PA_11), DigitalOut(PA_10)},  // Example pins
    key_pins{DigitalIn(PA_1), DigitalIn(PA_2), DigitalIn(PA_3)},                          // Example pins
    trimmer_pin(A0), buzzer_pin(PB_3), spi(PA_7, PA_6, PA_5)                              // SPI pins
{
    for (int i = 0; i < 4; i++) {
        led_pins[i] = 0;  // Initialize LEDs to OFF
    }
    for (int i = 0; i < 3; i++) {
        key_pins[i].mode(PullUp);  // Enable pull-up resistors for buttons
    }
    buzzer_pin = 0;  // Initialize buzzer to OFF
    spi.format(8, 3);  // Configure SPI format
    spi.frequency(1000000);  // Set SPI frequency
    t_disp = t_buttons = t_beep = 0;
    key_mask_pre = 0;
    disp_enable = true;
    disp_leading_zero = false;
}

void MFShield::onKeyPress(Callback<void(uint8_t)> func) {
    onKeyPress_func = func;
}

uint16_t MFShield::trimmer() {
    return trimmer_pin.read_u16();  // Read raw potentiometer value
}

uint16_t MFShield::getTrimmerValue() {
    return trimmer();
}

void MFShield::setLed(uint8_t led, bool state) {
    if (led < 1 || led > 4) return;
    led_pins[led - 1] = state;
}

bool MFShield::getLed(uint8_t led) {
    if (led < 1 || led > 4) return false;
    return led_pins[led - 1].read();
}

void MFShield::beep(uint16_t ms) {
    buzzer_pin = 1;  // Turn on the buzzer
    t_beep = Kernel::get_ms_count() + ms;
}

void MFShield::display(int16_t val, bool leading_zero) {
    raw_segment[0] = val / 1000 % 10;
    raw_segment[1] = val / 100 % 10;
    raw_segment[2] = val / 10 % 10;
    raw_segment[3] = val % 10;
    disp_leading_zero = leading_zero;
}

void MFShield::showDisplay(bool visible) {
    disp_enable = visible;
    if (!visible) {
        spi.write(0xFF);
    }
}

void MFShield::loop() {
    uint32_t time = Kernel::get_ms_count();

    // Update numeric display
    if (disp_enable && time - t_disp >= MFS_DISP_SCAN_INTERVAL_MS) {
        t_disp = time;
        current_segment = (current_segment + 1) % 4;
        spi.write(raw_segment[current_segment]);
    }

    // Handle button polling
    if (onKeyPress_func && time - t_buttons >= MFS_BUTTONS_POLLING_INTERVAL_MS) {
        t_buttons = time;
        uint8_t key_mask = 0;
        for (int i = 0; i < 3; i++) {
            if (!key_pins[i].read()) key_mask |= (1 << i);
        }

        if (key_mask != key_mask_pre) {
            key_mask_pre = key_mask;
            onKeyPress_func(key_mask);
        }
    }

    // Turn off buzzer after timeout
    if (t_beep && time >= t_beep) {
        buzzer_pin = 0;
        t_beep = 0;
    }
}