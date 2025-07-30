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
│   └── step_definitions/      # C++ 步驟定義
├── 📁 cucumber_ruby/          # Ruby Cucumber 測試環境
│   ├── features/              # Cucumber 功能檔案
│   │   ├── chinese_chess.feature      # 複製的特性檔案
│   │   ├── step_definitions/          # Ruby 步驟定義
│   │   │   └── chess_steps.rb         # 象棋規則實現
│   │   └── support/
│   │       └── env.rb                 # 測試環境設定
├── 📁 cucumber_features/      # Cucumber-CPP 功能檔案
├── 📁 scripts/                # 核心腳本檔案
│   ├── run_cucumber_tests.ps1        # 執行 Cucumber 測試
│   ├── cucumber.yml                  # Cucumber 配置
│   └── generate_cucumber_report.rb   # Ruby 報告生成器
├── 📁 reports/                # 測試報告
│   ├── final_cucumber_report.html    # 最終 Cucumber HTML 報告
│   └── final_cucumber_results.json   # 最終 Cucumber JSON 結果
├── 📁 docs/                   # 文檔檔案
│   ├── ARCHITECTURE.md        # 架構文檔
│   ├── CUCUMBER_INTEGRATION.md # Cucumber 整合文檔
│   ├── DEVELOPMENT_GUIDE.md   # 開發指南
│   ├── DEVELOPMENT_PROGRESS.md # 開發進度與後續任務
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

### 2. 執行 Cucumber 測試並生成報告
```powershell
# 切換到 cucumber_ruby 目錄並執行測試
cd cucumber_ruby
cucumber --format html --out ../reports/final_cucumber_report.html --format json --out ../reports/final_cucumber_results.json --publish-quiet
cd ..
```

### 3. 查看報告
```powershell
# 在瀏覽器中打開報告
start reports/final_cucumber_report.html
```

## 📊 測試報告

| 報告名稱 | 檔案位置 | 描述 |
|----------|----------|------|
| 最終 Cucumber 報告 | `reports/final_cucumber_report.html` | 真正執行 Cucumber 測試後生成的官方報告 |
| Cucumber JSON 結果 | `reports/final_cucumber_results.json` | 標準 Cucumber 格式的測試結果數據 |

## 🧪 測試場景

目前共有 **22 個測試場景**，涵蓋中國象棋的所有核心規則：

### 測試覆蓋範圍
- ✅ **將軍 (General)** - 3 個場景 (3 通過)
  - 九宮內移動 (合法)
  - 九宮外移動 (違法)
  - 飛將規則 (違法)
- ✅ **士 (Guard)** - 2 個場景 (2 通過)
  - 九宮內斜移 (合法)
  - 直線移動 (違法)
- ✅ **車 (Rook)** - 2 個場景 (2 通過)
  - 直線移動 (合法)
  - 跳過棋子 (違法)
- ✅ **馬 (Horse)** - 2 個場景 (2 通過)
  - 日字移動 (合法)
  - 拐馬腳 (違法)
- ⚠️ **炮 (Cannon)** - 4 個場景 (3 通過, 1 失敗)
  - 空路移動 (合法)
  - 隔子捕獲 (合法)
  - 無子捕獲 (違法)
  - 多子阻擋 (違法) ⚠️
- ✅ **相 (Elephant)** - 3 個場景 (3 通過)
  - 田字移動 (合法)
  - 過河移動 (違法)
  - 塞象眼 (違法)
- ✅ **兵 (Soldier)** - 4 個場景 (4 通過)
  - 過河前前進 (合法)
  - 過河前橫移 (違法)
  - 過河後橫移 (合法)
  - 過河後後退 (違法)
- ✅ **勝負判定** - 2 個場景 (2 通過)
  - 捕獲將軍獲勝 (合法)
  - 捕獲其他棋子 (合法)

### 測試統計
- **總通過率: 95.5% (21/22)**
- **唯一失敗**: 炮的多屏障測試需要進一步調試

## 🛠️ 核心工具

### 執行腳本
- `scripts/run_cucumber_tests.ps1` - 執行 Cucumber 測試的便捷腳本

### 配置檔案
- `scripts/cucumber.yml` - Cucumber 測試配置
- `scripts/generate_cucumber_report.rb` - Ruby 報告生成器

### 測試環境
- `cucumber_ruby/` - 完整的 Ruby Cucumber 測試環境
- `features/` - 原始的 BDD 功能描述檔案

## 🎯 主要特色

1. **真實的 Cucumber 測試** - 使用標準 Ruby Cucumber 框架執行
2. **完整的象棋規則覆蓋** - 涵蓋所有棋子的移動規則
3. **官方 Cucumber 報告** - 生成標準的 HTML 和 JSON 格式報告
4. **高測試覆蓋率** - 95.5% 的測試通過率
5. **清晰的檔案結構** - 按功能分類組織的專案結構

## 📈 最新狀態

- ✅ 建立了真正的 Cucumber 測試環境
- ✅ 實現了 22 個完整的測試場景
- ✅ 生成了官方格式的測試報告
- ✅ 清理了專案結構，移除了實驗性檔案
- ⚠️ **剩餘問題**: 炮的多屏障測試需要修正 (詳見 [開發進度報告](docs/DEVELOPMENT_PROGRESS.md))

> 📋 **開發者注意**: 請查看 [`docs/DEVELOPMENT_PROGRESS.md`](docs/DEVELOPMENT_PROGRESS.md) 了解詳細的開發狀態、未解決問題和後續開發指南。

## 🚀 執行測試

要執行完整的測試套件：

```powershell
# 方法 1: 直接在 cucumber_ruby 目錄執行
cd cucumber_ruby
cucumber --format html --out ../reports/final_cucumber_report.html --format json --out ../reports/final_cucumber_results.json --publish-quiet

# 方法 2: 使用便捷腳本
.\scripts\run_cucumber_tests.ps1
```

執行後，您可以在 `reports/final_cucumber_report.html` 查看完整的測試報告。

## 🤝 貢獻

歡迎提交 Issue 和 Pull Request 來改進這個專案！特別是對於炮的多屏障測試場景的修正。
