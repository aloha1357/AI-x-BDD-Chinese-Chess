#pragma once
#include "Piece.h"

class General : public Piece {
public:
    General(Color color) : Piece(PieceType::GENERAL, color) {}
    
    bool isValidMove(const Position& from, const Position& to) const override;
    
private:
    bool isInPalace(const Position& pos) const;
};
