import subprocess
import sys
import time

def run_cpp_engine():
    print("=== PYTHON ORCHESTRATOR BRIDGE ===")
    print("Compiling and launching C++ multi-seed engine...")
    
    # C++ kodunu derle
    compile_process = subprocess.run(["g++", "-O3", "main.cpp", "-o", "collatz_orch"])
    if compile_process.returncode != 0:
        print("Compilation failed!")
        return

    print("Compilation successful. Starting simulation stream...\n")
    
    # C++ motorunu çalıştır ve çıktılarını anlık olarak yakala
    process = subprocess.Popen(["./collatz_orch"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    
    try:
        while True:
            output = process.stdout.readline()
            if output == '' and process.poll() is not None:
                break
            if output:
                print(f"[ENGINE_LOG] {output.strip()}")
    except KeyboardInterrupt:
        print("\nStopping orchestrator safely...")
        process.terminate()

if __name__ == "__main__":
    run_cpp_engine()
