#pragma once
#include <ncurses.h>
#include "snake.hpp"
#include "board.hpp"

namespace snake{
class SnakeGame
{
public:
    // 생성자 호출 시 게임 창을 stage 0번으로 초기화
    SnakeGame();

    // 게임 시작할 시(= 생성자 호출 될 시) 진행하는 로직
    void initialize(int stageNum);

    // 입력 받은 값에 따라 작동을 달리하는 로직
    void getInputState();

    // 게임을 플레이하는 동안 진행하는 로직
    void playingState();

    // 뱀이 다음 위치로 어떻게 나아가야하는지 icon에 따라 조종하는 함수
    void handleNext(SnakePiece next);

    // stage 번호에 따라서 게임 창을 초기화하는 함수
    void setStage(int stageNum);

    // 현재 게임이 스테이지 몇인지 get하는 함수
    int getStageNum();

    // 게임 오버 됐는지 확인하는 함수
    bool isOver();

    // 게임 새로고침
    void redraw();

private:
    Board board;
    Snake snake;

    bool game_over = false;
};
}