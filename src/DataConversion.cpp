#include "DataConversion.h"

// Combines two values of type int8_t into one uint16_t word
uint16_t DataConversion::mergeInt8ToUint16(int8_t firstI8Value, int8_t secondI8Value)
{
    return ((uint16_t)firstI8Value << 8) | (uint8_t)secondI8Value;
}

// Separates a word of type uint16_t into two values of type int8_t
void DataConversion::splitUint16ToInt8(uint16_t valueUi16, int8_t &firstI8Value, int8_t &secondI8Value)
{
    firstI8Value = (int8_t)(valueUi16 >> 8);
    secondI8Value = (int8_t)(valueUi16 & 0xFF);
}

// Combines two values of type uint8_t into one uint16_t word
uint16_t DataConversion::mergeUint8ToUint16(uint8_t firstUi8Value, uint8_t secondUi8Value)
{
    return ((uint16_t)firstUi8Value << 8) | secondUi8Value;
}

// Separates a word of type uint16_t into two values of type uint8_t
void DataConversion::splitUint16ToUint8(uint16_t valueUi16, uint8_t &firstUi8Value, uint8_t &secondUi8Value)
{
    firstUi8Value = (uint8_t)(valueUi16 >> 8);
    secondUi8Value = (uint8_t)(valueUi16 & 0xFF);
}

// Combines two words of type uint16_t into one int32_t value
int32_t DataConversion::mergeUint16ToInt32(uint16_t ui16part1, uint16_t ui16part2)
{
    return ((int32_t)ui16part1 << 16) | ui16part2;
}

// Separates a value of type int32_t into two words of type uint16_t
void DataConversion::splitInt32ToUint16(int32_t valueI32, uint16_t &ui16part1, uint16_t &ui16part2)
{
    ui16part1 = (uint16_t)(valueI32 >> 16);
    ui16part2 = (uint16_t)(valueI32 & 0xFFFF);
}

// Combines two words of type uint16_t into one uint32_t value
uint32_t DataConversion::mergeUint16ToUint32(uint16_t ui16part1, uint16_t ui16part2)
{
    return ((uint32_t)ui16part1 << 16) | ui16part2;
}

// Separates a value of type uint32_t into two words of type uint16_t
void DataConversion::splitUint32ToUint16(uint32_t valueUi32, uint16_t &ui16part1, uint16_t &ui16part2)
{
    ui16part1 = (uint16_t)(valueUi32 >> 16);
    ui16part2 = (uint16_t)(valueUi32 & 0xFFFF);
}

// Combines two uint16_t words into a float value.
float DataConversion::mergeUint16ToFloat32(uint16_t ui16part1, uint16_t ui16part2)
{
    union
    {
        float floatValue;
        uint32_t intValue;
    } data;

    data.intValue = ((uint32_t)ui16part1 << 16) | ui16part2;
    return data.floatValue;
}

// Splits a float value into two uint16_t words.
void DataConversion::splitFloat32ToUint16(float valueF32, uint16_t &ui16part1, uint16_t &ui16part2)
{
    union
    {
        float floatValue;
        uint32_t intValue;
    } data;

    data.floatValue = valueF32;
    ui16part1 = (uint16_t)(data.intValue >> 16);
    ui16part2 = (uint16_t)(data.intValue & 0xFFFF);
}

// Combines four uint16_t words into an int64_t value.

int64_t DataConversion::mergeUint16ToInt64(uint16_t int64Part1, uint16_t int64Part2, uint16_t int64Part3, uint16_t int64Part4)
{
    int64_t result = 0;
    result |= ((int64_t)int64Part1 << 48);
    result |= ((int64_t)int64Part2 << 32);
    result |= ((int64_t)int64Part3 << 16);
    result |= (int64_t)int64Part4;

    return result;
}

// Splits an int64_t value into four uint16_t words.
void DataConversion::splitInt64ToUint16(int64_t valueI64, uint16_t &int64Part1, uint16_t &int64Part2, uint16_t &int64Part3, uint16_t &int64Part4)
{
    int64Part1 = (uint16_t)(valueI64 >> 48);
    int64Part2 = (uint16_t)(valueI64 >> 32);
    int64Part3 = (uint16_t)(valueI64 >> 16);
    int64Part4 = (uint16_t)valueI64;
}

// Combines four uint16_t words into a uint64_t value.
uint64_t DataConversion::mergeUint16ToUint64(uint16_t uint64Part1, uint16_t uint64Part2, uint16_t uint64Part3, uint16_t uint64Part4)
{
    uint64_t result = 0;
    result |= ((uint64_t)uint64Part1 << 48);
    result |= ((uint64_t)uint64Part2 << 32);
    result |= ((uint64_t)uint64Part3 << 16);
    result |= (uint64_t)uint64Part4;

    return result;
}

// Splits a uint64_t value into four uint16_t words.
void DataConversion::splitUint64ToUint16(uint64_t valueUi64, uint16_t &uint64Part1, uint16_t &uint64Part2, uint16_t &uint64Part3, uint16_t &uint64Part4)
{
    uint64Part1 = (uint16_t)(valueUi64 >> 48);
    uint64Part2 = (uint16_t)(valueUi64 >> 32);
    uint64Part3 = (uint16_t)(valueUi64 >> 16);
    uint64Part4 = (uint16_t)valueUi64;
}

// Combines four uint16_t parts into a double value.
double DataConversion::mergeUint16ToDouble(uint16_t dblPart1, uint16_t dblPart2, uint16_t dblPart3, uint16_t dblPart4)
{
    uint64_t mergedValue = 0;
    mergedValue |= ((uint64_t)dblPart1 << 48);
    mergedValue |= ((uint64_t)dblPart2 << 32);
    mergedValue |= ((uint64_t)dblPart3 << 16);
    mergedValue |= (uint64_t)dblPart4;
    double result = *reinterpret_cast<double *>(&mergedValue);

    return result;
}

// Splits a double value into four uint16_t parts.
void DataConversion::splitDoubleToUint16(double dblValue, uint16_t &dblPart1, uint16_t &dblPart2, uint16_t &dblPart3, uint16_t &dblPart4)
{
    uint64_t mergedValue = *reinterpret_cast<uint64_t *>(&dblValue);
    dblPart1 = (uint16_t)(mergedValue >> 48);
    dblPart2 = (uint16_t)(mergedValue >> 32);
    dblPart3 = (uint16_t)(mergedValue >> 16);
    dblPart4 = (uint16_t)mergedValue;
}