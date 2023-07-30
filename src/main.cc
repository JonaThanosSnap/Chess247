#include <iostream>
#include "render/renderostream.h"
#include "board.h"

int main() {
    Board board;
    RenderOStream render{&board, std::cout};
    render.render();
    return 0;
}