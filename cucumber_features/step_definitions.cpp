#include <cucumber-cpp/autodetect.hpp>
#include <gtest/gtest.h>
#include <memory>
#include "../src/game/Game.h"
#include "../src/game/Board.h"

// Cucumber World for sharing state between steps
struct ChessWorld {
    std::unique_ptr<Game> game;
    bool lastMoveResult;
    std::string lastErrorMessage;
    Position fromPos, toPos;
    
    ChessWorld() : game(std::make_unique<Game>()), lastMoveResult(false) {}
};

// Background step - runs before each scenario
BEFORE() {
    ScenarioScope<ChessWorld> world;
    world->game = std::make_unique<Game>();
    world->lastMoveResult = false;
    world->lastErrorMessage.clear();
}

// Given steps
GIVEN("^a standard Chinese Chess board$") {
    ScenarioScope<ChessWorld> world;
    world->game->initializeBoard();
}

GIVEN("^pieces are in their starting positions$") {
    ScenarioScope<ChessWorld> world;
    world->game->resetToStartingPosition();
}

GIVEN("^the (Red|Black) (General|Guard|Rook|Horse|Cannon|Elephant|Soldier) is at position \\(([0-9]+), ([0-9]+)\\)$") {
    REGEX_PARAM(std::string, color);
    REGEX_PARAM(std::string, pieceType);
    REGEX_PARAM(int, row);
    REGEX_PARAM(int, col);
    
    ScenarioScope<ChessWorld> world;
    
    // Clear board and place specific piece
    world->game->clearBoard();
    PieceColor pieceColor = (color == "Red") ? PieceColor::RED : PieceColor::BLACK;
    
    if (pieceType == "General") {
        world->game->placePiece(std::make_unique<General>(pieceColor, Position(row, col)));
    } else if (pieceType == "Guard") {
        world->game->placePiece(std::make_unique<Guard>(pieceColor, Position(row, col)));
    } else if (pieceType == "Rook") {
        world->game->placePiece(std::make_unique<Rook>(pieceColor, Position(row, col)));
    } else if (pieceType == "Horse") {
        world->game->placePiece(std::make_unique<Horse>(pieceColor, Position(row, col)));
    } else if (pieceType == "Cannon") {
        world->game->placePiece(std::make_unique<Cannon>(pieceColor, Position(row, col)));
    } else if (pieceType == "Elephant") {
        world->game->placePiece(std::make_unique<Elephant>(pieceColor, Position(row, col)));
    } else if (pieceType == "Soldier") {
        world->game->placePiece(std::make_unique<Soldier>(pieceColor, Position(row, col)));
    }
}

GIVEN("^a (.*) is at \\(([0-9]+), ([0-9]+)\\)$") {
    REGEX_PARAM(std::string, pieceDesc);
    REGEX_PARAM(int, row);
    REGEX_PARAM(int, col);
    
    ScenarioScope<ChessWorld> world;
    // Parse piece description and place it
    // Implementation for additional piece placement
}

GIVEN("^there are no pieces between \\(([0-9]+), ([0-9]+)\\) and \\(([0-9]+), ([0-9]+)\\)$") {
    REGEX_PARAM(int, row1);
    REGEX_PARAM(int, col1);
    REGEX_PARAM(int, row2); 
    REGEX_PARAM(int, col2);
    
    ScenarioScope<ChessWorld> world;
    // Verify path is clear
    EXPECT_TRUE(world->game->isPathClear(Position(row1, col1), Position(row2, col2)));
}

GIVEN("^position \\(([0-9]+), ([0-9]+)\\) is empty$") {
    REGEX_PARAM(int, row);
    REGEX_PARAM(int, col);
    
    ScenarioScope<ChessWorld> world;
    world->game->removePieceAt(Position(row, col));
}

// When steps
WHEN("^the (General|Guard|Rook|Horse|Cannon|Elephant|Soldier) moves to \\(([0-9]+), ([0-9]+)\\)$") {
    REGEX_PARAM(std::string, pieceType);
    REGEX_PARAM(int, row);
    REGEX_PARAM(int, col);
    
    ScenarioScope<ChessWorld> world;
    world->toPos = Position(row, col);
    
    // Find the piece and attempt move
    auto piece = world->game->findPieceByType(pieceType);
    if (piece) {
        world->fromPos = piece->getPosition();
        world->lastMoveResult = world->game->makeMove(world->fromPos, world->toPos);
        if (!world->lastMoveResult) {
            world->lastErrorMessage = world->game->getLastError();
        }
    }
}

WHEN("^the (.*) attempts to move to \\(([0-9]+), ([0-9]+)\\)$") {
    REGEX_PARAM(std::string, pieceDesc);
    REGEX_PARAM(int, row);
    REGEX_PARAM(int, col);
    
    ScenarioScope<ChessWorld> world;
    // Same as above but explicitly for illegal moves
    world->toPos = Position(row, col);
    world->lastMoveResult = world->game->makeMove(world->fromPos, world->toPos);
    if (!world->lastMoveResult) {
        world->lastErrorMessage = world->game->getLastError();
    }
}

WHEN("^the (.*) captures the (.*) at \\(([0-9]+), ([0-9]+)\\)$") {
    REGEX_PARAM(std::string, attackingPiece);
    REGEX_PARAM(std::string, targetPiece);
    REGEX_PARAM(int, row);
    REGEX_PARAM(int, col);
    
    ScenarioScope<ChessWorld> world;
    world->toPos = Position(row, col);
    world->lastMoveResult = world->game->makeMove(world->fromPos, world->toPos);
}

// Then steps
THEN("^the move should be legal$") {
    ScenarioScope<ChessWorld> world;
    EXPECT_TRUE(world->lastMoveResult) << "Move should have been legal but was rejected";
}

THEN("^the move should be rejected$") {
    ScenarioScope<ChessWorld> world;
    EXPECT_FALSE(world->lastMoveResult) << "Move should have been rejected but was allowed";
}

THEN("^an error message should indicate \"(.*)\"$") {
    REGEX_PARAM(std::string, expectedError);
    
    ScenarioScope<ChessWorld> world;
    EXPECT_FALSE(world->lastMoveResult);
    EXPECT_THAT(world->lastErrorMessage, testing::HasSubstr(expectedError));
}

THEN("^the reason should be \"(.*)\"$") {
    REGEX_PARAM(std::string, expectedReason);
    
    ScenarioScope<ChessWorld> world;
    EXPECT_THAT(world->lastErrorMessage, testing::HasSubstr(expectedReason));
}

THEN("^the (.*) should be at \\(([0-9]+), ([0-9]+)\\)$") {
    REGEX_PARAM(std::string, pieceType);
    REGEX_PARAM(int, row);
    REGEX_PARAM(int, col);
    
    ScenarioScope<ChessWorld> world;
    auto piece = world->game->getPieceAt(Position(row, col));
    EXPECT_NE(piece, nullptr);
    // Additional verification for piece type
}

THEN("^the (.*) should be captured$") {
    REGEX_PARAM(std::string, pieceDesc);
    
    ScenarioScope<ChessWorld> world;
    // Verify piece was removed from board
    EXPECT_EQ(world->game->getPieceAt(world->toPos), nullptr);
}

THEN("^(Red|Black) should win immediately$") {
    REGEX_PARAM(std::string, color);
    
    ScenarioScope<ChessWorld> world;
    PieceColor winningColor = (color == "Red") ? PieceColor::RED : PieceColor::BLACK;
    EXPECT_TRUE(world->game->isGameOver());
    EXPECT_EQ(world->game->getWinner(), winningColor);
}

THEN("^the game should continue$") {
    ScenarioScope<ChessWorld> world;
    EXPECT_FALSE(world->game->isGameOver());
}

THEN("^the game should end$") {
    ScenarioScope<ChessWorld> world;
    EXPECT_TRUE(world->game->isGameOver());
}

THEN("^it should be (.*)\'s turn$") {
    REGEX_PARAM(std::string, color);
    
    ScenarioScope<ChessWorld> world;
    PieceColor expectedColor = (color == "Red") ? PieceColor::RED : PieceColor::BLACK;
    EXPECT_EQ(world->game->getCurrentPlayer(), expectedColor);
}
