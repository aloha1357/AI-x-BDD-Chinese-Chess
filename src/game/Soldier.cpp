#include "Soldier.h"
#include <cmath>

bool Soldier::isValidMove(const Position& from, const Position& to) const {
    int rowDiff = to.row - from.row;
    int colDiff = to.col - from.col;
    
    // Must move exactly one step
    if (std::abs(rowDiff) + std::abs(colDiff) != 1) {
        return false;
    }
    
    bool crossedRiver = hasCrossedRiver(from);
    
    if (getColor() == Color::RED) {
        // Red soldiers move forward (increasing row numbers)
        if (rowDiff < 0) {
            // Cannot move backward
            return false;
        }
        
        if (!crossedRiver) {
            // Before crossing river, can only move forward
            return rowDiff == 1 && colDiff == 0;
        } else {
            // After crossing river, can move forward or sideways
            return (rowDiff == 1 && colDiff == 0) || (rowDiff == 0 && std::abs(colDiff) == 1);
        }
    } else {
        // Black soldiers move forward (decreasing row numbers)
        if (rowDiff > 0) {
            // Cannot move backward
            return false;
        }
        
        if (!crossedRiver) {
            // Before crossing river, can only move forward
            return rowDiff == -1 && colDiff == 0;
        } else {
            // After crossing river, can move forward or sideways
            return (rowDiff == -1 && colDiff == 0) || (rowDiff == 0 && std::abs(colDiff) == 1);
        }
    }
}

bool Soldier::hasCrossedRiver(const Position& pos) const {
    if (getColor() == Color::RED) {
        return pos.row >= 6; // Red soldiers cross river at row 6
    } else {
        return pos.row <= 5; // Black soldiers cross river at row 5
    }
}
