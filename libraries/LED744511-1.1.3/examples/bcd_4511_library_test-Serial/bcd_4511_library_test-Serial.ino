/* Example sketch using the LED744511 library to 
 * interface with 74'4511 BCD to 7-segment LED driver chip
 * using 74HC164 serial-to-parallel shift register

   https://github.com/Andy4495/LED744511

*/
/* Version History
   1.0.0    05/18/2018  A.T.   Original
*/
#include "LED744511.h"

// Define the output pins used to interface with 74'4511 chip(s)
#define DATA_IN 12
#define CLR 15
#define CLK 11
#define BCDLE1 13
#define BCDLE0 10
#define LT  18
#define BL  19

// Two digit display constructor
LED744511_Serial myLED(CLK, DATA_IN, BCDLE1, BCDLE0);
// Single digit display constructor
// LED744511_Serial myLED(CLK, DATA_IN, BCDLE0);


void setup() {

  Serial.begin(9600);

}

void loop() {
  for (int i = -10; i < 120; i++) {
    myLED.writeBCD(i);
    Serial.print("BCD: ");
    Serial.println(i);
    delay(1000);
  }
}
