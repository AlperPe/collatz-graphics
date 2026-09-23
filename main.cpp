#include <iostream>

unsigned long long CalculateShortCut(unsigned long long n, int k) {
 unsigned long long power_of_two = 1ULL << k;
 return (9 * n + 3 + power_of_two) / power_of_two;
}


void simulateA4Conservation(unsigned long long N) {
 double c = 0.005;
 double base_sum = N * 0.67;
 double midpoint = base_sum / 2.0;
 double deficit = c * N;
 double upper_layer_sum = midpoint - deficit;

 std::cout << "--- A4 Macro-Saved Analyze (N = " << N << ") ---" << std::endl;
 std::cout << "Midpoint: " << midpoint << std::endl;
 std::cout << "Diff (c * N): " << deficit << std::endl;
 std::cout << "Total Upper Layer (L >= 3): " << upper_layer_sum << std::endl;
}

int main() {
 std::cout << "=== A1-A3 SYSTEM MODEL ===" << std::endl;
 simulateA4Conservation(1000);
 std::cout << "--------------------------------------" << std::endl;
 std::cout << "======================================" << std::endl;
 return 0;
}
 
