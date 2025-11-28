# Smart-Air-Condition-System
This project presents a simple and efficient temperature control system built using the ATmega328P microcontroller and the LM35DZ temperature sensor. The system continuously monitors the surrounding environment and automatically responds when the measured temperature goes above or below a predefined threshold.
In the initial phase, we implemented the code necessary to display the temperature on the LCD in Proteus.
This section was also hardware-packaged and tested on the board.
Also, this part was closed and tested as hardware on the board. The documentation of this implementation is available in the image folder. 
At the beginning, these tasks are performed:
* - Set the direction of the data and control pins as outputs
* - Initial delay after power-on
* - Set the 4-bit mode
* - Set the display to two lines, 5x8 dots
* - Turn on the display, turn off the cursor
* - Enable Auto-increment address
* - Clear the page
In this process, the code necessary to send data to the lcd has been written. In such a way that it first sets the rs bit to zero. Then it sends the desired command or word in ascii mode.
It also clears the screen by sending the command 0x01 to the lcd.
In current commands, you can pass a complete string to the lcd_print function so that this function prints this input string on the lcd.
future:
In the rest of the project, you just need to use the thermometer module to receive the ambient temperature and display it on this LCD. You can also activate a trigger when the temperature rises or falls below a certain value.
Next, buttons will be added to the project to determine the temperature.