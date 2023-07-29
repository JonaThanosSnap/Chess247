#include "coordinate.h"

/////////////////////////////////////
//                                 //
//     Coordinate Implementation   //
//                                 //
/////////////////////////////////////

Coordinate::Coordinate(int x, int y): _x{x}, _y{y} {}

Coordinate::Coordinate(std::string p): _x{p[0]-'a'}, _y{p[1]-'1'} {}

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

bool Coordinate::operator==(const Coordinate& other) const noexcept {
    return _x == other._x && _y == other._y;
}

Coordinate Coordinate::operator+(const Coordinate& other) const noexcept {
    return Coordinate{_x + other._x, _y + other._y};
}

Coordinate Coordinate::operator-(const Coordinate& other) const noexcept {
    return Coordinate{_x - other._x, _y - other._y};
}

void Coordinate::normalizeComponents() noexcept {
    if (_x != 0) _x = _x / abs(_x);
    if (_y != 0) _y = _y / abs(_y);
}
