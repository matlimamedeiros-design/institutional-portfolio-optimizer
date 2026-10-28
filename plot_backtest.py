import pandas as pd
import matplotlib.pyplot as plt

# STEP 1: Load the C++ backtest results.
df = pd.read_csv("backtest_results.csv", parse_dates=["Date"])

if df.empty:
    raise ValueError("The backtest results file is empty.")

required_columns = [
    "Date",
    "PortfolioValue",
    "BenchmarkValue",
    "PortfolioReturn",
    "BenchmarkReturn",
    "PortfolioDrawdown",
    "BenchmarkDrawdown",
]

missing_columns = [
    column for column in required_columns
    if column not in df.columns
]

if missing_columns:
    raise ValueError(
        f"Missing columns in CSV: {missing_columns}"
    )

df = df.sort_values("Date").reset_index(drop=True)

# STEP 2: Display the analysis period.
print("\n=== BACKTEST DATA ===")
print(f"First date: {df['Date'].min().date()}")
print(f"Last date: {df['Date'].max().date()}")
print(f"Daily observations: {len(df)}")

# STEP 3: Plot the portfolio equity curves.
plt.figure(figsize=(12, 6))

plt.plot(
    df["Date"],
    df["PortfolioValue"],
    label="60% SPY / 40% AGG"
)

plt.plot(
    df["Date"],
    df["BenchmarkValue"],
    label="100% SPY"
)

plt.title("Portfolio Performance vs. SPY Benchmark")
plt.xlabel("Date")
plt.ylabel("Portfolio Value (USD)")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig("equity_curve.png", dpi=200)
plt.show()

# STEP 4: Plot historical drawdowns.
plt.figure(figsize=(12, 6))

plt.plot(
    df["Date"],
    df["PortfolioDrawdown"] * 100,
    label="60% SPY / 40% AGG"
)

plt.plot(
    df["Date"],
    df["BenchmarkDrawdown"] * 100,
    label="100% SPY"
)

plt.axhline(y=0, linewidth=1)

plt.title("Historical Drawdown Comparison")
plt.xlabel("Date")
plt.ylabel("Drawdown (%)")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig("drawdown_comparison.png", dpi=200)
plt.show()

# STEP 5: Plot the distribution of portfolio daily returns.
plt.figure(figsize=(10, 6))

plt.hist(
    df["PortfolioReturn"].dropna() * 100,
    bins=50
)

plt.title("Daily Returns Distribution: 60% SPY / 40% AGG")
plt.xlabel("Daily Return (%)")
plt.ylabel("Frequency")
plt.grid(True)
plt.tight_layout()

plt.savefig("daily_returns_distribution.png", dpi=200)
plt.show()

# STEP 6: Print additional summary statistics.
portfolio_returns = df["PortfolioReturn"].dropna()
benchmark_returns = df["BenchmarkReturn"].dropna()

print("\n=== ADDITIONAL PERFORMANCE ANALYSIS ===")

print(
    "Portfolio mean daily return: "
    f"{portfolio_returns.mean() * 100:.5f}%"
)

print(
    "Benchmark mean daily return: "
    f"{benchmark_returns.mean() * 100:.5f}%"
)

print(
    "Portfolio best daily return: "
    f"{portfolio_returns.max() * 100:.4f}%"
)

print(
    "Portfolio worst daily return: "
    f"{portfolio_returns.min() * 100:.4f}%"
)

print(
    "Benchmark best daily return: "
    f"{benchmark_returns.max() * 100:.4f}%"
)

print(
    "Benchmark worst daily return: "
    f"{benchmark_returns.min() * 100:.4f}%"
)

print("\nCharts saved:")
print("- equity_curve.png")
print("- drawdown_comparison.png")
print("- daily_returns_distribution.png")