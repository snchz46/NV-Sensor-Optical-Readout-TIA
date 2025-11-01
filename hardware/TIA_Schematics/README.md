# MCP607 TIA Schematic Notes

This folder hosts the schematic sources for the MCP607-based transimpedance amplifier that converts the BPW34 photodiode current into a measurable voltage for both ESP32 and ADS1115 data acquisition paths.

## Core Circuit Blocks
- **Photodiode stage:** BPW34 reverse biased at 5 V to reduce junction capacitance and improve linearity.
- **Transimpedance amplifier:** MCP607 configured in inverting mode with low-noise feedback network and guard ring routing recommendations.
- **Filter options:** Optional RC snubber and differential output driver footprints for shielded cable runs.

## Feedback Network Tuning
The effective gain and bandwidth are determined by the feedback components:
- **Rf:** Sets the transimpedance gain (V/A). Typical values from 220 kΩ to 1 MΩ.
- **Cf:** Stabilises the op-amp and introduces a pole to limit noise. Typical values from 3.3 pF to 10 nF depending on Rf and cable capacitance.
- Combine Rf and Cf according to the target cutoff frequency listed in the project README.

## Simulation Guidance
- Use LTspice, TI-TINA, or KiCad Ngspice with the MCP607 macro-model for stability analysis.
- Sweep input capacitance (photodiode + wiring) between 50 pF and 200 pF.
- Validate phase margin >45° for all operating points and check output swing versus expected photocurrent.

Document simulation results under `data/tia_rf_cf_sweep/` to maintain traceability between design and measurement.
