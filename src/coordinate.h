#ifndef COORDINATE_H_
#define COORDINATE_H_
#include <string>

/////////////////////////////////////
//                                 //
//       Coordinate Header         //
//                                 //
/////////////////////////////////////

class Coordinate {
    int _x;
    int _y;
    public:
        Coordinate(int x, int y);
        Coordinate(std::string p);
        std::string toString() const noexcept;
        void translate(int dx, int dy) noexcept;
        int x() const noexcept;
        int y() const noexcept;
};

#endif
