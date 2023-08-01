#ifndef AI_PLAYER_LEVEL4_H_
#define AI_PLAYER_LEVEL4_H_
#include "aiplayer.h"

/////////////////////////////////////
//                                 //
//    AI Player Level 4 Header     //
//                                 //
/////////////////////////////////////

class AIPlayerLevel4 : public AIPlayer {
public:
    // constructor
    AIPlayerLevel4(Board*, Team);
    // get the value of a piece
    int getPieceValue(Piece::Type); 
    //get a pair of coordinates representing the move
    std::pair<Coordinate, Coordinate> getMove() override;
};

#endif
