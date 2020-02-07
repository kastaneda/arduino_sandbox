void setup() {
  // initialize the digital pin as an output.
  pinMode(0, OUTPUT); //LED on Model B
  pinMode(1, OUTPUT); //LED on Model A
}

void loop() {
  // slow blink == LED on pin 1 == model A
  // fast blink == LED on pin 0 == model B

  for (int i = 1; i < 10; i++) {
    digitalWrite(0, HIGH);
    delay(100);
  }
  digitalWrite(1, HIGH);

  for (int i = 1; i < 10; i++) {
    digitalWrite(0, LOW);
    delay(100);
  }
  digitalWrite(1, LOW);
}

/*

  Arduino IDE log:

  Sketch uses 718 bytes (11%) of program storage space. Maximum is 6012 bytes.
  Global variables use 9 bytes of dynamic memory.
  Running Digispark Uploader...
  Plug in device now... (will timeout in 60 seconds)
  > Please plug in the device ...
  > Press CTRL+C to terminate the program.
  > Device is found!
  connecting: 16% complete
  connecting: 22% complete
  connecting: 28% complete
  connecting: 33% complete
  > Device has firmware version 1.6
  > Available space for user applications: 6012 bytes
  > Suggested sleep time between sending pages: 8ms
  > Whole page count: 94  page size: 64
  > Erase function sleep duration: 752ms
  parsing: 50% complete
  > Erasing the memory ...
  erasing: 55% complete
  erasing: 60% complete
  erasing: 65% complete
  >> Flash erase error -71 has occured ...
  >> Please unplug the device and restart the program.

  Damn.


  dmesg | grep usbfs
  [32685.575641] usb 8-1: usbfs: USBDEVFS_CONTROL failed cmd micronucleus rqt 192 rq 2 len 0 ret -71

*/
