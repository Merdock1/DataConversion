

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
  NR_TOTAL_REGISTERS       // Total number of registers.
};

// Global variables for 2 signed 8-bit to unsigned 16-bit.
int8_t varI8a = 0;                 // 8-bit signed variable initialized to 0.
int8_t varI8b = 0;                 // 8-bit signed variable initialized to 0.
uint16_t varMergeInt8ToUInt16 = 0; // 16-bit unsigned variable initialized to 0.

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


  // Perform ModbusIP task
  mb.task();
  // Yield to other tasks (if any)
  yield();

  // Print the value of the register.
  Serial.println("Read Register 01 = " + String(mb.Hreg(NR_MERGEINT8TOUINT16), DEC));
  
  delay(5000);
}

void loop()
{
  // Read the value from a specific holding register
  // Parameters: register number
  // Returns: value read from the register
  // Read the value of register 1
  varMergeInt8ToUInt16 = mb.Hreg(NR_MERGEINT8TOUINT16);
  

  // Perform ModbusIP task
  mb.task();
  // Yield to other tasks (if any)
  yield();

  
  // The splitUint16ToInt8 function divides a 16-bit unsigned variable into two 8-bit signed variables.
  DataConversion::splitUint16ToInt8(varMergeInt8ToUInt16, varI8a, varI8b);
  
  /* *Print the values of the variables* */
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if 1 second has elapsed
  if (currentMillis - previousMillis >= 1000)
  {
    // Update the previous time
    previousMillis = currentMillis;

    // Print the values of the variables
    // Print the values of the variables
    Serial.println("Register 1 Value = " + String(varMergeInt8ToUInt16, DEC));
    Serial.println("Register 1 varI8a = " + String(varI8a, DEC));
    Serial.println("Register 1 varI8b = " + String(varI8b, DEC));
  }
}
