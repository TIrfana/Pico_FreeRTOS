# Side Channel Analysis on Pico using FreeRTOS

## Project Description
Collect traces,plaintext and ciphertext for Side Channel Attack on AES128 encryption algorithm in ECB mode.

The computer collects traces,plaintext and ciphertext for Side Channel Attack.

## Directions
Download [File:PyCharms](https://github.com/TIrfana/Pico_FreeRTOS/tree/main/For_Com/PyCharms) into your laptop and open in PyCharm.

Either drag and drop [uf2_file](https://github.com/TIrfana/Pico_FreeRTOS/tree/main/For_Pico/UF2) into Pico 

- or make uf2 file using [C_code](https://github.com/TIrfana/Pico_FreeRTOS/tree/main/For_Pico) by following [Tutorial](https://embeddedcomputing.com/technology/open-source/linux-freertos-related/using-freertos-with-the-raspberry-pi-pico#:~:text=First%20off%2C%20what%20is%20FreeRTOS,Pi%20Pico%2C%20and%20small%20microprocessors.)

 ### - Set up oscilloscope library in laptop
1. Install activedoso.exe file inside the activedso.zip [here](https://github.com/TIrfana/Pico_FreeRTOS/blob/main/For_Com/activedso.zip) 

### - Running experiment
1. Connect Pico to laptop via mini usb to usb cable
2. Laptop(Mac) : After connecting wait a few seconds, type `python -m serial.tools.list_ports` in terminal to find serial port
