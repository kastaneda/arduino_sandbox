uint8_t reset_cnt __attribute__ ((section (".noinit")));
uint32_t first_run __attribute__ ((section (".noinit")));

void setup() {
 Serial.begin(9600);
  if(first_run !=0xDEAD0000)
  {
  reset_cnt = 0;
  Serial.println("First run after power down");
  first_run = 0xDEAD0000;
  }
  reset_cnt ++ ;
}

void loop() {
  Serial.print("Press Reset button #: ");
  Serial.println(reset_cnt);
  while(1);
}

// does not work on my board
