"""Convert CSV data into quick matplotlib plots for NV readout experiments."""

import argparse
from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd


def plot_csv(csv_path: Path, x_column: str, y_column: str) -> None:
    data = pd.read_csv(csv_path)
    plt.figure(figsize=(8, 4))
    plt.plot(data[x_column], data[y_column], marker="o", linestyle="-")
    plt.title(f"{y_column} vs {x_column}")
    plt.xlabel(x_column)
    plt.ylabel(y_column)
    plt.grid(True)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Plot CSV columns for NV optical readout experiments.")
    parser.add_argument("csv", type=Path, help="Path to CSV file")
    parser.add_argument("x", help="X-axis column")
    parser.add_argument("y", help="Y-axis column")
    args = parser.parse_args()

    plot_csv(args.csv, args.x, args.y)
