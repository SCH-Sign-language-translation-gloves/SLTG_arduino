void displayText(String msg) { Serial.println(msg); }

void blinkLED(int duration) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(duration);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}

void displayStatus(String msg) {
  displayText(msg);
  blinkLED(100);
}

void displayError(String msg) {
  displayText("Error: " + msg);
  blinkLED(300);
}

void displaySuspend(String msg) {
  displayText("Execution suspended: " + msg);
  digitalWrite(LED_BUILTIN, HIGH); // Turn on LED.
  while (true) {
    // Stop execution.
  }
}

void setupDisplay() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  if (!Serial) {
    // Allow enough time for our Serial Monitor to connect to the serial port.
    delay(3000);
  }
  if (Serial) {
    Serial.println("\nSerial port connected.");
  }
}
