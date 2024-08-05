//============================================================================
// Name        : LedTask.ino
// Author      : Created by Debinix Team (C). The MIT License (MIT).
// Version     : Date 2022-08-25.
// Description : This example shows the power of non-preemptive multitasking.
//               Four LEDs run close to independent of each other on Arduino.
//============================================================================

#include <LedTask.h>

// Instantiate a few led objects, and set led pin#
LedTask LedOne = LedTask(12);
LedTask LedTwo = LedTask(13);
LedTask LedThree = LedTask(8);
LedTask LedFour = LedTask(7);

void setup() {

    Serial.begin(9600);
    delay(1000);  // The only one.

//   LED time: on_ms,off_ms
    LedOne.begin(100, 400);
    LedTwo.begin(350, 350);
    LedThree.begin(125, 250);
    LedFour.begin(500, 400);

    Serial.println("Setup completed...");
}

// Do not add any delay statements in the loop().
// Arduino runs in non-preemptive multitasking!
void loop() {

    // Demo of four independent (blinking LEDs) tasks
    LedOne.updateBlinkLed();
    LedTwo.updateBlinkLed();
    LedThree.updateBlinkLed();
    LedFour.updateBlinkLed();
}
