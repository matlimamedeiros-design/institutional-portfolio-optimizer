#include <iostream>
#include <vector> 
#include <iomanip>

int main() {
std::vector<double> asset_returns = {0.10, -0.10, 0.15};

std::cout << std::fixed << std::setprecision(2);

std::cout << "=== ASSET RETURNS ===" << std::endl;

for (int i = 0; i < asset_returns.size(); i++) {
    std::cout << "Asset " << i + 1 << ": "
              << asset_returns[i] * 100 << "%"
              << std::endl;
}

return 0;

}