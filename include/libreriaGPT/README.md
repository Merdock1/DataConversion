# DataConversion Library

The DataConversion library provides convenient functions for merging and splitting various data types, such as `int8_t`, `uint8_t`, `uint16_t`, `int32_t`, and `uint32_t`. These functions are useful for converting data between different formats or extracting specific bytes from larger data types.

## Installation

1. Download the library as a ZIP file.
2. In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library**.
3. Select the downloaded ZIP file.
4. The library should now be installed and ready for use.

## Functions

### `mergeInt8ToUint16`

Combines two values of type `int8_t` into one `uint16_t` word.

`uint16_t mergeInt8ToUint16(int8_t firstI8Value, int8_t secondI8Value);`
`splitUint16ToInt8`
Separates a word of type `uint16_t` into two values of type `int8_t`.


`void splitUint16ToInt8(uint16_t valueUi16, int8_t& firstI8Value, int8_t& secondI8Value);`
`mergeUint8ToUint16`
Combines two values of type `uint8_t` into one `uint16_t` word.


`uint16_t mergeUint8ToUint16(uint8_t firstUi8Value, uint8_t secondUi8Value);`
`splitUint16ToUint8`
Separates a word of type `uint16_t` into two values of type `uint8_t`.

`void splitUint16ToUint8(uint16_t valueUi16, uint8_t& firstUi8Value, uint8_t& secondUi8Value);`
`mergeUint16ToInt32`
Combines two words of type `uint16_t` into one `int32_t` value.

`int32_t mergeUint16ToInt32(uint16_t ui16part1, uint16_t ui16part2);`
`splitInt32ToUint16`
Separates a value of type `int32_t` into two words of type `uint16_t`.

`void splitInt32ToUint16(int32_t valueI32, uint16_t& ui16part1, uint16_t& ui16part2);`
`mergeUint16ToUint32`
Combines two words of type `uint16_t` into one `uint32_t` value.

`uint32_t mergeUint16ToUint32(uint16_t ui16part1, uint16_t ui16part2);`
`splitUint32ToUint16`
Separates a value of type `uint32_t` into two words of type `uint16_t`.

`void splitUint32ToUint16(uint32_t valueUi32, uint16_t& ui16part1, uint16_t& ui16part2);`


Usage
Include the library in your Arduino sketch:

#include <DataConversion.h>
Use the provided functions to perform the desired data conversions. For example:

`int8_t firstValue = -12;`
`int8_t secondValue = 34;`
`uint16_t mergedResult = mergeInt8ToUint16(firstValue, secondValue);`
Refer to the function descriptions above for more details on each conversion function.
Contributing
Contributions to the DataConversion library are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request on the GitHub repository.

License
This library is released under the MIT License.
