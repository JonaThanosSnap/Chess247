#include "aiplayerlevel4.h"

AIPlayerLevel4::AIPlayerLevel4(Board* board, Team t): AIPlayer{board} {
    team = t;
};

int AIPlayerLevel4::getPieceValue(Piece::Type type) {
    switch (type) {
        case Piece::Type::None:
            return 0;
            break;
        case Piece::Type::Pawn:
            return 1;
            break;
        case Piece::Type::Knight:
            return 3;
            break;
        case Piece::Type::Bishop:
            return 3;
            break;
        case Piece::Type::Rook:
            return 5;
            break;
        case Piece::Type::Queen:
            return 9;
            break;
        default:
            return 0;
    }
}

std::pair<Coordinate, Coordinate> AIPlayerLevel4::getMove() {
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
                    // captures. weight this move according to piece value
                    for (int i=0; i < getPieceValue(board->getSquare(v).getType()); i++) {
                        preferredMoves.push_back(std::make_pair(currSquare, v));
                    }
                } else if (board->isCheckingMove(currSquare, v)) {
                    // check. weight this move by 12
                    for (int i=0; i < 12; i++) {
                        preferredMoves.push_back(std::make_pair(currSquare, v));
                    }
                } else if (board->isSquareThreatened(team, currSquare) 
                            && !board->isSquareThreatened(team, v)) {
                    // escape capture. weight this move by the value of the escaping piece
                    for (int i=0; i < getPieceValue(board->getSquare(currSquare).getType()); i++) {
                        preferredMoves.push_back(std::make_pair(currSquare, v));
                    }
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
