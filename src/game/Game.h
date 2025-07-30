#pragma once
#include "Board.h"

struct MoveResult {
    bool isLegal;
    bool gameEnded;
    Color winner;
    
    MoveResult(bool legal = false, bool ended = false, Color w = Color::RED) 
        : isLegal(legal), gameEnded(ended), winner(w) {}
};

class Game {
private:
    Board board_;
    Color currentPlayer_;
    
    bool wouldGeneralsFaceEachOther(const Position& from, const Position& to) const;
    bool areGeneralsDirectlyFacing(const Position& redPos, const Position& blackPos,
                                  const Position& moveFrom, const Position& moveTo) const;
    
public:
    Game();
    
    void reset();
    Board& getBoard() { return board_; }
    const Board& getBoard() const { return board_; }
    
    MoveResult makeMove(const Position& from, const Position& to);
    bool isGameOver() const;
};
