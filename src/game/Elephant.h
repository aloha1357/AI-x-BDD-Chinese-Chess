#pragma once
#include "Piece.h"

class Board; // Forward declaration

class Elephant : public Piece {
public:
    Elephant(Color color) : Piece(PieceType::ELEPHANT, color) {}
    
    bool isValidMove(const Position& from, const Position& to) const override;
    bool isValidMoveWithBoard(const Position& from, const Position& to, const Board& board) const;
    
private:
    bool canCrossRiver(const Position& pos) const;
    Position getMidpoint(const Position& from, const Position& to) const;
};
