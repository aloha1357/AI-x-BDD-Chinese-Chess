#pragma once
#include "Piece.h"

class Board; // Forward declaration

class Cannon : public Piece {
public:
    Cannon(Color color) : Piece(PieceType::CANNON, color) {}
    
    bool isValidMove(const Position& from, const Position& to) const override;
    bool isValidMoveWithBoard(const Position& from, const Position& to, const Board& board) const;
    
private:
    int countPiecesInPath(const Position& from, const Position& to, const Board& board) const;
};
