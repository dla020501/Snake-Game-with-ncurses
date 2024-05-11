#pragma once
#include <ncurses.h>
#include <stdlib.h>
#include "Drawable.hpp"

class Board{
    public:
    Board(){
        construct(0, 0);
    }

    Board(int height, int width){
        construct(height, width);    
    }

    // initialize function
    void initialize(){
        // board clear and print
        clear();
        refresh();
    }

    // create board's sideline size is 0*0
    void addBorder(){
        box(board_win, 0, 0);
    }

    // print drawable object on screen 
    void add(Drawable drawable)
    {
        addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
    }

    // print ch on board_win at (y, x)
    void addAt(int y, int x, char ch){
        mvwaddch(board_win, y, x, ch);
    }

    // on screen, get input value
    char getInput(){
        return wgetch(board_win);
    }

    // get empty space's direction y, x
    void getEmptyCoordinates(int &y, int &x)
    {   
        // rand() % height means get a random value between 0 to height 
        while((mvwinch(board_win, y = rand() % height, x = rand() % width)) != ' ');
    }

    // board clear
    void clear(){
        wclear(board_win);
        addBorder();
    }

    // print board
    void refresh(){
        wrefresh(board_win);
    }

private:
    WINDOW *board_win;
    int height, width;

    // set height, width value and create board with them
    void construct(int height, int width){
        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);       // get stdscr's height, width
        this->height = height;
        this->width = width;

        // create board from stdscr's middle
        board_win = newwin(height, width, (yMax/2) - (height/2), (xMax/2) - (width/2));

        
        wtimeout(board_win, 100);
    }
};