#include <iostream>
#include <iomanip>

double calculate_return(double initial_price, double final_price) {
if (initial_price <= 0) {
return 0.0;
}
return (final_price - initial_price) / initial_price;
}

double calculate_portfolio_return(
double weight_petrobras,
double return_petrobras,
double weight_vale,
double return_vale,
double weight_ambev,
double return_ambev
) {
return weight_petrobras * return_petrobras
+ weight_vale * return_vale
+ weight_ambev * return_ambev;
}

int main() {
std::cout << std::fixed << std::setprecision(2);

// Individual asset returns.
double return_petrobras = calculate_return(100.0, 110.0);
double return_vale = calculate_return(80.0, 72.0);
double return_ambev = calculate_return(200.0, 230.0);

// Portfolio weights: 50%, 30%, and 20%.
double weight_petrobras = 0.50;
double weight_vale = 0.30;
double weight_ambev = 0.20;

double portfolio_return = calculate_portfolio_return(
    weight_petrobras, return_petrobras,
    weight_vale, return_vale,
    weight_ambev, return_ambev
);

std::cout << "=== INSTITUTIONAL PORTFOLIO OPTIMIZER ===" << std::endl;

std::cout << "\n=== INDIVIDUAL ASSET RETURNS ===" << std::endl;

std::cout << "Petrobras: "
          << return_petrobras * 100 << "%" << std::endl;

std::cout << "Vale: "
          << return_vale * 100 << "%" << std::endl;

std::cout << "Ambev: "
          << return_ambev * 100 << "%" << std::endl;

std::cout << "\n=== PORTFOLIO WEIGHTS ===" << std::endl;

std::cout << "Petrobras: "
          << weight_petrobras * 100 << "%" << std::endl;

std::cout << "Vale: "
          << weight_vale * 100 << "%" << std::endl;

std::cout << "Ambev: "
          << weight_ambev * 100 << "%" << std::endl;

std::cout << "\nPortfolio Return: "
          << portfolio_return * 100 << "%" << std::endl;

return 0;

}