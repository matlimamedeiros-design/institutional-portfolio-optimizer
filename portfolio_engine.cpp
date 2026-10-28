#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

struct Asset {
std::string ticker;
double initial_price;
double final_price;
double weight;
};

double calculate_return(const Asset&asset) {
    return (asset.final_price - asset.initial_price) / asset.initial_price;
}

double calculate_contribution(const Asset& asset) {
    return asset.weight * calculate_return(asset);
}

int main() {
std::vector<Asset> portfolio = {
    {"Petrobras", 100.0, 110.0, 0.40},
    {"Vale", 80.0, 72.0, 0.30},
    {"Ambev", 200.0, 230.0, 0.20},
    {"ITAU", 30.0, 33.0, 0.10}
};

std::cout << "=== INTITUCIONAL PORTFOLIO ENGINE ===" << std::endl;

std::cout << std::fixed << std::setprecision(2);

double portfolio_return = 0.0;

for (const Asset& asset : portfolio) {
    double asset_return = calculate_return(asset);
    double contribution = calculate_contribution(asset);

    portfolio_return += contribution;

    std::cout << "\nAsset: " << asset.ticker << std::endl;

    std::cout << "Weight: "
              << asset.weight * 100.0 << "%" << std::endl;

    std::cout << "Return: "
              << asset_return * 100.0 << "%" << std::endl;

    std::cout << "Contribution: "
              << contribution * 100.0 << " percentage points"
              << std::endl;
}

std::cout << "\n=== PORTFOLIO SUMMARY ===" << std::endl;

std::cout << "Portfolio Return: "
          << portfolio_return * 100.0 << "%"
          << std::endl;

return 0;
}