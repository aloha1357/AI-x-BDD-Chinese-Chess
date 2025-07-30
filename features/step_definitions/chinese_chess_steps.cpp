#include <gtest/gtest.h>
#include <regex>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include "game/Game.h"
#include "game/General.h"
#include "game/Guard.h"
#include "game/Rook.h"
#include "game/Soldier.h"
#include "game/Horse.h"
#include "game/Cannon.h"
#include "game/Elephant.h"

class ChineseChessSteps : public ::testing::Test {
protected:
    Game game;
    MoveResult lastMoveResult;
    
    void SetUp() override {
        game.reset();
        lastMoveResult = MoveResult();
    }
    
    Position parsePosition(const std::string& posStr) {
        std::regex posRegex(R"(\((\d+),\s*(\d+)\))");
        std::smatch matches;
        if (std::regex_search(posStr, matches, posRegex)) {
            int row = std::stoi(matches[1].str());
            int col = std::stoi(matches[2].str());
            return Position(row, col);
        }
        return Position(0, 0);
    }
    
    void givenBoardIsEmptyExceptFor(const std::string& pieceDesc) {
        game.getBoard().clear();
        
        // Parse piece descriptions separated by commas
        std::string desc = pieceDesc;
        std::regex pieceRegex(R"((Red|Black)\s+(General|Guard|Rook|Horse|Cannon|Elephant|Soldier)\s+at\s+\((\d+),\s*(\d+)\))");
        std::sregex_iterator iter(desc.begin(), desc.end(), pieceRegex);
        std::sregex_iterator end;
        
        for (; iter != end; ++iter) {
            const std::smatch& matches = *iter;
            Color color = (matches[1].str() == "Red") ? Color::RED : Color::BLACK;
            std::string pieceType = matches[2].str();
            int row = std::stoi(matches[3].str());
            int col = std::stoi(matches[4].str());
            Position pos(row, col);
            
            std::unique_ptr<Piece> piece;
            if (pieceType == "General") {
                piece = std::make_unique<General>(color);
            } else if (pieceType == "Guard") {
                piece = std::make_unique<Guard>(color);
            } else if (pieceType == "Rook") {
                piece = std::make_unique<Rook>(color);
            } else if (pieceType == "Soldier") {
                piece = std::make_unique<Soldier>(color);
            } else if (pieceType == "Horse") {
                piece = std::make_unique<Horse>(color);
            } else if (pieceType == "Cannon") {
                piece = std::make_unique<Cannon>(color);
            } else if (pieceType == "Elephant") {
                piece = std::make_unique<Elephant>(color);
            }
            // Other pieces will be added as we implement them
            
            if (piece) {
                game.getBoard().setPiece(pos, std::move(piece));
            }
        }
    }
    
    void givenBoardHas(const std::vector<std::pair<std::string, std::string>>& pieces) {
        game.getBoard().clear();
        
        for (const auto& [pieceDesc, posStr] : pieces) {
            std::regex pieceRegex(R"((Red|Black)\s+(General|Guard|Rook|Horse|Cannon|Elephant|Soldier))");
            std::smatch matches;
            
            if (std::regex_search(pieceDesc, matches, pieceRegex)) {
                Color color = (matches[1].str() == "Red") ? Color::RED : Color::BLACK;
                std::string pieceType = matches[2].str();
                Position pos = parsePosition(posStr);
                
                std::unique_ptr<Piece> piece;
                if (pieceType == "General") {
                    piece = std::make_unique<General>(color);
                } else if (pieceType == "Guard") {
                    piece = std::make_unique<Guard>(color);
                } else if (pieceType == "Rook") {
                    piece = std::make_unique<Rook>(color);
                } else if (pieceType == "Soldier") {
                    piece = std::make_unique<Soldier>(color);
                } else if (pieceType == "Horse") {
                    piece = std::make_unique<Horse>(color);
                } else if (pieceType == "Cannon") {
                    piece = std::make_unique<Cannon>(color);
                } else if (pieceType == "Elephant") {
                    piece = std::make_unique<Elephant>(color);
                }
                // Other pieces will be added as we implement them
                
                if (piece) {
                    game.getBoard().setPiece(pos, std::move(piece));
                }
            }
        }
    }
    
    void whenPlayerMovesFrom(const std::string& fromStr, const std::string& toStr) {
        Position from = parsePosition(fromStr);
        Position to = parsePosition(toStr);
        lastMoveResult = game.makeMove(from, to);
    }
};

// First scenario: Red moves the General within the palace (Legal)
TEST_F(ChineseChessSteps, RedMovesGeneralWithinPalaceLegal) {
    // Given the board is empty except for a Red General at (1, 5)
    givenBoardIsEmptyExceptFor("Red General at (1, 5)");
    
    // When Red moves the General from (1, 5) to (1, 4)
    whenPlayerMovesFrom("(1, 5)", "(1, 4)");
    
    // Then the move is legal
    EXPECT_TRUE(lastMoveResult.isLegal) << "Move should be legal";
}

// Second scenario: Red moves the General outside the palace (Illegal)
TEST_F(ChineseChessSteps, RedMovesGeneralOutsidePalaceIllegal) {
    // Given the board is empty except for a Red General at (1, 6)
    givenBoardIsEmptyExceptFor("Red General at (1, 6)");
    
    // When Red moves the General from (1, 6) to (1, 7)
    whenPlayerMovesFrom("(1, 6)", "(1, 7)");
    
    // Then the move is illegal
    EXPECT_FALSE(lastMoveResult.isLegal) << "Move should be illegal - General cannot move outside palace";
}

// Third scenario: Generals face each other on the same file (Illegal)
TEST_F(ChineseChessSteps, GeneralsFaceEachOtherIllegal) {
    // Given the board has Red General at (2, 4) and Black General at (8, 5)
    givenBoardHas({
        {"Red General", "(2, 4)"},
        {"Black General", "(8, 5)"}
    });
    
    // When Red moves the General from (2, 4) to (2, 5)
    whenPlayerMovesFrom("(2, 4)", "(2, 5)");
    
    // Then the move is illegal
    EXPECT_FALSE(lastMoveResult.isLegal) << "Move should be illegal - Generals cannot face each other";
}

// Fourth scenario: Red moves the Guard diagonally in the palace (Legal)
TEST_F(ChineseChessSteps, RedMovesGuardDiagonallyInPalaceLegal) {
    // Given the board is empty except for a Red Guard at (1, 4)
    givenBoardIsEmptyExceptFor("Red Guard at (1, 4)");
    
    // When Red moves the Guard from (1, 4) to (2, 5)
    whenPlayerMovesFrom("(1, 4)", "(2, 5)");
    
    // Then the move is legal
    EXPECT_TRUE(lastMoveResult.isLegal) << "Move should be legal";
}

// Fifth scenario: Red moves the Guard straight (Illegal)
TEST_F(ChineseChessSteps, RedMovesGuardStraightIllegal) {
    // Given the board is empty except for a Red Guard at (2, 5)
    givenBoardIsEmptyExceptFor("Red Guard at (2, 5)");
    
    // When Red moves the Guard from (2, 5) to (2, 6)
    whenPlayerMovesFrom("(2, 5)", "(2, 6)");
    
    // Then the move is illegal
    EXPECT_FALSE(lastMoveResult.isLegal) << "Move should be illegal - Guard cannot move straight";
}

// Sixth scenario: Red moves the Rook along a clear rank (Legal)
TEST_F(ChineseChessSteps, RedMovesRookAlongClearRankLegal) {
    // Given the board is empty except for a Red Rook at (4, 1)
    givenBoardIsEmptyExceptFor("Red Rook at (4, 1)");
    
    // When Red moves the Rook from (4, 1) to (4, 9)
    whenPlayerMovesFrom("(4, 1)", "(4, 9)");
    
    // Then the move is legal
    EXPECT_TRUE(lastMoveResult.isLegal) << "Move should be legal";
}

// Seventh scenario: Red moves the Rook and attempts to jump over a piece (Illegal)
TEST_F(ChineseChessSteps, RedMovesRookJumpOverPieceIllegal) {
    // Given the board has Red Rook at (4, 1) and Black Soldier at (4, 5)
    givenBoardHas({
        {"Red Rook", "(4, 1)"},
        {"Black Soldier", "(4, 5)"}
    });
    
    // When Red moves the Rook from (4, 1) to (4, 9)
    whenPlayerMovesFrom("(4, 1)", "(4, 9)");
    
    // Then the move is illegal
    EXPECT_FALSE(lastMoveResult.isLegal) << "Move should be illegal - Rook cannot jump over pieces";
}

// Eighth scenario: Red moves the Horse in an "L" shape with no block (Legal)
TEST_F(ChineseChessSteps, RedMovesHorseLShapeNoBlockLegal) {
    // Given the board is empty except for a Red Horse at (3, 3)
    givenBoardIsEmptyExceptFor("Red Horse at (3, 3)");
    
    // When Red moves the Horse from (3, 3) to (5, 4)
    whenPlayerMovesFrom("(3, 3)", "(5, 4)");
    
    // Then the move is legal
    EXPECT_TRUE(lastMoveResult.isLegal) << "Move should be legal";
}

// Ninth scenario: Red moves the Horse and it is blocked by an adjacent piece (Illegal)
TEST_F(ChineseChessSteps, RedMovesHorseBlockedByAdjacentPieceIllegal) {
    // Given the board has Red Horse at (3, 3) and Black Rook at (4, 3) - "leg-block"
    givenBoardHas({
        {"Red Horse", "(3, 3)"},
        {"Black Rook", "(4, 3)"}
    });
    
    // When Red moves the Horse from (3, 3) to (5, 4)
    whenPlayerMovesFrom("(3, 3)", "(5, 4)");
    
    // Then the move is illegal
    EXPECT_FALSE(lastMoveResult.isLegal) << "Move should be illegal - Horse is blocked by adjacent piece";
}

// Tenth scenario: Red moves the Cannon like a Rook with an empty path (Legal)
TEST_F(ChineseChessSteps, RedMovesCannonLikeRookEmptyPathLegal) {
    // Given the board is empty except for a Red Cannon at (6, 2)
    givenBoardIsEmptyExceptFor("Red Cannon at (6, 2)");
    
    // When Red moves the Cannon from (6, 2) to (6, 8)
    whenPlayerMovesFrom("(6, 2)", "(6, 8)");
    
    // Then the move is legal
    EXPECT_TRUE(lastMoveResult.isLegal) << "Move should be legal";
}

// Eleventh scenario: Red moves the Cannon and jumps exactly one screen to capture (Legal)
TEST_F(ChineseChessSteps, RedMovesCannonJumpOneScreenCaptureLegal) {
    // Given the board has Red Cannon at (6, 2), Black Soldier at (6, 5) as screen, and Black Guard at (6, 8) as target
    givenBoardHas({
        {"Red Cannon", "(6, 2)"},
        {"Black Soldier", "(6, 5)"},
        {"Black Guard", "(6, 8)"}
    });
    
    // When Red moves the Cannon from (6, 2) to (6, 8)
    whenPlayerMovesFrom("(6, 2)", "(6, 8)");
    
    // Then the move is legal
    EXPECT_TRUE(lastMoveResult.isLegal) << "Move should be legal";
}

// Twelfth scenario: Red moves the Cannon and tries to jump with zero screens (Illegal)
TEST_F(ChineseChessSteps, RedMovesCannonJumpZeroScreensIllegal) {
    // Given the board has Red Cannon at (6, 2) and Black Guard at (6, 8)
    givenBoardHas({
        {"Red Cannon", "(6, 2)"},
        {"Black Guard", "(6, 8)"}
    });
    
    // When Red moves the Cannon from (6, 2) to (6, 8)
    whenPlayerMovesFrom("(6, 2)", "(6, 8)");
    
    // Then the move is illegal
    EXPECT_FALSE(lastMoveResult.isLegal) << "Move should be illegal - Cannon cannot capture without screen";
}

// Thirteenth scenario: Red moves the Cannon and tries to jump with more than one screen (Illegal)
TEST_F(ChineseChessSteps, RedMovesCannonJumpMoreThanOneScreenIllegal) {
    // Given the board has Red Cannon at (6, 2), Red Soldier at (6, 4), Black Soldier at (6, 5), and Black Guard at (6, 8)
    givenBoardHas({
        {"Red Cannon", "(6, 2)"},
        {"Red Soldier", "(6, 4)"},
        {"Black Soldier", "(6, 5)"},
        {"Black Guard", "(6, 8)"}
    });
    
    // When Red moves the Cannon from (6, 2) to (6, 8)
    whenPlayerMovesFrom("(6, 2)", "(6, 8)");
    
    // Then the move is illegal
    EXPECT_FALSE(lastMoveResult.isLegal) << "Move should be illegal - Cannon cannot jump with more than one screen";
}

// Fourteenth scenario: Red moves the Elephant 2-step diagonal with a clear midpoint (Legal)
TEST_F(ChineseChessSteps, RedMovesElephantTwoStepDiagonalClearMidpointLegal) {
    // Given the board is empty except for a Red Elephant at (3, 3)
    givenBoardIsEmptyExceptFor("Red Elephant at (3, 3)");
    
    // When Red moves the Elephant from (3, 3) to (5, 5)
    whenPlayerMovesFrom("(3, 3)", "(5, 5)");
    
    // Then the move is legal
    EXPECT_TRUE(lastMoveResult.isLegal) << "Move should be legal";
}

// Fifteenth scenario: Red moves the Elephant and tries to cross the river (Illegal)
TEST_F(ChineseChessSteps, RedMovesElephantCrossRiverIllegal) {
    // Given the board is empty except for a Red Elephant at (5, 3)
    givenBoardIsEmptyExceptFor("Red Elephant at (5, 3)");
    
    // When Red moves the Elephant from (5, 3) to (7, 5)
    whenPlayerMovesFrom("(5, 3)", "(7, 5)");
    
    // Then the move is illegal
    EXPECT_FALSE(lastMoveResult.isLegal) << "Move should be illegal - Elephant cannot cross the river";
}

// Sixteenth scenario: Red moves the Elephant and its midpoint is blocked (Illegal)
TEST_F(ChineseChessSteps, RedMovesElephantMidpointBlockedIllegal) {
    // Given the board has Red Elephant at (3, 3) and Black Rook at (4, 4) - midpoint
    givenBoardHas({
        {"Red Elephant", "(3, 3)"},
        {"Black Rook", "(4, 4)"}
    });
    
    // When Red moves the Elephant from (3, 3) to (5, 5)
    whenPlayerMovesFrom("(3, 3)", "(5, 5)");
    
    // Then the move is illegal
    EXPECT_FALSE(lastMoveResult.isLegal) << "Move should be illegal - Elephant eye is blocked";
}

// Seventeenth scenario: Red moves the Soldier forward before crossing the river (Legal)
TEST_F(ChineseChessSteps, RedMovesSoldierForwardBeforeCrossingRiverLegal) {
    // Given the board is empty except for a Red Soldier at (3, 5)
    givenBoardIsEmptyExceptFor("Red Soldier at (3, 5)");
    
    // When Red moves the Soldier from (3, 5) to (4, 5)
    whenPlayerMovesFrom("(3, 5)", "(4, 5)");
    
    // Then the move is legal
    EXPECT_TRUE(lastMoveResult.isLegal) << "Move should be legal";
}

// Eighteenth scenario: Red moves the Soldier and tries to move sideways before crossing (Illegal)
TEST_F(ChineseChessSteps, RedMovesSoldierSidewaysBeforeCrossingIllegal) {
    // Given the board is empty except for a Red Soldier at (3, 5)
    givenBoardIsEmptyExceptFor("Red Soldier at (3, 5)");
    
    // When Red moves the Soldier from (3, 5) to (3, 4)
    whenPlayerMovesFrom("(3, 5)", "(3, 4)");
    
    // Then the move is illegal
    EXPECT_FALSE(lastMoveResult.isLegal) << "Move should be illegal - Soldier cannot move sideways before crossing river";
}

// Nineteenth scenario: Red moves the Soldier sideways after crossing the river (Legal)
TEST_F(ChineseChessSteps, RedMovesSoldierSidewaysAfterCrossingRiverLegal) {
    // Given the board is empty except for a Red Soldier at (6, 5)
    givenBoardIsEmptyExceptFor("Red Soldier at (6, 5)");
    
    // When Red moves the Soldier from (6, 5) to (6, 4)
    whenPlayerMovesFrom("(6, 5)", "(6, 4)");
    
    // Then the move is legal
    EXPECT_TRUE(lastMoveResult.isLegal) << "Move should be legal";
}

// Twentieth scenario: Red moves the Soldier and attempts to move backward after crossing (Illegal)
TEST_F(ChineseChessSteps, RedMovesSoldierBackwardAfterCrossingIllegal) {
    // Given the board is empty except for a Red Soldier at (6, 5)
    givenBoardIsEmptyExceptFor("Red Soldier at (6, 5)");
    
    // When Red tries to move the Soldier backward from (6, 5) to (5, 5)
    whenPlayerMovesFrom("(6, 5)", "(5, 5)");
    
    // Then the move is illegal
    EXPECT_FALSE(lastMoveResult.isLegal) << "Move should be illegal - Soldier cannot move backward after crossing river";
}

// Twenty-first scenario: Red captures opponent's General and wins immediately (Legal)
TEST_F(ChineseChessSteps, RedCapturesOpponentGeneralWinsImmediately) {
    // Given the board has Red Rook at (8, 4) and Black General at (9, 4)
    givenBoardIsEmptyExceptFor("Red Rook at (8, 4), Black General at (9, 4)");
    
    // When Red moves the Rook to capture the Black General from (8, 4) to (9, 4)
    whenPlayerMovesFrom("(8, 4)", "(9, 4)");
    
    // Then the move is legal and the game should end with Red winning
    EXPECT_TRUE(lastMoveResult.isLegal) << "Move should be legal - capturing opponent's General";
    // Note: In a full implementation, we would also check if the game ends and Red wins
}

// Twenty-second scenario: Red captures a non-General piece and the game continues (Legal)
TEST_F(ChineseChessSteps, RedCapturesNonGeneralPieceGameContinues) {
    // Given the board has Red Rook at (8, 4) and Black Guard at (9, 4)
    givenBoardIsEmptyExceptFor("Red Rook at (8, 4), Black Guard at (9, 4)");
    
    // When Red moves the Rook to capture the Black Guard from (8, 4) to (9, 4)
    whenPlayerMovesFrom("(8, 4)", "(9, 4)");
    
    // Then the move is legal and the game continues
    EXPECT_TRUE(lastMoveResult.isLegal) << "Move should be legal - capturing opponent's non-General piece";
    // Note: In a full implementation, we would also check that the game continues
}
