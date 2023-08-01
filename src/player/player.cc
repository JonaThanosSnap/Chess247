#include "player.h"

/////////////////////////////////////
//                                 //
//       Player Implementation     //
//                                 //
/////////////////////////////////////

Player::~Player() {};

std::pair<Coordinate, Coordinate> Player::getMove() {
    return std::make_pair(Coordinate{-1, -1}, Coordinate{-1, -1});
};

bool Player::isHumanPlayer() const {
    return isHuman;
}

Team Player::getTeam() const {
    return team;
}