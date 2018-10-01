/*
    Name:       EvilBot.ino
    Created:	  9/30/2018 12:59:44
    Author:     Evgeny Vinnik
*/

#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

// connect motor controller pins to Arduino digital pins
// motor one
int enA = 44;
int in1 = 39;
int in2 = 41;
// motor two
int enB = 46;
int in3 = 40;
int in4 = 38;

USB Usb;
XBOXRECV Xbox(&Usb);

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {

        //go forward slower
        if (Xbox.getButtonClick(UP, i)) {
            analogWrite(enA, 100);
            analogWrite(enB, 100);
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);
        }

        //go backwards slower
        if (Xbox.getButtonClick(DOWN, i)) {
            analogWrite(enA, 100);
            analogWrite(enB, 100);
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);
        }

        //stop
        if (Xbox.getButtonClick(L1, i))
        {
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, LOW);
        }
        if (Xbox.getButtonClick(R1, i))
        {
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, LOW);
        }

        //go forward fast
        if (Xbox.getButtonClick(Y, i))
        {
            analogWrite(enA, 244);
            analogWrite(enB, 244);
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);
        }
        
        //go backward fast
        if (Xbox.getButtonClick(A, i))
        {   
            analogWrite(enA, 244);
            analogWrite(enB, 244);
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);
        }
        
        //turn right
        if (Xbox.getButtonClick(B, i))
        {
            analogWrite(enA, 100);
            analogWrite(enB, 100);
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);
        }
        
        //turn left
        if (Xbox.getButtonClick(X, i))
        {
            analogWrite(enA, 100);
            analogWrite(enB, 100);
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);   
        }
      }
    }
  }
}
