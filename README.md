# C-Reverse-LowLatency

A tiny C++ demo that shows a simple `Car` class and prints messages when cars are created.

## Files

- [src/1.cpp](src/1.cpp) 

Compiled by 

`g++ -O0 -g3 -std=c++20 -o ./out/1 1.cpp`

Opened in gdb

`gdb ./1`

Get the adress of the car1

```
(gdb) p &car1
$1 = (Car *) 0x7fffffffce80
```

Get the size of the object

```

(gdb) ptype /o car1
/* offset      |    size */  type = class Car {
/*      0      |      32 */    std::string brand;
/*     32      |      32 */    std::string model;
/*     64      |       4 */    int year;
/* XXX  4-byte padding   */

                               /* total size (bytes):   72 */
                             }

```

The memory layout of the car1 object

```

(gdb) x/72xg 0x7fffffffce80
0x7fffffffce80: 0x00007fffffffce90      0x0000000000000006
0x7fffffffce90: 0x000061746f796f54      0x79095db7d78e7500
0x7fffffffcea0: 0x00007fffffffceb0      0x0000000000000007
0x7fffffffceb0: 0x00616c6c6f726f43      0xffffffffffffff98
0x7fffffffcec0: 0x00007fff000007e4      0x00007ffff7e6c398
0x7fffffffced0: 0x00007fffffffcee0      0x0000000000000007
0x7fffffffcee0: 0x00616c6c6f726f43      0x00007ffff7e6c340
0x7fffffffcef0: 0x2e78786362696c67      0x0000000000012000
0x7fffffffcf00: 0x2e78786362696c67      0x6c6f6f705f68652e
0x7fffffffcf10: 0x00007fffffffcfb0      0x79095db7d78e7500
0x7fffffffcf20: 0x00007ffff7e7aa50      0x00007fffffffd058
0x7fffffffcf30: 0x00007fffffffcfd0      0x00007ffff782a1ca
0x7fffffffcf40: 0x0000000000000008      0x00007fffffffd058
0x7fffffffcf50: 0x00000001f7a04fa8      0x0000555555556309
0x7fffffffcf60: 0x00007fffffffd058      0x16400f33ab9816da
0x7fffffffcf70: 0x0000000000000001      0x0000000000000000
0x7fffffffcf80: 0x0000555555559d28      0x00007ffff7ffd000
0x7fffffffcf90: 0x16400f33aab816da      0x16401fc9773a16da
0x7fffffffcfa0: 0x00007fff00000000      0x0000000000000000
0x7fffffffcfb0: 0x0000000000000000      0x0000000000000001
0x7fffffffcfc0: 0x00007fffffffd050      0x79095db7d78e7500
0x7fffffffcfd0: 0x00007fffffffd030      0x00007ffff782a28b
0x7fffffffcfe0: 0x00007fffffffd068      0x0000555555559d28
0x7fffffffcff0: 0x00007fffffffd068      0x0000555555556309
0x7fffffffd000: 0x0000000000000000      0x0000000000000000
0x7fffffffd010: 0x0000555555556220      0x00007fffffffd050
0x7fffffffd020: 0x0000000000000000      0x0000000000000000
0x7fffffffd030: 0x0000000000000000      0x0000555555556245
0x7fffffffd040: 0x00007fffffffd048      0x0000000000000038
0x7fffffffd050: 0x0000000000000001      0x00007fffffffd55c
0x7fffffffd060: 0x0000000000000000      0x00007fffffffd599
0x7fffffffd070: 0x00007fffffffd5a9      0x00007fffffffd5fd
0x7fffffffd080: 0x00007fffffffd610      0x00007fffffffd622
0x7fffffffd090: 0x00007fffffffd636      0x00007fffffffd66a
0x7fffffffd0a0: 0x00007fffffffd697      0x00007fffffffd6af
0x7fffffffd0b0: 0x00007fffffffd6c6      0x00007fffffffd6f2

```

Detailed explanation of a object layout of the car1

```
car1 object @ 0x7fffffffce80
Total size: 72 bytes (0x48)

================================================================================
OFFSET   ADDRESS             DATA                              INTERPRETATION
================================================================================

[ brand : std::string ]  (32 bytes)
--------------------------------------------------------------------------------
0x00     0x7fffffffce80    0x00007fffffffce90    pointer to inline buffer
0x08     0x7fffffffce88    0x0000000000000006    size = 6

0x10     0x7fffffffce90    0x000061746f796f54
0x18     0x7fffffffce98    0x79095db7d78e7500

Little-endian decode:
54 6f 79 6f 74 61 00
 T  o  y  o  t  a

brand = "Toyota"

================================================================================

[ model : std::string ]  (32 bytes)
--------------------------------------------------------------------------------
0x20     0x7fffffffcea0    0x00007fffffffceb0    pointer to inline buffer
0x28     0x7fffffffcea8    0x0000000000000007    size = 7

0x30     0x7fffffffceb0    0x00616c6c6f726f43
0x38     0x7fffffffceb8    0xffffffffffffff98

Little-endian decode:
43 6f 72 6f 6c 6c 61 00
 C  o  r  o  l  l  a

model = "Corolla"

================================================================================

[ year : int ]  (4 bytes)
--------------------------------------------------------------------------------
0x40     0x7fffffffcec0    0x000007e4

Little-endian:
e4 07 00 00

0x07e4 = 2020

year = 2020

================================================================================

[ padding ]  (4 bytes)
--------------------------------------------------------------------------------
0x44     0x7fffffffcec4    0x00007fff

compiler-added alignment padding

================================================================================
OBJECT SUMMARY
================================================================================

0x7fffffffce80 ─┬─ brand std::string
                │    ptr  -> 0x7fffffffce90
                │    size -> 6
                │    data -> "Toyota"
                │
0x7fffffffcea0 ─┬─ model std::string
                │    ptr  -> 0x7fffffffceb0
                │    size -> 7
                │    data -> "Corolla"
                │
0x7fffffffcec0 ─┬─ year = 2020
                │
0x7fffffffcec4 ─┬─ padding

================================================================================


```