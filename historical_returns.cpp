#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
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

    // Ignora o cabeçalho
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string date;
        string priceA;
        string priceB;

        getline(ss, date, ',');
        getline(ss, priceA, ',');
        getline(ss, priceB, ',');

        prices.push_back({
            date,
            stod(priceA),
            stod(priceB)
        });
    }

    file.close();

    if (prices.size() < 2) {
        cerr << "ERROR: Not enough price data." << endl;
        return 1;
    }

    cout << fixed << setprecision(2);
    cout << "=== HISTORICAL DAILY RETURNS ===" << endl;

    for (size_t i = 1; i < prices.size(); ++i) {
        double returnA =
            prices[i].assetA / prices[i - 1].assetA - 1.0;

        double returnB =
            prices[i].assetB / prices[i - 1].assetB - 1.0;

        cout << prices[i].date
             << " | Asset A: " << returnA * 100.0 << "%"
             << " | Asset B: " << returnB * 100.0 << "%"
             << endl;
    }

    return 0;
}