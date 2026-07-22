// mBot Ranger Gyroscope Tilt Viewer
//
// Keep the Ranger still while the gyroscope starts.
// Tilt the robot to change the onboard light color.

#include <Arduino.h>
#include <Wire.h>
#include <MeAuriga.h>

MeGyro onboard_gyroscope(1, 0x69);
MeRGBLed onboard_lights(0, 12);

// -------------------------------------------------------
// STUDENT ZONE
// Increase this value to require a larger tilt.
// -------------------------------------------------------

const float kTiltLimitDegrees = 20.0;

// -------------------------------------------------------
// END STUDENT ZONE
// -------------------------------------------------------

const unsigned long kPrintIntervalMs = 250;

unsigned long last_print_time_ms = 0;

// Sets both onboard RGB lights to the same color.
void SetLightColor(int red, int green, int blue) {
  onboard_lights.setColor(0, red, green, blue);
  onboard_lights.show();
}

// Changes the light color based on the X-axis tilt angle.
void ShowTiltDirection(float tilt_angle_degrees) {
  if (tilt_angle_degrees > kTiltLimitDegrees) {
    SetLightColor(255, 0, 0);    // Red
  } else if (tilt_angle_degrees < -kTiltLimitDegrees) {
    SetLightColor(0, 80, 255);   // Blue
  } else {
    SetLightColor(0, 255, 0);    // Green
  }
}

void setup() {
  Serial.begin(9600);

  onboard_lights.setpin(44);
  onboard_lights.fillPixelsBak(0, 2, 1);

  Serial.println();
  Serial.println("MBOT RANGER GYROSCOPE TEST");
  Serial.println("Keep the robot still while the sensor starts.");
  Serial.println();

  onboard_gyroscope.begin();

  delay(2000);

  Serial.println("Gyroscope ready.");
  Serial.println();
}

void loop() {
  onboard_gyroscope.update();

  float tilt_angle_x =
      onboard_gyroscope.getAngleX();

  float tilt_angle_y =
      onboard_gyroscope.getAngleY();

  float rotation_angle_z =
      onboard_gyroscope.getAngleZ();

  ShowTiltDirection(tilt_angle_x);

  if (millis() - last_print_time_ms >= kPrintIntervalMs) {
    Serial.print("X tilt: ");
    Serial.print(tilt_angle_x);

    Serial.print(" | Y tilt: ");
    Serial.print(tilt_angle_y);

    Serial.print(" | Z rotation: ");
    Serial.println(rotation_angle_z);

    last_print_time_ms = millis();
  }
}
