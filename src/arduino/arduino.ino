bool sending = true;
byte msg{};

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (sending == true) {
  for (int i{0}; i < 8; ++i) {
      bitWrite(msg, i, analogRead(0) & 1);
      delayMicroseconds(10);
    }
    Serial.write(msg);
  }
}

/* TODO: Interrupts for read events */
void serialEvent() { 
  while (Serial.available()) {
    char new_char = (char) Serial.read();
    switch(new_char) {
      case 'a': sending = true; break;
      case 'b': sending = false; break;
    }
  }
}

void blink() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
