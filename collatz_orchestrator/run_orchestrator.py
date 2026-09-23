import subprocess
import sys
import time
from datetime import datetime
import os

def analyze_report(filename="collatz_master_report.txt"):
    if not os.path.exists(filename):
        print("Rapor dosyası bulunamadı.")
        return
    
    print("\n=== RASYONEL ANALİZ VE ÖZET ===")
    total_lines = 0
    seed_switches = 0
    last_steps = 0
    
    with open(filename, "r", encoding="utf-8") as f:
        for line in f:
            if "[ORCHESTRATOR]" in line:
                seed_switches += 1
            if "Steps:" in line:
                total_lines += 1
                parts = line.split("|")
                for p in parts:
                    if "Steps:" in p:
                        try:
                            last_steps = int(p.split(":")[1].strip())
                        except ValueError:
                            pass
                            
    print(f"Toplam Log Kaydı: {total_lines}")
    print(f"Seed Değişim (Rotasyon) Sayısı: {seed_switches}")
    print(f"İşlenen Son Toplam Adım: {last_steps}")
    print("================================\n")

def run_cpp_engine():
    print("=== MASTER ORCHESTRATOR & ANALYTICS BRIDGE ===")
    print("Compiling and launching C++ multi-seed engine...")
    
    compile_process = subprocess.run(["g++", "-O3", "main.cpp", "-o", "collatz_orch"])
    if compile_process.returncode != 0:
        print("Compilation failed!")
        return

    print("Compilation successful. Logging and monitoring active...\n")
    report_filename = "collatz_master_report.txt"
    
    with open(report_filename, "a", encoding="utf-8") as report_file:
        report_file.write(f"\n--- Simulation Session Started at {datetime.now()} ---\n")
        
        process = subprocess.Popen(["./collatz_orch"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        
        try:
            while True:
                output = process.stdout.readline()
                if output == '' and process.poll() is not None:
                    break
                if output:
                    clean_line = output.strip()
                    print(f"[ENGINE_LOG] {clean_line}")
                    report_file.write(clean_line + "\n")
                    report_file.flush()
                    
        except KeyboardInterrupt:
            print("\nStopping orchestrator safely...")
            report_file.write(f"--- Simulation Session Ended at {datetime.now()} ---\n")
            process.terminate()
            
    analyze_report(report_filename)

if __name__ == "__main__":
    run_cpp_engine()
