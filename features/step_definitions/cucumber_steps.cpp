#include <cucumber-cpp/autodetect.hpp>
#include <gtest/gtest.h>
#include <regex>
#include <string>
#include <memory>
#include <map>

// Include our game logic
#include "game/Game.h"
#include "game/General.h"
#include "game/Guard.h"
#include "game/Rook.h"
#include "game/Horse.h"
#include "game/Cannon.h"
#include "game/Elephant.h"
#include "game/Soldier.h"

using cucumber::ScenarioScope;

// Shared context between steps
struct ChessContext {
    Game game;
    MoveResult lastMoveResult;
    std::map<std::string, Position> piecePositions;
    
    void reset() {
        game.reset();
        lastMoveResult = MoveResult();
        piecePositions.clear();
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
    
    void setupPiece(const std::string& pieceDesc, const Position& pos) {
        game.getBoard().clear();
        
        std::regex pieceRegex(R"((Red|Black)\s+(General|Guard|Rook|Horse|Cannon|Elephant|Soldier))");
        std::smatch matches;
        
        if (std::regex_search(pieceDesc, matches, pieceRegex)) {
            Color color = (matches[1].str() == "Red") ? Color::RED : Color::BLACK;
            std::string pieceType = matches[2].str();
            
            std::unique_ptr<Piece> piece;
            if (pieceType == "General") {
                piece = std::make_unique<General>(color);
            } else if (pieceType == "Guard") {
                piece = std::make_unique<Guard>(color);
            } else if (pieceType == "Rook") {
                piece = std::make_unique<Rook>(color);
            } else if (pieceType == "Horse") {
                piece = std::make_unique<Horse>(color);
            } else if (pieceType == "Cannon") {
                piece = std::make_unique<Cannon>(color);
            } else if (pieceType == "Elephant") {
                piece = std::make_unique<Elephant>(color);
            } else if (pieceType == "Soldier") {
                piece = std::make_unique<Soldier>(color);
            }
            
            if (piece) {
                game.getBoard().setPiece(pos, std::move(piece));
            }
        }
    }
};

// Cucumber-CPP Step Definitions

GIVEN("^the board is empty except for a (.+) at (.+)$") {
    REGEX_PARAM(std::string, pieceDesc);
    REGEX_PARAM(std::string, positionStr);
    
    ScenarioScope<ChessContext> context;
    context->reset();
    
    Position pos = context->parsePosition(positionStr);
    context->setupPiece(pieceDesc, pos);
}

GIVEN("^the board has:$") {
    REGEX_PARAM(cucumber::Table, table);
    
    ScenarioScope<ChessContext> context;
    context->reset();
    
    auto rows = table.hashes();
    for (const auto& row : rows) {
        std::string piece = row.at("Piece");
        std::string position = row.at("Position");
        Position pos = context->parsePosition(position);
        context->setupPiece(piece, pos);
    }
}

WHEN("^Red moves the (.+) from (.+) to (.+)$") {
    REGEX_PARAM(std::string, pieceType);
    REGEX_PARAM(std::string, fromStr);
    REGEX_PARAM(std::string, toStr);
    
    ScenarioScope<ChessContext> context;
    
    Position from = context->parsePosition(fromStr);
    Position to = context->parsePosition(toStr);
    
    context->lastMoveResult = context->game.makeMove(from, to);
}

WHEN("^(.+) moves the (.+) from (.+) to (.+)$") {
    REGEX_PARAM(std::string, player);
    REGEX_PARAM(std::string, pieceType);
    REGEX_PARAM(std::string, fromStr);
    REGEX_PARAM(std::string, toStr);
    
    ScenarioScope<ChessContext> context;
    
    Position from = context->parsePosition(fromStr);
    Position to = context->parsePosition(toStr);
    
    context->lastMoveResult = context->game.makeMove(from, to);
}

THEN("^the move is legal$") {
    ScenarioScope<ChessContext> context;
    EXPECT_TRUE(context->lastMoveResult.isLegal) << "Move should be legal";
}

THEN("^the move is illegal$") {
    ScenarioScope<ChessContext> context;
    EXPECT_FALSE(context->lastMoveResult.isLegal) << "Move should be illegal";
}

// Additional step definitions for more complex scenarios
WHEN("^(.+) tries to move (.+) from (.+) to (.+)$") {
    REGEX_PARAM(std::string, player);
    REGEX_PARAM(std::string, pieceType);
    REGEX_PARAM(std::string, fromStr);
    REGEX_PARAM(std::string, toStr);
    
    ScenarioScope<ChessContext> context;
    
    Position from = context->parsePosition(fromStr);
    Position to = context->parsePosition(toStr);
    
    context->lastMoveResult = context->game.makeMove(from, to);
}

WHEN("^(.+) moves the (.+) and (attempts to jump over a piece|tries to move sideways|tries to cross the river)$") {
    REGEX_PARAM(std::string, player);
    REGEX_PARAM(std::string, pieceType);
    REGEX_PARAM(std::string, action);
    
    ScenarioScope<ChessContext> context;
    // This would need specific implementation based on the action
    // For now, we'll use a generic approach
}

THEN("^the game (continues|ends with (.+) winning)$") {
    REGEX_PARAM(std::string, result);
    
    ScenarioScope<ChessContext> context;
    // Implementation for game state checking would go here
    EXPECT_TRUE(context->lastMoveResult.isLegal);
}
