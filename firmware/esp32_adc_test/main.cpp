#include <Arduino.h>

constexpr uint8_t kAdcPin = 34;      // GPIO34 is input only on ESP32
constexpr size_t kSamplesPerBatch = 64;
constexpr uint32_t kSampleDelayUs = 200;  // 5 kHz sample rate target
constexpr float kEmaAlpha = 0.1f;

float emaValue = 0.0f;

void setup() {
  Serial.begin(115200);
  delay(500);
  analogReadResolution(12);
  analogSetPinAttenuation(kAdcPin, ADC_11db);
  emaValue = analogRead(kAdcPin);
  Serial.println("sample,timestamp_us,adc_raw,adc_avg,ema_filtered");
}

void loop() {
  uint32_t batchStartMicros = micros();
  uint32_t sum = 0;
  for (size_t i = 0; i < kSamplesPerBatch; ++i) {
    uint32_t value = analogRead(kAdcPin);
    sum += value;
    delayMicroseconds(kSampleDelayUs);
  }

  float avg = static_cast<float>(sum) / static_cast<float>(kSamplesPerBatch);
  emaValue = kEmaAlpha * avg + (1.0f - kEmaAlpha) * emaValue;

  static uint32_t sampleIndex = 0;
  uint32_t timestamp = micros();
  Serial.print(sampleIndex++);
  Serial.print(',');
  Serial.print(timestamp);
  Serial.print(',');
  Serial.print(sum / kSamplesPerBatch);
  Serial.print(',');
  Serial.print(avg, 4);
  Serial.print(',');
  Serial.println(emaValue, 4);

  // Maintain approximate loop rate of ~20 Hz for CSV logging.
  uint32_t loopDuration = micros() - batchStartMicros;
  if (loopDuration < 50000) {
    delayMicroseconds(50000 - loopDuration);
  }
}
