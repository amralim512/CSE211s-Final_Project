#include "mbed.h"

// Shift register pins (common anode)
DigitalOut shiftRegLatch(D4);
DigitalOut shiftRegClock(D7);
DigitalOut shiftRegData(D8);

// Buttons (Reset and Voltage Display Buttons)
DigitalIn resetButton(A1), voltageDisplayButton(A3);

// ADC for potentiometer (A0)
AnalogIn potentiometer(A0);

// Common anode segment patterns (0-9 with decimal point)
const uint8_t sevenSegPatterns[10] = {
    static_cast<uint8_t>(~0x3F), // 0
    static_cast<uint8_t>(~0x06), // 1
    static_cast<uint8_t>(~0x5B), // 2
    static_cast<uint8_t>(~0x4F), // 3
    static_cast<uint8_t>(~0x66), // 4
    static_cast<uint8_t>(~0x6D), // 5
    static_cast<uint8_t>(~0x7D), // 6
    static_cast<uint8_t>(~0x07), // 7
    static_cast<uint8_t>(~0x7F), // 8
    static_cast<uint8_t>(~0x6F)  // 9
};

// Digit positions (left to right)
const uint8_t digitPositions[4] = {0x01, 0x02, 0x04, 0x08};

// Timer and voltage variables
volatile int elapsedSeconds = 0, elapsedMinutes = 0;
volatile float minimumVoltage = 3.3f, maximumVoltage = 0.0f;
Ticker timerTicker;

// Function prototypes
void incrementTime();
void shiftOutByte(uint8_t value);
void sendToShiftRegister(uint8_t segments, uint8_t digit);
void displayValue(int number, bool showDecimal = false, int decimalPos = -1);

// ISR for timer updates
void incrementTime() {
    elapsedSeconds++;
    if (elapsedSeconds >= 60) {
        elapsedSeconds = 0;
        elapsedMinutes = (elapsedMinutes + 1) % 100;
    }
}

// Shift register driver
void shiftOutByte(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        shiftRegData = (value & (1 << i)) ? 1 : 0;
        shiftRegClock = 1;
        shiftRegClock = 0;
    }
}

// Write data to shift register
void sendToShiftRegister(uint8_t segments, uint8_t digit) {
    shiftRegLatch = 0;
    shiftOutByte(segments);
    shiftOutByte(digit);
    shiftRegLatch = 1;
}

// Display number with optional decimal point
void displayValue(int number, bool showDecimal, int decimalPos) {
    int digits[4] = {
        (number / 1000) % 10,
        (number / 100) % 10,
        (number / 10) % 10,
        number % 10
    };

    for (int i = 0; i < 4; i++) {
        uint8_t pattern = sevenSegPatterns[digits[i]];
        if (showDecimal && i == decimalPos) pattern &= ~0x80; // Enable DP
        sendToShiftRegister(pattern, digitPositions[i]);
        ThisThread::sleep_for(2ms);
    }
}

int main() {
    // Initialize hardware
    resetButton.mode(PullUp);
    voltageDisplayButton.mode(PullUp);
    timerTicker.attach(&incrementTime, 1.0f); // 1-second updates

    while (1) {
        // Reset timer on resetButton press
        if (!resetButton) {
            elapsedSeconds = 0;
            elapsedMinutes = 0;
            ThisThread::sleep_for(200ms); // Debounce
        }

        // Read potentiometer voltage
        float voltage = potentiometer.read() * 3.3f; // Convert to volts (0-3.3V)

        // Update min/max voltages
        if (voltage < minimumVoltage) minimumVoltage = voltage;
        if (voltage > maximumVoltage) maximumVoltage = voltage;

        // Display voltage if voltageDisplayButton pressed, else display time
        if (!voltageDisplayButton) {
            int voltageScaled = static_cast<int>(voltage * 100); // e.g., 2.45V → 245
            displayValue(voltageScaled, true, 1); // Show as X.XX
        } else {
            int timeDisplay = elapsedMinutes * 100 + elapsedSeconds; // MMSS format
            displayValue(timeDisplay);
        }
    }
}