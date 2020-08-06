/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int enabled=1; //opportunity to disable kod
int ledpin=13;
uint32_t idlecounter=0;
uint32_t redcode=0xDAEA83EC;

#if defined(ESP32)
int IR_RECEIVE_PIN = 15;
#else
int IR_RECEIVE_PIN = 2;
#endif
IRrecv irrecv(IR_RECEIVE_PIN);

decode_results results;

// On the Zero and others we switch explicitly to SerialUSB
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
    pinMode(ledpin, OUTPUT);
}

void loop() {
    //if(idlecounter>(10* 60 *100)) enabled=0; //enable for timeout
    digitalWrite(ledpin, enabled);
    if (irrecv.decode(&results)) {
        idlecounter=0;
        if (results.value==redcode) {//red button pressed
            enabled= (!enabled);
            digitalWrite(ledpin, enabled);
        }
        else if(enabled) Serial.println(results.value, HEX);

        //wait a bit before receiving the next value
        delay(100);
        irrecv.resume(); // Receive the next value
    }
    else idlecounter++;
    if(idlecounter==0xffffffff) idlecounter-=1;//overflow protection
    delay(10);
}