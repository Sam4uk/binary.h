
 "THE BEER-WARE LICENSE":
 ========================
 <sto.ukr.net@gmail.com> wrote this file. As long as you retain this
 notice you can do whatever you want with this stuff. If we meet some
 day, and you think this stuff is worth it, you can buy me a beer in
 return.
 
 Generator of definitions for binary constants. You can compile this
 file with any compiler: C or C++.
 
 This script generate header file "binary.h". His look like
 ```cpp
 #ifndef BINARY__H
   #define BINARY__H 1
   #define B0 0x00
     .  .  .
 #endif
```
 You can config this change defines `CAPS` and `BIT_S`. If you need this.

 Set `CAPS` to 1 if want hex digit look like `0x2e` (lower caps),
 or set to 2 if want - `0X1F` (UPPER CAPS). Who cares?

 Set `BIT_S` for change max length defines. If set 5 -maximum value was
 `B11111` or `0x1f` or `31`. If 8 - `B11111111` or `0xff` or `255` (default).

 How use?
 --------
 ```bash
 COMPILER -DCAPS=0 -DBIT_S=8 main.cpp -o BIN_GEN
 ./BIN_GEN
```
 The file `binary.h` will appear. Copy it where you need it
