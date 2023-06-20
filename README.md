# Modbus-Joins-and-separates-Hreg
Library to join and separate registers of 32 and Binary values of Retention registers.


#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else // ESP32
#include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>
#include "ToolSplitMerge.h"

int8_t var_i8a = 0;
int8_t var_i8b = 0;

git config --global user.email "fmol1975@gmail.com"
  git config --global user.name "Merdock1"

enum mbip_registro
{   nr_unir2int8,
    NR_IP_TOTAL_REGISTER,};
uint16_t var_unir2int8 = 0;
ModbusIP mb;
void setup()
{   Serial.begin(115200);
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
    mb.server();
    mb.addHreg(0, 0, NR_IP_TOTAL_REGISTER);
    mb.Hreg(nr_unir2int8, var_unir2int8);
    Serial.print("Register 0 = ");
    Serial.println(nr_unir2int8);
    delay(1500);
    var_i8a = -120;
    Serial.println("Write -120 in variable var_i8a ");
    var_i8b = 120;
    Serial.println("Write 120 in variable var_i8b ");
    delay(1000);
    var_unir2int8 = unirInt8(var_i8a, var_i8b);
    Serial.println("Value unir var_i8a + var_i8b ");
    delay(1000);
    mb.Hreg(nr_unir2int8, var_unir2int8);
    Serial.println("Writing value in modbus variable ");
    delay(1000);
    mb.task();
    yield();
    Serial.print("Register 0 = ");
    Serial.println(var_unir2int8);
    delay(10000);
}
void loop()
{   var_unir2int8 = mb.Hreg(nr_unir2int8);
    mb.task();
    yield();
    dividirUint16(var_unir2int8, var_i8a, var_i8b);
    Serial.print("Register 0 = ");
    Serial.println(var_unir2int8);
    Serial.print("Register 0 var_i8a = ");
    Serial.println(var_i8a);
    Serial.print("Register 0 var_i8b = ");
    Serial.println(var_i8b);
}