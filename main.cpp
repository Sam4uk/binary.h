/*
 * --------------------------------------------------------------------
 * "THE BEER-WARE LICENSE":
 * <sto.ukr.net@gmail.com> wrote this file. As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some
 * day, and you think this stuff is worth it, you can buy me a beer in
 * return.
 *
 * Generator of definitions for binary constants. You can compile this
 * file with any compiler: C or C++.
 *
 * This script generate header file "binary.h". His look like
 * #ifndef BINARY__H
 *   #define BINARY__H 1
 *   #define B0 0x00
 *     .  .  .
 * #endif
 *
 * You can config this change defines CAPS and BIT_S. If you need this.
 *
 * Set CAPS to 1 if want hex digit look like 0x2e (lower caps),
 * or set to 2 if want - 0X1F (UPPER CAPS). Who cares?
 *
 * Set BIT_S for change max length defines. If set 5 -maximum value was
 * B11111 or 0x1f or 31. If 8 - B11111111 or 0xff or 255 (default).
 *
 * How use?
 * COMPILER -DCAPS=0 -DBIT_S=8 main.cpp -o BIN_GEN
 * ./BIN_GEN
 *
 * The file binary.h will appear. Copy it where you need it
 * --------------------------------------------------------------------
 */

#ifndef CAPS
  #define CAPS 0  // 0- hex digits look like 0x2e
// #define CAPS 1  // 1- hex digits look like 0X1F
#endif
#ifndef BIT_S
  #define BIT_S 0x8
#endif

#define BEER_WARE                                                              \
  "/*\n"                                                                       \
  "* --------------------------------------------------------------------\n"   \
  "* binary.h - Definitions for binary constants\n"                            \
  "* \"THE BEER-WARE LICENSE\":\n"                                             \
  "* <sto.ukr.net@gmail.com> wrote this file. As long as you retain this \n"   \
  "* notice you can do whatever you want with this stuff. If we meet some\n"   \
  "* day, and you think this stuff is worth it, you can buy me a beer in \n"   \
  "* return.\n"                                                                \
  "* --------------------------------------------------------------------\n"   \
  "*/"

#define _NAME    "binary.h"
#define _ENDIF   "#endif"
#define _IFNDEF  "#ifndef"
#define _GUARD_H "BINARY__H"
#define _DEFINE  "  #define"

#ifdef __cplusplus  // check c++
  #include <algorithm>
  #include <cassert>
  #include <cstring>
  #include <fstream>
  #include <iostream>
  #include <limits>

struct H_file {
 public:
  static H_file& create(std::string name) {
    static H_file h{name};
    return h;
  }
  void rem_mono(std::string rem = "") { _output << "// " << rem << "\n"; }
  void code(std::string str = "") { _output << str << "\n"; }
  void define(std::string name, std::string value = "0") {
    _output << _DEFINE << " " << name << " " << value << "\n";
  }

 private:
  H_file(std::string name) : _name{name}, _output{name, std::ios::out} {
    code(BEER_WARE);
    H_begin();
  }
  ~H_file() { H_end(); }
  void H_begin() {
    _output << _IFNDEF << " " << _GUARD_H << "\n";
    define(_GUARD_H, "1");
  }
  void H_end() { _output << _ENDIF; }
  std::string _name;
  std::ofstream _output;
};
  #define CREATE_H(X)  H_file& header = H_file::create(X);
  #define DEFINE(N, V) header.define(N, V)
  #define SYS_MAX      std::numeric_limits<size_t>::max()
  #define CAST(X)      static_cast<char>
  #define CLOSE
#else  // not c++
  #include <stdio.h>
  #include <stdlib.h>

  #define SYS_MAX (__LONG_MAX__ * 2UL + 1)
  #define CAST(X) (X)
  #define CREATE_H(X)                                                          \
    FILE* cpp_h;                                                               \
    cpp_h = fopen(X, "w+");                                                    \
    CODE(BEER_WARE);                                                           \
    CODE(_IFNDEF " " _GUARD_H);                                                \
    DEFINE(_GUARD_H, "1")
  #define CODE(X)      fprintf(cpp_h, "%s\n", X)
  #define REM(X)       fprintf(cpp_h, "// %s\n", X)
  #define DEFINE(N, V) fprintf(cpp_h, _DEFINE " %s %s\n", N, V)
  #define CLOSE                                                                \
    CODE(_ENDIF "// " _GUARD_H);                                               \
    fclose(cpp_h)
#endif  // end check c++

#define MAX_BITS_IN_SYS (sizeof(size_t) * 0x8)

int main() {
  size_t stop_number = 0x0;
  for (size_t i = 0x0; i < BIT_S; i++) {
    stop_number |= 0x1 << i;
    if (stop_number == SYS_MAX) break;
  }

  size_t hex_count = 0x0;

  do {
    hex_count++;
  } while (stop_number >> (0x4 * hex_count));

  CREATE_H(_NAME);
  for (size_t numbers = 0x0; numbers <= stop_number; numbers++) {
    char hex[MAX_BITS_IN_SYS + 0x2] =
#if CAPS
        "0X";
#else
        "0x";
#endif
    for (size_t digits = 0x1; digits <= hex_count; digits++) {
      size_t key = (0xf << ((hex_count - digits) * 0x4));
      size_t lock = ((numbers & key) >> ((hex_count - digits) * 0x4));
      char dig[] = " ";
      if (lock <= 0x9) dig[0x0] = CAST(char)(lock + 0x30);
      if (lock >= 0xa)
        dig[0] = CAST(char)
#if CAPS
            (lock + 0x37);
#else
            (lock + 0x57);
#endif
      strcat(hex, dig);
    }
    // bin begin
    for (size_t j = 0x0; j <= BIT_S; j++) {
      if (numbers < (0x1 << j)) {
        char bin[MAX_BITS_IN_SYS + 0x1] = "B";
        {
          for (size_t bits = j - 0x1; bits <= MAX_BITS_IN_SYS; bits--) {
            strcat(bin, (numbers & (0x1 << bits)) ? "1" : "0");
          }
        }
        if (BIT_S && j) {
          DEFINE(bin, hex);
        }
      }
    }
  }
  CLOSE;
  return EXIT_SUCCESS;
}
