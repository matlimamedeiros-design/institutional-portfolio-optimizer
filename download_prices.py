import yfinance as yf

# Assets selected for the first real-data test
tickers = ["SPY", "AGG"]

print("Downloading historical market data...")

data = yf.download(
    tickers,
    period="5y",
    interval="1d",
    auto_adjust=True,
    progress=False
)

if data.empty:
    raise RuntimeError("No market data received.")

# Extract adjusted closing prices
prices = data["Close"]

# Preserve the requested asset order
prices = prices[tickers]

# Remove dates with missing prices
prices = prices.dropna()

# Sort dates from oldest to newest
prices = prices.sort_index()

if len(prices) < 3:
    raise RuntimeError("Not enough historical observations.")

# Export prices for the C++ engine
prices.index.name = "Date"
prices.to_csv("prices.csv", float_format="%.6f")

print("Download completed.")
print(f"Observations: {len(prices)}")
print(f"First date: {prices.index.min().date()}")
print(f"Last date: {prices.index.max().date()}")
print("Saved file: prices.csv")

print("\nLatest prices:")
print(prices.tail())