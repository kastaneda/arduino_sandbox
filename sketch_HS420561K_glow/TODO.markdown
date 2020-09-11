TODO: Simplify the wiring!!
===========================

 - avoid intersections
 - make it as short as possible
 - 'wrong' / 'random' leg order should be 'fixed' on code level
 - there should be some space left for 1 buzzer and probably 1 button

Current layout:

```cpp
// outputs connected to anodes (segments, connected to all digits)
byte segmentPins[] = { 9, 8, 7, 6, 5, 4, 3, 2 };

// outputs connected to cathodes (one cathode per digit)
byte cathodePins[] = { A3, A2, A1, A0 };
```

Layout in `refactoring.fzz`:

```cpp
// outputs connected to anodes (segments, connected to all digits)
byte segmentPins[] = { 12, 9, 7, 5, 10, 11, 6, 8 };

// outputs connected to cathodes (one cathode per digit)
byte cathodePins[] = { A1, A2, A3, A0 };
```
