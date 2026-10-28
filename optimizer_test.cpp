#include <iostream> 
#include <cmath>

using namespace std;

int main() {
    double varA = 0.04;
    double varB = 0.01;
    double covariance = 0.004;

    double bestWeightA = 0.0;
    double bestWeightB = 0.0;
    double lowestRisk = 1e9;

    // Testa 101 carteiras diferentes 
    for (int i = 0; i <= 100; ++i) {
        double weightA = i / 100.0;
        double weightB = 1.0 - weightA;

        double variance = weightA * weightA * varA + weightB * weightB * varB + 2.0 * weightA * weightB * covariance;

        double volatility = sqrt(variance);

        if (volatility < lowestRisk) {
            lowestRisk = volatility;
            bestWeightA = weightA;
            bestWeightB = weightB;
        }
    }

    cout << "OPTIMAL PORTFOLIO" << endl;

    cout << "Asset A: " << bestWeightA * 100.0 << "%" << endl;
    cout << "Asset B: " << bestWeightB * 100.0 << "%" << endl;

    cout << "Minimum volatility: " << lowestRisk * 100.0 << "%" << endl;

    return 0;
}