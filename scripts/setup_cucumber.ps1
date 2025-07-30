# Cucumber-CPP Quick Setup for Windows
# This script helps set up Cucumber-CPP integration

Write-Host "🥒 Setting up Cucumber-CPP Integration..." -ForegroundColor Green

# Check if vcpkg is available
$vcpkgPath = Get-Command vcpkg -ErrorAction SilentlyContinue
if (-not $vcpkgPath) {
    Write-Host "❌ vcpkg not found. Please install vcpkg first:" -ForegroundColor Red
    Write-Host "   1. git clone https://github.com/Microsoft/vcpkg.git" -ForegroundColor Yellow
    Write-Host "   2. cd vcpkg && .\bootstrap-vcpkg.bat" -ForegroundColor Yellow
    Write-Host "   3. .\vcpkg integrate install" -ForegroundColor Yellow
    Write-Host "   4. Add vcpkg to your PATH" -ForegroundColor Yellow
    exit 1
}

Write-Host "✅ vcpkg found at: $($vcpkgPath.Source)" -ForegroundColor Green

# Check if packages are installed
Write-Host "📦 Checking Cucumber-CPP dependencies..." -ForegroundColor Cyan

$packagesToInstall = @()

# Check for cucumber-cpp
try {
    $cucumberResult = vcpkg list | Select-String "cucumber-cpp"
    if (-not $cucumberResult) {
        $packagesToInstall += "cucumber-cpp:x64-windows"
    } else {
        Write-Host "✅ cucumber-cpp already installed" -ForegroundColor Green
    }
} catch {
    $packagesToInstall += "cucumber-cpp:x64-windows"
}

# Check for gtest
try {
    $gtestResult = vcpkg list | Select-String "gtest"
    if (-not $gtestResult) {
        $packagesToInstall += "gtest:x64-windows"
    } else {
        Write-Host "✅ gtest already installed" -ForegroundColor Green
    }
} catch {
    $packagesToInstall += "gtest:x64-windows"
}

# Install missing packages
if ($packagesToInstall.Count -gt 0) {
    Write-Host "📥 Installing missing packages: $($packagesToInstall -join ', ')" -ForegroundColor Yellow
    foreach ($package in $packagesToInstall) {
        Write-Host "Installing $package..." -ForegroundColor Cyan
        vcpkg install $package
        if ($LASTEXITCODE -ne 0) {
            Write-Host "❌ Failed to install $package" -ForegroundColor Red
            exit 1
        }
    }
    Write-Host "✅ All packages installed successfully!" -ForegroundColor Green
} else {
    Write-Host "✅ All required packages are already installed!" -ForegroundColor Green
}

# Check if Ruby is installed (needed for cucumber command)
$rubyPath = Get-Command ruby -ErrorAction SilentlyContinue
if (-not $rubyPath) {
    Write-Host "⚠️ Ruby not found. Installing Ruby..." -ForegroundColor Yellow
    Write-Host "Please install Ruby from: https://rubyinstaller.org/" -ForegroundColor Yellow
    Write-Host "After installing Ruby, run: gem install cucumber" -ForegroundColor Yellow
} else {
    Write-Host "✅ Ruby found at: $($rubyPath.Source)" -ForegroundColor Green
    
    # Check if cucumber gem is installed
    try {
        $gemList = gem list cucumber
        if ($gemList -match "cucumber") {
            Write-Host "✅ Cucumber gem already installed" -ForegroundColor Green
        } else {
            Write-Host "📥 Installing Cucumber gem..." -ForegroundColor Yellow
            gem install cucumber
        }
    } catch {
        Write-Host "📥 Installing Cucumber gem..." -ForegroundColor Yellow
        gem install cucumber
    }
}

# Backup current CMakeLists.txt
if (Test-Path "CMakeLists.txt") {
    Write-Host "💾 Backing up current CMakeLists.txt..." -ForegroundColor Cyan
    Copy-Item "CMakeLists.txt" "CMakeLists_original.txt" -Force
    Write-Host "✅ Backup saved as CMakeLists_original.txt" -ForegroundColor Green
}

# Create build directory for Cucumber
Write-Host "🏗️ Setting up build environment..." -ForegroundColor Cyan
if (Test-Path "build_cucumber") {
    Remove-Item "build_cucumber" -Recurse -Force
}
New-Item -ItemType Directory -Path "build_cucumber" | Out-Null

# Create a test script
$testScript = @"
#!/bin/bash
echo "🧪 Running Cucumber-CPP Tests..."

# Method 1: Run original tests for comparison
echo "Running original Google Test suite..."
cd build
./chinese_chess_tests.exe

# Method 2: Run Cucumber tests (when ready)
echo "To run Cucumber tests:"
echo "1. Build with: cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake"
echo "2. Run with: cucumber features/ --format html --out cucumber_report.html"

echo "✅ Test setup complete!"
"@

$testScript | Out-File -FilePath "run_cucumber_tests.sh" -Encoding UTF8

Write-Host "🎉 Cucumber-CPP setup complete!" -ForegroundColor Green
Write-Host "" -ForegroundColor White
Write-Host "📋 Next Steps:" -ForegroundColor Cyan
Write-Host "1. Read CUCUMBER_INTEGRATION.md for detailed instructions" -ForegroundColor White
Write-Host "2. Build the project with Cucumber support:" -ForegroundColor White
Write-Host "   cd build_cucumber" -ForegroundColor Yellow
Write-Host "   cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake" -ForegroundColor Yellow
Write-Host "   cmake --build ." -ForegroundColor Yellow
Write-Host "3. Run Cucumber tests:" -ForegroundColor White
Write-Host "   cucumber features/ --format html --out cucumber_report.html" -ForegroundColor Yellow
Write-Host "" -ForegroundColor White
Write-Host "🆚 Compare Results:" -ForegroundColor Cyan
Write-Host "• Original system: .\build\chinese_chess_tests.exe" -ForegroundColor White
Write-Host "• Cucumber system: cucumber features/" -ForegroundColor White
