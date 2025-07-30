#include "Rook.h"
#include <cmath>

bool Rook::isValidMove(const Position& from, const Position& to) const {
    // Rook moves horizontally or vertically
    int rowDiff = std::abs(to.row - from.row);
    int colDiff = std::abs(to.col - from.col);
    
    // Must move either horizontally or vertically (not both)
    if (rowDiff != 0 && colDiff != 0) {
        return false;
    }
    
    // Must actually move
    if (rowDiff == 0 && colDiff == 0) {
        return false;
    }
    
    // For now, we assume the path is clear - path checking will be implemented in Board class
    return true;
}
