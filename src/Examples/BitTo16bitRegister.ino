

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
  state16bitRegister = bitWrite(state16bitRegister, 7, HIGH);
  Serial.println("Write 1 in bit 7 ");
  delay(500);
  state16bitRegister = bitWrite(state16bitRegister, 14, HIGH);
  Serial.println("Write 1 in bit 14 ");
  delay(500);
  mb.Hreg(NR_STATE_16BIT_REGISTER, state16bitRegister);
  Serial.println("Writing value in modbus variable ");
  delay(500);


  // Perform ModbusIP task
  mb.task();
  // Yield to other tasks (if any)
  yield();

  // Print the value of the register.
  Serial.println("Read Register 00 BIN = " + String(state16bitRegister, BIN));
  
  delay(5000);
}

void loop()
{
  // Read the value from a specific holding register
  // Parameters: register number
  // Returns: value read from the register
  // Read the value of register 0
  state16bitRegister = mb.Hreg(NR_STATE_16BIT_REGISTER);
  

  // Perform ModbusIP task
  mb.task();
  // Yield to other tasks (if any)
  yield();

  // Read individual bits from the state16bitRegister and store them in corresponding variables
  bitValue00 = bitRead(state16bitRegister, 0);  // Read bit 0 from state16bitRegister and assign its value to bitValue00
  bitValue01 = bitRead(state16bitRegister, 1);  // Read bit 1 from state16bitRegister and assign its value to bitValue01
  bitValue02 = bitRead(state16bitRegister, 2);  // Read bit 2 from state16bitRegister and assign its value to bitValue02
  bitValue03 = bitRead(state16bitRegister, 3);  // Read bit 3 from state16bitRegister and assign its value to bitValue03
  bitValue04 = bitRead(state16bitRegister, 4);  // Read bit 4 from state16bitRegister and assign its value to bitValue04
  bitValue05 = bitRead(state16bitRegister, 5);  // Read bit 5 from state16bitRegister and assign its value to bitValue05
  bitValue06 = bitRead(state16bitRegister, 6);  // Read bit 6 from state16bitRegister and assign its value to bitValue06
  bitValue07 = bitRead(state16bitRegister, 7);  // Read bit 7 from state16bitRegister and assign its value to bitValue07
  bitValue08 = bitRead(state16bitRegister, 8);  // Read bit 8 from state16bitRegister and assign its value to bitValue08
  bitValue09 = bitRead(state16bitRegister, 9);  // Read bit 9 from state16bitRegister and assign its value to bitValue09
  bitValue10 = bitRead(state16bitRegister, 10); // Read bit 10 from state16bitRegister and assign its value to bitValue10
  bitValue11 = bitRead(state16bitRegister, 11); // Read bit 11 from state16bitRegister and assign its value to bitValue11
  bitValue12 = bitRead(state16bitRegister, 12); // Read bit 12 from state16bitRegister and assign its value to bitValue12
  bitValue13 = bitRead(state16bitRegister, 13); // Read bit 13 from state16bitRegister and assign its value to bitValue13
  bitValue14 = bitRead(state16bitRegister, 14); // Read bit 14 from state16bitRegister and assign its value to bitValue14
  bitValue15 = bitRead(state16bitRegister, 15); // Read bit 15 from state16bitRegister and assign its value to bitValue15

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

  }
}
