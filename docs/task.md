# Task

請你嚴格遵照**行為驅動開發 (BDD)** 流程，完成 **`features/chinese_chess.feature`** 內全部驗收情境。
不得同時進行 BDD 流程中多個步驟，也不得跳過任何一步；須逐步確認每一步執行結果。

## Context

### Domain & Design Guideline

* 棋盤為 9×10 座標系；採 (row, col)，Row 1 在紅方底線，Row 10 在黑方底線。
* 參考 ERD：@ERD.png 與 OOD：@OOD.png，但你可視需要增減類別／屬性／行為。
* **棋局規則** 以 `chinese_chess.feature` 為準，包括宮區、河界、馬腿、炮架、將帥相望等細節。

### Tech Stack

1. **C++17**
2. **cucumber-cpp**（Gherkin）
3. **Google Test** (gtest)
4. **CMake ≥ 3.20**

### Application Environment

```
.  
├── CMakeLists.txt  
├── src/  
│   ├── game/  
│   └── …  
├── features/  
│   ├── chinese_chess.feature  
│   └── step_definitions/  
└── test/
```

## BDD 開發流程

1. **建立 Cucumber Walking Skeleton**

   * 以最小可行專案讓 `cucumber` 成功驅動 `gtest`，且至少一個 Scenario 被執行到。
   * 確認 `cucumber` 離開碼為 **1**（紅燈）。

2. **一次實作一個 Scenario（最小增量）**
   針對八大區塊依序處理每個 Scenario，並重覆 **A→B→C**：

   **A. 撰寫步驟並驗證失敗**

   * 僅啟用當前 Scenario，其餘以 `@ignore` 或 `DISABLED_` 暫停。
   * Steps 先宣告介面、留空實作；執行後應因斷言失敗而紅燈。

   **B. 實作並讓測試轉綠燈**

   * 在 `src/` 實作必要類別與方法，使 Scenario 通過並覆述 *passed/total*。

   **C. 重構 & 回歸**

   * 按 clean‑code 原則重構；重跑測試確保仍綠燈。

> **注意**
>
> * 僅當前 Scenario 綠燈後，才可解鎖下一個。
> * 棋規驗證流：`MoveValidator` → `Board` → `Piece`。
> * 嚴格測試驅動，不得預先實作未覆蓋程式碼。

## 關鍵點速覽

| 面向    | 作法                                      | 補充               |
| ----- | --------------------------------------- | ---------------- |
| 棋盤結構  | `Piece* grid[10][9]` 或 `std::array`     | 介面 1‑based       |
| 位置合法性 | 單獨 `RuleSet` 檢查宮、河、象眼、馬腿…               | 易測試              |
| 步驟定義  | `BoardSteps::givenBoardIsEmptyExcept` … | 用 regex 擷取座標     |
| 勝負判定  | `Game::checkEnd()`                      | 判斷 win/stalemate |
