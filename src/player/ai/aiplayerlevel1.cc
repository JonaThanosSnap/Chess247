#include "aiplayerlevel1.h"
#include "../../coordinate.h"
#include "../../team.h"
#include <utility>
#include <iostream>

AIPlayerLevel1::AIPlayerLevel1(Board* board, Team t): AIPlayer{board} {
    team = t;
};

std::pair<Coordinate, Coordinate> AIPlayerLevel1::getMove() {
    // return a random legal move

    // to do this, we:
    //  1. call board.getValidMoves(p) for each p on this team
    //  2. randomly choose a move from (1)
    //  3. confirm that it is valid. if not, go back to (2)

    std::vector<std::pair<Coordinate, Coordinate>> possibleMoves;

    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            Coordinate currSquare{i, j};
            if (board->getSquare(currSquare).getTeam() != team) {
                // make sure this is our own piece!
                continue;
            }

            std::vector<Coordinate> possibleMovesFromThisSquare = 
                board->getValidMoves(currSquare);
            for (auto v : possibleMovesFromThisSquare) {
                possibleMoves.push_back(std::make_pair(currSquare, v));
            }
        }
    }

    std::pair<Coordinate, Coordinate> move = possibleMoves[rand() % possibleMoves.size()];
    while (!board->isValidMove(move.first, move.second)) {
        move = possibleMoves[rand() % possibleMoves.size()];
    }

    // std::cout << move.first.toString() << " " << move.second.toString() << std::endl;

    return move;   
}

