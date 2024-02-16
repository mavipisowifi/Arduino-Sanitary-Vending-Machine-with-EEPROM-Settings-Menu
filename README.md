# Sanitary Vending Machine with Arduino Uno & Settings Menu using EEPROM
This GitHub repository contains the code and documentation for a 4-tray sanitary vending machine project. Originally designed with a customized STM32 board from a Chinese supplier, the project faced challenges related to unavailability and lack of support during setup. To overcome these obstacles, the team, led by Marvin T. Bangcailan with assistance from Ivan Mamaril, transitioned to using an ARDUINO UNO. The modification process has been documented to facilitate the operational usage of the vending machine.

## Project Overview
This project aims to provide a functional and customizable sanitary vending machine using an Arduino Uno as the main controller. The code for this project is available in the Arduino Code directory.

## Materials Required
To replicate or modify the project, the following materials are needed:
```
1. Arduino Uno
2. LCD I2C 16x2 or higher (ensure it is I2C compatible)
3. 6 Buttons: Item1, Item2, Item3, Item4, Settings, and Reset (Reset button attached to pin: RES and GND)
4. Mosfet Switches
5. Vending machine spiral with limit switch and DC motor
6. Rainbow Cables
7. Pin headers kit
8. 12VDC Power Source (any brand, minimum 5A current)
9. Electronics tools
10. Coin Acceptor
```
### Note: For additional trays and buttons, consider using Arduino Mega or Arduino GIGA for more PWM pins. You can also add a relay module to manipulate a coin acceptor LED frame.

## Code Attribution
If you intend to use or modify the Arduino code for this sanitary vending machine in your own projects, please provide proper attribution to the original creators. Credits go to:

- Marvin T. Bangcailan
- Ivan B. Mamaril

## Getting Started
Clone this repository to your local machine.
Review the Arduino Code for the main codebase.
Ensure you have all the required materials listed above.
Follow the documentation for wiring and setup in the Documentation directory.

## Contributing
Contributions are welcome! Feel free to open issues, suggest improvements, or submit pull requests.

# License
This project is licensed under the MIT License.

### Note: Proper crediting is appreciated when using or modifying the codes for your own projects.
