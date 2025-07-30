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

bool Board::isValidPosition(const Position& pos) const {
    return pos.row >= 1 && pos.row <= 10 && pos.col >= 1 && pos.col <= 9;
}
