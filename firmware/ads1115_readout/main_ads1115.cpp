#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

constexpr uint8_t kChannel = 0;
constexpr size_t kWindow = 128;
constexpr float kFullScaleVoltage = 4.096f;  // Gain = 1
constexpr float kLsb = kFullScaleVoltage / 32768.0f;

float samples[kWindow];
size_t sampleIndex = 0;
bool bufferFilled = false;

float computeMean() {
  size_t count = bufferFilled ? kWindow : sampleIndex;
  if (count == 0) {
    return 0.0f;
  }
  float sum = 0.0f;
  for (size_t i = 0; i < count; ++i) {
    sum += samples[i];
  }
  return sum / static_cast<float>(count);
}

float computeRms(float mean) {
  size_t count = bufferFilled ? kWindow : sampleIndex;
  if (count == 0) {
    return 0.0f;
  }
  float accum = 0.0f;
  for (size_t i = 0; i < count; ++i) {
    float diff = samples[i] - mean;
    accum += diff * diff;
  }
  return sqrtf(accum / static_cast<float>(count));
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Wire.begin();

  if (!ads.begin()) {
    Serial.println("Error: Failed to initialise ADS1115");
    while (true) {
      delay(1000);
    }
  }

  ads.setGain(GAIN_ONE);  // ±4.096 V range
  ads.setDataRate(RATE_ADS1115_860SPS);

  Serial.println("sample,timestamp_us,voltage_mean,voltage_rms,buffer_count");
}

void loop() {
  int16_t raw = ads.readADC_SingleEnded(kChannel);
  float voltage = raw * kLsb;

  samples[sampleIndex] = voltage;
  sampleIndex = (sampleIndex + 1) % kWindow;
  if (sampleIndex == 0) {
    bufferFilled = true;
  }

  float mean = computeMean();
  float rmsNoise = computeRms(mean);

  static uint32_t recordIndex = 0;
  Serial.print(recordIndex++);
  Serial.print(',');
  Serial.print(micros());
  Serial.print(',');
  Serial.print(mean, 6);
  Serial.print(',');
  Serial.print(rmsNoise, 6);
  Serial.print(',');
  Serial.println(bufferFilled ? kWindow : sampleIndex);

  delay(50);
}
