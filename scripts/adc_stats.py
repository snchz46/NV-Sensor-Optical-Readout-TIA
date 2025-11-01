"""Compute basic statistics from ADC CSV logs."""

from pathlib import Path
import pandas as pd


def adc_statistics(csv_path: Path) -> pd.Series:
    data = pd.read_csv(csv_path)
    numeric_cols = data.select_dtypes(include="number")
    return numeric_cols.describe().loc[["mean", "std", "min", "max"]]


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="Summarise ADC log statistics.")
    parser.add_argument("csv", type=Path, help="CSV file exported from firmware logs")
    args = parser.parse_args()

    stats = adc_statistics(args.csv)
    print(stats)
