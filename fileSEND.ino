/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.1 January, 2019
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = D5;  // CHAN CON TRANG

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example of data captured by IRrecvDumpV2.ino
/*
uint16_t rawData[67] = {9000, 4500, 650, 550, 650, 1650, 600, 550, 650, 550,
                        600, 1650, 650, 550, 600, 1650, 650, 1650, 650, 1650,
                        600, 550, 650, 1650, 650, 1650, 650, 550, 600, 1650,
                        650, 1650, 650, 550, 650, 550, 650, 1650, 650, 550,
                        650, 550, 650, 550, 600, 550, 650, 550, 650, 550,
                        650, 1650, 600, 550, 650, 1650, 650, 1650, 650, 1650,
                        650, 1650, 650, 1650, 650, 1650, 600};
// Example Samsung A/C state captured from IRrecvDumpV2.ino
uint8_t samsungState[kSamsungAcStateLength] = {
    0x02, 0x92, 0x0F, 0x00, 0x00, 0x00, 0xF0,
    0x01, 0xE2, 0xFE, 0x71, 0x40, 0x11, 0xF0};
*/

uint16_t rawData[439] = {3454, 1696,  460, 1268,  456, 406,  456, 406,  458, 394,  472, 1266,  462, 404,  458, 334,  530, 402,  456, 408,  452, 1274,  480, 380,  456, 1270,  458, 1270,  454, 406,  452, 1276,  458, 1268,  456, 1270,  458, 1270,  464, 1262,  460, 404,  454, 408,  456, 1272,  484, 380,  454, 410,  476, 384,  452, 410,  478, 344,  494, 412,  456, 1272,  484, 1242,  454, 1272,  456, 1270,  482, 380,  456, 408,  456, 408,  454, 410,  456, 406,  458, 404,  480, 382,  452, 414,  480, 384,  456, 406,  456, 408,  456, 408,  452, 412,  484, 380,  458, 406,  484, 378,  482, 380,  484, 380,  456, 406,  484, 380,  454, 408,  484, 378,  482, 382,  484, 378,  484, 378,  480, 1248,  458, 404,  484, 378,  486, 378,  484, 378,  460, 402,  484, 380,  486, 29478,  3506, 1672,  480, 1248,  484, 376,  488, 376,  484, 380,  460, 1268,  488, 374,  486, 378,  484, 380,  452, 410,  482, 1246,  484, 378,  484, 1244,  484, 1242,  482, 380,  486, 1242,  486, 1242,  484, 1242,  486, 1242,  484, 1242,  482, 380,  480, 384,  482, 1246,  484, 378,  486, 376,  484, 378,  486, 378,  480, 382,  486, 378,  482, 380,  482, 382,  484, 378,  482, 380,  484, 380,  480, 384,  484, 376,  488, 376,  480, 384,  482, 380,  486, 380,  480, 380,  480, 1250,  478, 382,  484, 380,  484, 378,  482, 382,  484, 1242,  482, 380,  480, 382,  482, 382,  482, 382,  484, 380,  480, 382,  484, 380,  480, 382,  482, 1246,  484, 1244,  482, 382,  482, 378,  484, 380,  480, 382,  482, 382,  480, 384,  484, 378,  482, 382,  484, 378,  480, 384,  482, 384,  480, 382,  482, 380,  480, 1248,  484, 380,  480, 1248,  480, 384,  482, 380,  480, 382,  480, 384,  480, 382,  482, 380,  478, 384,  482, 380,  478, 388,  450, 412,  448, 414,  450, 414,  448, 414,  452, 412,  448, 416,  474, 390,  472, 390,  474, 390,  472, 390,  472, 392,  448, 414,  446, 416,  448, 416,  472, 390,  472, 392,  448, 414,  474, 388,  452, 412,  472, 390,  448, 416,  472, 394,  446, 416,  446, 418,  446, 418,  446, 418,  444, 420,  442, 420,  442, 418,  446, 420,  444, 420,  444, 420,  444, 418,  468, 394,  446, 418,  444, 420,  442, 420,  442, 422,  442, 444,  418, 446,  418, 444,  418, 444,  418, 426,  440, 444,  418, 444,  420, 1306,  420, 1306,  420, 442,  420, 444,  418, 444,  418, 444,  416, 448,  416, 446,  416, 446,  418, 446,  418, 446,  418, 446,  418, 446,  416, 446,  416, 446,  414, 448,  414, 448,  416, 448,  418, 1310,  414, 1312,  416, 450,  406, 456,  408, 1320,  408, 454,  408, 1320,  408, 454,  406};  // DAIKIN216
void setup() {
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
pinMode(D6, OUTPUT);
digitalWrite(D6, LOW);
}

void loop() {
  /*
  Serial.println("NEC");
  irsend.sendNEC(0x00FFE01FUL);
  delay(2000);
  Serial.println("Sony");
  irsend.sendSony(0xa90, 12, 2);  // 12 bits & 2 repeats
  delay(2000);
  Serial.println("a rawData capture from IRrecvDumpV2");
  irsend.sendRaw(rawData, 67, 38);  // Send a raw data capture at 38kHz.
  delay(2000);
  Serial.println("a Samsung A/C state from IRrecvDumpV2");
  irsend.sendSamsungAC(samsungState);
  delay(2000);
  */
  if(digitalRead(D6) == HIGH)
    {
     delay(500);
     irsend.sendRaw(rawData, 439, 38); 
    }
}
