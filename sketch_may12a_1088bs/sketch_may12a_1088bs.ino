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


#define hello_width 120
#define hello_height 8
static unsigned char hello_bits[] = {
   0x00, 0x00, 0x00, 0x04, 0x00, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x40, 0x41, 0x02, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x06, 0x00,
   0x00, 0x90, 0x00, 0x00, 0x00, 0x02, 0x20, 0x9d, 0x74, 0x76, 0xb0, 0xb3,
   0x0b, 0x89, 0x1d, 0xe7, 0x90, 0x6a, 0xce, 0x54, 0x02, 0x20, 0xa5, 0x94,
   0x24, 0x88, 0x24, 0x09, 0x41, 0x21, 0x09, 0x91, 0xaa, 0x90, 0x54, 0x02,
   0x20, 0xa5, 0x74, 0x24, 0x89, 0x23, 0x09, 0x41, 0x39, 0xc7, 0xe1, 0xa6,
   0x9c, 0x5c, 0x02, 0x20, 0x9d, 0x96, 0x24, 0x89, 0x24, 0x09, 0x41, 0x25,
   0x29, 0x81, 0x6a, 0x92, 0x54, 0x02, 0x20, 0x85, 0x75, 0xae, 0xb0, 0x73,
   0x01, 0x2e, 0x59, 0xc7, 0x62, 0x2a, 0xac, 0x55, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 };

static unsigned char video_ram[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

static unsigned char offset = 0;
static unsigned int frames = 0;

void loop() {
  unsigned char row, row_prev;

  row_prev = 7;
  for (row = 0; row < 8; row++) {
    hide_row(row_prev);
    show_row(row, video_ram[row]);
    row_prev = row;
    delayMicroseconds(500);
  }

  frames++;

  if (frames > 15) {
    frames = 0;

    offset++;
    if (offset > (hello_width-8)) {
      offset = 0;
    }
      
    for (unsigned char y = 0; y < 8; y++) {
      video_ram[y] = 0;
      for (unsigned char x = 0; x < 8; x++) {
        unsigned char bit_value;
        unsigned int bit_addr;
        bit_addr = hello_width*y + x +offset;
        bit_value = (hello_bits[bit_addr >> 3] >> (bit_addr & 7)) & 1;
        video_ram[y] = video_ram[y] | (bit_value << (7-x)); 
      }
    }
  }

}
