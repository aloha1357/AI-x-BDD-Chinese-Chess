#include "Horse.h"
#include "Board.h"
#include <cmath>

bool Horse::isValidMove(const Position& from, const Position& to) const {
    int rowDiff = std::abs(to.row - from.row);
    int colDiff = std::abs(to.col - from.col);
    
    // Horse moves in "L" shape: 2 squares in one direction, 1 square perpendicular
    bool isValidLShape = (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
    
    return isValidLShape;
}

bool Horse::isValidMoveWithBoard(const Position& from, const Position& to, const Board& board) const {
    if (!isValidMove(from, to)) {
        return false;
    }
    
    // Check if the "leg" is blocked
    Position legPosition = getLegBlockPosition(from, to);
    return board.isEmpty(legPosition);
}

Position Horse::getLegBlockPosition(const Position& from, const Position& to) const {
    int rowDiff = to.row - from.row;
    int colDiff = to.col - from.col;
    
    // Determine which direction the horse is moving
    if (std::abs(rowDiff) == 2) {
        // Moving 2 squares vertically, 1 horizontally
        return Position(from.row + (rowDiff > 0 ? 1 : -1), from.col);
    } else {
        // Moving 2 squares horizontally, 1 vertically
        return Position(from.row, from.col + (colDiff > 0 ? 1 : -1));
    }
}
