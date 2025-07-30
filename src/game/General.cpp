#include "General.h"
#include <cmath>

bool General::isValidMove(const Position& from, const Position& to) const {
    // Check if both positions are within the palace
    if (!isInPalace(from) || !isInPalace(to)) {
        return false;
    }
    
    // General can only move one step horizontally or vertically
    int rowDiff = std::abs(to.row - from.row);
    int colDiff = std::abs(to.col - from.col);
    
    // Valid moves: one step in orthogonal direction only
    return (rowDiff == 1 && colDiff == 0) || (rowDiff == 0 && colDiff == 1);
}

bool General::isInPalace(const Position& pos) const {
    if (getColor() == Color::RED) {
        // Red palace: rows 1-3, cols 4-6
        return pos.row >= 1 && pos.row <= 3 && pos.col >= 4 && pos.col <= 6;
    } else {
        // Black palace: rows 8-10, cols 4-6
        return pos.row >= 8 && pos.row <= 10 && pos.col >= 4 && pos.col <= 6;
    }
}
