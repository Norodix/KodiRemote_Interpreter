import serial
import time
from pynput.keyboard import Key, Controller
#dependencies
#PySerial
#pynput

#key codes
up=     b'C26BF044'
down=   b'C4FFB646'
right=  b'53801EE8'
left=   b'758C9D82'
ok=     b'8AF13528'
red=    b'DAEA83EC'
green=  b'2BAFCEEC'
yellow= b'B5210DA6'
blue=   b'71A1FE88'
back=   b'3BCD58C8'
exit=   b'974F362'
menu=   b'ED45D744'

#USB serial link
USBLink='/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0'

def SelectButton(button):
    return{
        up:     Key.up,
        down:   Key.down,
        right:  Key.right,
        left:   Key.left,
        ok:     Key.enter,
        #red toggles wether the arduino sends data or not
        green:  ';', #change audio language
        yellow: 'l', #next subtitle
        blue:   Key.space,
        back:   Key.backspace,
        exit:   'x',
        menu:   'c'
    }.get(button, '')

keyboard=Controller()

while True:
    try:
        time.sleep(0.005) #sleep 5 ms
        ser = serial.Serial(USBLink)  # open serial port
        input_message=ser.readline().rstrip()
        print(input_message)
        button=SelectButton(input_message)
        print(button)
        keyboard.press(button)
        time.sleep(0.005)
        keyboard.release(button)


    except KeyboardInterrupt:
        quit()
    except:
        pass


