/*
 Authors:	Eric Desgranges
 Licensed under the GNU General Public License v3.0
*/

#include <FlexCAN.h>

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.x / Teensy LC have the LED on pin 13
const int ledPin = 13;

// -------------------------------------------------------------
static void hexDump(uint8_t dumpLen, uint8_t *bytePtr)
{
	uint8_t hex[17] = "0123456789abcdef";
	uint8_t working;
	while (dumpLen--) {
		working = *bytePtr++;
		Serial.write(hex[working >> 4]);
		Serial.write(hex[working & 15]);
	}
	Serial.write('\r');
	Serial.write('\n');
}

// -------------------------------------------------------------
void setup(void)
{
	pinMode(ledPin, OUTPUT); digitalWrite(ledPin, HIGH); delay(200); digitalWrite(ledPin, LOW);    // Blink once!
	Can0.begin();
	Serial.println(F("Hello Teensy E85!"));
}

// -------------------------------------------------------------
void loop(void)
{
	CAN_message_t rxMsg;
	while (Can0.available())
	{
		Can0.read(rxMsg);
		Serial.print("CAN BUS: "); hexDump(8, rxMsg.buf);
	}
}
