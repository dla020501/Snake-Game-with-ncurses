#include <ncurses.h>
#include "board.hpp"

using namespace snake;

int main()
{   
    // ncurses 시작
    initscr();
    // 일단 초기화 진행
    refresh();
    // 입력된 키 표시 안함
    noecho();
    // 커서 안보이게 설정
    curs_set(0);

    // 게임 보드 만들기
    Board board;

    for (int i = 0; i < 4; i++)
    {
        board.initialize(i);

        // 아이템 추가
        board.add(4, 4, 'I');

        // 뱀 추가
        board.add(1, 1, '#');
        board.add(1, 2, '#');
        board.add(1, 3, '#');
        board.add(1, 4, '@');
        
        board.getInput();
    }

    // 입력 값 받을 때 까지 대기
    getch();
    // ncurses 종료
    endwin();
}