\# Institutional Portfolio Optimizer



A quantitative finance project focused on portfolio analytics, risk measurement, portfolio optimization, and historical backtesting using C++17 and Python.



\## Overview



The Institutional Portfolio Optimizer explores how portfolio construction, asset allocation, and covariance affect investment performance and risk.



The project combines C++ implementations of portfolio calculations and optimization algorithms with Python tools for historical market data retrieval and visualization.



It is an educational and research project, not a production-grade investment system or investment recommendation.



\## Features



\### 1. Portfolio Analytics

\- Calculate individual asset returns.

\- Calculate weighted portfolio returns.

\- Measure each asset's contribution to total portfolio return.



\### 2. Portfolio Validation

\- Check whether a portfolio has valid weights.

\- Reject negative or non-finite weights.

\- Verify that portfolio weights sum to 100%, within a numerical tolerance.



\### 3. Risk Measurement

\- Calculate portfolio volatility using a covariance matrix.

\- Process historical asset prices and calculate daily returns.

\- Account for covariance when measuring portfolio risk.



\### 4. Portfolio Optimization

\- Search for minimum-volatility portfolios using a grid search.

\- Search for maximum-Sharpe portfolios using a grid search.

\- Compare asset allocations under different hypothetical return and risk assumptions.



The current optimization examples use two assets and test 101 weight combinations, from 0% to 100% in 1-percentage-point increments.



\### 5. Historical Backtesting

\- Simulate a portfolio with 60% SPY and 40% AGG.

\- Compare its historical performance against a 100% SPY benchmark.

\- Calculate cumulative returns, annualized returns, annualized volatility, and maximum drawdown.

\- Export daily results to CSV.



\### 6. Data Analysis and Visualization

Python scripts retrieve historical market data, process backtest output, and generate:

\- Portfolio equity curves.

\- Historical drawdown comparisons.

\- Daily return distributions.



\## Technology Stack



\- \*\*C++17:\*\* portfolio calculations, risk measurement, optimization examples, and backtesting.

\- \*\*Python:\*\* historical data retrieval and visualization.

\- \*\*NumPy / pandas:\*\* numerical and tabular data processing where required by the Python scripts.

\- \*\*Matplotlib:\*\* charts and visualization.

\- \*\*yfinance:\*\* historical market data retrieval.



\## Repository Structure



The current project uses standalone source files in the repository root.



| File | Purpose |

|---|---|

| `main.cpp` | Basic portfolio return calculations |

| `portfolio\_engine.cpp` | Asset representation, weighted returns, and return contributions |

| `validation\_test.cpp` | Portfolio weight validation examples |

| `historical\_returns.cpp` | Historical return calculations |

| `historical\_risk.cpp` | Daily return calculations from historical prices |

| `risk\_test.cpp` | Portfolio volatility calculation using a covariance matrix |

| `optimizer\_test.cpp` | Minimum-volatility grid search |

| `sharpe\_optimizer.cpp` | Maximum-Sharpe grid search |

| `backtest.cpp` | Historical portfolio and benchmark simulation |

| `download\_prices.py` | Historical market data download |

| `plot\_backtest.py` | Backtest analysis and chart generation |



Several C++ files contain their own `main()` function and are intended to be compiled as separate programs.



\## Installation



\### Prerequisites



\- A C++17-compatible compiler, such as GCC.

\- Python 3.

\- pip.



\### Python Dependencies



Install the required packages:



```bash

python -m pip install yfinance pandas matplotlib

```



NumPy is also used by some Python environments as a dependency of the packages above. Install it explicitly if another project script requires it:



```bash

python -m pip install numpy

```



\## Running the Historical Backtest



Run the following commands from the project directory.



\### Step 1: Download historical prices



```bash

python download\_prices.py

```



This script downloads historical prices for SPY and AGG and saves them to `prices.csv`.



\### Step 2: Compile the C++ backtest



Using GCC:



```bash

g++ -std=c++17 -Wall -Wextra -pedantic backtest.cpp -o backtest.exe

```



\### Step 3: Execute the backtest



On Windows PowerShell:



```powershell

.\\backtest.exe

```



The program simulates the portfolio and benchmark and generates `backtest\_results.csv`.



\### Step 4: Generate charts



```bash

python plot\_backtest.py

```



The script generates:

\- `equity\_curve.png`

\- `drawdown\_comparison.png`

\- `daily\_returns\_distribution.png`



The scripts should be run in the same directory unless their file paths are updated.



\## Historical Backtest Example



The current historical test uses a portfolio with fixed weights of 60% SPY and 40% AGG, compared against a 100% SPY benchmark.



For the previously tested historical dataset, the reported results were:



| Metric | 60% SPY / 40% AGG | 100% SPY Benchmark |

|---|---:|---:|

| Initial capital | $10,000.00 | $10,000.00 |

| Final portfolio value | $14,354.08 | $17,853.82 |

| Total return | 43.54% | 78.54% |

| Annualized return | 7.53% | 12.35% |

| Annualized volatility | 11.09% | 17.15% |

| Maximum drawdown | -20.54% | -24.50% |



These figures describe a historical simulation using the dataset available when the test was run. They are not a guarantee of future performance. Results may change when the historical data is downloaded again.



The lower-volatility portfolio also produced a lower return than the SPY benchmark over this test period. This illustrates the trade-off between risk and return; it does not establish that the portfolio is superior.



\## Charts



\### Portfolio Performance



!\[Portfolio Performance](equity\_curve.png)



\### Drawdown Comparison



!\[Historical Drawdown Comparison](drawdown\_comparison.png)



\### Daily Return Distribution



!\[Daily Return Distribution](daily\_returns\_distribution.png)



\## Current Limitations



\- The basic portfolio examples use hypothetical asset prices.

\- The optimization examples use hypothetical expected returns, variances, and covariance values.

\- The grid-search optimizers test discrete weight combinations rather than solving a continuous optimization problem.

\- The historical backtest uses fixed portfolio weights and does not implement periodic rebalancing.

\- Transaction costs, taxes, slippage, and market impact are not modeled.

\- Historical backtest results depend on the downloaded dataset and the assumptions implemented in the code.

\- The project is not yet a unified production application; the C++ programs are standalone examples and components.



\## Future Improvements



\- Integrate historical return estimates into portfolio optimization.

\- Implement a reusable portfolio optimization engine.

\- Improve validation of prices, covariance matrices, and numerical inputs.

\- Add configurable asset universes and portfolio constraints.

\- Implement periodic rebalancing and transaction cost assumptions.

\- Add automated unit tests and reproducible evaluation procedures.

\- Improve benchmark comparisons and risk-adjusted performance analysis.



\## Disclaimer



This project is for educational and research purposes only. It does not constitute investment advice, a recommendation to buy or sell securities, or a guarantee of investment performance.



Market data is retrieved through third-party services. Users are responsible for reviewing the applicable data-provider terms and conditions before using or redistributing data.



\## Author



Developed as a personal project to study quantitative finance, portfolio construction, risk analytics, optimization, and C++/Python applications in investment management.

