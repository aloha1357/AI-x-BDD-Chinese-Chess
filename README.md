# AI-x-BDD-Chinese-Chess

基於 AI 和行為驅動開發 (BDD) 的中國象棋專案

## 📁 專案結構

```
AI-x-BDD-Chinese-Chess/
├── 📁 src/                    # 核心源代碼
│   ├── game/                  # 遊戲邏輯
│   │   ├── Board.cpp/h        # 棋盤邏輯
│   │   ├── Game.cpp/h         # 遊戲主邏輯
│   │   ├── General.cpp/h      # 將軍棋子邏輯
│   │   └── Piece.h            # 棋子基類
│   └── ...
├── 📁 test/                   # 測試代碼
│   ├── main.cpp               # 測試主程式
│   ├── TestFramework.cpp/h    # 測試框架
│   └── ...
├── 📁 features/               # BDD 功能描述 (Gherkin)
│   ├── chinese_chess.feature  # 中國象棋規則特性
│   └── step_definitions/      # 步驟定義
├── 📁 cucumber_features/      # Cucumber-CPP 功能檔案
│   └── chinese_chess.feature  # 完整的 Cucumber 特性檔案
├── 📁 scripts/                # 所有腳本檔案
│   ├── setup_ultimate_cucumber.ps1  # 終極 Cucumber 設定
│   ├── setup_cucumber.ps1            # 基本 Cucumber 設定
│   ├── run_cucumber_tests.ps1        # 執行 Cucumber 測試
│   ├── generate_*.ps1                # 各種報告生成器
│   ├── check_status.ps1              # 狀態檢查
│   ├── cucumber.yml                  # Cucumber 配置
│   └── generate_cucumber_report.rb   # Ruby 報告生成器
├── 📁 reports/                # 所有生成的報告
│   ├── professional_cucumber_report.html  # 專業 Cucumber 報告
│   ├── perfect_cucumber_report.html       # 完美 Cucumber 報告
│   ├── cucumber_report.html               # 基本 Cucumber 報告
│   ├── dynamic_test_report.html           # 動態測試報告
│   ├── bdd_comparison.html                # BDD 比較報告
│   ├── scenarios_report_en.html           # 英文場景報告
│   ├── project_summary.html               # 專案摘要報告
│   ├── test_report.html                   # 測試報告
│   └── test_results.xml                   # XML 測試結果
├── 📁 docs/                   # 文檔檔案
│   ├── ARCHITECTURE.md        # 架構文檔
│   ├── CUCUMBER_INTEGRATION.md # Cucumber 整合文檔
│   ├── DEVELOPMENT_GUIDE.md   # 開發指南
│   ├── PROJECT_STATUS.md      # 專案狀態
│   ├── setup.md              # 設定說明
│   └── task.md               # 任務說明
├── 📁 build/                  # CMake 建置檔案
├── 📁 build_cucumber/         # Cucumber 建置檔案
├── 📁 vcpkg/                  # vcpkg 套件管理器
├── CMakeLists.txt             # CMake 主配置
├── CMakeLists_cucumber.txt    # Cucumber CMake 配置
└── README.md                  # 此檔案
```

## 🚀 快速開始

### 1. 基本測試
```powershell
# 執行基本測試
.\build\chinese_chess_tests.exe
```

### 2. 生成專業 Cucumber 報告
```powershell
# 生成專業報告（修復版，無圖表問題）
.\scripts\generate_cucumber_report.ps1
```

### 3. 設定完整 Cucumber-CPP 環境
```powershell
# 設定終極 Cucumber 環境
.\scripts\setup_ultimate_cucumber.ps1

# 執行 Cucumber 測試
.\scripts\run_cucumber_tests.ps1
```

## 📊 報告類型

| 報告名稱 | 檔案位置 | 描述 |
|----------|----------|------|
| 專業 Cucumber 報告 | `reports/professional_cucumber_report.html` | 具有互動式圖表和篩選功能 |
| 完美 Cucumber 報告 | `reports/perfect_cucumber_report.html` | 完整功能的 Cucumber 報告 |
| 動態測試報告 | `reports/dynamic_test_report.html` | 即時更新的測試報告 |
| BDD 比較報告 | `reports/bdd_comparison.html` | BDD 方法比較分析 |
| 英文場景報告 | `reports/scenarios_report_en.html` | 英文版本的場景報告 |

## 🧪 測試場景

目前共有 **22 個測試場景**，涵蓋：
- ✅ **將軍 (General)** - 3 個場景
- ✅ **士 (Guard)** - 2 個場景  
- ✅ **車 (Rook)** - 2 個場景
- ✅ **馬 (Horse)** - 2 個場景
- ✅ **炮 (Cannon)** - 4 個場景
- ✅ **相 (Elephant)** - 3 個場景
- ✅ **兵 (Soldier)** - 4 個場景
- ✅ **勝負判定** - 2 個場景

## 🛠️ 工具和腳本

### 設定腳本
- `setup_ultimate_cucumber.ps1` - 完整 Cucumber-CPP 環境設定
- `setup_cucumber.ps1` - 基本 Cucumber 設定

### 執行腳本
- `run_cucumber_tests.ps1` - 執行 Cucumber 測試
- `check_status.ps1` - 檢查專案狀態

### 報告生成器
- `generate_cucumber_report.ps1` - 專業 Cucumber 報告（修復版）
- `generate_perfect_report.ps1` - 完美報告生成器
- `generate_dynamic_report.ps1` - 動態報告生成器
- `generate_comparison.ps1` - BDD 比較報告
- `generate_english_report.ps1` - 英文報告生成器
- `generate_scenarios_report.ps1` - 場景報告生成器
- `generate_summary.ps1` - 摘要報告生成器

## 🎯 主要特色

1. **完整的 BDD 測試覆蓋** - 涵蓋所有象棋規則
2. **專業 Cucumber 報告** - 具有互動式圖表和篩選功能
3. **多語言支援** - 中文和英文報告
4. **CI/CD 整合** - 支援多種輸出格式
5. **即時視覺化** - 動態更新的測試狀態

## 📈 最新狀態

- ✅ 所有 22 個測試場景都能正確執行
- ✅ 專業 Cucumber 報告已修復圖表問題
- ✅ 檔案結構已完整整理
- ✅ 支援完整的 Cucumber-CPP 生態系統

## 🤝 貢獻

歡迎提交 Issue 和 Pull Request 來改進這個專案！
