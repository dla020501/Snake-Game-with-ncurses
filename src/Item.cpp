#include "Item.hpp"

Item::Item(int y = 0, int x = 0)
{
    row = y;
    col = x;
    icon = ' ';
}

int Item::getX()
{
    return col;
}

int Item::getY()
{
    return row;
}

void Item::setIcon(char ch)
{
    icon = ch;
}  