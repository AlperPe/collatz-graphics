#include <iostream>

unsigned long long CalculateShortCut(unsigned long long n, int k) {
 unsigned long long power_of_two = 1ULL << k;
 return (9 * n + 3 + power_of_two) / power_of_two;
}
int main() {
 std::cout << "=== 0(1) COLLATZ GENERAL MODEL ===" << std::endl;

 unsigned long long test_values[] = {7, 15, 31};
 int k_values[] = {1, 2, 3};
 
 for (int i = 0; i < 3; i++) {
   unsigned long  long n = test_values[i];
   int k = k_values[i];
   unsigned long long next_n = CalculateShortCut(n, k);
   
   std::cout << "n = " << n << ", k = " << k << " --> Next Number: " << next_n << std::endl;
 }

 
 std::cout << "=== 0(1) COLLATZ ANALYZE MODEL ===" << std::endl;
 std::cout << "=================================" << std::endl;

 return 0;
}

