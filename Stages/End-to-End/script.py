#!/usr/bin/env python3

import sys
import subprocess
import time
from pathlib import Path

# -------- Configuration --------
EXECUTABLE = Path("bin/C2RISC_Engine")
TEST_DIR = Path("test")
ERROR_LOG = Path("output/testing.log")

# -------- Parse Arguments --------
filter_prefix = sys.argv[1] if len(sys.argv) >= 2 else None
if len(sys.argv) >= 3:
    EXECUTABLE = Path(sys.argv[2])

# -------- Ensure Executable Exists --------
if not EXECUTABLE.exists() or not EXECUTABLE.is_file():
    print("⚙️  Executable not found, trying to build with make...")
    result = subprocess.run(["make", "compiler"])
    if result.returncode != 0:
        print("❌ Make failed.")
        sys.exit(1)

# -------- Ensure Output Directory Exists --------
ERROR_LOG.parent.mkdir(parents=True, exist_ok=True)
ERROR_LOG.write_text("")  # Clear previous log

# -------- Find Matching Test Files --------
def find_test_files():
    if filter_prefix:
        matched_dirs = [
            folder for folder in TEST_DIR.iterdir()
            if folder.is_dir() and folder.name.startswith(filter_prefix)
        ]
        files = []
        for folder in matched_dirs:
            files += sorted(folder.rglob("*.c"))
        return files
    else:
        return sorted(TEST_DIR.rglob("*.c"))

# -------- Run Each Test File --------
def run_tests():
    print(f"🚀 Running tests with: {EXECUTABLE}")
    test_files = find_test_files()

    if not test_files:
        print("⚠️  No test files found.")
        return

    for test_file in test_files:
        print(f"🔹 Running on: {test_file}")
        try:
            subprocess.run(
                [str(EXECUTABLE), str(test_file), "-t"],
                stderr=open(ERROR_LOG, "a"),
                stdout=subprocess.DEVNULL
            )
        except Exception as e:
            print(f"⚠️  Failed on: {test_file} — {e}")
        print("---------------------------")
        time.sleep(0.5)

# -------- Main --------
if __name__ == "__main__":
    run_tests()