#pragma once

class Rhombus
{
public:
    void DragRhombus(int x, int y);
protected:
    int color; // 0 - Empty, 1 = Pink, 2 = Turquoise, 3 = Yellow, 4 = Purple
    int price;
    float size = 1;
    int x, y;
    bool destroy = false;

public:
    Rhombus(int color, int price, int x, int y)
        : color(color),
          price(price),
          x(x),
          y(y)
    {
    }

    Rhombus() = default;
};
