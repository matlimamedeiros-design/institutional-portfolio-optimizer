#include <iostream>
#include <vector>
#include <iomanip>

int main () {
std::vector<double> asset_returns = {0.10, -0.10, 0.15};
std::vector<double> portfolio_weights = {0.40, 0.40, 0.20};

double portfolio_return = 0.0;
for (int i = 0; i < asset_returns.size(); i++) {
    portfolio_return += asset_returns[i] * portfolio_weights[i];

}
std::cout << std::fixed << std::setprecision(2);

std::cout << "=== PORTFOLIO ANALYSIS ===" << std::endl;

std::cout << "Portfolio Return: "
          << portfolio_return * 100 << "%"
          << std::endl;

          return 0;
}