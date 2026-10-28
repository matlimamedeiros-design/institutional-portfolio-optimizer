#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

double calculatePortfolioVolatility(
    const vector<double>& weights,
    const vector<vector<double>>& covariance
) {
    int n = weights.size();

    if (n == 0 || covariance.size() != weights.size()) {
        throw invalid_argument("Invalid portfolio dimensions.");
    }

    double variance = 0.0;

    for (int i = 0; i < n; ++i) {
        if (covariance[i].size() != weights.size()) {
            throw invalid_argument("Invalid covariance matrix.");
        }

        for (int j = 0; j < n; ++j) {
            variance += weights[i] * weights[j]
                      * covariance[i][j];
        }
    }

    if (variance < 0.0) {
        throw invalid_argument("Invalid portfolio variance.");
    }

    return sqrt(variance);
}

int main() {
    vector<double> weights = {0.60, 0.40};

    vector<vector<double>> covariance = {
        {0.04,  0.004},
        {0.004, 0.01}
    };

    double volatility =
        calculatePortfolioVolatility(weights, covariance);

    cout << "Annualized portfolio volatility: "
         << volatility * 100.0 << "%" << endl;

    return 0;
}