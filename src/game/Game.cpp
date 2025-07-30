#include "Game.h"

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
    
    // Move is legal - for now just return true without actually moving
    // (We'll implement the actual move execution later)
    return MoveResult(true);
}

bool Game::isGameOver() const {
    // Placeholder implementation - will be filled during BDD cycle
    return false;
}
