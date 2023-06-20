#include <DataConversion.h>

// Create an instance of the DataConversion class
DataConversion dataConverter;

void setup()
{
    // Setup code
    // ...
}

void loop()
{
    // Your code
    // ...

    // Example usage of the DataConversion functions
    int8_t firstValue = -12;
    int8_t secondValue = 34;
    uint16_t mergedResult = dataConverter.mergeInt8ToUint16(firstValue, secondValue);

    // More code
    // ...
}
