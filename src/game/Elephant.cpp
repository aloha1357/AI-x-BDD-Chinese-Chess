#include "Elephant.h"
#include "Board.h"
#include <cmath>

bool Elephant::isValidMove(const Position& from, const Position& to) const {
    int rowDiff = std::abs(to.row - from.row);
    int colDiff = std::abs(to.col - from.col);
    
    // Elephant moves exactly 2 steps diagonally
    if (rowDiff != 2 || colDiff != 2) {
        return false;
    }
    
    // Check if elephant can cross the river
    if (!canCrossRiver(to)) {
        return false;
    }
    
    return true;
}

bool Elephant::isValidMoveWithBoard(const Position& from, const Position& to, const Board& board) const {
    if (!isValidMove(from, to)) {
        return false;
    }
    
    // Check if the midpoint (elephant eye) is blocked
    Position midpoint = getMidpoint(from, to);
    return board.isEmpty(midpoint);
}

bool Elephant::canCrossRiver(const Position& pos) const {
    if (getColor() == Color::RED) {
        // Red elephants cannot cross to row 6 or higher
        return pos.row <= 5;
    } else {
        // Black elephants cannot cross to row 5 or lower
        return pos.row >= 6;
    }
}

Position Elephant::getMidpoint(const Position& from, const Position& to) const {
    int midRow = (from.row + to.row) / 2;
    int midCol = (from.col + to.col) / 2;
    return Position(midRow, midCol);
}
