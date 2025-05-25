

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
  NR_TOTAL_REGISTERS       // Total number of registers.
};

// Global variables for 1 unsigned 32-bit to 2 unsigned 16-bit.
uint16_t varValueUi32Part1 = 0;      // 16-bit unsigned variable initialized to 0.
uint16_t varValueUi32Part2 = 0;      // 16-bit unsigned variable initialized to 0.
uint32_t varMergeUInt16ToUInt32 = 0; // 32-bit unsigned variable initialized to 0.

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

  // Perform ModbusIP task
  mb.task();
  // Yield to other tasks (if any)
  yield();

  // Print the value of the register.
  Serial.println("Read Register 05 = " + String(mb.Hreg(NR_VALUEUI32PART1), DEC));
  Serial.println("Read Register 06 = " + String(mb.Hreg(NR_VALUEUI32PART2), DEC));
  
  delay(5000);
}

void loop()
{
  // Read the value from a specific holding register
  // Parameters: register number
  // Returns: value read from the register
  // Read the value of register 5
  varValueUi32Part1 = mb.Hreg(NR_VALUEUI32PART1);
  // Read the value of register 6
  varValueUi32Part2 = mb.Hreg(NR_VALUEUI32PART2);
  

  // Perform ModbusIP task
  mb.task();
  // Yield to other tasks (if any)
  yield();

  // Combines a high word and a low word into a 32-bit unsigned integer.
  varMergeUInt16ToUInt32 = DataConversion::mergeUint16ToUint32(varValueUi32Part1, varValueUi32Part2);
  
  /* *Print the values of the variables* */
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if 1 second has elapsed
  if (currentMillis - previousMillis >= 1000)
  {
    // Update the previous time
    previousMillis = currentMillis;

    // Print the values of the variables
    
    // Print the values of the variables Uint32
    Serial.println("Register 5 varHighWord = " + String(varValueUi32Part1, DEC));
    Serial.println("Register 6 varLowWord = " + String(varValueUi32Part2, DEC));
    Serial.println("Register 5+6 Value = " + String(varMergeUInt16ToUInt32, DEC));
    
  }
}
