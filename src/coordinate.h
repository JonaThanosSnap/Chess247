#ifndef COORDINATE_H_
#define COORDINATE_H_
#include <string>

/////////////////////////////////////
//                                 //
//       Coordinate Header         //
//                                 //
/////////////////////////////////////

class Coordinate {
    // private data members
    int _x;
    int _y;
    public:
        // constructors
        Coordinate(int x, int y);
        Coordinate(std::string p);

        // convert coordiante to string (x,y) -> board coordinate (e.g. e5, f6, etc)
        std::string toString() const noexcept;

        // translate coordinate by dx and dy
        void translate(int dx, int dy) noexcept;

        // retrieve x and y components
        int x() const noexcept;
        int y() const noexcept;

        // operator overloads
        bool operator==(const Coordinate& other) const noexcept;
        Coordinate operator+(const Coordinate& other) const noexcept;
        Coordinate operator-(const Coordinate& other) const noexcept;
        Coordinate operator*(int scalar) const noexcept;

        // normalize x and y components
        void normalizeComponents() noexcept;
};

#endif
