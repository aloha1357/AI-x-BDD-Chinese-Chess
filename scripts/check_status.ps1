# 項目狀態檢查腳本 (PowerShell)
# 用於快速了解當前開發狀態

Write-Host "===========================================" -ForegroundColor Green
Write-Host "中國象棋 BDD 項目狀態檢查" -ForegroundColor Green  
Write-Host "===========================================" -ForegroundColor Green

Write-Host ""
Write-Host "📁 項目結構檢查：" -ForegroundColor Yellow
Write-Host "✅ CMakeLists.txt: $(if (Test-Path 'CMakeLists.txt') { '存在' } else { '❌ 缺失' })"
Write-Host "✅ src/game/: $(if (Test-Path 'src/game') { '存在' } else { '❌ 缺失' })"
Write-Host "✅ features/: $(if (Test-Path 'features') { '存在' } else { '❌ 缺失' })"
Write-Host "✅ build/: $(if (Test-Path 'build') { '存在' } else { '❌ 缺失' })"

Write-Host ""
Write-Host "🧪 測試文件檢查：" -ForegroundColor Yellow
Write-Host "✅ chinese_chess.feature: $(if (Test-Path 'features/chinese_chess.feature') { '存在' } else { '❌ 缺失' })"
Write-Host "✅ chinese_chess_steps.cpp: $(if (Test-Path 'features/step_definitions/chinese_chess_steps.cpp') { '存在' } else { '❌ 缺失' })"

Write-Host ""
Write-Host "🎯 已實作的棋子類別：" -ForegroundColor Yellow
Write-Host "✅ Piece.h: $(if (Test-Path 'src/game/Piece.h') { '存在' } else { '❌ 缺失' })"
Write-Host "✅ General: $(if ((Test-Path 'src/game/General.h') -and (Test-Path 'src/game/General.cpp')) { '完成' } else { '❌ 缺失' })"
Write-Host "❓ Guard: $(if ((Test-Path 'src/game/Guard.h') -and (Test-Path 'src/game/Guard.cpp')) { '完成' } else { '❌ 待實作' })"
Write-Host "❓ Rook: $(if ((Test-Path 'src/game/Rook.h') -and (Test-Path 'src/game/Rook.cpp')) { '完成' } else { '❌ 待實作' })"
Write-Host "❓ Horse: $(if ((Test-Path 'src/game/Horse.h') -and (Test-Path 'src/game/Horse.cpp')) { '完成' } else { '❌ 待實作' })"
Write-Host "❓ Cannon: $(if ((Test-Path 'src/game/Cannon.h') -and (Test-Path 'src/game/Cannon.cpp')) { '完成' } else { '❌ 待實作' })"
Write-Host "❓ Elephant: $(if ((Test-Path 'src/game/Elephant.h') -and (Test-Path 'src/game/Elephant.cpp')) { '完成' } else { '❌ 待實作' })"
Write-Host "❓ Soldier: $(if ((Test-Path 'src/game/Soldier.h') -and (Test-Path 'src/game/Soldier.cpp')) { '完成' } else { '❌ 待實作' })"

Write-Host ""
Write-Host "🔧 構建和測試：" -ForegroundColor Yellow

if (Test-Path "build") {
    Push-Location build
    Write-Host "正在構建項目..."
    
    try {
        $buildResult = cmake --build . 2>&1
        if ($LASTEXITCODE -eq 0) {
            Write-Host "✅ 構建成功" -ForegroundColor Green
            Write-Host ""
            Write-Host "🧪 運行測試：" -ForegroundColor Yellow
            
            if (Test-Path "chinese_chess_tests.exe") {
                & .\chinese_chess_tests.exe
            } else {
                Write-Host "❌ 找不到測試可執行文件" -ForegroundColor Red
            }
        } else {
            Write-Host "❌ 構建失敗" -ForegroundColor Red
            Write-Host $buildResult
        }
    }
    catch {
        Write-Host "❌ 構建過程中發生錯誤" -ForegroundColor Red
    }
    
    Pop-Location
} else {
    Write-Host "❌ build 目錄不存在，請先運行 cmake" -ForegroundColor Red
}

Write-Host ""
Write-Host "📋 下一步建議：" -ForegroundColor Cyan
Write-Host "1. 查看 DEVELOPMENT_GUIDE.md 了解詳細開發指南"
Write-Host "2. 檢查 features/chinese_chess.feature 了解待實作的 scenarios"
Write-Host "3. 按照 BDD 流程實作下一個 scenario：Guard 棋子"

Write-Host ""
Write-Host "🚀 快速開始命令：" -ForegroundColor Cyan
Write-Host "# 清理並重新構建："
Write-Host "Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue"
Write-Host "mkdir build; cd build; cmake ..; cmake --build ."
Write-Host ""
Write-Host "# 運行測試："
Write-Host ".\chinese_chess_tests.exe"

Write-Host ""
Write-Host "===========================================" -ForegroundColor Green
