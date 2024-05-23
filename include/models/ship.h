#ifndef SHIP_H
#define SHIP_H

class Ship {
public:
    bool is_horizontal = true;
    int length = 1;
    int x = 0;
    int y = 0;

    Ship(bool is_horizontal, int length, int x, int y);
};

#endif // SHIP_H
