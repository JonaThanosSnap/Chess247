#include "coordinate.h"

/////////////////////////////////////
//                                 //
//     Coordinate Implementation   //
//                                 //
/////////////////////////////////////

// constructor using x and y coordinates
Coordinate::Coordinate(int x, int y): _x{x}, _y{y} {}

// constructor using a board coordiante
Coordinate::Coordinate(std::string p): _x{p[0]-'a'}, _y{p[1]-'1'} {}

// convert coordinate to string (x,y) -> board coordinate (e.g. e5, f6, etc)
std::string Coordinate::toString() const noexcept{
    char letter = 'a' + _x;
    std::string result = letter + std::to_string(_y+1);
    return result;
}

// translate coordinate by dx and dy
void Coordinate::translate(int dx, int dy) noexcept{
    _x += dx;
    _y += dy;
}

// retrieve x and y components
int Coordinate::x() const noexcept{
    return _x;
}

// retrieve x and y components
int Coordinate::y() const noexcept{
    return _y;
}

// equality operator
bool Coordinate::operator==(const Coordinate& other) const noexcept {
    return _x == other._x && _y == other._y;
}

// addition operator
Coordinate Coordinate::operator+(const Coordinate& other) const noexcept {
    return Coordinate{_x + other._x, _y + other._y};
}

// subtraction operator
Coordinate Coordinate::operator-(const Coordinate& other) const noexcept {
    return Coordinate{_x - other._x, _y - other._y};
}

// multiplication operator
Coordinate Coordinate::operator*(int scalar) const noexcept {
    return Coordinate{_x*scalar, _y*scalar};
}

// normalize x and y components
void Coordinate::normalizeComponents() noexcept {
    if (_x != 0) _x = _x / abs(_x);
    if (_y != 0) _y = _y / abs(_y);
}
