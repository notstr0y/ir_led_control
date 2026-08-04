#include <Arduino.h>
#include <IRremote.hpp>

#define IR_PIN 7
#define NUM_LEDS 4

const uint8_t led_pins[NUM_LEDS] = {3, 4, 5, 11}; // the red and blue leds 

// Captured previously from the remote 
const uint32_t CODE_1 = 0x748BF300;
const uint32_t CODE_2 = 0x6F90F300;
const uint32_t CODE_3 = 0x758AF300;
const uint32_t CODE_4 = 0x6C93F300;

const uint32_t CODE_POWER = 0x6E91F300;

void set_led_count(uint8_t n) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        digitalWrite(led_pins[i], i < n ? HIGH : LOW);
    }
}

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        pinMode(led_pins[i], OUTPUT);
        digitalWrite(led_pins[i], LOW);
    }

    Serial.println("Ready! ");
}

void loop() {
    if (IrReceiver.decode()) {
        uint32_t code = IrReceiver.decodedIRData.decodedRawData;
 
        Serial.print("Received: 0x");
        Serial.print(code, HEX);
        Serial.println(" ");

        if (code == CODE_1) { set_led_count(1); } else if (code == CODE_2) { set_led_count(2); } else if (code == CODE_3) { set_led_count(3); } else if (code == CODE_4) { set_led_count(4); } else if (code == CODE_POWER) { set_led_count(0); } // anything else (e.g. repeat frames) is ignored
 
        IrReceiver.resume();
    }
}

