# 中國象棋 BDD 開發指南

## 項目概覽

這是一個使用 **行為驅動開發 (BDD)** 流程開發的中國象棋項目，採用 C++17、Google Test 和自定義的 BDD 測試框架。

### 技術棧
- **C++17**
- **Google Test** (gtest)
- **CMake ≥ 3.20**
- **自定義 BDD 測試框架**（類似 Cucumber）

### 項目結構
```
.
├── CMakeLists.txt              # CMake 配置文件
├── task.md                     # 原始需求文檔
├── DEVELOPMENT_GUIDE.md        # 本開發指南
├── src/                        # 源代碼目錄
│   └── game/                   # 遊戲邏輯
│       ├── Piece.h             # 棋子基類和通用定義
│       ├── General.h/.cpp      # 將軍類別
│       ├── Board.h/.cpp        # 棋盤類別
│       └── Game.h/.cpp         # 遊戲主邏輯
├── features/                   # BDD 特性文件
│   ├── chinese_chess.feature   # Gherkin 格式的測試場景
│   └── step_definitions/       # 測試步驟定義
│       └── chinese_chess_steps.cpp
├── test/                       # 測試相關
│   └── main.cpp               # 測試主程序
└── build/                     # 構建目錄
    └── chinese_chess_tests.exe # 可執行測試程序
```

## 當前開發狀態

### ✅ 已完成功能

#### 1. 基礎框架
- **Cucumber Walking Skeleton** 已建立並正常運行
- **CMake 構建系統** 配置完成，支持 Google Test
- **基礎類別架構** 已建立（Piece, Board, Game）

#### 2. General（將軍）規則 - 3 scenarios 完成
- ✅ **Red moves the General within the palace (Legal)** - 宮內移動
- ✅ **Red moves the General outside the palace (Illegal)** - 宮外移動限制
- ✅ **Generals face each other on the same file (Illegal)** - 將帥相望規則

### 🔄 當前測試狀態
```bash
[  PASSED  ] 3 tests.
```

### 📋 待開發功能
根據 `features/chinese_chess.feature`，接下來需要實作的 scenarios：

#### 2. Guard（士）- 2 scenarios
- ❌ Red moves the Guard diagonally in the palace (Legal)
- ❌ Red moves the Guard straight (Illegal)

#### 3. Rook（車）- 2 scenarios  
- ❌ Red moves the Rook along a clear rank (Legal)
- ❌ Red moves the Rook and attempts to jump over a piece (Illegal)

#### 4. Horse（馬）- 2 scenarios
- ❌ Red moves the Horse in an "L" shape with no block (Legal) 
- ❌ Red moves the Horse and it is blocked by an adjacent piece (Illegal)

#### 5. Cannon（炮）- 4 scenarios
- ❌ Red moves the Cannon like a Rook with an empty path (Legal)
- ❌ Red moves the Cannon and jumps exactly one screen to capture (Legal)
- ❌ Red moves the Cannon and tries to jump with zero screens (Illegal)
- ❌ Red moves the Cannon and tries to jump with more than one screen (Illegal)

#### 6. Elephant（相）- 3 scenarios
- ❌ Red moves the Elephant 2-step diagonal with a clear midpoint (Legal)
- ❌ Red moves the Elephant and tries to cross the river (Illegal)
- ❌ Red moves the Elephant and its midpoint is blocked (Illegal)

#### 7. Soldier（兵）- 3 scenarios
- ❌ Red moves the Soldier forward before crossing the river (Legal)
- ❌ Red moves the Soldier and tries to move sideways before crossing (Illegal)
- ❌ Red moves the Soldier sideways after crossing the river (Legal)

## 嚴格的 BDD 開發流程

### ⚠️ 重要原則
1. **一次只開發一個 scenario**
2. **嚴格遵守紅-綠-重構循環**
3. **不得跳過任何步驟**
4. **不得預先實作未測試的代碼**

### 開發步驟（每個 scenario 必須重複）

#### A. 撰寫步驟並驗證失敗 🔴
1. **選擇下一個 scenario**（按照 feature 文件順序）
2. **在 `chinese_chess_steps.cpp` 中添加新的 TEST_F**
3. **實作 Steps（given, when, then）**，但類別行為留空
4. **編譯並運行測試**
5. **確認測試失敗**，且失敗原因是期望值錯誤（不是框架錯誤）

#### B. 實作並讓測試轉綠燈 🟢
1. **在 `src/game/` 實作必要的類別和方法**
2. **編譯並運行測試**
3. **確認測試通過**
4. **覆述當前通過的測試數量**（例如：4 tests PASSED）

#### C. 重構 & 回歸 🔄
1. **按 Clean Code 原則重構代碼**
2. **重新運行所有測試**
3. **確保所有測試仍然通過**

## 如何繼續開發

### 1. 環境準備
```bash
# 確保在項目根目錄
cd c:\Users\aloha\Documents\GitHub\AI-x-BDD-Chinese-Chess

# 清理並重新構建
Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue
mkdir build
cd build
cmake ..
cmake --build .

# 運行當前測試確認狀態
.\chinese_chess_tests.exe
```

### 2. 下一步開發：Guard（士）

#### A. 添加 Guard 測試（步驟 A）
在 `features/step_definitions/chinese_chess_steps.cpp` 中添加：

```cpp
// Fourth scenario: Red moves the Guard diagonally in the palace (Legal)
TEST_F(ChineseChessSteps, RedMovesGuardDiagonallyInPalaceLegal) {
    // Given the board is empty except for a Red Guard at (1, 4)
    givenBoardIsEmptyExceptFor("Red Guard at (1, 4)");
    
    // When Red moves the Guard from (1, 4) to (2, 5)
    whenPlayerMovesFrom("(1, 4)", "(2, 5)");
    
    // Then the move is legal
    EXPECT_TRUE(lastMoveResult.isLegal) << "Move should be legal";
}
```

#### B. 創建 Guard 類別
創建 `src/game/Guard.h` 和 `src/game/Guard.cpp`

#### C. 更新 givenBoardIsEmptyExceptFor 方法
在 `chinese_chess_steps.cpp` 中添加 Guard 的創建邏輯

### 3. 重要的實作細節

#### 棋盤座標系統
- **9×10 棋盤**：9 列（col）× 10 行（row）
- **座標系統**：(row, col)，基於 1 的索引
- **Row 1**：紅方底線，**Row 10**：黑方底線
- **Column 1**：最左列，**Column 9**：最右列

#### 宮區定義
- **紅方宮區**：rows 1-3, cols 4-6
- **黑方宮區**：rows 8-10, cols 4-6

#### 河界定義
- **河界**：row 5（紅方） 和 row 6（黑方）之間

## 代碼架構說明

### 核心類別

#### `Piece` (基類)
```cpp
class Piece {
    PieceType type_;
    Color color_;
public:
    virtual bool isValidMove(const Position& from, const Position& to) const = 0;
    Color getColor() const;
    PieceType getType() const;
};
```

#### `Board`
```cpp
class Board {
    std::array<std::array<std::unique_ptr<Piece>, 9>, 10> grid_;
public:
    void setPiece(const Position& pos, std::unique_ptr<Piece> piece);
    Piece* getPiece(const Position& pos) const;
    bool isEmpty(const Position& pos) const;
    bool isValidPosition(const Position& pos) const;
};
```

#### `Game`
```cpp
class Game {
    Board board_;
    Color currentPlayer_;
public:
    MoveResult makeMove(const Position& from, const Position& to);
    bool wouldGeneralsFaceEachOther(const Position& from, const Position& to) const;
};
```

### 測試架構

#### `ChineseChessSteps` 測試類
```cpp
class ChineseChessSteps : public ::testing::Test {
protected:
    Game game;
    MoveResult lastMoveResult;
    
    void givenBoardIsEmptyExceptFor(const std::string& pieceDesc);
    void whenPlayerMovesFrom(const std::string& fromStr, const std::string& toStr);
    Position parsePosition(const std::string& posStr);
};
```

## 構建和測試命令

### Windows PowerShell 命令
```bash
# 構建
cd build
cmake --build .

# 運行測試
.\chinese_chess_tests.exe

# 清理重構建
cd ..
Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue
mkdir build
cd build
cmake ..
cmake --build .
```

## 常見問題和注意事項

### 1. 棋子創建模式
每個新棋子類別都需要：
- 繼承 `Piece` 類別
- 實作 `isValidMove` 方法
- 在 `givenBoardIsEmptyExceptFor` 中添加創建邏輯

### 2. 移動驗證流程
```
Game::makeMove() → 
    檢查棋子存在 → 
    檢查玩家回合 → 
    Piece::isValidMove() → 
    檢查目標位置 → 
    檢查特殊規則（如將帥相望）
```

### 3. 測試命名規則
- 測試方法名：`{棋子}{動作}{結果}`
- 例如：`RedMovesGeneralWithinPalaceLegal`

### 4. 失敗時的檢查清單
- [ ] 編譯是否成功？
- [ ] 測試是否被執行？
- [ ] 失敗原因是期望值錯誤還是框架錯誤？
- [ ] 是否遵循了 BDD 流程？

## 項目目標

最終目標是完成 `features/chinese_chess.feature` 中的所有 scenarios，建立一個完整的中國象棋規則驗證系統。每個 scenario 的實作都必須嚴格遵循 BDD 流程，確保代碼質量和測試覆蓋率。

---

**記住：嚴格遵循 BDD 流程，一次只實作一個 scenario，紅-綠-重構，不要跳步！**
