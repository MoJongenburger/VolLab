# VolLab Terminal

A professional C++20 scaffold for a quant/market-data terminal.

## What Stage 0 gives you
- CMake-based C++20 project
- vcpkg manifest dependencies
- Catch2 unit tests + CTest
- GitHub Actions CI (Ubuntu + macOS)

## Local Quickstart (Codespaces/Linux/macOS)
1) Install vcpkg (one-time):
```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh
export VCPKG_ROOT="$HOME/vcpkg"
