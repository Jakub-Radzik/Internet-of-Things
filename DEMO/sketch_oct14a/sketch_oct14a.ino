void setup() {
  // put your setup code here, to run once: 
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(8, OUTPUT);
}

void loop() {
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  delay(100);
}
