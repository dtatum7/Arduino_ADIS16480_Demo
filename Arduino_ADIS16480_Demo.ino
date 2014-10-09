#include <ADIS16480.h>
#include <SPI.h>

ADIS16480 IMU(9,8,7); // chip select pin for ADIS16480

//unsigned int PROD_ID = 0x007E;
int errorCount = 0;

void setup() {
  #ifdef DEBUG
    // Serial settings for PC interface
    Serial.begin(57600); // Baud rate was set arbitrarily
    Serial.println("**********DEBUG MODE**********");
  #endif
  Serial.begin(57600); // Baud rate was set arbitrarily
  IMU.reset();
  for (long int i = 0; i < 1000000; ++i) {
    if (IMU.regRead(PROD_ID) != 16480) {
      ++errorCount;
    }
  }
  Serial.print("number of errors: ");
  Serial.print(errorCount);
  Serial.println("!!");
}

void loop() {
}
