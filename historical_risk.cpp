#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iomanip>

using namespace std;

struct PriceData {
    string date;
    double assetA;
    double assetB;
};

int main() {
    ifstream file("prices.csv");

    if (!file.is_open()) {
        cerr << "ERROR: Could not open prices.csv" << endl;
        return 1;
    }

    string line;
    vector<PriceData> prices;

    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string date, priceA, priceB;

        if (!getline(ss, date, ',') ||
            !getline(ss, priceA, ',') ||
            !getline(ss, priceB, ',')) {
            cerr << "ERROR: Invalid CSV row." << endl;
            return 1;
        }

        try {
            double a = stod(priceA);
            double b = stod(priceB);

            if (!isfinite(a) || !isfinite(b) ||
                a <= 0.0 || b <= 0.0) {
                cerr << "ERROR: Invalid prices." << endl;
                return 1;
            }

            prices.push_back({date, a, b});
        } catch (const exception&) {
            cerr << "ERROR: Could not parse CSV prices." << endl;
            return 1;
        }
    }

    file.close();

    if (prices.size() < 3) {
        cerr << "ERROR: Need at least three price observations."
             << endl;
        return 1;
    }

    vector<double> returnsA;
    vector<double> returnsB;

    for (size_t i = 1; i < prices.size(); ++i) {
        returnsA.push_back(
            prices[i].assetA / prices[i - 1].assetA - 1.0
        );

        returnsB.push_back(
            prices[i].assetB / prices[i - 1].assetB - 1.0
        );
    }

    size_t n = returnsA.size();

    double meanA = 0.0;
    double meanB = 0.0;

    for (size_t i = 0; i < n; ++i) {
        meanA += returnsA[i];
        meanB += returnsB[i];
    }

    meanA /= n;
    meanB /= n;

    double varianceA = 0.0;
    double varianceB = 0.0;
    double covariance = 0.0;

    for (size_t i = 0; i < n; ++i) {
        double deviationA = returnsA[i] - meanA;
        double deviationB = returnsB[i] - meanB;

        varianceA += deviationA * deviationA;
        varianceB += deviationB * deviationB;
        covariance += deviationA * deviationB;
    }

    varianceA /= (n - 1);
    varianceB /= (n - 1);
    covariance /= (n - 1);

    // Annualize using 252 trading days
    double annualVarianceA = varianceA * 252.0;
    double annualVarianceB = varianceB * 252.0;
    double annualCovariance = covariance * 252.0;

    double weightA = 0.60;
    double weightB = 0.40;

    double portfolioVariance =
        weightA * weightA * annualVarianceA +
        weightB * weightB * annualVarianceB +
        2.0 * weightA * weightB * annualCovariance;

    if (portfolioVariance < 0.0) {
        cerr << "ERROR: Invalid portfolio variance." << endl;
        return 1;
    }

    double portfolioVolatility = sqrt(portfolioVariance);

    cout << fixed << setprecision(4);
    cout << "=== HISTORICAL RISK ENGINE ===" << endl;
    cout << "Daily return observations: " << n << endl;

    cout << "Asset A annualized volatility: "
         << sqrt(annualVarianceA) * 100.0 << "%" << endl;

    cout << "Asset B annualized volatility: "
         << sqrt(annualVarianceB) * 100.0 << "%" << endl;

    cout << "Annualized covariance: "
         << annualCovariance << endl;

    cout << "Portfolio weights: A = 60%, B = 40%" << endl;

    cout << "Portfolio annualized volatility: "
         << portfolioVolatility * 100.0 << "%" << endl;

    return 0;
}