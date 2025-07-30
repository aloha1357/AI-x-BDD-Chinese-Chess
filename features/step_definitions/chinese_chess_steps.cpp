#include <gtest/gtest.h>
#include <regex>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include "game/Game.h"
#include "game/General.h"

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
        
        // Parse piece description like "Red General at (1, 5)"
        std::regex pieceRegex(R"((Red|Black)\s+(General|Guard|Rook|Horse|Cannon|Elephant|Soldier)\s+at\s+\((\d+),\s*(\d+)\))");
        std::smatch matches;
        
        if (std::regex_search(pieceDesc, matches, pieceRegex)) {
            Color color = (matches[1].str() == "Red") ? Color::RED : Color::BLACK;
            std::string pieceType = matches[2].str();
            int row = std::stoi(matches[3].str());
            int col = std::stoi(matches[4].str());
            Position pos(row, col);
            
            std::unique_ptr<Piece> piece;
            if (pieceType == "General") {
                piece = std::make_unique<General>(color);
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
