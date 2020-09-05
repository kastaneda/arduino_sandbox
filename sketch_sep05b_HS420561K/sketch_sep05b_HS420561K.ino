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
//   DDDD       9 = A B C D   F G       0b01111011
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
byte decimalToSegments[] = {
    0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
    0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01111011 };

void setup() {
    for (int i = 0; i < sizeof(segmentPins); i++) {
        pinMode(segmentPins[i], OUTPUT);
    }
    for (int i = 0; i < sizeof(cathodePins); i++) {
        pinMode(cathodePins[i], OUTPUT);
    }
}

// configure output wires connected to seven-segments
void setDecimalDigit(byte decimal) {
    // number to set of segments
    byte fontBitMask = decimalToSegments[decimal];

    // loop over all output legs
    for (int i = 0; i < sizeof(segmentPins); i++) {
        // check one bit
        if (fontBitMask & (1 << i)) {
            // turn on this segment's LED
            digitalWrite(segmentPins[i], HIGH);
        } else {
            // turn off
            digitalWrite(segmentPins[i], LOW);
        }
    }
}

// one digit position enabled, others disabled
void setDigitPosition(byte positionEnabled) {
    // loop over all four digits
    for (int i = 0; i < sizeof(cathodePins); i++) {
        // if this 
        if (i == positionEnabled) {
            // LOW on cathode enables drain sink
            digitalWrite(cathodePins[i], LOW);
        } else {
            // HIGH on cathode disables drain (thus, no current)
            digitalWrite(cathodePins[i], LOW);
        }
    }
}

static int pow10[] = { 1, 10, 100, 1000, 10000 };

void loop() {
    // from 0000 to 9999
    for (int counter = 0; counter < 10000; counter++) {
        // show every digit N times
        for (int frame = 0; frame < 100; frame++) {
            int reminder = counter;
            for (int digitPosition = 0; digitPosition < 4; digitPosition++) {
                // continuously get all decimal digits in counter
                byte digitValue = reminder % 10;
                reminder = reminder / 10;

                // show this
                setDecimalDigit(digitValue);
                setDigitPosition(digitPosition);

                // time to show this digit
                delay(100);
            }
        }
    }
}
