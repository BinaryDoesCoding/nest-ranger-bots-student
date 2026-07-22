// mBot Ranger Line-Follower Sensor State Viewer
//
// Move the sensor over black and white surfaces.
// The onboard lights show the current sensor state.

#include <Arduino.h>
#include <MeAuriga.h>

MeLineFollower line_follower_sensor(PORT_9);
MeRGBLed onboard_lights(0, 12);

const unsigned long kPrintIntervalMs = 250;

unsigned long last_print_time_ms = 0;

// Sets both onboard RGB lights to the same color.
void SetLightColor(int red, int green, int blue) {
  onboard_lights.setColor(0, red, green, blue);
  onboard_lights.show();
}

// Returns a readable description of the line-follower state.
const char* GetLineStateName(uint8_t line_sensor_state) {
  if (line_sensor_state == S1_IN_S2_IN) {
    return "LEFT BLACK | RIGHT BLACK";
  }

  if (line_sensor_state == S1_IN_S2_OUT) {
    return "LEFT BLACK | RIGHT WHITE";
  }

  if (line_sensor_state == S1_OUT_S2_IN) {
    return "LEFT WHITE | RIGHT BLACK";
  }

  if (line_sensor_state == S1_OUT_S2_OUT) {
    return "LEFT WHITE | RIGHT WHITE";
  }

  return "UNKNOWN STATE";
}

// Displays a different color for each possible sensor state.
void ShowLineState(uint8_t line_sensor_state) {
  if (line_sensor_state == S1_IN_S2_IN) {
    SetLightColor(150, 0, 255);  // Purple
  } else if (line_sensor_state == S1_IN_S2_OUT) {
    SetLightColor(255, 180, 0);  // Yellow
  } else if (line_sensor_state == S1_OUT_S2_IN) {
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
  Serial.println("MBOT RANGER LINE-FOLLOWER TEST");
  Serial.println("Move the sensor over black and white surfaces.");
  Serial.println();
}

void loop() {
  uint8_t line_sensor_state =
      line_follower_sensor.readSensors();

  ShowLineState(line_sensor_state);

  if (millis() - last_print_time_ms >= kPrintIntervalMs) {
    Serial.print("Line state value: ");
    Serial.print(line_sensor_state);

    Serial.print(" | Meaning: ");
    Serial.println(GetLineStateName(line_sensor_state));

    last_print_time_ms = millis();
  }
}
