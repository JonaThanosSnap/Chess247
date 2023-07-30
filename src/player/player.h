#ifndef PLAYER_H_
#define PLAYER_H_
#include <utility>
#include "../coordinate.h"

class Player {
protected:
    int score=0;
    bool isHuman=false;
public:
    virtual ~Player() {};
    virtual std::pair<Coordinate, Coordinate> getMove() {
        return std::make_pair(Coordinate{-1, -1}, Coordinate{-1, -1});
    };
    bool isHumanPlayer() const {
        return isHuman;
    }
};

#endif
