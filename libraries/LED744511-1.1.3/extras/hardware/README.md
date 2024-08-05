Seven Segment Interface Board Design
====================================

This is a reference design (schematic and PCB) to use with the LED744511 library.

It uses 42056-type 7-segment LED digits and 74HC4511 driver chips. It also supports an optional 74HC164 serial-to-parallel shift register for slightly reduced pin requirements.

If using the 74HC164 shift register, then connect VCC, GND, CLK, DIN, LE-MSB, and LE-LSB pins to the microcontroller.

If not using the 74HC164 shift register, then connect VCC, GND, D0, D1, D2, D3, LE-MSB, and LE-LSB pins to the microcontroller.

The /CLR, /LT, and /BT pins should have a weak pull-up (10K) resistor populated on the board. It should not normally be necessary to control those signals, but header pins are available if desired.

Note that the circuit only uses 4 bits of the shift register (QE, QF, QG, QH) - those pins are connected in parallel to the data-in bits on the 74HC4511 chips. The LE-MSB and LE-LSB pins are used to control which driver chip is being addressed. The other 4 bits (QA, QB, QC, QD) are brought out to a separate header and could potentially be used for other functions external to the board.

References
----------

+ 74'4511 [Datasheet][1]
+ 74HC1164 [Datasheet][2]

[1]: http://www.ti.com/lit/ds/symlink/cd74hc4511.pdf
[2]: http://www.ti.com/lit/ds/symlink/sn74hc164.pdf
[200]: https://github.com/Andy4495/LED744511
