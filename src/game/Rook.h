#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
    Rook(Color color) : Piece(PieceType::ROOK, color) {}
    
    bool isValidMove(const Position& from, const Position& to) const override;
};
