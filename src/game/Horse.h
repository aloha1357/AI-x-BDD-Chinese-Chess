#pragma once
#include "Piece.h"

class Board; // Forward declaration

class Horse : public Piece {
public:
    Horse(Color color) : Piece(PieceType::HORSE, color) {}
    
    bool isValidMove(const Position& from, const Position& to) const override;
    bool isValidMoveWithBoard(const Position& from, const Position& to, const Board& board) const;
    
private:
    Position getLegBlockPosition(const Position& from, const Position& to) const;
};
