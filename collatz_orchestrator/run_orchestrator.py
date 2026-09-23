import subprocess
import sys
import time
from datetime import datetime
import os
import threading

report_filename = "collatz_master_report.txt"
lock = threading.Lock()

# İstatistik sayaçları
total_purged_lines = 0
total_lifetime_errors = 0

def autonomous_auditor():
    global total_purged_lines, total_lifetime_errors
    """Her 100 saniyede bir log dosyasını kontrol eder, çöpe atılan satırları ve hata sayısını raporlar."""
    while True:
        time.sleep(100)
        with lock:
            if not os.path.exists(report_filename):
                continue
            
            print(f"\n[AUTONOMOUS AUDIT] {datetime.now()} - 100 saniyelik periyodik kontrol yapılıyor...")
            error_count_in_batch = 0
            lines_in_batch = 0
            
            try:
                with open(report_filename, "r", encoding="utf-8") as f:
                    for line in f:
                        if line.strip():
                            lines_in_batch += 1
                        if "Audits:" in line:
                            if "Audits: 0" not in line:
                                error_count_in_batch += 1
                                print(f"[KRİTİK HATA TESPİT EDİLDİ]: {line.strip()}")
                
                total_purged_lines += lines_in_batch
                total_lifetime_errors += error_count_in_batch
                
                print(f"--- DÖNGÜ İSTATİSTİKLERİ ---")
                print(f"Bu Periyotta Temizlenen/Çöpe Atılan Satır Sayısı: {lines_in_batch}")
                print(f"Bu Periyotta Tespit Edilen Hata Sayısı: {error_count_in_batch}")
                print(f"Genel Toplam Temizlenen Satır: {total_purged_lines}")
                print(f"Genel Toplam Hata Sayısı: {total_lifetime_errors}")
                
                if error_count_in_batch > 0:
                    print("[ALARM] Sistemde matematiksel sapma veya hata saptandı!")
                else:
                    print("[BAŞARILI] Hata yok. Rapor dosyası temizleniyor ve döngü yenileniyor.")
                    open(report_filename, "w", encoding="utf-8").close()
                    
            except Exception as e:
                print(f"[AUDIT ERROR] Kontrol sırasında hata oluştu: {e}")
            print("==================================================\n")

def run_cpp_engine():
    print("=== OTONOM KOLLATZ ORCHESTRATOR & STATS AUDITOR ===")
    print("C++ motoru derleniyor...")
    
    compile_process = subprocess.run(["g++", "-O3", "main.cpp", "-o", "collatz_orch"])
    if compile_process.returncode != 0:
        print("Derleme başarısız!")
        return

    print("Derleme başarılı. Gelişmiş istatistikli otonom denetçi başlatılıyor...\n")
    
    with lock:
        open(report_filename, "w", encoding="utf-8").write(f"--- Simulation Started at {datetime.now()} ---\n")

    auditor_thread = threading.Thread(target=autonomous_auditor, daemon=True)
    auditor_thread.start()
    
    process = subprocess.Popen(["./collatz_orch"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    
    try:
        while True:
            output = process.stdout.readline()
            if output == '' and process.poll() is not None:
                break
            if output:
                clean_line = output.strip()
                print(f"[ENGINE_LOG] {clean_line}")
                with lock:
                    with open(report_filename, "a", encoding="utf-8") as report_file:
                        report_file.write(clean_line + "\n")
                        report_file.flush()
                    
    except KeyboardInterrupt:
        print("\nOtonom sistem güvenli bir şekilde durduruluyor...")
        process.terminate()

if __name__ == "__main__":
    run_cpp_engine()
