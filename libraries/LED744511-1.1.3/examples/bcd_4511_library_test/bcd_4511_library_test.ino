/* Example sketch using the LED744511 library to 
 * interface with 74'4511 BCD to 7-segment LED driver chip.

   https://github.com/Andy4495/LED744511

*/
/* Version History
   1.0.0    03/28/2018  A.T.   Original
*/
#include "LED744511.h"

// Define the output pins used to interface with 74'4511 chip(s)
#define BCD1  15
#define BCD2  14
#define BCDLE1 13
#define BCDLE0 10
#define BCD3  12
#define BCD0  11

// Two digit display constructor
LED744511 myLED(BCD3, BCD2, BCD1, BCD0, BCDLE1, BCDLE0);
// Single digit display constructor
// LED744511 myLED(BCD3, BCD2, BCD1, BCD0, BCDLE0);


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
