# Kodi Remote Interpreter
This simple project implements the most basic commands on kodi using an ordinary TV remote controller.
## Hardware
The hardware consists of an **arduino nano**, a **TSOP4838**, and a PC running **Kodi**.
## Software Structure
The sturcture of the project is very simple. The arduino simply decodes the infrared signals from the remote controller and sends the received data through the virtual serial port to the PC. There, a python client receives and emulates the appropriate keystroke to control the running Kodi.

#### Notes
For different operating systems and different versions of arduino, or other microcontroller the software most likely needs to be modified.
The software is only intended for my personal use.