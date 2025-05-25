#include <Arduino.h>
#include <DataConversion.h> // Assuming DataConversion.h is in the library's src directory or accessible

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("DataConversion Library: Bit Manipulation Example");
  Serial.println("---------------------------------------------");

  uint16_t myWord = 0; // Start with 0 (all bits clear)

  // Initial value
  Serial.print("Initial word: 0b");
  for (int i = 15; i >= 0; i--) {
    Serial.print(DataConversion::readBit(myWord, i));
  }
  Serial.println(" (Decimal: " + String(myWord) + ")");

  // Test setBit
  Serial.println("\nTesting setBit():");
  myWord = DataConversion::setBit(myWord, 0);  // Set bit 0
  myWord = DataConversion::setBit(myWord, 7);  // Set bit 7
  myWord = DataConversion::setBit(myWord, 15); // Set bit 15
  myWord = DataConversion::setBit(myWord, 7);  // Set bit 7 again (should have no effect)
  // Attempt to set a bit out of bounds (should be handled gracefully by the function)
  myWord = DataConversion::setBit(myWord, 16); 


  Serial.print("After setBit(0, 7, 15): 0b");
  for (int i = 15; i >= 0; i--) {
    Serial.print(DataConversion::readBit(myWord, i));
  }
  Serial.println(" (Decimal: " + String(myWord) + ")");

  // Test readBit
  Serial.println("\nTesting readBit():");
  Serial.println("Bit 0 is: " + String(DataConversion::readBit(myWord, 0))); // Should be 1
  Serial.println("Bit 1 is: " + String(DataConversion::readBit(myWord, 1))); // Should be 0
  Serial.println("Bit 7 is: " + String(DataConversion::readBit(myWord, 7))); // Should be 1
  Serial.println("Bit 15 is: " + String(DataConversion::readBit(myWord, 15)));// Should be 1
  // Attempt to read a bit out of bounds
  Serial.println("Bit 16 is (out of bounds): " + String(DataConversion::readBit(myWord, 16)));


  // Test clearBit
  Serial.println("\nTesting clearBit():");
  myWord = DataConversion::clearBit(myWord, 7);  // Clear bit 7
  myWord = DataConversion::clearBit(myWord, 0);  // Clear bit 0
  myWord = DataConversion::clearBit(myWord, 7);  // Clear bit 7 again (should have no effect)
  // Attempt to clear a bit out of bounds
  myWord = DataConversion::clearBit(myWord, 17);

  Serial.print("After clearBit(0, 7): 0b");
  for (int i = 15; i >= 0; i--) {
    Serial.print(DataConversion::readBit(myWord, i));
  }
  Serial.println(" (Decimal: " + String(myWord) + ")");
  Serial.println("Bit 7 is now: " + String(DataConversion::readBit(myWord, 7))); // Should be 0

  // Test toggleBit
  Serial.println("\nTesting toggleBit():");
  Serial.print("Before toggleBit(5): 0b");
  for (int i = 15; i >= 0; i--) {
    Serial.print(DataConversion::readBit(myWord, i));
  }
  Serial.println(" (Bit 5 is " + String(DataConversion::readBit(myWord, 5)) + ")");
  
  myWord = DataConversion::toggleBit(myWord, 5); // Toggle bit 5 (0 -> 1)
  
  Serial.print("After toggleBit(5) (0->1): 0b");
  for (int i = 15; i >= 0; i--) {
    Serial.print(DataConversion::readBit(myWord, i));
  }
  Serial.println(" (Bit 5 is " + String(DataConversion::readBit(myWord, 5)) + ")");

  myWord = DataConversion::toggleBit(myWord, 5); // Toggle bit 5 again (1 -> 0)

  Serial.print("After toggleBit(5) (1->0): 0b");
  for (int i = 15; i >= 0; i--) {
    Serial.print(DataConversion::readBit(myWord, i));
  }
  Serial.println(" (Bit 5 is " + String(DataConversion::readBit(myWord, 5)) + ")");

  // Attempt to toggle a bit out of bounds
  myWord = DataConversion::toggleBit(myWord, 18);
  Serial.print("After toggleBit(18) (out of bounds): 0b");
   for (int i = 15; i >= 0; i--) {
    Serial.print(DataConversion::readBit(myWord, i));
  }
  Serial.println(" (Decimal: " + String(myWord) + ")");


  Serial.println("\n--- End of Bit Manipulation Example ---");
}

void loop() {
  // Nothing to do here for this example
}
