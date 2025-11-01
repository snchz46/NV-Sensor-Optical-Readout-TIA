"""Moving average utilities."""

import numpy as np


def moving_average(data: np.ndarray, window_size: int) -> np.ndarray:
    if window_size <= 0:
        raise ValueError("window_size must be positive")
    kernel = np.ones(window_size) / window_size
    return np.convolve(data, kernel, mode="valid")
