#include "aiplayerlevel3.h"

AIPlayerLevel3::AIPlayerLevel3(Board* board, Team t): AIPlayer{board} {
    team = t;
};

std::pair<Coordinate, Coordinate> AIPlayerLevel3::getMove() {
    // return a random legal move preferring captures and checks

    // to do this, we:
    //  1. maintain a list of prefered moves (that capture or check)

    std::vector<std::pair<Coordinate, Coordinate>> possibleMoves;
    std::vector<std::pair<Coordinate, Coordinate>> preferredMoves;

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
                if (!board->isValidMove(currSquare, v)) {
                    continue;
                }
                possibleMoves.push_back(std::make_pair(currSquare, v));

                // if this move escapes capture, captures, or checks, prefer it

                if (board->getSquare(v).getType() != Piece::Type::None && board->getSquare(v).getTeam() != team) {
                    preferredMoves.push_back(std::make_pair(currSquare, v));
                } else if (board->isCheckingMove(currSquare, v)) {
                    preferredMoves.push_back(std::make_pair(currSquare, v));
                } else if (board->isSquareThreatened(team, currSquare) 
                            && !board->isSquareThreatened(team, v)) {
                    preferredMoves.push_back(std::make_pair(currSquare, v));
                }
            }
        }
    }

    srand(time(0));

    if (preferredMoves.size() == 0) {
        return possibleMoves[rand() % possibleMoves.size()];
    } else {
        return preferredMoves[rand() % preferredMoves.size()];
    }
}
