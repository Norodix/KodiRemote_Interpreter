#include <IRremote.h>

int enabled=1; //can disable the transmission of the decoded IR signal
int ledpin=13;
uint32_t idlecounter=0;

uint32_t redcode=0xDAEA83EC; //This code is used to toggle enable flag

int IR_RECEIVE_PIN = 2;
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