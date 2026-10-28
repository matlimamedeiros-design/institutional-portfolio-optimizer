#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

double calculatePortfolioReturn(
    const vector<double>& weights,
    const vector<double>& returns
) {
    if (weights.empty() || weights.size() != returns.size()) {
        throw invalid_argument("Invalid portfolio inputs.");
    }

    double totalWeight = 0.0;
    double portfolioReturn = 0.0;

    for (size_t i = 0; i < weights.size(); ++i) {
        if (!isfinite(weights[i]) ||
            !isfinite(returns[i]) ||
            weights[i] < 0.0) {
            throw invalid_argument("Invalid weight or return.");
        }

        totalWeight += weights[i];
        portfolioReturn += weights[i] * returns[i];
    }

    if (abs(totalWeight - 1.0) > 1e-9) {
        throw invalid_argument("Weights must sum to 1.0.");
    }

    return portfolioReturn;
}

int main() {
    vector<double> weights = {
        0.50, 0.30, 0.20
    };

    vector<double> returns = {
        0.10, 0.05, -0.02
    };

    double result = calculatePortfolioReturn(weights, returns);

    cout << "Portfolio return: "
         << result * 100.0
         << "%" << endl;

    return 0;
}