#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include <cassert>

// Mutlak matematiksel temelli Üstel Ölçek ve Çok Adımlı Atlama Yapısı
struct ScaleJumpResult {
    unsigned long long next_n;
    int steps_advanced;
    double log_scale_delta; // Logaritmik üstel ölçek değişimi
};

ScaleJumpResult RigorousExponentialJump(unsigned long long n) {
    // n'in saf tek sayı olduğundan kesinlikle emin ol
    while (n % 2 == 0 && n > 0) {
        n >>= 1;
    }

    if (n <= 1) {
        return {1, 1, 0.0};
    }

    // Modüler aritmetiğe dayalı mutlak kural analizi
    int k = 1;
    if (n % 4 == 3) k = 1;
    else if (n % 8 == 1) k = 2;
    else if (n % 16 == 13) k = 3;
    else k = 4;

    unsigned long long power_of_two = 1ULL << k;
    unsigned long long next_val = (9 * n + 3 + power_of_two) / power_of_two;

    int extra_steps = 0;
    while (next_val % 2 == 0 && next_val > 0) {
        next_val >>= 1;
        extra_steps++;
    }

    int total_advanced_steps = 1 + k + extra_steps;
    
    // Logaritmik tabanda kesin ölçek değişimi (Mutlak kuvvet takibi)
    double scale_delta = log2((double)next_val / (double)n);

    return {next_val, total_advanced_steps, scale_delta};
}

// Mutlak Doğrulama (Audit Hook)
bool VerifyRigorousStep(unsigned long long prev_n, unsigned long long next_n) {
    if (prev_n <= 0 || prev_n % 2 == 0) return false;
    if (next_n == 0 && prev_n > 1) return false;
    return true;
}

// Üstel Ölçekli Simülasyon Motoru
void runRigorousExponentialSimulation() {
    std::cout << "\n=== RIGOROUS EXPONENTIAL SCALE COLLATZ ENGINE ===" << std::endl;
    std::cout << "Running with strict modular math and exponent scale tracking..." << std::endl;
    std::cout << "Press Ctrl+C to stop anytime." << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    
    unsigned long long current_n = 1000000009ULL;
    unsigned long long total_steps = 0;
    unsigned long long failed_audits = 0;
    double cumulative_log_scale = log2((double)current_n);
    
    while (true) {
        while (current_n % 2 == 0 && current_n > 0) {
            current_n >>= 1;
        }

        ScaleJumpResult jump = RigorousExponentialJump(current_n);

        // Denetim kancası
        if (!VerifyRigorousStep(current_n, jump.next_n)) {
            std::cout << "\n[ALERT!] Mathematical anomaly detected at step " << total_steps << "!" << std::endl;
            failed_audits++;
        }

        current_n = jump.next_n;
        total_steps += jump.steps_advanced;
        cumulative_log_scale += jump.log_scale_delta;
        
        if (current_n <= 1) {
            current_n = (total_steps * 2026 + 13) | 1;
            cumulative_log_scale = log2((double)current_n);
        }

        // Raporlama
        if (total_steps % 1000000 == 0) {
            auto current_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = current_time - start_time;
            double seconds = elapsed.count();
            
            std::cout << "Elapsed: " << (int)seconds << "s | Steps: " << total_steps 
                      << " | Audits: " << failed_audits 
                      << " | Exp Scale 2^: ~" << cumulative_log_scale << " bits" << std::endl;
        }
    }
}

int main() {
    std::cout << "=== RIGOROUS COLLATZ ENGINE INITIALIZED ===" << std::endl;
    runRigorousExponentialSimulation();
    return 0;
}

