# CSE211s Final Project

Welcome to the **CSE211s Final Project** repository! This project involves implementing a real-time clock (RTC) and an analog signal display using the Nucleo board and the Arduino multifunction shield. The project has been developed using the Mbed IDE and demonstrates embedded systems programming and hardware interfacing.

## Table of Contents

- [About the Project](#about-the-project)
- [Team Members](#team-members)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Usage](#usage)
- [Project Demo](#project-demo)

## Team Members

- **Abdelrhman Yasser Adel** - ID: 2000414
- **Amr Adel Abdel Alim** - ID: 2000959
- **Ahmed Yousry Mohamed** - ID:2002051

## About the Project

This project uses the Nucleo board and the Arduino multifunction shield to implement the following functionality:

### Real-Time Clock (RTC)

- After the board resets, the 7-segment display begins counting the elapsed time in minutes and seconds starting from zero.
  - The least two digits count the **seconds**.
  - The higher digits count the **minutes**.
- Pressing **switch S1** at any time restarts the clock from zero.

### Analog Signal Value Display

- The **on-board potentiometer** is used to generate a variable voltage input to the on-chip ADC.
- Pressing **switch S3**:
  - The 7-segment display shows the ADC’s input voltage value in volts.
  - The RTC continues running in the background while S3 is pressed.
- Releasing **switch S3**:
  - The 7-segment display switches back to displaying time.

## Features

- Real-Time Clock (RTC) functionality with restart capability.
- Analog-to-Digital Conversion (ADC) for voltage measurement.
- Dynamic 7-segment display switching between time and voltage values.
- Seamless integration of hardware components via the Nucleo board and Arduino multifunction shield.

## Technologies Used

- **Mbed IDE** for embedded systems development.
- **Nucleo Board** as the microcontroller platform.
- **Arduino Multifunction Shield** for interfacing switches, potentiometer, and 7-segment display.

## Usage

1. Connect the Nucleo board with the Arduino multifunction shield.
2. Power on the board and observe the 7-segment display:
   - The display will start counting time from zero.
3. Interact with the system:
   - **Press S1**: Restart the clock.
   - **Press S3**: Display the ADC input voltage in volts.
   - **Release S3**: Switch back to displaying time.

## Project Demo

To demonstrate the project, you can upload a video showcasing its functionality. Follow these steps to upload a video to

