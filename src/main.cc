#include <iostream>
#include "render/renderostream.h"
#include "board.h"

int main() {
    Board board;
    RenderOStream render{&board, std::cout};

    //board.setSquare(Coordinate{"e2"}, Piece::Empty());
    //board.setSquare(Coordinate{"e5"}, Piece::Pawn(Team::Black));

    render.render();

    std::cout << board.isValidMove(Coordinate{"e7"}, Coordinate{"e4"}) << std::endl;
    return 0;
}