#include "Soldier.h"
#include <cmath>

bool Soldier::isValidMove(const Position& from, const Position& to) const {
    // Simple implementation for now - just allow any move
    // Detailed soldier movement rules will be implemented when we get to soldier scenarios
    return true;
}

bool Soldier::hasCrossedRiver(const Position& pos) const {
    if (getColor() == Color::RED) {
        return pos.row >= 6; // Red soldiers cross river at row 6
    } else {
        return pos.row <= 5; // Black soldiers cross river at row 5
    }
}
