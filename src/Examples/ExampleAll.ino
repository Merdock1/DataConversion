

#include <Arduino.h>
/*
  Modbus-Arduino Example - Test Holding Register (Modbus IP ESP8266)
  Configure Holding Register (offset 100) with initial value 0xABCD
  You can get or set this holding register
  Original library
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino
  Current version
  (c)2017 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

/*
The DataConversion library now provides platform-independent bit manipulation functions:
- DataConversion::readBit() to read a specific bit.
- DataConversion::setBit() to set a specific bit.
- DataConversion::clearBit() to clear a specific bit.
- DataConversion::toggleBit() to toggle a specific bit.
These can be used as an alternative to Arduino's built-in bitRead() and bitWrite().
*/
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else // ESP32
#include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>
#include <DataConversion.h>

/*
The enum function is used to create an enumerated data type.
In this case, it is creating the MbipRegister enumeration type.
The enumeration defines a set of named constants that represent possible values.
Each constant is automatically assigned an integer value (0, 1, 2, etc.).
The constants defined in this enumeration represent different registers used in the program.
These registers are used to reference specific memory addresses.
*/

// Enum is used to name the registration numbers.
enum ModbusRegisters
{
  NR_STATE_16BIT_REGISTER, // Register 0: State register (16-bit). Used in Function bitRead() and bitWrite.
  NR_MERGEINT8TOUINT16,    // Register 1: Merging 2 signed 8-bit values to an unsigned 16-bit value. Used in Function mergeInt8ToUint16() and splitUint16ToInt8().
  NR_MERGEUINT8TOUINT16,   // Register 2: Merging 2 unsigned 8-bit values to an unsigned 16-bit value. Used in Function mergeUint8ToUint16() and splitUint16ToUint8().
  NR_VALUEI32PART1,        // Register 3: High word of a 32-bit value split into 2 unsigned 16-bit values. Used in Function mergeUint16ToInt32() and splitInt32ToUint16.
  NR_VALUEI32PART2,        // Register 4: Low word of a 32-bit value split into 2 unsigned 16-bit values. Used in Function mergeUint16ToInt32() and splitInt32ToUint16.
  NR_VALUEUI32PART1,       // Register 5: High value of a 32-bit unsigned value split into 2 unsigned 16-bit values. Used in Function mergeUint16ToUint32() and splitUint32ToUint16..
  NR_VALUEUI32PART2,       // Register 6: Low value of a 32-bit unsigned value split into 2 unsigned 16-bit values. Used in Function mergeUint16ToUint32() and splitUint32ToUint16..
  NR_FLOATPART1,           // Register 7: High word of a 32-bit floating-point value split into 2 unsigned 16-bit values. Used in Function mergeUint16ToFloat32() and splitFloat32ToUint16().
  NR_FLOATPART2,           // Register 8: Low word of a 32-bit floating-point value split into 2 unsigned 16-bit values. Used in Function mergeUint16ToFloat32() and splitFloat32ToUint16().
  NR_VALUEI64PART1,        // Register 9: First 16-bit unsigned variable. Used in Function mergeUint16ToInt64() and splitInt64ToUint16().
  NR_VALUEI64PART2,        // Register 10: Second 16-bit unsigned variable. Used in Function mergeUint16ToInt64() and splitInt64ToUint16().
  NR_VALUEI64PART3,        // Register 11: Third 16-bit unsigned variable. Used in Function mergeUint16ToInt64() and splitInt64ToUint16().
  NR_VALUEI64PART4,        // Register 12: Fourth 16-bit unsigned variable. Used in Function mergeUint16ToInt64() and splitInt64ToUint16().
  NR_VALUEUI64PART1,       // Register 13: First 16-bit unsigned variable. Used in Function mergeUint16ToUint64() and splitUint64ToUint16().
  NR_VALUEUI64PART2,       // Register 14: Second 16-bit unsigned variable. Used in Function mergeUint16ToUint64() and splitUint64ToUint16().
  NR_VALUEUI64PART3,       // Register 15: Third 16-bit unsigned variable. Used in Function mergeUint16ToUint64() and splitUint64ToUint16().
  NR_VALUEUI64PART4,       // Register 16: Fourth 16-bit unsigned variable. Used in Function mergeUint16ToUint64() and splitUint64ToUint16().
  NR_VALUEDBPART1,         // Register 17: First 16-bit unsigned variable. Used in Function mergeUint16ToDouble() and splitDoubleToUint16().
  NR_VALUEDBPART2,         // Register 18: Second 16-bit unsigned variable. Used in Function mergeUint16ToDouble() and splitDoubleToUint16().
  NR_VALUEDBPART3,         // Register 19: Third 16-bit unsigned variable. Used in Function mergeUint16ToDouble() and splitDoubleToUint16().
  NR_VALUEDBPART4,         // Register 20: Fourth 16-bit unsigned variable. Used in Function mergeUint16ToDouble() and splitDoubleToUint16().
  NR_TOTAL_REGISTERS       // Total number of registers.
};

// Variable that stores the 16-bit state register.
uint16_t state16bitRegister = 0;
// Individual boolean variables to store the values of each bit in the state16bitRegister.
bool bitValue00; // Value of bit 0.
bool bitValue01; // Value of bit 1.
bool bitValue02; // Value of bit 2.
bool bitValue03; // Value of bit 3.
bool bitValue04; // Value of bit 4.
bool bitValue05; // Value of bit 5.
bool bitValue06; // Value of bit 6.
bool bitValue07; // Value of bit 7.
bool bitValue08; // Value of bit 8.
bool bitValue09; // Value of bit 9.
bool bitValue10; // Value of bit 10.
bool bitValue11; // Value of bit 11.
bool bitValue12; // Value of bit 12.
bool bitValue13; // Value of bit 13.
bool bitValue14; // Value of bit 14.
bool bitValue15; // Value of bit 15.

// Global variables for 2 signed 8-bit to unsigned 16-bit.
int8_t varI8a = 0;                 // 8-bit signed variable initialized to 0.
int8_t varI8b = 0;                 // 8-bit signed variable initialized to 0.
uint16_t varMergeInt8ToUInt16 = 0; // 16-bit unsigned variable initialized to 0.

// Global variables for 2 unsigned 8-bit to unsigned 16-bit.
uint8_t varUi8a = 0;                // 8-bit unsigned variable initialized to 0.
uint8_t varUi8b = 0;                // 8-bit unsigned variable initialized to 0.
uint16_t varMergeUint8ToUint16 = 0; // 16-bit unsigned variable initialized to 0.

// Global variables for 1 signed 32-bit to 2 unsigned 16-bit.
uint16_t varValueI32Part1 = 0;     // 16-bit unsigned variable initialized to 0.
uint16_t varValueI32Part2 = 0;     // 16-bit unsigned variable initialized to 0.
int32_t varMergeUInt16ToInt32 = 0; // 32-bit signed variable initialized to 0.

// Global variables for 1 unsigned 32-bit to 2 unsigned 16-bit.
uint16_t varValueUi32Part1 = 0;      // 16-bit unsigned variable initialized to 0.
uint16_t varValueUi32Part2 = 0;      // 16-bit unsigned variable initialized to 0.
uint32_t varMergeUInt16ToUInt32 = 0; // 32-bit unsigned variable initialized to 0.

// Global variables for 1 float 32-bit to 2 unsigned 16-bit.
uint16_t varFloatPart1 = 0;           // 16-bit unsigned variable initialized to 0.
uint16_t varFloatPart2 = 0;           // 16-bit unsigned variable initialized to 0.
float varMergeUInt16ToFloat32 = 0.0f; // 32-bit float variable initialized to 0.0.

// Global variables for 1 signed 64-bit to 4 unsigned 16-bit.
uint16_t varValueI64Part1 = 0;     // 16-bit unsigned variable initialized to 0.
uint16_t varValueI64Part2 = 0;     // 16-bit unsigned variable initialized to 0.
uint16_t varValueI64Part3 = 0;     // 16-bit unsigned variable initialized to 0.
uint16_t varValueI64Part4 = 0;     // 16-bit unsigned variable initialized to 0.
int64_t varMergeUInt16ToInt64 = 0; // 64-bit signed variable initialized to 0.

// Global variables for 1 unsigned 64-bit to 4 unsigned 16-bit.
uint16_t varValueUi64Part1 = 0;      // 16-bit unsigned variable initialized to 0.
uint16_t varValueUi64Part2 = 0;      // 16-bit unsigned variable initialized to 0.
uint16_t varValueUi64Part3 = 0;      // 16-bit unsigned variable initialized to 0.
uint16_t varValueUi64Part4 = 0;      // 16-bit unsigned variable initialized to 0.
uint64_t varMergeUInt16ToUInt64 = 0; // 64-bit unsigned variable initialized to 0.

// Global variables for 1 double to 4 unsigned 16-bit.
uint16_t varValueDbPart1 = 0;        // 16-bit unsigned variable initialized to 0.
uint16_t varValueDbPart2 = 0;        // 16-bit unsigned variable initialized to 0.
uint16_t varValueDbPart3 = 0;        // 16-bit unsigned variable initialized to 0.
uint16_t varValueDbPart4 = 0;        // 16-bit unsigned variable initialized to 0.
double varMergeUInt16ToDouble = 0.0; // 64-bit double variable initialized to 0.0.

// Variable to store the previous time
static unsigned long previousMillis = 0;

// ModbusIP object
ModbusIP mb;

void setup()
{
  Serial.begin(115200);

  WiFi.begin("SSID", "PASSWORD");

  Serial.println("");
  Serial.println("Initializing WiFi connection");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(2000);

  mb.server();
  // Add holding registers to the ModbusIP object
  // Parameters: starting address, initial value, number of registers
  mb.addHreg(0, 0, NR_TOTAL_REGISTERS);

  // Write a value to a specific holding register
  // Parameters: register number, value to be written
  mb.Hreg(NR_STATE_16BIT_REGISTER, state16bitRegister);
  Serial.println("Register 0 BIN= " + String(state16bitRegister, BIN));
  delay(1500);
  state16bitRegister = DataConversion::setBit(state16bitRegister, 7);
  Serial.println("Write 1 in bit 7 using DataConversion::setBit()");
  delay(500);
  state16bitRegister = DataConversion::setBit(state16bitRegister, 14);
  Serial.println("Write 1 in bit 14 using DataConversion::setBit()");
  delay(500);
  mb.Hreg(NR_STATE_16BIT_REGISTER, state16bitRegister);
  Serial.println("Writing value in modbus variable ");
  delay(500);

  /* Part that works with 2 signed 8-bit values*/
  mb.Hreg(NR_MERGEINT8TOUINT16, varMergeInt8ToUInt16);
  // Print the value of the register
  Serial.println("Register 1 = " + String(varMergeInt8ToUInt16, DEC));
  delay(500);
  // Assign values to variables and merge them
  varI8a = -128;
  Serial.println("Write -128 in variable varI8a ");
  varI8b = 127;
  Serial.println("Write 127 in variable varI8b ");
  delay(500);

  // The mergeUint8ToUint16 function combines two 8-bit unsigned variables into one 16-bit unsigned variable.
  varMergeInt8ToUInt16 = DataConversion::mergeInt8ToUint16(varI8a, varI8b);
  Serial.println("Value merge varI8a + varI8b ");
  delay(500);
  // Write value to Modbus variable
  mb.Hreg(NR_MERGEINT8TOUINT16, varMergeInt8ToUInt16);
  Serial.println("Writing value in modbus variable ");
  delay(500);

  /* Part that works with 2 unsigned 8-bit values*/
  mb.Hreg(NR_MERGEUINT8TOUINT16, varMergeUint8ToUint16);
  // Print the value of the register
  Serial.println("Register 2 = " + String(varMergeUint8ToUint16, BIN));
  // Serial.println(varMergeUint8ToUint16);
  delay(500);
  // Assign values to variables and merge them
  varUi8a = 128;
  Serial.println("Write 128 in variable varUi8a ");
  varUi8b = 255;
  Serial.println("Write 255 in variable varUi8b ");
  delay(500);

  // The mergeUint8ToUint16 function combines two 8-bit unsigned variables into one 16-bit unsigned variable.
  varMergeUint8ToUint16 = DataConversion::mergeUint8ToUint16(varUi8a, varUi8b);
  Serial.println("Value merge varUi8a + varUi8b ");
  delay(500);
  // Write value to Modbus variable
  mb.Hreg(NR_MERGEUINT8TOUINT16, varMergeUint8ToUint16);
  Serial.println("Writing value in modbus variable ");
  delay(500);

  /* Part that works with signed 32-bit value*/
  mb.Hreg(NR_VALUEI32PART1, varValueI32Part1);
  mb.Hreg(NR_VALUEI32PART2, varValueI32Part2);
  // Print the value of the register
  Serial.println("Register 3 = " + String(varValueI32Part1, DEC));
  // Serial.println(varValueI32Part1);
  Serial.println("Register 4 = " + String(varValueI32Part2, DEC));
  // Serial.println(varLowWord);
  delay(500);
  // Assign values to variables and merge them
  varMergeUInt16ToInt32 = -2147483648;
  Serial.println("Write -2147483648 in variable varMergeUInt16ToInt32 ");

  // Splits a 32-bit integer into two 16-bit words.
  DataConversion::splitInt32ToUint16(varMergeUInt16ToInt32, varValueI32Part1, varValueI32Part2);
  delay(500);
  // Write value to Modbus variable
  mb.Hreg(NR_VALUEI32PART1, varValueI32Part1);
  mb.Hreg(NR_VALUEI32PART2, varValueI32Part2);
  Serial.println("Writing value in modbus variable ");
  delay(500);

  /* Part that works with unsigned 32-bit value*/
  mb.Hreg(NR_VALUEUI32PART1, varValueUi32Part1);
  mb.Hreg(NR_VALUEUI32PART2, varValueUi32Part2);
  // Print the value of the register
  Serial.println("Register 5 = " + String(varValueUi32Part1, DEC));
  // Serial.println(varHighValue);
  Serial.println("Register 6 = " + String(varValueUi32Part2, DEC));
  // Serial.println(varLowValue);
  delay(500);
  // Assign values to variables and merge them
  varMergeUInt16ToUInt32 = 4294967295;
  Serial.println("Write 4294967295 in variable varMergeUInt16ToInt32 ");

  // Separates a uint32_t value into two uint16_t values.
  DataConversion::splitUint32ToUint16(varMergeUInt16ToUInt32, varValueUi32Part1, varValueUi32Part2);
  delay(500);
  // Write value to Modbus variable
  mb.Hreg(NR_VALUEUI32PART1, varValueUi32Part1);
  mb.Hreg(NR_VALUEUI32PART2, varValueUi32Part2);
  Serial.println("Writing value in modbus variable ");
  delay(500);

  // Part that works with float 32-bit value
  mb.Hreg(NR_FLOATPART1, varFloatPart1);
  mb.Hreg(NR_FLOATPART2, varFloatPart2);
  // Print the value of the register
  Serial.println("Register 7 = " + String(varFloatPart1, DEC));
  Serial.println("Register 8 = " + String(varFloatPart2, DEC));
  delay(500);
  // Assign values to variables and merge them
  varMergeUInt16ToFloat32 = 31.12345;
  Serial.println("Write 31.12345 in variable varMergeUInt16ToFloat32 ");
  // Separates a float value into two uint16_t values.
  DataConversion::splitFloat32ToUint16(varMergeUInt16ToFloat32, varFloatPart1, varFloatPart2);
  delay(500);
  // Write value to Modbus variable
  mb.Hreg(NR_FLOATPART1, varFloatPart1);
  mb.Hreg(NR_FLOATPART2, varFloatPart2);
  Serial.println("Writing value in modbus variable ");
  delay(500);

  // Part that works with int 64-bit value
  mb.Hreg(NR_VALUEI64PART1, varValueI64Part1);
  mb.Hreg(NR_VALUEI64PART2, varValueI64Part2);
  mb.Hreg(NR_VALUEI64PART3, varValueI64Part3);
  mb.Hreg(NR_VALUEI64PART4, varValueI64Part4);
  // Print the value of the register
  Serial.println("Register 09 = " + String(varValueI64Part1, DEC));
  Serial.println("Register 10 = " + String(varValueI64Part2, DEC));
  Serial.println("Register 11 = " + String(varValueI64Part3, DEC));
  Serial.println("Register 12 = " + String(varValueI64Part4, DEC));
  delay(500);
  // Assign values to variables and merge them
  varMergeUInt16ToInt64 = -4294967295;
  Serial.println("Write -4294967295 in variable varMergeUInt16ToInt64 ");
  // Separates a int64 value into four uint16_t values.
  DataConversion::splitInt64ToUint16(varMergeUInt16ToInt64, varValueI64Part1, varValueI64Part2, varValueI64Part3, varValueI64Part4);
  delay(500);
  // Write value to Modbus variable
  mb.Hreg(NR_VALUEI64PART1, varValueI64Part1);
  mb.Hreg(NR_VALUEI64PART2, varValueI64Part2);
  mb.Hreg(NR_VALUEI64PART3, varValueI64Part3);
  mb.Hreg(NR_VALUEI64PART4, varValueI64Part4);
  Serial.println("Writing value in modbus variable ");
  delay(500);

  // Part that works with uint 64-bit value
  mb.Hreg(NR_VALUEUI64PART1, varValueUi64Part1);
  mb.Hreg(NR_VALUEUI64PART2, varValueUi64Part2);
  mb.Hreg(NR_VALUEUI64PART3, varValueUi64Part3);
  mb.Hreg(NR_VALUEUI64PART4, varValueUi64Part4);
  // Print the value of the register
  Serial.println("Register 13 = " + String(varValueUi64Part1, DEC));
  Serial.println("Register 14 = " + String(varValueUi64Part2, DEC));
  Serial.println("Register 15 = " + String(varValueUi64Part3, DEC));
  Serial.println("Register 16 = " + String(varValueUi64Part4, DEC));
  delay(500);
  // Assign values to variables and merge them
  varMergeUInt16ToUInt64 = 84294967295;
  Serial.println("Write 84294967295 in variable varMergeUInt16ToUInt64 ");
  // Separates a int64 value into four uint16_t values.
  DataConversion::splitUint64ToUint16(varMergeUInt16ToUInt64, varValueUi64Part1, varValueUi64Part2, varValueUi64Part3, varValueUi64Part4);
  delay(500);
  // Write value to Modbus variable
  mb.Hreg(NR_VALUEUI64PART1, varValueUi64Part1);
  mb.Hreg(NR_VALUEUI64PART2, varValueUi64Part2);
  mb.Hreg(NR_VALUEUI64PART3, varValueUi64Part3);
  mb.Hreg(NR_VALUEUI64PART4, varValueUi64Part4);
  Serial.println("Writing value in modbus variable ");
  delay(500);
  //////////////////////////////////////////////////////////////////////////////////
  // Part that works with double 64-bit value
  mb.Hreg(NR_VALUEDBPART1, varValueDbPart1);
  mb.Hreg(NR_VALUEDBPART2, varValueDbPart2);
  mb.Hreg(NR_VALUEDBPART3, varValueDbPart3);
  mb.Hreg(NR_VALUEDBPART4, varValueDbPart4);
  // Print the value of the register
  Serial.println("Register 17 = " + String(varValueDbPart1, DEC));
  Serial.println("Register 18 = " + String(varValueDbPart2, DEC));
  Serial.println("Register 19 = " + String(varValueDbPart3, DEC));
  Serial.println("Register 20 = " + String(varValueDbPart4, DEC));
  delay(500);
  // Assign values to variables and merge them
  varMergeUInt16ToDouble = -12345.0123456789;
  Serial.println("Write -12345.023456789 in variable varMergeUInt16ToDouble ");
  // Separates a int64 value into four uint16_t values.
  DataConversion::splitDoubleToUint16(varMergeUInt16ToDouble, varValueDbPart1, varValueDbPart2, varValueDbPart3, varValueDbPart4);
  delay(500);
  // Write value to Modbus variable
  mb.Hreg(NR_VALUEDBPART1, varValueDbPart1);
  mb.Hreg(NR_VALUEDBPART2, varValueDbPart2);
  mb.Hreg(NR_VALUEDBPART3, varValueDbPart3);
  mb.Hreg(NR_VALUEDBPART4, varValueDbPart4);
  Serial.println("Writing value in modbus variable ");
  delay(500);

  // Perform ModbusIP task
  mb.task();
  // Yield to other tasks (if any)
  yield();

  // Print the value of the register.
  Serial.println("Read Register 00 BIN = " + String(state16bitRegister, BIN));
  Serial.println("Read Register 01 = " + String(mb.Hreg(NR_MERGEINT8TOUINT16), DEC));
  Serial.println("Read Register 02 = " + String(mb.Hreg(NR_MERGEUINT8TOUINT16), DEC));
  Serial.println("Read Register 03 = " + String(mb.Hreg(NR_VALUEI32PART1), DEC));
  Serial.println("Read Register 04 = " + String(mb.Hreg(NR_VALUEI32PART2), DEC));
  Serial.println("Read Register 05 = " + String(mb.Hreg(NR_VALUEUI32PART1), DEC));
  Serial.println("Read Register 06 = " + String(mb.Hreg(NR_VALUEUI32PART2), DEC));
  Serial.println("Read Register 07 = " + String(mb.Hreg(NR_FLOATPART1), DEC));
  Serial.println("Read Register 08 = " + String(mb.Hreg(NR_FLOATPART2), DEC));
  Serial.println("Read Register 09 = " + String(mb.Hreg(NR_VALUEI64PART1), DEC));
  Serial.println("Read Register 10 = " + String(mb.Hreg(NR_VALUEI64PART2), DEC));
  Serial.println("Read Register 11 = " + String(mb.Hreg(NR_VALUEI64PART3), DEC));
  Serial.println("Read Register 12 = " + String(mb.Hreg(NR_VALUEI64PART4), DEC));
  Serial.println("Read Register 13 = " + String(mb.Hreg(NR_VALUEUI64PART1), DEC));
  Serial.println("Read Register 14 = " + String(mb.Hreg(NR_VALUEUI64PART2), DEC));
  Serial.println("Read Register 15 = " + String(mb.Hreg(NR_VALUEUI64PART3), DEC));
  Serial.println("Read Register 16 = " + String(mb.Hreg(NR_VALUEUI64PART4), DEC));
  Serial.println("Read Register 17 = " + String(mb.Hreg(NR_VALUEDBPART1), DEC));
  Serial.println("Read Register 18 = " + String(mb.Hreg(NR_VALUEDBPART2), DEC));
  Serial.println("Read Register 19 = " + String(mb.Hreg(NR_VALUEDBPART3), DEC));
  Serial.println("Read Register 20 = " + String(mb.Hreg(NR_VALUEDBPART4), DEC));
  delay(5000);
}

void loop()
{
  // Read the value from a specific holding register
  // Parameters: register number
  // Returns: value read from the register
  // Read the value of register 0
  state16bitRegister = mb.Hreg(NR_STATE_16BIT_REGISTER);
  // Read the value of register 1
  varMergeInt8ToUInt16 = mb.Hreg(NR_MERGEINT8TOUINT16);
  // Read the value of register 2
  varMergeUint8ToUint16 = mb.Hreg(NR_MERGEUINT8TOUINT16);
  // Read the value of register 3
  varValueI32Part1 = mb.Hreg(NR_VALUEI32PART1);
  // Read the value of register 4
  varValueI32Part2 = mb.Hreg(NR_VALUEI32PART2);
  // Read the value of register 5
  varValueUi32Part1 = mb.Hreg(NR_VALUEUI32PART1);
  // Read the value of register 6
  varValueUi32Part2 = mb.Hreg(NR_VALUEUI32PART2);
  // Read the value of register 7
  varFloatPart1 = mb.Hreg(NR_FLOATPART1);
  // Read the value of register 8
  varFloatPart2 = mb.Hreg(NR_FLOATPART2);
  // Read the value of register 9
  varValueI64Part1 = mb.Hreg(NR_VALUEI64PART1);
  // Read the value of register 10
  varValueI64Part2 = mb.Hreg(NR_VALUEI64PART2);
  // Read the value of register 11
  varValueI64Part3 = mb.Hreg(NR_VALUEI64PART3);
  // Read the value of register 12
  varValueI64Part4 = mb.Hreg(NR_VALUEI64PART4);
  // Read the value of register 13
  varValueUi64Part1 = mb.Hreg(NR_VALUEUI64PART1);
  // Read the value of register 14
  varValueUi64Part2 = mb.Hreg(NR_VALUEUI64PART2);
  // Read the value of register 15
  varValueUi64Part3 = mb.Hreg(NR_VALUEUI64PART3);
  // Read the value of register 16
  varValueUi64Part4 = mb.Hreg(NR_VALUEUI64PART4);
  // Read the value of register 17
  varValueDbPart1 = mb.Hreg(NR_VALUEDBPART1);
  // Read the value of register 18
  varValueDbPart2 = mb.Hreg(NR_VALUEDBPART2);
  // Read the value of register 19
  varValueDbPart3 = mb.Hreg(NR_VALUEDBPART3);
  // Read the value of register 20
  varValueDbPart4 = mb.Hreg(NR_VALUEDBPART4);

  // Perform ModbusIP task
  mb.task();
  // Yield to other tasks (if any)
  yield();

  // Read individual bits from the state16bitRegister and store them in corresponding variables using DataConversion::readBit()
  bitValue00 = DataConversion::readBit(state16bitRegister, 0);  // Read bit 0
  bitValue01 = DataConversion::readBit(state16bitRegister, 1);  // Read bit 1
  bitValue02 = DataConversion::readBit(state16bitRegister, 2);  // Read bit 2
  bitValue03 = DataConversion::readBit(state16bitRegister, 3);  // Read bit 3
  bitValue04 = DataConversion::readBit(state16bitRegister, 4);  // Read bit 4
  bitValue05 = DataConversion::readBit(state16bitRegister, 5);  // Read bit 5
  bitValue06 = DataConversion::readBit(state16bitRegister, 6);  // Read bit 6
  bitValue07 = DataConversion::readBit(state16bitRegister, 7);  // Read bit 7
  bitValue08 = DataConversion::readBit(state16bitRegister, 8);  // Read bit 8
  bitValue09 = DataConversion::readBit(state16bitRegister, 9);  // Read bit 9
  bitValue10 = DataConversion::readBit(state16bitRegister, 10); // Read bit 10
  bitValue11 = DataConversion::readBit(state16bitRegister, 11); // Read bit 11
  bitValue12 = DataConversion::readBit(state16bitRegister, 12); // Read bit 12
  bitValue13 = DataConversion::readBit(state16bitRegister, 13); // Read bit 13
  bitValue14 = DataConversion::readBit(state16bitRegister, 14); // Read bit 14
  bitValue15 = DataConversion::readBit(state16bitRegister, 15); // Read bit 15

  // The splitUint16ToInt8 function divides a 16-bit unsigned variable into two 8-bit signed variables.
  DataConversion::splitUint16ToInt8(varMergeInt8ToUInt16, varI8a, varI8b);
  // The splitUint16ToUint8 function divides a 16-bit unsigned variable into two 8-bit unsigned variables.
  DataConversion::splitUint16ToUint8(varMergeUint8ToUint16, varUi8a, varUi8b);
  // Combines a high word and a low word into a 32-bit integer.
  varMergeUInt16ToInt32 = DataConversion::mergeUint16ToInt32(varValueI32Part1, varValueI32Part2);
  // Combines a high word and a low word into a 32-bit unsigned integer.
  varMergeUInt16ToUInt32 = DataConversion::mergeUint16ToUint32(varValueUi32Part1, varValueUi32Part2);
  // Combines a high word and a low word into a 32-bit float.
  varMergeUInt16ToFloat32 = DataConversion::mergeUint16ToFloat32(varFloatPart1, varFloatPart2);
  // Combines four word into a 64-bit integer.
  varMergeUInt16ToInt64 = DataConversion::mergeUint16ToInt64(varValueI64Part1, varValueI64Part2, varValueI64Part3, varValueI64Part4);
  // Combines four word into a 64-bit unsigned integer.
  varMergeUInt16ToUInt64 = DataConversion::mergeUint16ToUint64(varValueUi64Part1, varValueUi64Part2, varValueUi64Part3, varValueUi64Part4);
  // Combines four word into a 64-bit double.
  varMergeUInt16ToDouble = DataConversion::mergeUint16ToDouble(varValueDbPart1, varValueDbPart2, varValueDbPart3, varValueDbPart4);

  /* *Print the values of the variables* */
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if 1 second has elapsed
  if (currentMillis - previousMillis >= 1000)
  {
    // Update the previous time
    previousMillis = currentMillis;

    // Print the values of the variables
    // Print the values of individual bits
    Serial.println("Bit values:");
    Serial.println("bitValue00: " + String(bitValue00, BIN));
    Serial.println("bitValue01: " + String(bitValue01, BIN));
    Serial.println("bitValue02: " + String(bitValue02, BIN));
    Serial.println("bitValue03: " + String(bitValue03, BIN));
    Serial.println("bitValue04: " + String(bitValue04, BIN));
    Serial.println("bitValue05: " + String(bitValue05, BIN));
    Serial.println("bitValue06: " + String(bitValue06, BIN));
    Serial.println("bitValue07: " + String(bitValue07, BIN));
    Serial.println("bitValue08: " + String(bitValue08, BIN));
    Serial.println("bitValue09: " + String(bitValue09, BIN));
    Serial.println("bitValue10: " + String(bitValue10, BIN));
    Serial.println("bitValue11: " + String(bitValue11, BIN));
    Serial.println("bitValue12: " + String(bitValue12, BIN));
    Serial.println("bitValue13: " + String(bitValue13, BIN));
    Serial.println("bitValue14: " + String(bitValue14, BIN));
    Serial.println("bitValue15: " + String(bitValue15, BIN));
    // Print the binary value of the state16bitRegister
    Serial.println("Register 0 BIN= " + String(state16bitRegister, BIN));
    //  Print the decimal value of the state16bitRegister
    Serial.println("Register 0 DEC= " + String(state16bitRegister, DEC));

    // Print the values of the variables
    Serial.println("Register 1 Value = " + String(varMergeInt8ToUInt16, DEC));
    Serial.println("Register 1 varI8a = " + String(varI8a, DEC));
    Serial.println("Register 1 varI8b = " + String(varI8b, DEC));

    // Print the values of the variables
    Serial.println("Register 2 Value = " + String(varMergeUint8ToUint16, DEC));
    Serial.println("Register 2 varUi8a = " + String(varUi8a, DEC));
    Serial.println("Register 2 varUi8b = " + String(varUi8b, DEC));

    // Print the values of the variables Int32
    Serial.println("Register 3 varHighWord = " + String(varValueI32Part1, DEC));
    Serial.println("Register 4 varLowWord = " + String(varValueI32Part2, DEC));
    Serial.println("Register 3+4 Value = " + String(varMergeUInt16ToInt32, DEC));

    // Print the values of the variables Uint32
    Serial.println("Register 5 varHighWord = " + String(varValueUi32Part1, DEC));
    Serial.println("Register 6 varLowWord = " + String(varValueUi32Part2, DEC));
    Serial.println("Register 5+6 Value = " + String(varMergeUInt16ToUInt32, DEC));
    // Print the values of the variables float 32
    Serial.println("Register 7+8 Value float32 = " + String(varMergeUInt16ToFloat32, 5));
    // Print the values of the variables int64
    Serial.println("Register 9+10+11+12 Value int64 = " + String(varMergeUInt16ToInt64, DEC));
    // Print the values of the variables uint64
    Serial.println("Register 13+14+15+16 Value int64 = " + String(varMergeUInt16ToUInt64, DEC));
    // Print the values of the variables double
    Serial.println("Register 17+18+19+20 Value int64 = " + String(varMergeUInt16ToDouble, 10));
  }
}
