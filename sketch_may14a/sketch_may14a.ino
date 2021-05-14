void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("INSERT INTO sensor (board_id, A0, A1, A2, millis) VALUES (1, ");
  Serial.print(analogRead(A0)); Serial.print(", ");
  Serial.print(analogRead(A1)); Serial.print(", ");
  Serial.print(analogRead(A2)); Serial.print(", ");
  Serial.print(millis());
  Serial.println(");");
  delay(1000);
}
