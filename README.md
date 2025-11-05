# NV-Sensor-Optical-Readout-TIA

Development of an optical NV-diamond fluorescence sensing platform using a BPW34 photodiode and MCP607 transimpedance amplifier (TIA), read out by either the ESP32 internal ADC or an external 16-bit ADS1115.

## System Overview
- Photodiode: BPW34 reverse-biased
- Op-Amp: MCP607, low-noise rail-to-rail
- ADC: ADS1115 via I²C (16-bit) and ESP32 internal (12-bit)
- Magnetic field applied via adjustable neodymium magnet (threaded rod system)
- Output signal measured as fluorescence intensity quenching under magnetic field

## Hardware
Rf/Cf tuning for gain–bandwidth tradeoff:
| Rf (Ω) | Cf (F) | Cutoff (Hz) |
|---------|--------|--------------|
| 1MΩ | 3.3pF | 48kHz |
| 470kΩ | 10nF | 34Hz |
| 220kΩ | 10nF | 72Hz |

## Firmware
Includes:
- ESP32 ADC test firmware (analogRead averaging, exponential filter)
- ADS1115 readout firmware (noise RMS calculation, CSV logging)
- Real-time noise comparison (ESP32 vs ADS1115)

## Data & Analysis
- Data stored as CSV under `/data/`
- Python scripts for plotting and computing noise, SNR, and ΔI/I vs magnetic field
- Lock-in analysis planned for modulated field measurements

## Example Results
| Parameter | ESP32 ADC | ADS1115 |
|------------|------------|----------|
| Resolution | 12-bit | 16-bit |
| RMS Noise | ~6.6 mV | ~0.34 mV |
| SNR | – | +26 dB |
| Range | 0–2.6 V | 0–4.1 V |

## Roadmap
- [ ] Implement software lock-in detection
- [ ] Integrate higher-resolution ADC (ADS131M04)
- [ ] Design modular PCB with adjustable feedback network
- [ ] Add ROS2 node for remote NV-sensor readout

## Author
Samuel Sánchez Moreno  
Fraunhofer IAO Project
