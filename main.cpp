#include <iostream>
#include <string>

// O(1) Analytical Shortcut Function
unsigned long long CalculateShortCut(unsigned long long n, int k) {
    unsigned long long power_of_two = 1ULL << k;
    return (9 * n + 3 + power_of_two) / power_of_two;
}

// G1 / G2 Modular Classification and k Prediction
void classifyAndExecute(unsigned long long n) {
    int k = 1;
    std::string group = "";

    if (n % 4 == 3) {
        k = 1;
        group = "G1 (%50 zone, k=1)";
    } else if (n % 8 == 1) {
        k = 2;
        group = "G2 (25% zone, k=2)";
    } else if (n % 16 == 13) {
        k = 3;
        group = "G2 (12.5% zone, k=3)";
    } else {
        k = 4;
        group = "G2 (Longest Zone, k>=4)";
    }

    unsigned long long next_n = CalculateShortCut(n, k);

    std::cout << "Number (n): " << n << " -> group: " << group 
              << " | Result Number k: " << k 
              << " | Next Number: " << next_n << std::endl;
}

int main() {
    std::cout << "=== G1 / G2 MODULAR ANALYZE MODEL ===" << std::endl;
    
    unsigned long long test_set[] = {7, 9, 13, 5};
    
    for (int i = 0; i < 4; i++) {
        classifyAndExecute(test_set[i]);
    }
    
    std::cout << "=====================================" << std::endl;
    
    return 0;
}
