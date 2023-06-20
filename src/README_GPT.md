# Funciones de conversión de datos para Arduino

Esta biblioteca de Arduino proporciona varias funciones de conversión de datos para combinar y separar diferentes tipos de datos. Estas funciones pueden ser útiles para manipular, almacenar y transmitir datos en proyectos de Arduino.

## Funciones

A continuación se muestra una descripción detallada de cada función:

### `mergeInt8ToUint16`

Combina dos valores `int8_t` en una palabra `uint16_t`.

**Parámetros:**
- `firstI8Value`: El byte más significativo.
- `secondI8Value`: El byte menos significativo.

**Retorno:**
- El resultado de combinar los bytes en una palabra `uint16_t`.

### `splitUint16ToInt8`

Separa un valor `uint16_t` en dos valores `int8_t`.

**Parámetros:**
- `valueUi16`: La palabra `uint16_t` a separar.
- `firstI8Value`: Referencia al byte más significativo resultante.
- `secondI8Value`: Referencia al byte menos significativo resultante.

### `mergeUint8ToUint16`

Combina dos valores `uint8_t` en una palabra `uint16_t`.

**Parámetros:**
- `firstUi8Value`: El byte más significativo.
- `secondUi8Value`: El byte menos significativo.

**Retorno:**
- El resultado de combinar los bytes en una palabra `uint16_t`.

### `splitUint16ToUint8`

Separa un valor `uint16_t` en dos valores `uint8_t`.

**Parámetros:**
- `valueUi16`: La palabra `uint16_t` a separar.
- `firstUi8Value`: Referencia al byte más significativo resultante.
- `secondUi8Value`: Referencia al byte menos significativo resultante.

### `mergeUint16ToInt32`

Combina dos valores `uint16_t` en un valor `int32_t`.

**Parámetros:**
- `ui16part1`: La palabra más significativa.
- `ui16part2`: La palabra menos significativa.

**Retorno:**
- El resultado de combinar las palabras en un valor `int32_t`.

### `splitInt32ToUint16`

Separa un valor `int32_t` en dos valores `uint16_t`.

**Parámetros:**
- `valueI32`: El valor `int32_t` a separar.
- `ui16part1`: Referencia a la palabra más significativa resultante.
- `ui16part2`: Referencia a la palabra menos significativa resultante.

### `mergeUint16ToUint32`

Combina dos valores `uint16_t` en un valor `uint32_t`.

**Parámetros:**
- `ui16part1`: La palabra más significativa.
- `ui16part2`: La palabra menos significativa.

**Retorno:**
- El resultado de combinar las palabras en un valor `uint32_t`.

### `splitUint32ToUint16`

Separa un valor `uint32_t` en dos valores `uint16_t`.

**Parámetros:**
- `valueUi32`: El valor `uint32_t` a separar.
- `ui16part1`: Referencia a la palabra más significativa resultante.
- `ui16part2`: Referencia a la palabra menos significativa resultante.

### `mergeUint16ToFloat32`

Combina dos valores `uint16_t` en un valor `float`.

**Parámetros:**
- `ui16part1`: La palabra más significativa.
- `ui16part2`: La palabra menos significativa.

**Retorno:**
- El resultado de combinar las palabras en un valor `float`.

### `splitFloat32ToUint16`

Separa un valor `float` en dos valores `uint16_t`.

**Parámetros:**
- `valueFloat`: El valor `float` a separar.
- `ui16part1`: Referencia a la palabra más significativa resultante.
- `ui16part2`: Referencia a la palabra menos significativa resultante.

### `mergeUint16ToInt64`

Combina cuatro valores `uint16_t` en un valor `int64_t`.

**Parámetros:**
- `ui16part1`: La palabra más significativa.
- `ui16part2`: La segunda palabra más significativa.
- `ui16part3`: La segunda palabra menos significativa.
- `ui16part4`: La palabra menos significativa.

**Retorno:**
- El resultado de combinar las palabras en un valor `int64_t`.

### `splitInt64ToUint16`

Separa un valor `int64_t` en cuatro valores `uint16_t`.

**Parámetros:**
- `valueI64`: El valor `int64_t` a separar.
- `ui16part1`: Referencia a la palabra más significativa resultante.
- `ui16part2`: Referencia a la segunda palabra más significativa resultante.
- `ui16part3`: Referencia a la segunda palabra menos significativa resultante.
- `ui16part4`: Referencia a la palabra menos significativa resultante.

### `mergeUint16ToUint64`

Combina cuatro valores `uint16_t` en un valor `uint64_t`.

**Parámetros:**
- `ui16part1`: La palabra más significativa.
- `ui16part2`: La segunda palabra más significativa.
- `ui16part3`: La segunda palabra menos significativa.
- `ui16part4`: La palabra menos significativa.

**Retorno:**
- El resultado de combinar las palabras en un valor `uint64_t`.

### `splitUint64ToUint16`

Separa un valor `uint64_t` en cuatro valores `uint16_t`.

**Parámetros:**
- `valueUi64`: El valor `uint64_t` a separar.
- `ui16part1`: Referencia a la palabra más significativa resultante.
- `ui16part2`: Referencia a la segunda palabra más significativa resultante.
- `ui16part3`: Referencia a la segunda palabra menos significativa resultante.
- `ui16part4`: Referencia a la palabra menos significativa resultante.

### `mergeUint16ToDouble`

Combina cuatro valores `uint16_t` en un valor `double`.

**Parámetros:**
- `ui16part1`: La palabra más significativa.
- `ui16part2`: La segunda palabra más significativa.
- `ui16part3`: La segunda palabra menos significativa.
- `ui16part4`: La palabra menos significativa.

**Retorno:**
- El resultado de combinar las palabras en un valor `double`.

### `splitDoubleToUint16`

Separa un valor `double` en cuatro valores `uint16_t`.

**Parámetros:**
- `valueDouble`: El valor `double` a separar.
- `ui16part1`: Referencia a la palabra más significativa resultante.
- `ui16part2`: Referencia a la segunda palabra más significativa resultante.
- `ui16part3`: Referencia a la segunda palabra menos significativa resultante.
- `ui16part4`: Referencia a la palabra menos significativa resultante.

