
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

void myBlink(int timeLight, int timeDark) {
  digitalWrite(led, HIGH);
  delay(timeLight);
  digitalWrite(led, LOW);
  delay(timeDark);
}

// the loop routine runs over and over again forever:
void loop() {
  myBlink(100, 300);
  myBlink(100, 500);
  
  myBlink(100, 100);
  myBlink(100, 100);
  myBlink(100, 500);
  
  myBlink(100, 75);
  myBlink(100, 75);
  myBlink(100, 75);
  myBlink(100, 500);

  myBlink(100, 100);
  myBlink(100, 1500);


}
