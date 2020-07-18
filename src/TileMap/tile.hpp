#pragma once

class Tile
{
 public:
    /* Constructors */
    Tile();
    Tile(int x, int y);
    
    /* Operators */
    bool operator==(const Tile&) const;
    bool operator!=(const Tile&) const;
    Tile& operator=(const Tile&);
    
    /* Public data */
    int x;
    int y;
};