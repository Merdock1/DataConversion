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
#include "ToolSplitMerge.h"
/*
The enum function is used to create an enumerated data type.
In this case, it is creating the MbipRegister enumeration type.
The enumeration defines a set of named constants that represent possible values.
Each constant is automatically assigned an integer value (0, 1, 2, etc.).
The constants defined in this enumeration represent different registers used in the program.
These registers are used to reference specific memory addresses.
*/
enum MbipRegister
{
    NR_ZERO,              // Register 0
    NR_JOIN2INT8,         // Register 1 to join two signed 8-bit values
    NR_JOIN2UINT8,        // Register 2 to join two unsigned 8-bit values
    NR_IP_TOTAL_REGISTER, // Total IP register
};

// Global variables
uint8_t varUi8a = 0;        // 8-bit unsigned variable initialized to 0
uint8_t varUi8b = 0;        // 8-bit unsigned variable initialized to 0
uint16_t varJoin2Uint8 = 0; // 16-bit unsigned variable initialized to 0

// Variable to store the previous time
static unsigned long previousMillis = 0;

// ModbusIP object
ModbusIP mb;

void setup()
{
    // Start serial communication
    Serial.begin(115200);

    // Connect to WiFi network
    // WiFi.begin("Fernando", "123456789");
    WiFi.begin("Curufinwe", "Tengoquecortarelpastoenel2022.");
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

    // Set up ModbusIP server
    mb.server();
    // Add the holding registers (Initial register, Initial value, number of registers)
    mb.addHreg(0, 0, NR_IP_TOTAL_REGISTER);
    // Writing holding registers. (Number register, value)
    mb.Hreg(NR_JOIN2UINT8, varJoin2Uint8);

    // Print the value of the register
    Serial.print("Register 1 = ");
    Serial.println(varJoin2Uint8);
    delay(1500);

    // Assign values to variables and join them
    varUi8a = 122;
    Serial.println("Write 122 in variable varUi8a ");
    varUi8b = 255;
    Serial.println("Write 255 in variable varUi8b ");
    delay(1000);
    /*
    The joinUint8 function combines two 8-bit unsigned variables into one 16-bit unsigned variable.
    It receives two parameters:
      - varUi8a: The first 8-bit unsigned variable to be combined.
      - varUi8b: The second 8-bit unsigned variable to be combined.
    It returns the result of the combination, which is a 16-bit unsigned variable.
    */
    varJoin2Uint8 = joinUint8(varUi8a, varUi8b);

    Serial.println("Value join varUi8a + varUi8b ");
    delay(1000);

    // Write value to Modbus variable
    mb.Hreg(NR_JOIN2UINT8, varJoin2Uint8);
    Serial.println("Writing value in modbus variable ");
    delay(1000);

    // Execute Modbus tasks
    mb.task();
    yield();

    // Print the value of the register
    Serial.print("Read Register 2 = ");
    Serial.println(mb.Hreg(NR_JOIN2UINT8));
    delay(10000);
}

void loop()
{
    // Read the value of register 2 and split it
    varJoin2Uint8 = mb.Hreg(NR_JOIN2UINT8);
    // Execute Modbus tasks
    mb.task();
    yield();

    /*
    The splitUint16Ui8 function divides a 16-bit unsigned variable into two 8-bit unsigned variables.
    It receives three parameters:
      - varJoin2Uint8: The 16-bit unsigned variable to be split.
      - varUi8a: The first 8-bit unsigned variable where the high part of varJoin2Uint8 will be stored.
      - varUi8b: The second 8-bit unsigned variable where the low part of varJoin2Uint8 will be stored.
    The function separates the upper 8 bits of varJoin2Uint8 and stores them in varUi8a,
    while the lower 8 bits are stored in varUi8b.
    */
    splitUint16Ui8(varJoin2Uint8, varUi8a, varUi8b);

    /* *Print the values of the variables* */

    // Get the current time
    unsigned long currentMillis = millis();

    // Check if 1 second has elapsed
    if (currentMillis - previousMillis >= 1000)
    {
        // Update the previous time
        previousMillis = currentMillis;

        // Print the values of the variables
        Serial.print("Register 2 Value = ");
        Serial.println(varJoin2Uint8);
        Serial.print("Register 2 varUi8a = ");
        Serial.println(varUi8a);
        Serial.print("Register 2 varUi8b = ");
        Serial.println(varUi8b);
    }
}
