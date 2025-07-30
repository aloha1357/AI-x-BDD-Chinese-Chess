#pragma once

enum class PieceType {
    GENERAL, GUARD, ROOK, HORSE, CANNON, ELEPHANT, SOLDIER
};

enum class Color {
    RED, BLACK
};

struct Position {
    int row;
    int col;
    
    Position(int r = 0, int c = 0) : row(r), col(c) {}
    
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

class Piece {
private:
    PieceType type_;
    Color color_;
    
public:
    Piece(PieceType type, Color color) : type_(type), color_(color) {}
    virtual ~Piece() = default;
    
    PieceType getType() const { return type_; }
    Color getColor() const { return color_; }
    
    virtual bool isValidMove(const Position& from, const Position& to) const = 0;
};
