# VolLab Terminal

A professional C++20 scaffold for a quant/market-data terminal.

## Stage 0 includes
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
````

2. Configure + build + test:

```bash
cmake -S . -B build -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"

cmake --build build
ctest --test-dir build --output-on-failure
```






