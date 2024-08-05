/* Library to interface with 74'4511 BCD to 7-segment LED driver chip.

   https://github.com/Andy4495/LED744511

   The library supports either 1 or 2 7-segment displays.
   For a single digit, a minimum of 5 output pins are required:
      BCD bits 3-0 and /LE.
      You can also optionally define the /LE and /BL signals.
   For two digit setups, a minimum of 6 output pins are required:
      BCD bits 3-0, /LE for each of the two digits
      You can also optionally define the /LE and /BL signals.
*/
/* Version History
   1.0.0    03/28/2018  A.T.   Original
   1.1.0    05/18/2018  A.T.   Add support for 74HC164 serial to parallel shift register
                               to decrease I/O pin requirements.
*/

#include "LED744511.h"

// LED4511 class member function definitions (parallel interface)
// Single digit constructors
LED744511::LED744511(int bcd3, int bcd2, int bcd1, int bcd0, int LE) {
  init(bcd3, bcd2, bcd1, bcd0, NO_PIN, LE, NO_PIN, NO_PIN);
}

LED744511::LED744511(int bcd3, int bcd2, int bcd1, int bcd0, int LE, int LT, int BL) {
  init(bcd3, bcd2, bcd1, bcd0, NO_PIN, LE, LT, BL);
}

// Dual digit constructors
LED744511::LED744511(int bcd3, int bcd2, int bcd1, int bcd0, int LE_1, int LE_0) {
  init(bcd3, bcd2, bcd1, bcd0, LE_1, LE_0, NO_PIN, NO_PIN);
}

LED744511::LED744511(int bcd3, int bcd2, int bcd1, int bcd0, int LE_1, int LE_0, int LT, int BL) {
  init(bcd3, bcd2, bcd1, bcd0, LE_1, LE_0, LT, BL);
}

void LED744511::init(int bcd3, int bcd2, int bcd1, int bcd0, int LE_1, int LE_0, int LT, int BL) {
  bcd3_pin  = bcd3;
  bcd2_pin  = bcd2;
  bcd1_pin  = bcd1;
  bcd0_pin  = bcd0;
  LE_pin[1] = LE_1;
  LE_pin[0] = LE_0;
  LT_pin    = LT;
  BL_pin    = BL;

  // Make sure that the control signals are disabled during initialization
  if (LE_pin[1] != NO_PIN) {
    digitalWrite(LE_pin[1], HIGH);
    pinMode(LE_pin[1], OUTPUT);
  }
  if (LE_pin[0] != NO_PIN) {
    digitalWrite(LE_pin[0], HIGH);
    pinMode(LE_pin[0], OUTPUT);
  }
  if (LT_pin != NO_PIN) {
    digitalWrite(LT_pin, HIGH);
    pinMode(LT_pin, OUTPUT);
  }
  if (BL_pin != NO_PIN) {
    digitalWrite(BL_pin, HIGH);
    pinMode(BL_pin, OUTPUT);
  }
  // Set up the BCD data pins
  pinMode(bcd3_pin, OUTPUT);
  pinMode(bcd2_pin, OUTPUT);
  pinMode(bcd1_pin, OUTPUT);
  pinMode(bcd0_pin, OUTPUT);
}

void LED744511::writeBCD(int value) {
  // 2 digit displays:
  //   values between 10 and 99 inclusive: display normally
  //   values < 10: display leading blank digit
  //   values > 100: display leading '0' digit
  //   values < 0: blank display (all segments off)
  // 1 digit displays:
  //   values >= 0: display value (modulus 10)
  //   values < 0: blank display (all segments off)
  if (LE_pin[1] != NO_PIN) {             // 2 LED digits defined
    // Values between 10 and 99 includes print normally
    if ((value < 100) && (value > 9)) {
      writeDigit(1, value/10);
    }
    // Values < 10 or negative values print a blank leading digit
    if (value < 10) {
      writeDigit(1, LED744511::BLANK_DIGIT);
    }
    // Values > 99 print a zero leading digit when necessary
    if (value > 99) {
      writeDigit(1, (value / 10) % 10);
    }
  }
  // Least significant digit: blank display if < 0
  if (value < 0) writeDigit(0, LED744511::BLANK_DIGIT);
  else writeDigit(0, value%10);
}

void LED744511::lampTest(int onoff) {
  if (LT_pin != NO_PIN) {
    digitalWrite(LT_pin, onoff);
  }
}

void LED744511::blankDisplay(int onoff) {
  if (BL_pin != NO_PIN) {
    digitalWrite(BL_pin, onoff);
  }
}

void LED744511::writeDigit(int digit, int n) {
  digitalWrite(bcd3_pin, n & 8);
  digitalWrite(bcd2_pin, n & 4);
  digitalWrite(bcd1_pin, n & 2);
  digitalWrite(bcd0_pin, n & 1);
  digitalWrite(LE_pin[digit], LOW);
  digitalWrite(LE_pin[digit], HIGH);
}
//---------------------------------------------------------------------//
// LED4511_Serial class member function definitions (serial interface)
// Single digit constructors
LED744511_Serial::LED744511_Serial(int clk, int din, int LE) {
  init(clk, din, NO_PIN, LE, NO_PIN, NO_PIN, NO_PIN);
}

LED744511_Serial::LED744511_Serial(int clk, int din, int LE, int clr, int LT, int BL) {
  init(clk, din, NO_PIN, LE, clr, LT, BL);
}

// Dual digit constructors
LED744511_Serial::LED744511_Serial(int clk, int din, int LE_1, int LE_0) {
  init(clk, din, LE_1, LE_0, NO_PIN, NO_PIN, NO_PIN);
}

LED744511_Serial::LED744511_Serial(int clk, int din, int LE_1, int LE_0, int clr, int LT, int BL) {
  init(clk, din, LE_1, LE_0, clr, LT, BL);
}

void LED744511_Serial::init(int clk, int din, int LE_1, int LE_0, int clr, int LT, int BL) {
  clk_pin   = clk;
  din_pin   = din;
  clr_pin   = clr;
  LE_pin[1] = LE_1;
  LE_pin[0] = LE_0;
  LT_pin    = LT;
  BL_pin    = BL;

  DP_ms     = 0;
  DP_ls     = 0;

  // Make sure that the control signals are disabled during initialization
  if (LE_pin[1] != NO_PIN) {
    digitalWrite(LE_pin[1], HIGH);
    pinMode(LE_pin[1], OUTPUT);
  }
  if (LE_pin[0] != NO_PIN) {
    digitalWrite(LE_pin[0], HIGH);
    pinMode(LE_pin[0], OUTPUT);
  }
  if (LT_pin != NO_PIN) {
    digitalWrite(LT_pin, HIGH);
    pinMode(LT_pin, OUTPUT);
  }
  if (BL_pin != NO_PIN) {
    digitalWrite(BL_pin, HIGH);
    pinMode(BL_pin, OUTPUT);
  }
  if (clr_pin != NO_PIN) {
    digitalWrite(clr_pin, HIGH);
    pinMode(clr_pin, OUTPUT);
  }  // Set up the serial data pins
  pinMode(clk_pin, OUTPUT);
  pinMode(din_pin, OUTPUT);
}

void LED744511_Serial::writeBCD(int value) {
  // 2 digit displays:
  //   values between 10 and 99 inclusive: display normally
  //   values < 10: display leading blank digit
  //   values > 100: display leading '0' digit
  //   values < 0: blank display (all segments off)
  // 1 digit displays:
  //   values >= 0: display value (modulus 10)
  //   values < 0: blank display (all segments off)
  if (LE_pin[1] != NO_PIN) {             // 2 LED digits defined
    // Values between 10 and 99 includes print normally
    if ((value < 100) && (value > 9)) {
      writeSerial(value/10);
    }
    // Values < 10 or negative values print a blank leading digit
    if (value < 10) {
      writeSerial(LED744511_Serial::BLANK_DIGIT);
    }
    // Values > 99 print a zero leading zero if necessary
    if (value > 99) {
      writeSerial((value / 10) % 10);
    }
    digitalWrite(LE_pin[1], LOW);
    digitalWrite(LE_pin[1], HIGH);
  }
  // Least significant digit: blank display if < 0
  if (value < 0) writeSerial(LED744511_Serial::BLANK_DIGIT);
  else writeSerial(value%10);
  digitalWrite(LE_pin[0], LOW);
  digitalWrite(LE_pin[0], HIGH);
}

void LED744511_Serial::lampTest(int onoff) {
  if (LT_pin != NO_PIN) {
    digitalWrite(LT_pin, onoff);
  }
}

void LED744511_Serial::blankDisplay(int onoff) {
  if (BL_pin != NO_PIN) {
    digitalWrite(BL_pin, onoff);
  }
}

void LED744511_Serial::clr74HC164(int onoff) {
  if (clr_pin != NO_PIN) {
    digitalWrite(clr_pin, onoff);
  }
}

void LED744511_Serial::setDP(int ms, int ls) {
  DP_ms = ms;
  DP_ls = ls;
}

void LED744511_Serial::writeSerial(int value) {
  digitalWrite(din_pin, value & 0x01);  // QH
  toggle_clk();
  digitalWrite(din_pin, value & 0x02);  // QG
  toggle_clk();
  digitalWrite(din_pin, value & 0x04);  // QF
  toggle_clk();
  digitalWrite(din_pin, value & 0x08);  // QE
  toggle_clk();
  // Both LED digits are tied to QE, QF, QG, QH
  // QD and QC may be connected to Decimal Point control lines
  digitalWrite(din_pin, DP_ms);   // QD tied to most signicant decimal point
  toggle_clk();
  digitalWrite(din_pin, DP_ls);   // QC tied to least significant decimal point
  toggle_clk();
  // QB and QA assumed not connected, but need to clock in dummy data
  toggle_clk();
  toggle_clk();
}

void LED744511_Serial::toggle_clk() {
  digitalWrite(clk_pin, LOW);
  digitalWrite(clk_pin, HIGH);
}
