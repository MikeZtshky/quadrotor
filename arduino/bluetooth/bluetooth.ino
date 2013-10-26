#include <SoftwareSerial.h>

int BLUETOOTH_RX = 4;
int BLUETOOTH_TX = 5;

SoftwareSerial bluesmirf(BLUETOOTH_RX, BLUETOOTH_TX);

void setup() {
  pinMode(BLUETOOTH_RX, INPUT);
  pinMode(BLUETOOTH_TX, OUTPUT);
  digitalWrite(BLUETOOTH_RX, HIGH);
  
  Serial.begin(9600);
  bluesmirf.begin(9600);
}

void loop() {
  if (bluesmirf.available())
    Serial.print((char)bluesmirf.read());
  if (Serial.available())
    bluesmirf.write(Serial.read());
}

