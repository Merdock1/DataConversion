

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
These write and read bit functions in variables are redundant.
Since within the arduino framework they exist.
bitRead() to read a specific bit from a variable.
https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/bitread/
bitWrite() to write a specific bit from a variable.
https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/bitwrite/
*/
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else // ESP32
#include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>
#include <DataConversion.h>

// Create an instance of the DataConversion class
DataConversion dtConv;

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
  dtConv.splitDoubleToUint16(varMergeUInt16ToDouble, varValueDbPart1, varValueDbPart2, varValueDbPart3, varValueDbPart4);
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

  // Combines four word into a 64-bit double.
  varMergeUInt16ToDouble = dtConv.mergeUint16ToDouble(varValueDbPart1, varValueDbPart2, varValueDbPart3, varValueDbPart4);

  /* *Print the values of the variables* */
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if 1 second has elapsed
  if (currentMillis - previousMillis >= 1000)
  {
    // Update the previous time
    previousMillis = currentMillis;

    // Print the values of the variables
    // Print the values of the variables double
    Serial.println("Register 17+18+19+20 Value int64 = " + String(varMergeUInt16ToDouble, 10));
  }
}
