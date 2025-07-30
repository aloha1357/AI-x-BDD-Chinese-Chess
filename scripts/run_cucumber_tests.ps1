# Ultimate Cucumber Test Runner
Write-Host "?? Running Ultimate Cucumber Tests..." -ForegroundColor Green

# Build with Cucumber CMake
Write-Host "??儭?Building Cucumber tests..." -ForegroundColor Cyan
if (-not (Test-Path "build_cucumber")) {
    New-Item -Path "build_cucumber" -ItemType Directory | Out-Null
}

Set-Location "build_cucumber"
cmake .. -DCMAKE_TOOLCHAIN_FILE=..\vcpkg\scripts\buildsystems\vcpkg.cmake -f ..\CMakeLists_cucumber.txt
cmake --build . --config Release

# Run Cucumber tests
Write-Host "?妒 Executing Cucumber BDD tests..." -ForegroundColor Yellow
.\cucumber_tests.exe

# Generate professional report
Write-Host "?? Generating professional report..." -ForegroundColor Magenta
Set-Location ..
ruby .\generate_cucumber_report.rb

Write-Host "??Complete Cucumber test suite executed!" -ForegroundColor Green
Write-Host "?? Reports generated:" -ForegroundColor Cyan
Write-Host "   - cucumber_results.json (Raw data)" -ForegroundColor White
Write-Host "   - cucumber_report.html (Standard report)" -ForegroundColor White  
Write-Host "   - professional_cucumber_report.html (Enhanced report)" -ForegroundColor White
Write-Host "   - cucumber_junit.xml (CI/CD integration)" -ForegroundColor White

# Open the professional report
Start-Process "professional_cucumber_report.html"
