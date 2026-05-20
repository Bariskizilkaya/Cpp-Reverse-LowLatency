- [src/2.cpp](src/2.cpp) 

```
(gdb) p &car1
$1 = (Car *) 0x7fffffffce90
(gdb) ptype /o car1
/* offset      |    size */  type = struct Car {
/*      0      |      32 */    std::string brand;
/*     32      |      32 */    std::string model;
/*     64      |       4 */    int year;
/* XXX  4-byte padding   */

                               /* total size (bytes):   72 */
                             }
(gdb) x/72xg 0x7fffffffce90
0x7fffffffce90: 0x00007fffffffcea0      0x0000000000000006
0x7fffffffcea0: 0x000061746f796f54      0x0000000000000000
0x7fffffffceb0: 0x00007fffffffcec0      0x0000000000000007
0x7fffffffcec0: 0x00616c6c6f726f43      0x0000000000000000
0x7fffffffced0: 0x00000000000007e4      0x00007ffff7e6c398
0x7fffffffcee0: 0x00007fffffffcf20      0x00007ffff78ad812
0x7fffffffcef0: 0x00007fffffffcf20      0x00007ffff7e6c340
0x7fffffffcf00: 0x2e78786362696c67      0x0000000000012000
0x7fffffffcf10: 0x2e78786362696c67      0x6c6f6f705f68652e
0x7fffffffcf20: 0x00007fffffffcfc0      0x8b65ab4de5bf0f00
0x7fffffffcf30: 0x00007fffffffd068      0x0000000000000001
0x7fffffffcf40: 0x00007fffffffcfe0      0x00007ffff782a1ca
0x7fffffffcf50: 0x0000000000000008      0x00007fffffffd068
0x7fffffffcf60: 0x00000001f7a04fa8      0x0000555555556289
0x7fffffffcf70: 0x00007fffffffd068      0xee8ed6819ffb4a90
0x7fffffffcf80: 0x0000000000000001      0x0000000000000000
0x7fffffffcf90: 0x0000555555559d50      0x00007ffff7ffd000
0x7fffffffcfa0: 0xee8ed6819e9b4a90      0xee8ec67b43394a90
0x7fffffffcfb0: 0x00007fff00000000      0x0000000000000000
0x7fffffffcfc0: 0x0000000000000000      0x0000000000000001
0x7fffffffcfd0: 0x00007fffffffd060      0x8b65ab4de5bf0f00
0x7fffffffcfe0: 0x00007fffffffd040      0x00007ffff782a28b
0x7fffffffcff0: 0x00007fffffffd078      0x0000555555559d50
0x7fffffffd000: 0x00007fffffffd078      0x0000555555556289
0x7fffffffd010: 0x0000000000000000      0x0000000000000000
0x7fffffffd020: 0x00005555555561a0      0x00007fffffffd060
0x7fffffffd030: 0x0000000000000000      0x0000000000000000
0x7fffffffd040: 0x0000000000000000      0x00005555555561c5
0x7fffffffd050: 0x00007fffffffd058      0x0000000000000038
0x7fffffffd060: 0x0000000000000001      0x00007fffffffd564
0x7fffffffd070: 0x0000000000000000      0x00007fffffffd5a1
0x7fffffffd080: 0x00007fffffffd5b1      0x00007fffffffd605
0x7fffffffd090: 0x00007fffffffd618      0x00007fffffffd62a
0x7fffffffd0a0: 0x00007fffffffd63e      0x00007fffffffd672
0x7fffffffd0b0: 0x00007fffffffd69f      0x00007fffffffd6b7
0x7fffffffd0c0: 0x00007fffffffd6ce      0x00007fffffffd6fa
(gdb)
```

Memory Layout explanation

```
```txt
Car Object Memory Layout (64-bit Linux, libstdc++, GCC)

Source Code
-----------

class Car
{
    std::string brand;
    std::string model;
    int year;
};

GDB Output
----------

(gdb) p &car1
$1 = (Car *) 0x7fffffffce90

(gdb) ptype /o car1

/* offset      |    size */  type = struct Car {
/*      0      |      32 */    std::string brand;
/*     32      |      32 */    std::string model;
/*     64      |       4 */    int year;
/* XXX  4-byte padding   */

                               /* total size (bytes):   72 */
                             }

------------------------------------------------------------
1. Overall Object Layout
------------------------------------------------------------

Address: 0x7fffffffce90

+-------------------------------+
| brand std::string   (32B)     |  offset 0
+-------------------------------+
| model std::string   (32B)     |  offset 32
+-------------------------------+
| year int            (4B)      |  offset 64
+-------------------------------+
| padding             (4B)      |  offset 68
+-------------------------------+

Total Size = 72 bytes

------------------------------------------------------------
2. Important Note About x/72xg
------------------------------------------------------------

Command used:

(gdb) x/72xg 0x7fffffffce90

Meaning:

72 units
each unit = giant word (8 bytes)

Total dumped memory:

72 * 8 = 576 bytes

So GDB printed much more than the object itself.

Correct command for exactly the object:

(gdb) x/9gx 0x7fffffffce90

because:

72 bytes / 8 = 9 giant words

------------------------------------------------------------
3. Actual Car Object Memory
------------------------------------------------------------

0x7fffffffce90: 0x00007fffffffcea0  0x0000000000000006
0x7fffffffcea0: 0x000061746f796f54  0x0000000000000000

0x7fffffffceb0: 0x00007fffffffcec0  0x0000000000000007
0x7fffffffcec0: 0x00616c6c6f726f43  0x0000000000000000

0x7fffffffced0: 0x00000000000007e4  0x00007ffff7e6c398

------------------------------------------------------------
4. std::string Internal Layout
------------------------------------------------------------

On this platform:

sizeof(std::string) = 32 bytes

Typical libstdc++ layout:

struct string {
    char* ptr;        // 8 bytes
    size_t size;      // 8 bytes

    union {
        size_t capacity;
        char small_buffer[16];
    };
};

This implementation supports:

Small String Optimization (SSO)

Small strings are stored directly inside the object
without heap allocation.

------------------------------------------------------------
5. First std::string : brand = "Toyota"
------------------------------------------------------------

Starts at:

0x7fffffffce90

--------------------------------------------------
Pointer
--------------------------------------------------

0x7fffffffce90: 0x00007fffffffcea0

Meaning:

ptr = 0x7fffffffcea0

The pointer points INSIDE the object itself.

This indicates:

SSO is active.

--------------------------------------------------
Size
--------------------------------------------------

0x7fffffffce98: 0x0000000000000006

Meaning:

size = 6

because:

"Toyota" = 6 characters

--------------------------------------------------
Character Buffer
--------------------------------------------------

0x7fffffffcea0: 0x000061746f796f54
0x7fffffffcea8: 0x0000000000000000

ASCII bytes:

54 6f 79 6f 74 61
 T  o  y  o  t  a

So the internal buffer contains:

"Toyota"

stored directly inside std::string.

------------------------------------------------------------
6. Second std::string : model = "Corolla"
------------------------------------------------------------

Starts at:

0x7fffffffceb0

--------------------------------------------------
Pointer
--------------------------------------------------

0x7fffffffceb0: 0x00007fffffffcec0

Meaning:

ptr = 0x7fffffffcec0

Again points INSIDE the object.

SSO is active again.

--------------------------------------------------
Size
--------------------------------------------------

0x7fffffffceb8: 0x0000000000000007

Meaning:

size = 7

because:

"Corolla" = 7 characters

--------------------------------------------------
Character Buffer
--------------------------------------------------

0x7fffffffcec0: 0x00616c6c6f726f43

ASCII bytes:

43 6f 72 6f 6c 6c 61
 C  o  r  o  l  l  a

So the buffer contains:

"Corolla"

stored inline inside std::string.

------------------------------------------------------------
7. Integer Member : year
------------------------------------------------------------

At offset 64:

0x7fffffffced0: 0x00000000000007e4

Hex:

0x07e4

Decimal:

2020

Meaning:

year = 2020

------------------------------------------------------------
8. Padding
------------------------------------------------------------

The compiler inserted 4 bytes of padding
after the integer for alignment purposes.

Layout:

offset 64 -> int year (4 bytes)
offset 68 -> padding (4 bytes)

Total object size becomes:

72 bytes

------------------------------------------------------------
9. Complete Visual Representation
------------------------------------------------------------

Object Start:
0x7fffffffce90

OFFSET   CONTENT
------   ----------------------------------------

0x00     ptr -> 0x7fffffffcea0
0x08     size = 6
0x10     'T' 'o' 'y' 'o' 't' 'a' '\0'
0x18     remaining SSO bytes

0x20     ptr -> 0x7fffffffcec0
0x28     size = 7
0x30     'C' 'o' 'r' 'o' 'l' 'l' 'a' '\0'
0x38     remaining SSO bytes

0x40     year = 2020
0x44     padding

------------------------------------------------------------
10. Why The Pointer Points Inside The Object
------------------------------------------------------------

This is Small String Optimization (SSO).

Instead of:

stack object ---> heap allocation

small strings become:

stack object ---> internal inline buffer

Benefits:

- avoids malloc/free
- reduces heap fragmentation
- improves cache locality
- improves performance

------------------------------------------------------------
11. What Happens With Long Strings
------------------------------------------------------------

Example:

brand = "VeryVeryVeryLongCarBrand"

Now SSO no longer fits.

The layout changes to:

ptr -> heap memory

The object stores:

- pointer
- size
- capacity

while actual characters live on the heap.

------------------------------------------------------------
12. Key Reverse Engineering Observation
------------------------------------------------------------

This value:

ptr = 0x7fffffffcea0

points INSIDE the same object.

Object start:

0x7fffffffce90

String data:

0x7fffffffcea0

Difference:

0x10 = 16 bytes

Exactly where the inline SSO buffer begins.

This is one of the easiest ways to reverse engineer
STL implementations directly from memory dumps.
```

```