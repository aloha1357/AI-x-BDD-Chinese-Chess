#include "Board.h"

Board::Board() {
    clear();
}

void Board::clear() {
    for (auto& row : grid_) {
        for (auto& cell : row) {
            cell.reset();
        }
    }
}

void Board::setPiece(const Position& pos, std::unique_ptr<Piece> piece) {
    if (isValidPosition(pos)) {
        grid_[pos.row - 1][pos.col - 1] = std::move(piece);
    }
}

Piece* Board::getPiece(const Position& pos) const {
    if (isValidPosition(pos)) {
        return grid_[pos.row - 1][pos.col - 1].get();
    }
    return nullptr;
}

bool Board::isEmpty(const Position& pos) const {
    return getPiece(pos) == nullptr;
}

bool Board::isPathClear(const Position& from, const Position& to) const {
    // Check if the path between from and to is clear (excluding from and to positions)
    int rowStep = 0, colStep = 0;
    
    if (to.row != from.row) {
        rowStep = (to.row > from.row) ? 1 : -1;
    }
    if (to.col != from.col) {
        colStep = (to.col > from.col) ? 1 : -1;
    }
    
    Position current = from;
    current.row += rowStep;
    current.col += colStep;
    
    while (current.row != to.row || current.col != to.col) {
        if (!isEmpty(current)) {
            return false; // Path is blocked
        }
        current.row += rowStep;
        current.col += colStep;
    }
    
    return true; // Path is clear
}

bool Board::isValidPosition(const Position& pos) const {
    return pos.row >= 1 && pos.row <= 10 && pos.col >= 1 && pos.col <= 9;
}
