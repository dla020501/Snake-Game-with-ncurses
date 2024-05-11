#pragma once
#include <ncurses.h>
// add time and stdlib libraries
#include <time.h>
#include <stdlib.h>
#include "Apple.hpp"
#include "Empty.hpp"
#include "Board.hpp"
#include "Drawable.hpp"
#include "Snake.hpp"

class SnakeGame
{
private:
    Board board;
    bool game_over;
    Apple *apple;
    Snake snake;

public:
    // will create board size height * width and initialize
    SnakeGame(int height, int width)
    {
        board = Board(height, width);
        initialize();
    }

    ~SnakeGame()
    {
        delete apple;
    }

    void initialize()
    {
        apple = NULL;
        board.initialize();
        game_over = false;
        // time random seed
        srand(time(NULL));

        // snake's default direction is down
        snake.setDirection(down);

        SnakePiece next = SnakePiece(1, 1);
        board.add(next);
        snake.addPiece(next);

        next = snake.nexthead();
        board.add(next);
        snake.addPiece(next);

        next = snake.nexthead();
        board.add(next);
        snake.addPiece(next);

        snake.setDirection(right);

        next = snake.nexthead();
        board.add(next);
        snake.addPiece(next);
    }

    void processInput()
    {
        char input = board.getInput();
        // process input
    }

    void updateState()
    {
        //update state

        // if apple object is not in screen
        if (apple == NULL)
        {
            int y, x;
            board.getEmptyCoordinates(y, x);
            apple = new Apple(y, x);
            board.add(*apple);
        }
        
        // create drawable snake piece object it has y, x position snake will go to
        SnakePiece next = snake.nexthead();

        // if the apple is not existed at the position snake will go to
        if (next.getX() != apple->getX() && next.getY() != apple->getY())
        {
            // print empty space at the position of snake's tail
            int emptyRow = snake.tail().getY();
            int emptyCol = snake.tail().getX();
            board.add(Empty(emptyRow,emptyCol));

            // and remove snake's tail
            snake.removePiece();

            // print snake piece
            board.add(next);
            
            // add next to front
            snake.addPiece(next);
        }
    }

    void redraw()
    {
        board.refresh();
    }

    bool isOver()
    {
        return game_over;
    }

};
