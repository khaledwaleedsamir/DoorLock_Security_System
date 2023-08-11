# DoorLock_Security_System
Simple door lock system using 2 AVR atmega32 microcontrollers communicating with each other via UART, the first microcontroller is the Human Machine Interface and the second one is the Control MCU, the HMI MCU contains a keypad for the user to enter the password and an lcd display, the control MCU controls the motor for opening the door and the buzzer and some leds and has an external EEPROM communicating via I2C, when the user launches the system for the first time he is asked to create his password and confirm it, his password is then saved in the EEPROM, the 2 main options after creating a password are to open the door or to change the password, both options require the user to enter his password, the user has 3 maximum attempts to enter a wrong password before getting blocked for 60 seconds and the buzzer is turned on during those 60 seconds.
