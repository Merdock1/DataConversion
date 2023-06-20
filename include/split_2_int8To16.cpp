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

// Enum to name the register numbers
enum MbipRegister
{
    NR_ZERO,
    NR_JOIN2INT8,
    NR_JOIN2UINT8,
    NR_IP_TOTAL_REGISTER,
};

// Global variables
int8_t varUi8a = 0;     // 8-bit signed variable initialized to 0
int8_t varUi8b = 0;         // 8-bit signed variable initialized to 0
uint16_t varJoin2uint8 = 0; // 16-bit unsigned variable initialized to 0

// ModbusIP object
ModbusIP mb;

void setup()
{
    // Start serial communication
    Serial.begin(115200);

    // Connect to WiFi network
    WiFi.begin("Fernando", "12345678");
    //WiFi.begin("Curufinwe", "Tengoquecortarelpastoenel2022.");
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
    mb.Hreg(NR_JOIN2UINT8, varJoin2uint8);

    // Print the value of the register
    Serial.print("Register 1 = ");
    Serial.println(varJoin2uint8);
    delay(1500);

    // Assign values to variables and join them
    varUi8a = 122;
    Serial.println("Write -120 in variable varI8a ");
    varUi8b = 255;
    Serial.println("Write 120 in variable varI8b ");
    delay(1000);
    varJoin2uint8 = joinUint8(varUi8a, varUi8b);
    Serial.println("Value join varI8a + varI8b ");
    delay(1000);

    // Write value to Modbus variable
    mb.Hreg(NR_JOIN2UINT8, varJoin2uint8);
    Serial.println("Writing value in modbus variable ");
    delay(1000);

    // Execute Modbus tasks
    mb.task();
    yield();

    // Print the value of the register
    Serial.print("Register 1 = ");
    Serial.println(mb.Hreg(NR_JOIN2UINT8));
    delay(10000);
}

void loop()
{
    // Read the value of the register and split it
    varJoin2uint8 = mb.Hreg(NR_JOIN2UINT8);
    mb.task();
    yield();
    splitUint16I8(varJoin2uint8, varUi8a, varUi8b);

    // Print the values of the variables
    Serial.print("Register 1 = ");
    Serial.println(varJoin2uint8);
    Serial.print("Register 1 varI8a = ");
    Serial.println(varUi8a);
    Serial.print("Register 1 varI8b = ");
    Serial.println(varUi8b);
}
