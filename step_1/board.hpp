#pragma once
#include <ncurses.h>
#include <stdlib.h>

namespace snake{

    class Board
    {
    public:
        // 생성자 호출하면 21 21 크기의 gameBoard 만듬
        Board();

        // 초기화 함수
        void initialize(int num);

        // gameBoard의 메모리상에서 (y, x) 위치에 ch 문자 추가하기
        void add(int y, int x, char ch);

        // 입력 값 get하기
        char getInput();

    private:
        int xMax, yMax;
        WINDOW *gameBoard;
        int stageNum;
    };
}