#include "tile.hpp"

Tile::Tile()
    : Tile(0, 0)
{}

Tile::Tile(int x, int y)
    : x(x), y(y)
{}

bool Tile::operator==(const Tile& a) const
{
    return x == a.x && y == a.y;
}

bool Tile::operator!=(const Tile& a) const
{
    return !(*this == a);
}

Tile& Tile::operator=(const Tile& a)
{
    x = a.x;
    y = a.y;
    return *this;
}