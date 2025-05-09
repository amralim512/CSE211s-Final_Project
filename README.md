# CSE211s Final Project

Welcome to the **CSE211s Final Project** repository! This project involves implementing a real-time clock (RTC) and an analog signal display using the Nucleo board and the Arduino multifunction shield. The project has been developed using the Mbed IDE and demonstrates embedded systems programming and hardware interfacing.

## Table of Contents

- [About the Project](#about-the-project)
- [Team Members](#team-members)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

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

## Team Members

- **Abdelrhman Yasser Adel** - ID: 2000414
- **Amr Adel Abdel Alim** - ID: 2000959

## Features

- Real-Time Clock (RTC) functionality with restart capability.
- Analog-to-Digital Conversion (ADC) for voltage measurement.
- Dynamic 7-segment display switching between time and voltage values.
- Seamless integration of hardware components via the Nucleo board and Arduino multifunction shield.

## Technologies Used

- **Mbed IDE** for embedded systems development.
- **Nucleo Board** as the microcontroller platform.
- **Arduino Multifunction Shield** for interfacing switches, potentiometer, and 7-segment display.

## Installation

To set up the project locally:

1. Clone the repository:
   ```bash
   git clone https://github.com/amralim512/CSE211s-Final_Project.git
   ```
2. Import the project into the **Mbed IDE**.

3. Connect the **Nucleo board** and ensure the hardware setup matches the project requirements.

4. Compile and flash the code to the board.

## Usage

1. Connect the Nucleo board with the Arduino multifunction shield.
2. Power on the board and observe the 7-segment display:
   - The display will start counting time from zero.
3. Interact with the system:
   - **Press S1**: Restart the clock.
   - **Press S3**: Display the ADC input voltage in volts.
   - **Release S3**: Switch back to displaying time.

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new feature branch:
   ```bash
   git checkout -b feature/YourFeature
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add YourFeature"
   ```
4. Push to the branch:
   ```bash
   git push origin feature/YourFeature
   ```
5. Open a Pull Request.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Contact

If you have any questions or want to get in touch, please contact:

- **Abdelrhman Yasser Adel** - ID: 2000414
- **Amr Adel Abdel Alim** - ID: 2000959
- GitHub: [amralim512](https://github.com/amralim512)

Feel free to contribute or report issues on GitHub!
