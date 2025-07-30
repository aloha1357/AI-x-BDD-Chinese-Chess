#include "Cannon.h"
#include "Board.h"
#include <cmath>

bool Cannon::isValidMove(const Position& from, const Position& to) const {
    // Cannon moves horizontally or vertically like a Rook
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
    
    return true;
}

bool Cannon::isValidMoveWithBoard(const Position& from, const Position& to, const Board& board) const {
    if (!isValidMove(from, to)) {
        return false;
    }
    
    int piecesInPath = countPiecesInPath(from, to, board);
    
    // Check if destination has a piece
    bool hasTargetPiece = !board.isEmpty(to);
    
    if (hasTargetPiece) {
        // To capture, must have exactly one piece in path (cannon mount)
        return piecesInPath == 1;
    } else {
        // To move without capturing, path must be clear
        return piecesInPath == 0;
    }
}

int Cannon::countPiecesInPath(const Position& from, const Position& to, const Board& board) const {
    int count = 0;
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
        if (!board.isEmpty(current)) {
            count++;
        }
        current.row += rowStep;
        current.col += colStep;
    }
    
    return count;
}
