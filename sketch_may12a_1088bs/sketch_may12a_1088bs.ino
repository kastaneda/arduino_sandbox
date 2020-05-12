//
//  Blinking LEDs on 1088BS LED 8x8 matrix
//

/********************************************

    8 rows (R1-R8), 8 cols (C1-C8)

    R1 --|>|-- C1
    row(HIGH) ....+LED-.... col(LOW)
    
    Schematic physical pinout:
    
        C8  C7  R2  C1  R4  C6  C4  R1
        :   :   :   :   :   :   :   :
        :   :   :   :   :   :   :   :
    +--16--15--14--13-_-12--11--10--9---+
    |C1R1                               |
    |C1R2                               |
    |...                                |
    |                                   |
    |              1088BS               |
    |                                   |
    |                                   |
    |                                   |
    |C1R8                           C8R8|
    +---1---2---3---4-_-5---6---7---8---+
        :   :   :   :   :   :   :   :
        :   :   :   :   :   :   :   :
        R5  R7  C2  C3  R8  C5  R6  R3

********************************************/

//
// NOTE: that's my current breadboard setup!
//
unsigned char row_pins[8] = {11, 10,  9,  8,  7,  6,  5,  4};
unsigned char col_pins[8] = { 3,  2, A0, A1, A2, A3, A4, A5};

void setup() {
   for (unsigned char i = 0; i < 8; i++) {
     pinMode(col_pins[i], OUTPUT);
     pinMode(row_pins[i], OUTPUT);
     digitalWrite(col_pins[i], HIGH);
     digitalWrite(row_pins[i], LOW);
   }
}

void hide_row(unsigned char row) {
  // Damn, I 
  digitalWrite(col_pins[row], HIGH);
}

void show_row(unsigned char row, unsigned char data) {
  for (unsigned char i = 0; i < 8; i++) {
    digitalWrite(row_pins[i], data & 1);
    data = data >> 1;
  }
  digitalWrite(col_pins[row], LOW);
}

//unsigned char videoRAM[8] = {
//  B11111111,
//  B10000001,
//  B10100101,
//  B10011001,
//  B10011001,
//  B10100101,
//  B10000001,
//  B11111111,
//};

// include "smile.xbm" -- da fuck? no suck file, WTF

// Okay, I'll put it right here
#define smile_width 8
#define smile_height 8
static unsigned char smile_bits[] = {
   0x3c, 0x42, 0xa5, 0x81, 0xa5, 0x99, 0x42, 0x3c };


void loop() {
  unsigned char row, row_prev;

  row_prev = 7;
  for (row = 0; row < 8; row++) {
    hide_row(row_prev);
    show_row(row, smile_bits[row]);
    row_prev = row;
    delayMicroseconds(500);
  }

}
