#include "Game.h"
#include "Horse.h"
#include "Cannon.h"
#include "Elephant.h"
#include <algorithm>

Game::Game() : currentPlayer_(Color::RED) {
    reset();
}

void Game::reset() {
    board_.clear();
    currentPlayer_ = Color::RED;
}

MoveResult Game::makeMove(const Position& from, const Position& to) {
    // Check if there's a piece at the from position
    Piece* piece = board_.getPiece(from);
    if (!piece) {
        return MoveResult(false);
    }
    
    // Check if it's the correct player's piece
    if (piece->getColor() != currentPlayer_) {
        return MoveResult(false);
    }
    
    // Check if the move is valid for this piece type
    if (!piece->isValidMove(from, to)) {
        return MoveResult(false);
    }
    
    // Check if destination is within board bounds
    if (!board_.isValidPosition(to)) {
        return MoveResult(false);
    }
    
    // Check if destination has own piece (can't capture own piece)
    Piece* targetPiece = board_.getPiece(to);
    if (targetPiece && targetPiece->getColor() == currentPlayer_) {
        return MoveResult(false);
    }
    
    // Check path clearance for pieces that can't jump (Rook, Cannon)
    if (piece->getType() == PieceType::ROOK && !board_.isPathClear(from, to)) {
        return MoveResult(false);
    }
    
    // Check cannon jumping rules
    if (piece->getType() == PieceType::CANNON) {
        Cannon* cannon = static_cast<Cannon*>(piece);
        if (!cannon->isValidMoveWithBoard(from, to, board_)) {
            return MoveResult(false);
        }
    }
    
    // Check leg blocking for Horse
    if (piece->getType() == PieceType::HORSE) {
        Horse* horse = static_cast<Horse*>(piece);
        if (!horse->isValidMoveWithBoard(from, to, board_)) {
            return MoveResult(false);
        }
    }
    
    // Check elephant eye blocking for Elephant
    if (piece->getType() == PieceType::ELEPHANT) {
        Elephant* elephant = static_cast<Elephant*>(piece);
        if (!elephant->isValidMoveWithBoard(from, to, board_)) {
            return MoveResult(false);
        }
    }
    
    // Special rule for General: check if move would cause generals to face each other
    if (piece->getType() == PieceType::GENERAL && wouldGeneralsFaceEachOther(from, to)) {
        return MoveResult(false);
    }
    
    // Move is legal - for now just return true without actually moving
    // (We'll implement the actual move execution later)
    return MoveResult(true);
}

bool Game::isGameOver() const {
    // Placeholder implementation - will be filled during BDD cycle
    return false;
}

bool Game::wouldGeneralsFaceEachOther(const Position& from, const Position& to) const {
    // Find positions of both generals after the move
    Position redGeneralPos(0, 0);
    Position blackGeneralPos(0, 0);
    bool foundRed = false, foundBlack = false;
    
    // Search for generals on the board
    for (int row = 1; row <= 10; ++row) {
        for (int col = 1; col <= 9; ++col) {
            Position currentPos(row, col);
            Piece* piece = board_.getPiece(currentPos);
            
            if (piece && piece->getType() == PieceType::GENERAL) {
                // If this is the piece being moved, use the destination position
                Position finalPos = (currentPos == from) ? to : currentPos;
                
                if (piece->getColor() == Color::RED) {
                    redGeneralPos = finalPos;
                    foundRed = true;
                } else {
                    blackGeneralPos = finalPos;
                    foundBlack = true;
                }
            }
        }
    }
    
    // If both generals found and they're in the same column
    if (foundRed && foundBlack && redGeneralPos.col == blackGeneralPos.col) {
        // Check if there are no pieces between them
        return areGeneralsDirectlyFacing(redGeneralPos, blackGeneralPos, from, to);
    }
    
    return false;
}

bool Game::areGeneralsDirectlyFacing(const Position& redPos, const Position& blackPos, 
                                    const Position& moveFrom, const Position& moveTo) const {
    int minRow = std::min(redPos.row, blackPos.row);
    int maxRow = std::max(redPos.row, blackPos.row);
    
    // Check each position between the generals
    for (int row = minRow + 1; row < maxRow; ++row) {
        Position checkPos(row, redPos.col);
        
        // Skip the position we're moving from (it will be empty after the move)
        if (checkPos == moveFrom) {
            continue;
        }
        
        // If there's a piece at this position (and it's not being moved), 
        // then generals don't face each other
        if (board_.getPiece(checkPos) != nullptr) {
            return false;
        }
    }
    
    return true; // No pieces between generals
}
