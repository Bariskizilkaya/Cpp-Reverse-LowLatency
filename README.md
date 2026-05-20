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