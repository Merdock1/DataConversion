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

//    float min =   -1.175494
float min_Float =   -1.175494;
//    float max =    3.40282346638528859811704183484516925440
float max_Float =    3.402823;

//     double min = -2.225073858507201
double min_Double = -2.225073858507201;
//     double max = 1.79769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368
double max_Double = 1.797693134862315;

//      long Double min = -22.2250738585072014
long double min_LDouble = -22.2250738585072014;
//      long Double max =  11.7976931348623157
long double max_LDouble =  11.7976931348623157;

// bit to bit Variable
uint16_t bitTobit = 0;





void setup()
{
  Serial.begin(115200);

  WiFi.begin("Curufinwe", "Tengoquecortarelpastoenel2022.");

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

  Serial.print("   Type Data    = ");
  Serial.print("Size of Data = ");
  Serial.println("    Max_Value     = ");

  Serial.print("INT8        MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(int8_t));
  Serial.print("       ");
  Serial.println(INT8_MIN);

  Serial.print("INT8        MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(int8_t));
  Serial.print("        ");
  Serial.println(INT8_MAX);

  Serial.print("UINT8       MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(uint8_t));
  Serial.print("        ");
  Serial.println("0");

  Serial.print("UINT8       MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(uint8_t));
  Serial.print("        ");
  Serial.println(UINT8_MAX);

  Serial.print("bool        MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(bool));
  Serial.print("        ");
  Serial.println("0");

  Serial.print("bool        MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(bool));
  Serial.print("        ");
  Serial.println(UINT8_MAX);

  Serial.print("CHAR        MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(char));
  Serial.print("        ");
  Serial.println(CHAR_MIN);

  Serial.print("UCHAR       MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(char));
  Serial.print("        ");
  Serial.println(UCHAR_MAX);

  Serial.print("INT16       MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(int16_t));
  Serial.print("       ");
  Serial.println(INT16_MIN);

  Serial.print("INT16       MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(int16_t));
  Serial.print("        ");
  Serial.println(INT16_MAX);

  Serial.print("UINT16      MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(uint16_t));
  Serial.print("        ");
  Serial.println("0");

  Serial.print("UINT16      MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(uint16_t));
  Serial.print("        ");
  Serial.println(UINT16_MAX);

  Serial.print("INT32       MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(int32_t));
  Serial.print("       ");
  Serial.println(INT32_MIN);

  Serial.print("INT32       MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(int32_t));
  Serial.print("        ");
  Serial.println(INT32_MAX);


  Serial.print("INT         MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(int));
  Serial.print("       ");
  Serial.println(INT_MIN);

  Serial.print("INT         MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(int));
  Serial.print("        ");
  Serial.println(INT_MAX);

  Serial.print("Long        MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(long));
  Serial.print("       ");
  Serial.println(LONG_MIN);

  Serial.print("Long        MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(long));
  Serial.print("        ");
  Serial.println(LONG_MAX);

  Serial.print("UINT        MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(uint));
  Serial.print("        ");
  Serial.println("0");


  Serial.print("UINT        MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(uint));
  Serial.print("        ");
  Serial.println(UINT_MAX);

  Serial.print("UINT32      MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(uint32_t));
  Serial.print("        ");
  Serial.println("0");

  Serial.print("UINT32      MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(uint32_t));
  Serial.print("        ");
  Serial.println(UINT32_MAX);

  Serial.print("Ulong       MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(ulong));
  Serial.print("        ");
  Serial.println("0");

  Serial.print("Ulong       MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(ulong));
  Serial.print("        ");
  Serial.println(ULONG_MAX);

  Serial.print("INT64       MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(int64_t));
  Serial.print("       ");
  Serial.println(INT64_MIN);

  Serial.print("INT64       MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(int64_t));
  Serial.print("        ");
  Serial.println(INT64_MAX);

  Serial.print("long Long   MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(long long));
  Serial.print("       ");
  Serial.println(__LONG_LONG_MAX__ * -1);

  Serial.print("long Long   MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(long long));
  Serial.print("        ");
  Serial.println(__LONG_LONG_MAX__);

  Serial.print("UINT64      MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(uint64_t));
  Serial.print("        ");
  Serial.println("0");

  Serial.print("UINT64      MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(uint64_t));
  Serial.print("        ");
  Serial.println(UINT64_MAX);

  Serial.print("Float       MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(float));
  Serial.print("       ");
  Serial.println(min_Float, 6);

  Serial.print("Float       MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(float));
  Serial.print("        ");
  Serial.println(max_Float, 6);

  Serial.print("Double      MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(double));
  Serial.print("       ");
  Serial.println(min_Double, 15);

  Serial.print("Double      MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(double));
  Serial.print("        ");
  Serial.println(max_Double, 15);

  Serial.print("Long Double MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(long double));
  Serial.print("       ");
  Serial.println(-22.2250738585072014,16);

  Serial.print("Long Double MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(long double));
  Serial.print("        ");
  Serial.println(11.7976931348623157,16);

  Serial.print("bit to bit  MIN = ");
  Serial.print("       ");
  Serial.print(sizeof(uint16_t));
  Serial.print("        ");
  Serial.println(0, BIN);

  Serial.print("bit to bit  MAX = ");
  Serial.print("       ");
  Serial.print(sizeof(uint16_t));
  Serial.print("        ");
  Serial.println(UINT16_MAX, BIN);

}

void loop()
{

  

  
}