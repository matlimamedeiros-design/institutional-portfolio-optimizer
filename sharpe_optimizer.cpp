#include <iostream> 
#include <cmath> 

using namespace std;

int main() { 
    // Retornos anuais esperados
    double returnA = 0.12;
    double returnB = 0.07;

    // Variâncias e covariância anualizadas
    double varA = 0.04;
    double varB = 0.01;
    double covariance = 0.004;

    // Taxa livre de risco hipotética: 3% ao ano
    double riskFreeRate = 0.03;

    double bestWeightA = 0.0;
    double bestWeightB = 0.0;
    double bestReturn = 0.0;
    double bestVolatility = 0.0;
    double bestSharpe = -1e9;

    // Testa 101 combinações de pesos 
    for (int i= 0; i <= 100; ++i) {
        double weightA = i / 100.0;
        double weightB = 1.0 - weightA;

        // Retorno esperado da carteira
        double portfolioReturn = weightA * returnA + weightB * returnB;

        // Variância da carteira 
        double variance = weightA * weightA * varA + weightB * weightB * varB + 2.0 * weightA * weightB * covariance;

         // Volatilidade da carteira
        double volatility = sqrt(variance);

        // Índice de Sharpe
        double sharpe =
            (portfolioReturn - riskFreeRate) / volatility;

        // Guarda a carteira com maior Sharpe
        if (sharpe > bestSharpe) {
            bestSharpe = sharpe;
            bestWeightA = weightA;
            bestWeightB = weightB;
            bestReturn = portfolioReturn;
            bestVolatility = volatility;
        }
    }

    cout << "=== SHARPE PORTFOLIO OPTIMIZER ===" << endl;

    cout << "Asset A: "
         << bestWeightA * 100.0 << "%" << endl;

    cout << "Asset B: "
         << bestWeightB * 100.0 << "%" << endl;

    cout << "Expected return: "
         << bestReturn * 100.0 << "%" << endl;

    cout << "Annual volatility: "
         << bestVolatility * 100.0 << "%" << endl;

    cout << "Sharpe ratio: "
         << bestSharpe << endl;

    return 0;
    }