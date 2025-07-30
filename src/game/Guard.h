#pragma once
#include "Piece.h"

class Guard : public Piece {
public:
    Guard(Color color) : Piece(PieceType::GUARD, color) {}
    
    bool isValidMove(const Position& from, const Position& to) const override;
    
private:
    bool isInPalace(const Position& pos) const;
};
