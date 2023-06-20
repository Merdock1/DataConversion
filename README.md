## Utilidad para trabajar con distintos tipos de datos en paquetes de 16 bit.

Cada registro de retencion trabaja con palabras de 16 bits

En las tablas de los registros Modbus aparecen los siguientes tipos de datos:

| Nombre   | Descripción                              | Alcance                                                |
| -------- | ----------------------------------------- | ------------------------------------------------------ |
| UINT     | Entero de 16 bits sin signo (1 registro)  | 0...65535                                              |
| INT      | Entero de 16 bits con signo (1 registro)  | -32768...+32767                                        |
| UINT32   | Entero de 32 bits sin signo (2 registros) | 0...4 294 967 295                                      |
| INT32    | Entero de 32 bits con signo (2 registros) | -2 147 483 648...+2 147 483 647                        |
| INT64    | Entero de 64 bits con signo (4 registros) | -9 223 372 036 854 775 808...9 223 372 036 854 775 807 |
| Float32  | Valor de 32 bits (2 registros)            | -3,4028E+38...+3,4028E+38                              |
| ASCII    | Carácter alfanumérico de 8 bits         | Tabla de caracteres ASCII                              |
| BITMAP   | Campo de 16 bits (1 palabra)              | –                                                     |
| DATETIME | Consultar a continuación                 | –                                                     |

Tabla 1.

**NOTA:**

* Float32Tipo de datos : flotante de precisión sencilla con bit de signo, exponente de 8 bits, mantisa de 23 bits (real normalizado positivo y negativo)
* Para los datos de tipo ASCII, el orden de transmisión de los caracteres de las palabras (registros de 16 bits) es el siguiente:
* Carácter n de peso no significativo
* Carácter n + 1 de peso significativo
* Todos los registros (de 16 bits o 2 bytes) se transmiten con la codificación Big Endian:
* El byte más significativo se transmite en primer lugar.
* El byte menos significativo se transmite en segundo lugar.
* Las variables de 32 bits guardadas en dos palabras de 16 bits (por ejemplo, medidores de consumo) se encuentran en formato Big Endian:
* La palabra de peso significativo se transmite primero y, a continuación, la de peso no significativo.
* Las variables de 64 bits guardadas en cuatro palabras de 16 bits (por ejemplo, fechas) se encuentran en formato Big Endian:
* La palabra de peso significativo se transmite primero y así sucesivamente.

#### Comensemos con la explicacion.

No hay un estandar definido para el alamcenamiento de valores mayores a 16 bits en los registros Modbus pero si una convencion.
Aqui una explicacion grafica de como se almacenan normalmente los registros de 32 bits en 2 registros de 16 bits.

![figura1](../resource/figura1.png)

Figura 1.

**Fuentes:**

* [Schneider Electric](https://product-help.schneider-electric.com/ED/PowerTag/Smartlink_SIB/EDMS/DOCA0123ES/DOCA0123xx/Tables_of_Modbus_Registers/Tables_of_Modbus_Registers-4.htm "Tipos de datos")
* [National Instruments](https://www.ni.com/en-us/innovations/white-papers/14/the-modbus-protocol-in-depth.html "¿Qué es el protocolo Modbus y cómo funciona?")
* [Industruino](https://industruino.com/blog/our-news-1/post/modbus-tips-for-industruino-26#blog_content "Split 32-bit values into 16-bit registers")

Palabra de 8 bits usados por ESP

| Tipo        | atmega328p | esp32 | rpi 3 arm32 | Win x64 x64 MSC++ | Win x64 G++ | linux x64 g++ |
| ----------- | ---------- | ----- | ----------- | ----------------- | ----------- | ------------- |
| bool        | 1          | 1     | 1           | 1                 | 1           | 1             |
| char        | 1          | 1     | 1           | 1                 | 1           | 1             |
| int         | 2          | 4     | 4           | 4                 | 4           | 4             |
| long        | 4          | 4     | 4           | 4                 | 4           | 8             |
| long long   | 8          | 8     | 8           | 8                 | 8           | 8             |
| float       | 4          | 4     | 4           | 4                 | 4           | 4             |
| double      | 4          | 8     | 8           | 8                 | 8           | 8             |
| long double | 4          | 8     | 8           | 8                 | 16          | 16            |

Tabla 2.

Fuente: [LUIS LLAMAS](https://www.luisllamas.es/tamanos-de-variables-en-esp32-arduino-raspberry-pi-windows-y-linux/ "TAMAÑOS DE VARIABLES EN ESP32, ARDUINO, RASPBERRY PI, WINDOWS Y LINUX")

Segun los datos obtenidos en la tabla 2, si pasamos los valores a 16 bits quedarian:


Palabra de 8 bits usados por ESP

| Tipo        | atmega328p | esp32 |
| ----------- | ---------- | ----- |
| bool        | 0.5        | 0.5   |
| char        | 0.5        | 0.5   |
| int         | 1          | 1     |
| long        | 2          | 1     |
| long long   | 4          | 4     |
| float       | 2          | 2     |
| double      | 2          | 4     |
| long double | 2          | 4     |

Tabla 3.

Entonces segun la tabla 3 vamos a tener las siguientes tareas o funciones.

Leer y escribir el registro de retencion 0 bit a bit.

Leer y escribir un valor uint en el registro 1.

Leer y escribir un valor int en el registro 2.

Leer y escribir un valor ulong en el registro 3.

Leer y escribir un valor long en el registro 4.

Leer y escribir un valor long long en el registro 5 y 6.

Leer y escribir un valor float en el registro 7 y 8.

Leer y escribir un valor double en el registro 9 y 10.

Leer y escribir un valor long double en el registro 11 y 12.

| Nombres                                                      |       Valor minimo       |       Valor maximo       |  |  |
| ------------------------------------------------------------ | :-----------------------: | :----------------------: | - | - |
| Leer y escribir el registro de retencion 0 bit a bit.        |     0000000000000000     |     1111111111111111     |  |  |
| Leer y escribir un valor uint en el registro 1.              |             0             |          65535          |  |  |
| Leer y escribir un valor int en el registro 2.               |          -32768          |          32767          |  |  |
| Leer y escribir un valor ulong en el registro 3.             |             0             |        4294967295        |  |  |
| Leer y escribir un valor long en el registro 4.              |        -2147483648        |        2147483647        |  |  |
| Leer y escribir un valor long long en el registro 5 y 6.     |   -9223372036854775808   |   9223372036854775807   |  |  |
| Leer y escribir un valor float en el registro 7 y 8.         |  1.18e-38 ( 7-dígitos)  |  3.40e38 ( 7-dígitos)  |  |  |
| Leer y escribir un valor double en el registro 9 y 10.       | 2.23e-308 (15-dígitos) | 1.79e308 (15-dígitos) |  |  |
| Leer y escribir un valor long double en el registro 11 y 12. | 3.37e-4932 (18-dígitos) | 1.18e4932 (18-dígitos) |  |  |


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