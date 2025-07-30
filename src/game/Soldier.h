#pragma once
#include "Piece.h"

class Soldier : public Piece {
public:
    Soldier(Color color) : Piece(PieceType::SOLDIER, color) {}
    
    bool isValidMove(const Position& from, const Position& to) const override;
    
private:
    bool hasCrossedRiver(const Position& pos) const;
};
