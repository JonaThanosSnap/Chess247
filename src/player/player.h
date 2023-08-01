#ifndef PLAYER_H_
#define PLAYER_H_
#include <utility>
#include "../coordinate.h"
#include "../team.h"

/////////////////////////////////////
//                                 //
//          Player Header          //
//                                 //
/////////////////////////////////////

class Player {
protected:
    // player score
    int score = 0;
    // isHuman is true if the player is a human player
    bool isHuman=false;
    // team is the team of the player
    Team team;
public:
    // destructor
    virtual ~Player();
    // getMove returns a pair of coordinates representing the move
    virtual std::pair<Coordinate, Coordinate> getMove();
    // isHumanPlayer returns true if the player is a human player
    bool isHumanPlayer() const;
    // getTeam returns the team of the player
    Team getTeam() const;
};

#endif
