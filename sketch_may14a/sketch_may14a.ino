void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("INSERT INTO sensor (board_id, A0, A1, A2, A4, A5, millis) VALUES (3, ");
  Serial.print(analogRead(A0)); Serial.print(", ");
  Serial.print(analogRead(A1)); Serial.print(", ");
  Serial.print(analogRead(A2)); Serial.print(", ");
  Serial.print(analogRead(A4)); Serial.print(", ");
  Serial.print(analogRead(A5)); Serial.print(", ");
  Serial.print(millis());
  Serial.println(");");
  delay(10000);
}
