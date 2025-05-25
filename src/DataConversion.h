#ifndef DataConversion_h
#define DataConversion_h

#include <Arduino.h>

class DataConversion
{
public:
    /**
     * Combines two values of type int8_t into one uint16_t word.
     *
     * @param firstI8Value The most significant byte.
     * @param secondI8Value The least significant byte.
     * @return The result of combining the bytes into a uint16_t word.
     */
    static uint16_t mergeInt8ToUint16(int8_t firstI8Value, int8_t secondI8Value);

    /**
     * Separates a word of type uint16_t into two values of type int8_t.
     *
     * @param valueUi16 the word uint16_t to separate.
     * @param firstI8Value Reference to the resulting most significant byte.
     * @param secondI8Value Reference to the resulting least significant byte.
     */
    static void splitUint16ToInt8(uint16_t valueUi16, int8_t &firstI8Value, int8_t &secondI8Value);

    /**
     * Combines two values of type uint8_t into one uint16_t word.
     *
     * @param firstUi8Value The most significant byte.
     * @param secondUi8Value The least significant byte.
     * @return The result of combining the bytes into a uint16_t word.
     */
    static uint16_t mergeUint8ToUint16(uint8_t firstUi8Value, uint8_t secondUi8Value);

    /**
     * Separates a word of type uint16_t into two values of type uint8_t.
     *
     * @param valueUi16 The word uint16_t to separate.
     * @param firstUi8Value Reference to the resulting most significant byte.
     * @param secondUi8Value Reference to the resulting least significant byte.
     */
    static void splitUint16ToUint8(uint16_t valueUi16, uint8_t &firstUi8Value, uint8_t &secondUi8Value);

    /**
     * Combines two words of type uint16_t into one int32_t value.
     *
     * @param ui16part1 The most significant word.
     * @param ui16part2 The least significant word.
     * @return The result of combining the words into an int32_t value.
     */
    static int32_t mergeUint16ToInt32(uint16_t ui16part1, uint16_t ui16part2);

    /**
     * Separates a value of type int32_t into two words of type uint16_t.
     *
     * @param valueI32 The int32_t value to split.
     * @param ui16part1 Reference to the resulting most significant word.
     * @param ui16part2 Reference to the resulting least significant word.
     */
    static void splitInt32ToUint16(int32_t valueI32, uint16_t &ui16part1, uint16_t &ui16part2);

    /**
     * Combines two words of type uint16_t into one uint32_t value.
     *
     * @param ui16part1 The most significant word.
     * @param ui16part2 The least significant word.
     * @return The result of combining the words into a uint32_t value.
     */
    static uint32_t mergeUint16ToUint32(uint16_t ui16part1, uint16_t ui16part2);

    /**
     * Separates a value of type uint32_t into two words of type uint16_t.
     *
     * @param valueUi32 The uint32_t value to separate.
     * @param ui16part1 Reference to the resulting most significant word.
     * @param ui16part2 Reference to the resulting least significant word.
     */
    static void splitUint32ToUint16(uint32_t valueUi32, uint16_t &ui16part1, uint16_t &ui16part2);

    /**
     * Combines two uint16_t words into a float value.
     *
     * @param ui16part1 The most significant word.
     * @param ui16part2 The least significant word.
     * @return The result of combining the words into a float value.
     */
    static float mergeUint16ToFloat32(uint16_t ui16part1, uint16_t ui16part2);

    /**
     * Splits a float value into two uint16_t words.
     *
     * @param valueF32 The float value to split.
     * @param ui16part1 Reference to the resulting most significant word.
     * @param ui16part2 Reference to the resulting least significant word.
     */
    static void splitFloat32ToUint16(float valueF32, uint16_t &ui16part1, uint16_t &ui16part2);

    /**
     * Combines four uint16_t words into an int64_t value.
     *
     * @param int64Part1 The first word.
     * @param int64Part2 The second word.
     * @param int64Part3 The third word.
     * @param int64Part4 The fourth word.
     * @return The result of combining the words into an int64_t value.
     */
    static int64_t mergeUint16ToInt64(uint16_t int64Part1, uint16_t int64Part2, uint16_t int64Part3, uint16_t int64Part4);

    /**
     * Splits an int64_t value into four uint16_t words.
     *
     * @param valueI64 The int64_t value to split.
     * @param int64Part1 Reference to the resulting first word.
     * @param int64Part2 Reference to the resulting second word.
     * @param int64Part3 Reference to the resulting third word.
     * @param int64Part4 Reference to the resulting fourth word.
     */
    static void splitInt64ToUint16(int64_t valueI64, uint16_t &int64Part1, uint16_t &int64Part2, uint16_t &int64Part3, uint16_t &int64Part4);

    /**
     * Combines four uint16_t words into a uint64_t value.
     *
     * @param uint64Part1 The first word.
     * @param uint64Part2 The second word.
     * @param uint64Part3 The third word.
     * @param uint64Part4 The fourth word.
     * @return The result of combining the words into a uint64_t value.
     */
    static uint64_t mergeUint16ToUint64(uint16_t uint64Part1, uint16_t uint64Part2, uint16_t uint64Part3, uint16_t uint64Part4);

    /**
     * Splits a uint64_t value into four uint16_t words.
     *
     * @param valueUi64 The uint64_t value to split.
     * @param uint64Part1 Reference to the resulting first word.
     * @param uint64Part2 Reference to the resulting second word.
     * @param uint64Part3 Reference to the resulting third word.
     * @param uint64Part4 Reference to the resulting fourth word.
     */
    static void splitUint64ToUint16(uint64_t valueUi64, uint16_t &uint64Part1, uint16_t &uint64Part2, uint16_t &uint64Part3, uint16_t &uint64Part4);

    /**
     * Combines four uint16_t words into a double value.
     *
     * @param dblPart1 The first part of the double value.
     * @param dblPart2 The second part of the double value.
     * @param dblPart3 The third part of the double value.
     * @param dblPart4 The fourth part of the double value.
     * @return The result of combining the four parts into a double value.
     */
    static double mergeUint16ToDouble(uint16_t dblPart1, uint16_t dblPart2, uint16_t dblPart3, uint16_t dblPart4);

    /**
     * Splits a double value into four uint16_t parts.
     *
     * @param dblValue The double value to split.
     * @param dblPart1 Reference to the resulting first part.
     * @param dblPart2 Reference to the resulting second part.
     * @param dblPart3 Reference to the resulting third part.
     * @param dblPart4 Reference to the resulting fourth part.
     */
    static void splitDoubleToUint16(double dblValue, uint16_t &dblPart1, uint16_t &dblPart2, uint16_t &dblPart3, uint16_t &dblPart4);

    /**
     * Sets a specific bit in a uint16_t value.
     *
     * @param data The original uint16_t value.
     * @param bitPosition The position of the bit to set (0-15).
     * @return The uint16_t value with the specified bit set.
     */
    static uint16_t setBit(uint16_t data, uint8_t bitPosition);

    /**
     * Clears a specific bit in a uint16_t value.
     *
     * @param data The original uint16_t value.
     * @param bitPosition The position of the bit to clear (0-15).
     * @return The uint16_t value with the specified bit cleared.
     */
    static uint16_t clearBit(uint16_t data, uint8_t bitPosition);

    /**
     * Reads a specific bit from a uint16_t value.
     *
     * @param data The uint16_t value to read from.
     * @param bitPosition The position of the bit to read (0-15).
     * @return True if the bit is set (1), false if it is clear (0).
     */
    static bool readBit(uint16_t data, uint8_t bitPosition);

    /**
     * Toggles a specific bit in a uint16_t value.
     *
     * @param data The original uint16_t value.
     * @param bitPosition The position of the bit to toggle (0-15).
     * @return The uint16_t value with the specified bit toggled.
     */
    static uint16_t toggleBit(uint16_t data, uint8_t bitPosition);
};

#endif
