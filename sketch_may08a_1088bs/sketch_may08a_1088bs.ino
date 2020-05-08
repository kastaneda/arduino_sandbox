//
//  Blinking LEDs on 1088BS LED 8x8 matrix
//

/********************************************

    8 rows (R1-R8), 8 cols (C1-C8)
    R1 --|>|-- C1
    
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
int row_pins[8] = {11, 10,  9,  8,  7,  6,  5,  4};
int col_pins[8] = { 3,  2, A0, A1, A2, A3, A4, A5};

void setup() {
   for (int i = 0; i < 8; i++) {
     pinMode(col_pins[i], OUTPUT);
     pinMode(row_pins[i], OUTPUT);
   }
}

void loop() {
  // FIXME
}
