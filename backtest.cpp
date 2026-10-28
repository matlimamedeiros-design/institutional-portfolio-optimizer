#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Each observation stores the results for one trading day.
struct DailyResult {
    string date;
    double portfolioValue;
    double benchmarkValue;
    double portfolioReturn;
    double benchmarkReturn;
    double portfolioDrawdown;
    double benchmarkDrawdown;
};

// Calculate annualized volatility from daily returns.
double calculateAnnualizedVolatility(
    const vector<double>& dailyReturns
) {
    if (dailyReturns.size() < 2) {
        return 0.0;
    }

    double meanReturn = 0.0;

    for (double dailyReturn : dailyReturns) {
        meanReturn += dailyReturn;
    }

    meanReturn /= dailyReturns.size();

    double sumSquaredDifferences = 0.0;

    for (double dailyReturn : dailyReturns) {
        double difference = dailyReturn - meanReturn;
        sumSquaredDifferences += difference * difference;
    }

    double dailyVariance =
        sumSquaredDifferences / (dailyReturns.size() - 1);

    return sqrt(dailyVariance) * sqrt(252.0);
}

int main() {

    // STEP 1: Open the historical price file.
    ifstream file("prices.csv");

    if (!file.is_open()) {
        cerr << "Error: Could not open prices.csv\n";
        return 1;
    }

    string line;

    // Skip the CSV header.
    getline(file, line);

    // Read the first row of historical prices.
    if (!getline(file, line)) {
        cerr << "Error: No historical price data found.\n";
        return 1;
    }

    stringstream firstRow(line);

    string firstDate;
    string firstSPYText;
    string firstAGGText;

    getline(firstRow, firstDate, ',');
    getline(firstRow, firstSPYText, ',');
    getline(firstRow, firstAGGText, ',');

    double previousSPY = stod(firstSPYText);
    double previousAGG = stod(firstAGGText);

    if (previousSPY <= 0.0 || previousAGG <= 0.0) {
        cerr << "Error: Prices must be positive.\n";
        return 1;
    }

    // STEP 2: Define the investment assumptions.
    const double initialCapital = 10000.0;

    const double weightSPY = 0.60;
    const double weightAGG = 0.40;

    double portfolioValue = initialCapital;
    double benchmarkValue = initialCapital;

    double portfolioPeak = initialCapital;
    double benchmarkPeak = initialCapital;

    double maximumPortfolioDrawdown = 0.0;
    double maximumBenchmarkDrawdown = 0.0;

    vector<double> portfolioReturns;
    vector<double> benchmarkReturns;

    vector<DailyResult> results;

    // STEP 3: Process each remaining trading day.
    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        stringstream row(line);

        string date;
        string spyText;
        string aggText;

        getline(row, date, ',');
        getline(row, spyText, ',');
        getline(row, aggText, ',');

        if (date.empty() || spyText.empty() || aggText.empty()) {
            cerr << "Error: Invalid CSV row.\n";
            return 1;
        }

        double currentSPY = stod(spyText);
        double currentAGG = stod(aggText);

        if (currentSPY <= 0.0 || currentAGG <= 0.0) {
            cerr << "Error: Prices must be positive.\n";
            return 1;
        }

        // STEP 4: Calculate each asset's daily return.
        double spyReturn =
            currentSPY / previousSPY - 1.0;

        double aggReturn =
            currentAGG / previousAGG - 1.0;

        // STEP 5: Calculate the portfolio and benchmark returns.
        double portfolioReturn =
            weightSPY * spyReturn +
            weightAGG * aggReturn;

        double benchmarkReturn = spyReturn;

        // STEP 6: Update both investment values.
        portfolioValue *= (1.0 + portfolioReturn);
        benchmarkValue *= (1.0 + benchmarkReturn);

        portfolioReturns.push_back(portfolioReturn);
        benchmarkReturns.push_back(benchmarkReturn);

        // STEP 7: Update the historical peaks.
        if (portfolioValue > portfolioPeak) {
            portfolioPeak = portfolioValue;
        }

        if (benchmarkValue > benchmarkPeak) {
            benchmarkPeak = benchmarkValue;
        }

        // STEP 8: Calculate each strategy's drawdown.
        double portfolioDrawdown =
            portfolioValue / portfolioPeak - 1.0;

        double benchmarkDrawdown =
            benchmarkValue / benchmarkPeak - 1.0;

        if (portfolioDrawdown < maximumPortfolioDrawdown) {
            maximumPortfolioDrawdown = portfolioDrawdown;
        }

        if (benchmarkDrawdown < maximumBenchmarkDrawdown) {
            maximumBenchmarkDrawdown = benchmarkDrawdown;
        }

        // STEP 9: Save this day's results in memory.
        results.push_back({
            date,
            portfolioValue,
            benchmarkValue,
            portfolioReturn,
            benchmarkReturn,
            portfolioDrawdown,
            benchmarkDrawdown
        });

        // Prepare the prices for the next trading day.
        previousSPY = currentSPY;
        previousAGG = currentAGG;
    }

    file.close();

    if (portfolioReturns.size() < 2) {
        cerr << "Error: Not enough historical observations.\n";
        return 1;
    }

    // STEP 10: Calculate performance metrics.
    double totalReturnPortfolio =
        portfolioValue / initialCapital - 1.0;

    double totalReturnBenchmark =
        benchmarkValue / initialCapital - 1.0;

    double annualizedReturnPortfolio =
        pow(
            portfolioValue / initialCapital,
            252.0 / portfolioReturns.size()
        ) - 1.0;

    double annualizedReturnBenchmark =
        pow(
            benchmarkValue / initialCapital,
            252.0 / benchmarkReturns.size()
        ) - 1.0;

    double volatilityPortfolio =
        calculateAnnualizedVolatility(portfolioReturns);

    double volatilityBenchmark =
        calculateAnnualizedVolatility(benchmarkReturns);

    // STEP 11: Export the daily results to a CSV file.
    ofstream output("backtest_results.csv");

    if (!output.is_open()) {
        cerr << "Error: Could not create backtest_results.csv\n";
        return 1;
    }

    output
        << "Date,"
        << "PortfolioValue,"
        << "BenchmarkValue,"
        << "PortfolioReturn,"
        << "BenchmarkReturn,"
        << "PortfolioDrawdown,"
        << "BenchmarkDrawdown\n";

    output << fixed << setprecision(8);

    for (const DailyResult& result : results) {
        output
            << result.date << ","
            << result.portfolioValue << ","
            << result.benchmarkValue << ","
            << result.portfolioReturn << ","
            << result.benchmarkReturn << ","
            << result.portfolioDrawdown << ","
            << result.benchmarkDrawdown << "\n";
    }

    output.close();

    // STEP 12: Display the summary.
    cout << fixed << setprecision(4);

    cout << "\n=== PORTFOLIO BACKTEST ===\n";

    cout << "\n--- 60% SPY / 40% AGG Portfolio ---\n";
    cout << "Initial capital: $"
         << initialCapital << "\n";
    cout << "Final value: $"
         << portfolioValue << "\n";
    cout << "Total return: "
         << totalReturnPortfolio * 100.0 << "%\n";
    cout << "Annualized return: "
         << annualizedReturnPortfolio * 100.0 << "%\n";
    cout << "Annualized volatility: "
         << volatilityPortfolio * 100.0 << "%\n";
    cout << "Maximum drawdown: "
         << maximumPortfolioDrawdown * 100.0 << "%\n";

    cout << "\n--- SPY Benchmark ---\n";
    cout << "Initial capital: $"
         << initialCapital << "\n";
    cout << "Final value: $"
         << benchmarkValue << "\n";
    cout << "Total return: "
         << totalReturnBenchmark * 100.0 << "%\n";
    cout << "Annualized return: "
         << annualizedReturnBenchmark * 100.0 << "%\n";
    cout << "Annualized volatility: "
         << volatilityBenchmark * 100.0 << "%\n";
    cout << "Maximum drawdown: "
         << maximumBenchmarkDrawdown * 100.0 << "%\n";

    cout << "\nDaily results saved to backtest_results.csv\n";

    return 0;
}