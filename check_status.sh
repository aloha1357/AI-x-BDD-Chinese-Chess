#!/bin/bash
# 項目狀態檢查腳本
# 用於快速了解當前開發狀態

echo "=========================================="
echo "中國象棋 BDD 項目狀態檢查"
echo "=========================================="

echo ""
echo "📁 項目結構檢查："
echo "✅ CMakeLists.txt: $(test -f CMakeLists.txt && echo '存在' || echo '❌ 缺失')"
echo "✅ src/game/: $(test -d src/game && echo '存在' || echo '❌ 缺失')"
echo "✅ features/: $(test -d features && echo '存在' || echo '❌ 缺失')"
echo "✅ build/: $(test -d build && echo '存在' || echo '❌ 缺失')"

echo ""
echo "🧪 測試文件檢查："
echo "✅ chinese_chess.feature: $(test -f features/chinese_chess.feature && echo '存在' || echo '❌ 缺失')"
echo "✅ chinese_chess_steps.cpp: $(test -f features/step_definitions/chinese_chess_steps.cpp && echo '存在' || echo '❌ 缺失')"

echo ""
echo "🎯 已實作的棋子類別："
echo "✅ Piece.h: $(test -f src/game/Piece.h && echo '存在' || echo '❌ 缺失')"
echo "✅ General: $(test -f src/game/General.h && test -f src/game/General.cpp && echo '存在' || echo '❌ 缺失')"
echo "❓ Guard: $(test -f src/game/Guard.h && test -f src/game/Guard.cpp && echo '存在' || echo '❌ 待實作')"
echo "❓ Rook: $(test -f src/game/Rook.h && test -f src/game/Rook.cpp && echo '存在' || echo '❌ 待實作')"
echo "❓ Horse: $(test -f src/game/Horse.h && test -f src/game/Horse.cpp && echo '存在' || echo '❌ 待實作')"
echo "❓ Cannon: $(test -f src/game/Cannon.h && test -f src/game/Cannon.cpp && echo '存在' || echo '❌ 待實作')"
echo "❓ Elephant: $(test -f src/game/Elephant.h && test -f src/game/Elephant.cpp && echo '存在' || echo '❌ 待實作')"
echo "❓ Soldier: $(test -f src/game/Soldier.h && test -f src/game/Soldier.cpp && echo '存在' || echo '❌ 待實作')"

echo ""
echo "🔧 構建和測試："
if [ -d "build" ]; then
    cd build
    echo "正在構建項目..."
    if cmake --build . > /dev/null 2>&1; then
        echo "✅ 構建成功"
        echo ""
        echo "🧪 運行測試："
        if [ -f "chinese_chess_tests.exe" ]; then
            ./chinese_chess_tests.exe
        elif [ -f "chinese_chess_tests" ]; then
            ./chinese_chess_tests
        else
            echo "❌ 找不到測試可執行文件"
        fi
    else
        echo "❌ 構建失敗"
    fi
    cd ..
else
    echo "❌ build 目錄不存在，請先運行 cmake"
fi

echo ""
echo "📋 下一步建議："
echo "1. 查看 DEVELOPMENT_GUIDE.md 了解詳細開發指南"
echo "2. 檢查 features/chinese_chess.feature 了解待實作的 scenarios"
echo "3. 按照 BDD 流程實作下一個 scenario：Guard 棋子"
echo ""
echo "=========================================="
