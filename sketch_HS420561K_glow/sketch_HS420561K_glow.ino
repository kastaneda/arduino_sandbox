////////////////////////////////////////////////////////////////////////
//
//  Playing with 7-segment LED module HS420561K-C30 (common cathode)
//
////////////////////////////////////////////////////////////////////////
//
//  One 7-segment LED: segments A, B, C, D, E, F, G
//
//              0 = A B C D E F         0b00111111
//   AAAA       1 =   B C               0b00000110
//  F    B      2 = A B   D E   G       0b01011011
//  F    B      3 = A B C D     G       0b01001111
//  F    B      4 =   B C     F G       0b01100110
//   GGGG       5 = A   C D   F G       0b01101101
//  E    C      6 = A   C D E F G       0b01111101
//  E    C      7 = A B C               0b00000111
//  E    C      8 = A B C D E F G       0b01111111
//   DDDD       9 = A B C D   F G       0b01101111
//
////////////////////////////////////////////////////////////////////////
//
//  My schema:
//
//      D9 ---[  R 220Ω ]--- leg 11     (segment A)
//      D8 ---[  R 220Ω ]--- leg  7     (segment B)
//      D7 ---[  R 220Ω ]--- leg  4     (segment C)
//      D6 ---[  R 220Ω ]--- leg  2     (segment D)
//      D5 ---[  R 220Ω ]--- leg  1     (segment E)
//      D4 ---[  R 220Ω ]--- leg 10     (segment F)
//      D3 ---[  R 220Ω ]--- leg  5     (segment G)
//      D2 ---[  R 220Ω ]--- leg  3     (point)
//
//      A0 ----------------- leg 12     (cathode, digit 1)
//      A1 ----------------- leg  9     (cathode, digit 2)
//      A2 ----------------- leg  8     (cathode, digit 3)
//      A3 ----------------- leg  6     (cathode, digit 4)
//
////////////////////////////////////////////////////////////////////////
//
//      Module legs numbering:
//
//
//                     12  11  10   9   8   7
//                      |   |   |   |   |   |
//      +---------------+---+---+---+---+---+---------------+
//      |                                                   |
//      |      ---         ---         ---         ---      |
//      |     |   |       |   |       |   |       |   |     |
//      |     |   |       |   |   *   |   |       |   |     |
//      |      ---         ---         ---         ---      |
//      |     |   |       |   |   *   |   |       |   |     |
//      |     |   |       |   |       |   |       |   |     |
//      |      --- .       --- .       --- .       --- .    |
//      |                                                   |
//      +---------------------------------------------------+
//      |                   HS420561K-C30                   |
//      +---------------+---+---+---+---+---+---------------+
//                      |   |   |   |   |   |
//                      1   2   3   4   5   6
//
//  
////////////////////////////////////////////////////////////////////////


// outputs connected to anodes (segments, connected to all digits)
byte segmentPins[] = { 9, 8, 7, 6, 5, 4, 3, 2 };

// outputs connected to cathodes (one cathode per digit)
byte cathodePins[] = { A3, A2, A1, A0 };

// uhmmm, you knowm, this is kinda... font!
// 0xHGFEDCBA
byte digitToSegments[] = {
    0b00111111,   // zero
    0b00000110,   // one
    0b01011011,   // two
    0b01001111,   // three
    0b01100110,   // four
    0b01101101,   // five
    0b01111101,   // six
    0b00000111,   // seven
    0b01111111,   // eight
    0b01101111,   // nine
    0b01110111,   // A
    0b01111100,   // B
    0b00111001,   // C
    0b01011110,   // D
    0b01111001,   // E
    0b01110001    // F
};

static unsigned int pow10[] = { 1, 10, 100, 1000, 10000 };

// configure output wires connected to seven-segments
// all digit positions connected to same segments
// input value is bitmask
void setDigitSegments(byte segmentsBitmask) {
    // loop over all output legs
    for (byte i = 0; i < sizeof(segmentPins); i++) {
        // check one bit
        if (segmentsBitmask & (1 << i)) {
            // turn on this segment's LED
            digitalWrite(segmentPins[i], HIGH);
        } else {
            // turn off
            digitalWrite(segmentPins[i], LOW);
        }
    }
}

// configure output wires connected to seven-segments
// input value is one (hexa)decimal digit
void setDigitValue(byte digitValue) {
    setDigitSegments(digitToSegments[digitValue]);
}

// configure output wires connected to common cathodes
// one digit position enabled, all others disabled
void setDigitPosition(byte digitPosition) {
    // loop over all four digits
    for (byte i = 0; i < sizeof(cathodePins); i++) {
        // if this is one to show
        if (i == digitPosition) {
            // LOW on cathode enables drain sink
            digitalWrite(cathodePins[i], LOW);
        } else {
            // HIGH on cathode disables drain (thus, no current)
            digitalWrite(cathodePins[i], HIGH);
        }
    }
}

// blank display
void clearDigitPosition() {
  setDigitPosition(255); // value far beyond
}

// all together
void showOneDigit(byte decimalValue, byte digitPosition, unsigned int microseconds) {
  setDigitValue(decimalValue);
  setDigitPosition(digitPosition);
  delayMicroseconds(microseconds);
  clearDigitPosition();
}

void setup() {
    for (byte i = 0; i < sizeof(segmentPins); i++) {
        pinMode(segmentPins[i], OUTPUT);
    }
    for (byte i = 0; i < sizeof(cathodePins); i++) {
        pinMode(cathodePins[i], OUTPUT);
    }
}

void loop() {
    unsigned int digitsToDisplay = (millis() >> 8) & 0xFFFF;

    for (byte digitPosition = 0; digitPosition < 4; digitPosition++) {
        byte digitValue = digitsToDisplay & 0x0F;
        digitsToDisplay = digitsToDisplay >> 4;
        showOneDigit(digitValue, digitPosition, 50);
    }
}
