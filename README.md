These codes must be loaded into the microcontroller from the Arduino IDE software on Windows.
To upload the program to the microcontroller, follow the following instructions:
  1. Download and install the Arduino IDE software from https://www.arduino.cc/en/software
  2. Update the Tools settings: `Tools` > `Board` [Select `Arduino Nano`]
  3. Update the Tools settings: `Tools` > `Processor` [Select `ATmega328P (Old Bootloader)`]
  4. Update the Tools settinng: `Tools` > `Port` [Select the working port: COM11, COM8 etc]

When you want to upload a program to the microcontroller, follow these instructions:
  1. Connect the USB cable from the Trainer to the computer system before you open the Arduino IDE software. This is important!
  1. After opening the desired program experiment, click on the `Upload` button. (This should be the arrow-right icon on the task bar or you click `Ctrl + U`.)
  2. The code should upload to the microcontroller, BUT if it doesn't...
  3. Select another Port and upload again. (Change to COM8, COM6 COM11 or any available port until it uploads successfully to the microcontroller.)
  4. If you follow the instructions, the program should upload successfully after changing the ports.

To control the devices after upload a program:
  1. Download the Bluetooth Electronics from PlayStore.
  2. Setup a new environment for the experiment you are running. [Check the GitHub repo for instructions]
