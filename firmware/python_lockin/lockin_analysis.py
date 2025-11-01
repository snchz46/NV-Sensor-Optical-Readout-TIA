"""Placeholder module for software lock-in demodulation of NV fluorescence signals."""

from dataclasses import dataclass
from typing import Iterable, Tuple
import numpy as np


@dataclass
class LockInConfig:
    reference_frequency: float
    lowpass_cutoff: float
    sample_rate: float


def lock_in_demodulate(signal: Iterable[float], reference: Iterable[float], config: LockInConfig) -> Tuple[np.ndarray, np.ndarray]:
    """Demodulate `signal` using `reference` with a simple quadrature lock-in approach."""
    signal_array = np.asarray(list(signal), dtype=float)
    reference_array = np.asarray(list(reference), dtype=float)

    if signal_array.size != reference_array.size:
        raise ValueError("Signal and reference must have the same length")

    # Placeholder: return zero arrays until implementation is completed.
    return np.zeros_like(signal_array), np.zeros_like(signal_array)


if __name__ == "__main__":
    example_config = LockInConfig(reference_frequency=1234.0, lowpass_cutoff=50.0, sample_rate=10000.0)
    i_component, q_component = lock_in_demodulate([0.0, 1.0], [1.0, 0.0], example_config)
    print("I:", i_component)
    print("Q:", q_component)
