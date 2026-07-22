constexpr uint8_t LED_PIN  = 9;
constexpr uint8_t FLEX_PIN = A0;

// Adjust these after observing the sensor in Serial Monitor.
constexpr int FLEX_MIN = 0;
constexpr int FLEX_MAX = 300;

constexpr uint8_t SAMPLE_COUNT = 10;
constexpr unsigned long LOOP_DELAY_MS = 20;

int readFlexSensor() {
  long total = 0;

  for (uint8_t i = 0; i < SAMPLE_COUNT; ++i) {
    total += analogRead(FLEX_PIN);
  }

  return total / SAMPLE_COUNT;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(FLEX_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  const int flexReading = readFlexSensor();

  // Prevent readings outside the calibrated range from overflowing.
  const int constrainedReading =
      constrain(flexReading, FLEX_MIN, FLEX_MAX);

  // Most Arduino boards expect analogWrite values from 0 to 255.
  const uint8_t ledBrightness =
      map(constrainedReading, FLEX_MIN, FLEX_MAX, 0, 255);

  analogWrite(LED_PIN, ledBrightness);

  Serial.print("Flex: ");
  Serial.print(flexReading);
  Serial.print(" | LED: ");
  Serial.println(ledBrightness);

  delay(LOOP_DELAY_MS);
}
