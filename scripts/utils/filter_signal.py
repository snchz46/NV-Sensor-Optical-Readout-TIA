"""Signal filtering utilities for NV optical readout analysis."""

import numpy as np
from scipy.signal import butter, filtfilt


def lowpass(data: np.ndarray, cutoff_hz: float, sample_rate: float, order: int = 4) -> np.ndarray:
    nyquist = 0.5 * sample_rate
    normal_cutoff = cutoff_hz / nyquist
    b, a = butter(order, normal_cutoff, btype="low", analog=False)
    return filtfilt(b, a, data)
