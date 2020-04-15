### Tryna figure out the 'does not name a type' error:

**https://stackoverflow.com/questions/30872950/arduino-struct-does-not-name-a-type-error/30874740 <-- Got the answer**

Other, of various usefullness
- https://arduino.stackexchange.com/questions/12304/arduino-raise-the-error-does-not-name-a-type-when-an-object-is-used-outside-o
- https://www.reddit.com/r/learnprogramming/comments/1gau0m/struct_does_not_name_a_type_c/
- https://forum.arduino.cc/index.php?topic=514226.0
- https://stackoverflow.com/questions/13357312/arduino-servo-struct-does-not-name-a-type#comment18233186_13357312
- https://stackoverflow.com/questions/612328/difference-between-struct-and-typedef-struct-in-c
- https://forum.arduino.cc/index.php?topic=80086.0

### Tryna look at the compiled code

- https://godbolt.org/z/z9Yd8-

### Looking for the source files I need to compile to binary on godbolt

- https://grep.app/search?q=tone%7Cdelay&regexp=true&filter[repo][0]=arduino/ArduinoCore-avr
- https://github.com/arduino/ArduinoCore-avr/tree/master/cores/arduino
