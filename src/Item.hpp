#pragma once
#include <ncurses.h>

class Item
{
public:
    int row, col;
    char icon;

    Item(int y = 0, int x = 0)
    {
        row = y;
        col = x;
        icon = ' ';
    }

    int getX()
    {
        return col;
    }

    int getY()
    {
        return row;
    }

    void setIcon(char ch)
    {
        icon = ch;
    }    
};

class Apple : public Item
{
public:
    Apple(int y = 0, int x = 0)
    {
        row = y;
        col = x;
        icon = 'A';
    }
};

class Bomb : public Item
{
public:
    Bomb(int y = 0, int x = 0)
    {
        row = y;
        col = x;
        icon = 'B';
    }
};