# Dynamic Test Report Generator
# This generates a report based on actual test execution results

Write-Host " Generating Dynamic Test Report..." -ForegroundColor Green

# Run tests and capture detailed output
$buildPath = ".\build\chinese_chess_tests.exe"
if (-not (Test-Path $buildPath)) {
    Write-Host " Test executable not found: $buildPath" -ForegroundColor Red
    exit 1
}

# Capture test output with timing and details
$testOutput = & $buildPath --gtest_output=xml:test_results.xml 2>&1
$testExitCode = $LASTEXITCODE

# Parse the actual test results
$passedCount = 0
$failedCount = 0
$testResults = @()

# Parse test output line by line
foreach ($line in $testOutput) {
    if ($line -match "\[\s+OK\s+\]\s+(.+?)\s+\((\d+)\s*ms\)") {
        $testResults += @{
            Name = $matches[1]
            Status = "PASSED"
            Duration = $matches[2]
        }
        $passedCount++
    }
    elseif ($line -match "\[\s+FAILED\s+\]\s+(.+?)\s+\((\d+)\s*ms\)") {
        $testResults += @{
            Name = $matches[1]
            Status = "FAILED"
            Duration = $matches[2]
        }
        $failedCount++
    }
}

$totalTests = $passedCount + $failedCount
$successRate = if ($totalTests -gt 0) { [math]::Round(($passedCount / $totalTests) * 100, 2) } else { 0 }

# Generate dynamic HTML report
$htmlContent = @"
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Chinese Chess BDD Test Report - Live Results</title>
    <style>
        body { font-family: 'Segoe UI', Arial, sans-serif; margin: 0; background: #f8f9fa; }
        .container { max-width: 1200px; margin: 0 auto; padding: 20px; }
        .header { background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; padding: 40px; border-radius: 15px; text-align: center; margin-bottom: 30px; }
        .status-badge { display: inline-block; padding: 8px 16px; border-radius: 20px; font-weight: bold; margin: 0 10px; }
        .status-passed { background: #28a745; color: white; }
        .status-failed { background: #dc3545; color: white; }
        .stats-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 20px; margin: 30px 0; }
        .stat-card { background: white; padding: 25px; border-radius: 10px; box-shadow: 0 4px 6px rgba(0,0,0,0.1); text-align: center; }
        .stat-number { font-size: 2.5em; font-weight: bold; margin-bottom: 10px; }
        .stat-passed { color: #28a745; }
        .stat-failed { color: #dc3545; }
        .stat-total { color: #007bff; }
        .test-list { background: white; border-radius: 10px; padding: 20px; box-shadow: 0 4px 6px rgba(0,0,0,0.1); }
        .test-item { display: flex; justify-content: space-between; align-items: center; padding: 15px; border-bottom: 1px solid #eee; }
        .test-item:last-child { border-bottom: none; }
        .test-name { font-weight: 500; color: #333; }
        .test-duration { color: #666; font-size: 0.9em; }
        .icon { font-size: 1.2em; margin-right: 10px; }
        .passed-icon { color: #28a745; }
        .failed-icon { color: #dc3545; }
        .timestamp { color: #666; font-size: 0.9em; margin-top: 10px; }
        .progress-bar { background: #e9ecef; height: 8px; border-radius: 4px; overflow: hidden; margin: 20px 0; }
        .progress-fill { height: 100%; background: linear-gradient(90deg, #28a745, #20c997); transition: width 0.3s ease; }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>Chinese Chess BDD Test Report</h1>
            <p>Live Test Execution Results</p>
            <div>
                <span class="status-badge status-passed">&check; $passedCount Passed</span>
                <span class="status-badge status-failed">&cross; $failedCount Failed</span>
            </div>
            <div class="timestamp">Executed: $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')</div>
        </div>

        <div class="stats-grid">
            <div class="stat-card">
                <div class="stat-number stat-total">$totalTests</div>
                <div>Total Tests</div>
            </div>
            <div class="stat-card">
                <div class="stat-number stat-passed">$passedCount</div>
                <div>Passed</div>
            </div>
            <div class="stat-card">
                <div class="stat-number stat-failed">$failedCount</div>
                <div>Failed</div>
            </div>
            <div class="stat-card">
                <div class="stat-number" style="color: #007bff;">$successRate%</div>
                <div>Success Rate</div>
            </div>
        </div>

        <div class="progress-bar">
            <div class="progress-fill" style="width: $successRate%;"></div>
        </div>

        <div class="test-list">
            <h2>Test Results Details</h2>
"@

# Add each test result
foreach ($test in $testResults) {
    $icon = if ($test.Status -eq "PASSED") { "&check;" } else { "&cross;" }
    $iconClass = if ($test.Status -eq "PASSED") { "passed-icon" } else { "failed-icon" }
    
    $htmlContent += @"
            <div class="test-item">
                <div>
                    <span class="icon $iconClass">$icon</span>
                    <span class="test-name">$($test.Name)</span>
                </div>
                <div class="test-duration">$($test.Duration)ms</div>
            </div>
"@
}

$htmlContent += @"
        </div>

        <div style="margin-top: 40px; padding: 20px; background: white; border-radius: 10px; text-align: center;">
            <h3>Project Information</h3>
            <p><strong>Framework:</strong> Custom BDD with Google Test (C++17)</p>
            <p><strong>Architecture:</strong> NOT standard Cucumber - Manual BDD implementation</p>
            <p><strong>Test Execution:</strong> Direct Google Test runner</p>
            <p><strong>Report Generation:</strong> Dynamic, based on actual test results</p>
        </div>
    </div>
</body>
</html>
"@

# Write the dynamic report
$htmlContent | Out-File -FilePath "dynamic_test_report.html" -Encoding UTF8

Write-Host " Dynamic test report generated: dynamic_test_report.html" -ForegroundColor Green
Write-Host " Tests executed: $totalTests | Passed: $passedCount | Failed: $failedCount" -ForegroundColor Cyan
Write-Host " Success rate: $successRate%" -ForegroundColor Yellow

if ($failedCount -gt 0) {
    Write-Host " Some tests failed. Check the report for details." -ForegroundColor Red
} else {
    Write-Host " All tests passed!" -ForegroundColor Green
}
