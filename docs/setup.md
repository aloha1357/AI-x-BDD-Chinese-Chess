# Development Environment Setup

本專案以 **C++17 + Google Test + cucumber‑cpp + CMake ≥ 3.20** 為基礎。若你已安裝 CMake 與支援 C++17 的編譯器，仍需準備 **兩個測試相關框架**：

| 元件                      | 作用                                             | 安裝選項                                            |
| ----------------------- | ---------------------------------------------- | ----------------------------------------------- |
| **Google Test (gtest)** | 原生單元測試執行器；cucumber‑cpp 亦以它為後端                  | apt / brew / vcpkg / Conan / CMake FetchContent |
| **cucumber‑cpp**        | Gherkin 步驟 → gtest 橋接，讓 `*.feature` 能驅動 C++ 代碼 | vcpkg / Conan / 源碼編譯                            |

---

## 1 ⋯ 安裝 Google Test

### A. 以 **FetchContent** 嵌入（推薦，跨平台）

在你的 `CMakeLists.txt` <sup>top‑level</sup> 加入：

```cmake
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# v1.14.0 支援 C++17
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # Windows-MSVCRT fix
FetchContent_MakeAvailable(googletest)
```

CMake 會自動下載、建構並提供 `gtest_main`、`gtest` target。

### B. 直接安裝

| OS                   | 指令                                                                                                                                                      |
| -------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Ubuntu 22.04**     | `sudo apt-get install libgtest-dev && sudo apt-get install cmake && cd /usr/src/googletest && sudo cmake -DBUILD_SHARED_LIBS=ON . && sudo make install` |
| **macOS (Homebrew)** | `brew install googletest`                                                                                                                               |
| **Windows (vcpkg)**  | `vcpkg install gtest`                                                                                                                                   |

---

## 2 ⋯ 安裝 cucumber‑cpp

### A. 使用 **vcpkg**

```bash
# 假設 vcpkg 已設定三方 toolchain
vcpkg install cucumber-cpp
```

安裝完成後在 CMake 設定：

```cmake
find_package(cucumber-cpp CONFIG REQUIRED)
```

### B. 以 **Conan**

`conanfile.txt`：

```
[requires]
cucumber-cpp/0.5

[generators]
CMakeDeps
CMakeToolchain
```

然後：

```bash
conan install . --output-folder=build --build=missing
```

### C. 源碼編譯

```bash
git clone https://github.com/cucumber/cucumber-cpp.git
cd cucumber-cpp && mkdir build && cd build
cmake -DCMAKE_CXX_STANDARD=17 -DUSE_GTEST=on ..
make -j$(nproc)
sudo make install   # /usr/local by default
```

> **提示**：需先裝好 Boost、gtest；`-DUSE_GTEST=on` 指定後端。

---

## 3 ⋯ 專案 CMake 快速範例

```cmake
cmake_minimum_required(VERSION 3.20)
project(ChineseChess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 引入 GoogleTest
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
FetchContent_MakeAvailable(googletest)

# cucumber‑cpp
find_package(cucumber-cpp CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(features)
```

`features/CMakeLists.txt`:

```cmake
cucumber_add_features(ChineseChessFeature
  TEST_TARGET_NAME chinese_chess_steps   # 你的 step 定義 target
  FEATURE_FILES chinese_chess.feature
  # 其他選項…
)
```

---

## 4 ⋯ 驗證安裝

```bash
mkdir build && cd build
cmake -S .. -B . -DCMAKE_TOOLCHAIN_FILE=<vcpkg>/scripts/buildsystems/vcpkg.cmake # 若用 vcpkg
cmake --build . -j
ctest --output-on-failure    # 或直接執行 cucumber 命令
```

若你看到 **cucumber** 執行並報告至少一個紅燈 Scenario，即代表骨架搭建成功！

---

## 常見問題 (FAQ)

| 症狀                         | 可能原因 / 解法                                                   |
| -------------------------- | ----------------------------------------------------------- |
| 找不到 `libgtest.so`          | 未 `make install` 或未加入 to CMake target\_link\_libraries      |
| `cucumber` 執行但 0 scenarios | `cucumber_add_features` 無正確指向 `.feature` 檔                  |
| Windows 下連結錯誤 LNK2019      | 忘記 `set(gtest_force_shared_crt ON ...)` 或 MD/MT runtime 不一致 |

