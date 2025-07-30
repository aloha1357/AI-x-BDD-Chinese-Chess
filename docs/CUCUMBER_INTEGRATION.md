# Cucumber-CPP Integration Guide

## 🎯 Overview

This guide shows how to integrate **Cucumber-CPP** with our Chinese Chess project to get real Cucumber functionality with dynamic reporting.

## 📦 Prerequisites

### Windows Setup (Using vcpkg)

1. **Install vcpkg** (if not already installed):
```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
```

2. **Install Cucumber-CPP dependencies**:
```bash
# Install required packages
.\vcpkg install cucumber-cpp:x64-windows
.\vcpkg install gtest:x64-windows
.\vcpkg install boost:x64-windows
```

### Alternative: Manual Build

```bash
# Clone Cucumber-CPP
git clone https://github.com/cucumber/cucumber-cpp.git
cd cucumber-cpp

# Build with CMake
mkdir build && cd build
cmake .. -DCUKE_ENABLE_EXAMPLES=OFF
cmake --build . --config Release
cmake --install . --prefix /usr/local
```

## 🔧 Project Setup

### 1. Use Cucumber CMake Configuration

```bash
# Backup current CMakeLists.txt
cp CMakeLists.txt CMakeLists_original.txt

# Use Cucumber-enabled configuration
cp CMakeLists_cucumber.txt CMakeLists.txt
```

### 2. Build Cucumber Runner

```bash
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

### 3. Install Cucumber Ruby (for runner)

```bash
# Install Ruby and Cucumber
gem install cucumber
```

## 🚀 Running Cucumber Tests

### Method 1: Full Cucumber Suite
```bash
# Run all scenarios
cucumber features/

# Run specific tags
cucumber --tags @General features/
cucumber --tags @Guard features/
```

### Method 2: Direct Cucumber-CPP Runner
```bash
# Start the step definition server
./cucumber_runner &

# Run cucumber in another terminal
cucumber features/ --format html --out cucumber_report.html
```

## 📊 Cucumber Reports

### Built-in HTML Report
```bash
cucumber features/ --format html --out reports/cucumber_report.html
```

### JSON Report for CI/CD
```bash
cucumber features/ --format json --out reports/cucumber_report.json
```

### Multiple Formats
```bash
cucumber features/ \
  --format html --out reports/cucumber_report.html \
  --format json --out reports/cucumber_report.json \
  --format junit --out reports/cucumber_junit.xml
```

## 🎯 Comparison: Our Custom vs Cucumber-CPP

| Feature | Custom BDD | Cucumber-CPP |
|---------|------------|--------------|
| **Feature Parsing** | Manual | ✅ Automatic |
| **Step Mapping** | Manual | ✅ Automatic |
| **Reporting** | Custom HTML | ✅ Built-in HTML/JSON/JUnit |
| **CI/CD Integration** | Manual | ✅ Standard formats |
| **Tag Support** | No | ✅ Yes (@General, @Guard, etc.) |
| **Scenario Outline** | No | ✅ Yes |
| **Background Steps** | No | ✅ Yes |
| **Hooks** | No | ✅ Yes (Before/After) |
| **Performance** | Fast | Slightly slower |
| **Learning Curve** | Low | Medium |

## 📁 Project Structure with Cucumber-CPP

```
project/
├── features/
│   ├── chinese_chess.feature           # ✅ Used by Cucumber
│   └── step_definitions/
│       ├── cucumber_steps.cpp          # ✅ Real Cucumber steps
│       └── chinese_chess_steps.cpp     # ✅ Keep for comparison
├── src/game/                           # ✅ Shared game logic
├── reports/                            # ✅ Cucumber-generated reports
│   ├── cucumber_report.html
│   ├── cucumber_report.json
│   └── cucumber_junit.xml
└── CMakeLists.txt                      # ✅ Cucumber-enabled build
```

## 🔄 Migration Steps

### Step 1: Keep Both Systems
Run both systems in parallel to compare results:
```bash
# Traditional Google Test
./chinese_chess_tests

# New Cucumber-CPP
cucumber features/ --format html --out cucumber_report.html
```

### Step 2: Validate Equivalence
Ensure both systems pass the same scenarios with identical logic.

### Step 3: Choose Your Path
- **Keep Custom**: Faster, more control, easier debugging
- **Switch to Cucumber**: Standard reports, better CI/CD, ecosystem support

## 💡 Recommended Approach

1. **Implement Cucumber-CPP** as shown above
2. **Generate both reports** for comparison
3. **Keep the custom system** for development speed
4. **Use Cucumber** for formal reporting and CI/CD

## 🛠️ Quick Start Script

```bash
# Create a setup script
cat > setup_cucumber.sh << 'EOF'
#!/bin/bash
echo "Setting up Cucumber-CPP integration..."

# Install dependencies (adjust for your package manager)
# vcpkg install cucumber-cpp gtest boost

# Build project
mkdir -p build_cucumber
cd build_cucumber
cmake .. -f ../CMakeLists_cucumber.txt
cmake --build .

echo "✅ Cucumber-CPP setup complete!"
echo "Run: cucumber features/ --format html --out cucumber_report.html"
EOF

chmod +x setup_cucumber.sh
```

---

**With Cucumber-CPP, you'll get authentic Cucumber reports that automatically sync with your test execution!** 🎉
