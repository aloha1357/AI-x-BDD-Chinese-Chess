#pragma once
#include "Piece.h"
#include <array>
#include <memory>

class Board {
private:
    std::array<std::array<std::unique_ptr<Piece>, 9>, 10> grid_;
    
public:
    Board();
    ~Board() = default;
    
    void clear();
    void setPiece(const Position& pos, std::unique_ptr<Piece> piece);
    Piece* getPiece(const Position& pos) const;
    bool isEmpty(const Position& pos) const;
    bool isPathClear(const Position& from, const Position& to) const;
    
    bool isValidPosition(const Position& pos) const;
};
