#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool validatePortfolio(const vector<double>& weights) {
const double tolerance = 1e-9;
double totalWeight = 0.0;

if (weights.empty()) {
    return false;
}

for (double weight : weights) {
    if (!isfinite(weight) || weight < 0.0) {
        return false;
    }

    totalWeight += weight;
}

return abs(totalWeight - 1.0) <= tolerance;
}

int main(){ 
vector<double> validWeights = {0.40, 0.30, 0.20, 0.10};

vector<double> overweightWeights = {0.50, 0.40, 0.30};

vector<double> negativeWeights = {0.60, 0.50, -0.10};

cout << boolalpha;

cout << "Valid portfolio: " << validatePortfolio(validWeights) << endl;

cout << "Overweight portfolio: " << validatePortfolio(overweightWeights) << endl;

cout << "Negative weight portfolio: " << validatePortfolio(negativeWeights) << endl;

return 0;
}