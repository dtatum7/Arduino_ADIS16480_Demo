#include <ADIS16480.h>
#include <SPI.h>

//#define DEBUG // Comment out this line to disable DEBUG mode
unsigned char roll = 0;
unsigned char pitch = 0;
unsigned char yaw = 0;
unsigned char syncWord = 0xFF; // Used to synchronize serial data received by GUI on PC

ADIS16480 IMU(9,8,7); // Instatiate IMU(Chip Select, Data Ready, HW Reset)

void setup() {
  Serial.begin(57600); // Baud rate was set arbitrarily
  // Reminder that you're in DEBUG mode
  #ifdef DEBUG
    Serial.println("**********DEBUG MODE**********");
  #endif
  IMU.reset(); // Reset IMU
}

void loop() {
  if(digitalRead(8) == LOW) { // 
    roll = (unsigned char)(IMU.regRead(ROLL_C23_OUT) >> 8); // Read roll register and cast to char
    pitch = (unsigned char)(IMU.regRead(PITCH_C31_OUT) >> 8); // Read pitch register and cast to char
    yaw = (unsigned char)(IMU.regRead(YAW_C32_OUT) >> 8); // Read pitch register and cast to char
    // 0xFF is a reserved word used for data synchronization
    if(roll == 0xFF) { // 0xFF represents 360 degrees
      roll = 0; // This makes sense since 0 and 360 degrees are the same place
    }
    if(pitch == 0xFF) { // 0xFF represents 360 degrees
      pitch = 0; // This makes sense since 0 and 360 degrees are the same place
    }
    if(yaw == 0xFF) { // 0xFF represents 360 degrees
      yaw = 0; // This makes sense since 0 and 360 degrees are the same place
    }
  }
  Serial.write(roll); // Write roll data to serial connection
  Serial.write(pitch); // Write pitch data to serial connection
  Serial.write(yaw); // Write yaw data to serial connection
  Serial.write(syncWord); // Write synchronization word to serial connection
}


