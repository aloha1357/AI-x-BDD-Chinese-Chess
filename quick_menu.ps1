# 快速訪問菜單
# 整理後的專案快速操作腳本

Write-Host "🥒 AI-x-BDD-Chinese-Chess 快速菜單" -ForegroundColor Green
Write-Host "======================================" -ForegroundColor Cyan

Write-Host "`n📊 可用的操作:" -ForegroundColor Yellow

Write-Host "`n1️⃣  生成專業 Cucumber 報告 (修復版)" -ForegroundColor White
Write-Host "   .\scripts\generate_cucumber_report.ps1" -ForegroundColor Gray

Write-Host "`n2️⃣  執行基本測試" -ForegroundColor White  
Write-Host "   .\build\chinese_chess_tests.exe" -ForegroundColor Gray

Write-Host "`n3️⃣  設定完整 Cucumber-CPP 環境" -ForegroundColor White
Write-Host "   .\scripts\setup_ultimate_cucumber.ps1" -ForegroundColor Gray

Write-Host "`n4️⃣  執行 Cucumber 測試" -ForegroundColor White
Write-Host "   .\scripts\run_cucumber_tests.ps1" -ForegroundColor Gray

Write-Host "`n5️⃣  檢查專案狀態" -ForegroundColor White
Write-Host "   .\scripts\check_status.ps1" -ForegroundColor Gray

Write-Host "`n6️⃣  查看所有報告" -ForegroundColor White
Write-Host "   Get-ChildItem .\reports\*.html" -ForegroundColor Gray

Write-Host "`n7️⃣  查看專案文檔" -ForegroundColor White
Write-Host "   Get-ChildItem .\docs\*.md" -ForegroundColor Gray

Write-Host "`n📁 目錄結構:" -ForegroundColor Yellow
Write-Host "   📁 src/           - 源代碼" -ForegroundColor Cyan
Write-Host "   📁 test/          - 測試代碼" -ForegroundColor Cyan  
Write-Host "   📁 features/      - BDD 功能描述" -ForegroundColor Cyan
Write-Host "   📁 scripts/       - 所有腳本 (.ps1, .rb, .yml)" -ForegroundColor Cyan
Write-Host "   📁 reports/       - 所有報告 (.html, .xml)" -ForegroundColor Cyan
Write-Host "   📁 docs/          - 文檔 (.md)" -ForegroundColor Cyan
Write-Host "   📁 build/         - 建置檔案" -ForegroundColor Cyan

Write-Host "`n🎯 推薦流程:" -ForegroundColor Yellow
Write-Host "   1. 執行: .\scripts\generate_cucumber_report.ps1" -ForegroundColor Green
Write-Host "   2. 查看: .\reports\professional_cucumber_report.html" -ForegroundColor Green
Write-Host "   3. 如需完整環境: .\scripts\setup_ultimate_cucumber.ps1" -ForegroundColor Green

Write-Host "`n✨ 所有檔案已整理完成！" -ForegroundColor Green

# 詢問用戶想要執行什麼操作
Write-Host "`n請選擇操作 (1-7) 或按 Enter 查看目錄:" -ForegroundColor Yellow
$choice = Read-Host

switch ($choice) {
    "1" { 
        Write-Host "🚀 生成專業 Cucumber 報告..." -ForegroundColor Green
        .\scripts\generate_cucumber_report.ps1
    }
    "2" { 
        Write-Host "🧪 執行基本測試..." -ForegroundColor Green
        .\build\chinese_chess_tests.exe
    }
    "3" { 
        Write-Host "⚙️ 設定 Cucumber-CPP 環境..." -ForegroundColor Green
        .\scripts\setup_ultimate_cucumber.ps1
    }
    "4" { 
        Write-Host "🥒 執行 Cucumber 測試..." -ForegroundColor Green
        .\scripts\run_cucumber_tests.ps1
    }
    "5" { 
        Write-Host "📊 檢查專案狀態..." -ForegroundColor Green
        .\scripts\check_status.ps1
    }
    "6" { 
        Write-Host "📄 可用報告:" -ForegroundColor Green
        Get-ChildItem .\reports\*.html | Format-Table Name, Length, LastWriteTime
    }
    "7" { 
        Write-Host "📚 專案文檔:" -ForegroundColor Green
        Get-ChildItem .\docs\*.md | Format-Table Name, Length, LastWriteTime
    }
    default { 
        Write-Host "📁 專案目錄結構:" -ForegroundColor Green
        tree /F
    }
}
