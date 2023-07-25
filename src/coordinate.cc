#include "coordinate.h"

/////////////////////////////////////
//                                 //
//     Coordinate Implementation   //
//                                 //
/////////////////////////////////////

Coordinate::Coordinate(int x, int y): _x{x}, _y{y} {}

Coordinate::Coordinate(std::string p): _x{p[0]-'a'}, _y{p[1]-'0'} {}

std::string Coordinate::toString() const noexcept{
    char letter = 'a' + _x;
    std::string result = letter + std::to_string(_y);
    return result;
}

void Coordinate::translate(int dx, int dy) noexcept{
    _x += dx;
    _y += dy;
}

int Coordinate::x() const noexcept{
    return _x;
}

int Coordinate::y() const noexcept{
    return _y;
}