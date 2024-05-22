#pragma once
#include <ncurses.h>
#include "Snake.hpp"
#include "Board.hpp"
#include "Item.hpp"

class SnakeGame
{
public:
    // 생성자 호출 시 게임 창을 stage 0번으로 초기화
    SnakeGame()
    {
        initialize(0);
    }

    // 소멸자 호출 시 동적으로 할당했던 변수 delete
    ~SnakeGame()
    {
        delete apple;
        delete bomb;
    }

    // 게임 시작할 시(= 생성자 호출 될 시) 진행하는 로직
    void initialize(int stageNum)
    {
        // 게임 창을 stageNum 번째 stage로 초기화
        board.initialize(stageNum);

        // snake queue를 게임 창 좌측 상단에 ###@ 형태로 초기화
        snake.initialize();

        // 게임 창에 메모리 상으로 초기화 된 snake 위치 표시한다
        board.add(1, 4, '@');
        board.add(1, 3, '#');
        board.add(1, 2, '#');
        board.add(1, 1, '#');

        // 사과랑 폭탄 만든다
        createApple();
        createBomb();
    }

    // 사과 만드는 함수
    void createApple()
    {
        int y, x;

        // 아이템이 생성될 수 있는 위치 get하기
        board.getItemPos(y, x);

        apple = new Apple(y, x);

        // 게임 창의 메모리 상으로 사과 A 추가
        board.add(y, x, 'A');
    }

    // 폭탄 만드는 함수
    void createBomb()
    {
        int y, x;

        // 아이템이 생성될 수 있는 위치 get하기
        board.getItemPos(y, x);

        bomb = new Bomb(y, x);

        // 게임 창의 메모리 상으로 사과 B 추가
        board.add(y, x, 'B');
    }

    // 입력 받은 값에 따라 작동을 달리하는 로직
    void getInputState()
    {
        char input = board.getInput();

        switch (input)
        {
            // w a s d로 뱀 움직이기
            case 'w':
                if (!snake.setDirection(up))
                    game_over = true;
                break;
            case 's':
                if (!snake.setDirection(down))
                    game_over = true;
                break;
            case 'd':
                if (!snake.setDirection(right))
                    game_over = true;
                break;
            case 'a':
                if (!snake.setDirection(left))
                    game_over = true;
                break;

            // p 누르면 pause
            case 'p':
                // 게임 창 속도를 음수로 함으로써 멈추게 한다
                board.setTimeout(-1);
                // p가 다시 입력될 때까지 while문 못 빠져 나감
                while (board.getInput() != 'p')
                    ;
                // while문 빠져 나왔다는 것은 p를 다시 눌렀다는 것이니까
                // 다시 게임 속도 원상태로 돌려놓기
                board.setTimeout(300);
                break;
            
            // 임시로 만든 기능. n 누르면 다음 스테이지로 넘어감
            case 'n':
                // 현재 게임의 stage 번호를 num에 저장
                int num = getStageNum();

                

                
                // 다음 스테이지로 넘어가야하므로 ++num 한 것
                initialize(++num);
                break;
                
                

        }
    }

    // 게임을 플레이하는 동안 진행하는 로직
    void playingState()
    {
        // 스테이지가 4라는 것은 스테이지 끝이라는 뜻
        if (getStageNum() == 4)
        {   
            // 게임 오버로 하자
            game_over = true;
        }
        // next는 snake가 다음 어디로 가야할지 그 위치의 값을 가진 SnakePiece이다
        SnakePiece next = snake.nexthead();

        // next 라는 SnakePiece를 가지고 뱀을 조종
        handleNext(next);

        // 만약 사과나 폭탄이 NULL 상태라면 생성해야 한다
        if (apple == NULL)
        {
            createApple();
        }

        if (bomb == NULL)
        {
            createBomb();
        }

        // 만약 snake의 몸 길이가 3 미만이라면 게임 오버로 간주
        if (snake.getSize() < 3)
        {
            game_over = true;
        }
    }

    void handleNext(SnakePiece next)
    {   
        // 뱀이 움직인 틱 개수를 세는 변수 by 전역 범위로
        static int count = 0;

        int nextRow = next.getY();
        int nextCol = next.getX();

        // 만약 15번 뱀이 움직였다면
        if (count == 15)
        {   
            // count 값은 0으로 초기화
            count = 0;

            // 아이템 먹은걸로 하자
            eatApple();
            eatBomb();
        }

        // 만약 다음으로 나아갈 위치가 ' '이라면
        // 이하 "뱀이 앞으로 나아가는 로직" 이라고 칭함
        if (board.getCharAt(nextRow, nextCol) == ' ')
        {   
            // snake의 꼬리 위치에다가 ' ' add 한다
            board.add(snake.tail().getY(), snake.tail().getX(), ' ');
            // snake의 꼬리를 없앤다
            snake.removeBody();

            // 현 상태의 snake의 머리 부분의 icon을 '#'으로 설정
            snake.head().setIcon('#');
            // 게임 창에도 똑같이 snake의 머리 부분 위치를 '#'으로 바꿈(=add)
            board.add(snake.head().getY(), snake.head().getX(), '#');

            // snake에다가 next 추가
            snake.addBody(next);
            // next를 추가한 최종 snake의 머리 부분의 icon을 '@'로 설정
            snake.head().setIcon('@');
            // 게임 창에도 똑같이 반영
            board.add(snake.head().getY(), snake.head().getX(), '@');

            // 뱀이 나아갔으니 count에 1 추가
            ++count;
        }

        // 사과를 먹는다면
        else if (board.getCharAt(nextRow, nextCol) == 'A')
        {
            // 사과 먹는 함수 실행
            eatApple();

            // 뱀이 앞으로 나아가는 로직에서 꼬리 부분을 없애는 과정을 건너뛰면 된다
            snake.head().setIcon('#');
            board.add(snake.head().getY(), snake.head().getX(), '#');

            snake.addBody(next);
            snake.head().setIcon('@');
            board.add(snake.head().getY(), snake.head().getX(), '@');
        }

        // 폭탄을 먹는다면
        else if (board.getCharAt(nextRow, nextCol) == 'B')
        {  
            // 폭탄을 먹는 함수 실행
            eatBomb();

            // 꼬리를 한번 더 삭제하고 앞으로 나아가는 로직 진행
            board.add(snake.tail().getY(), snake.tail().getX(), ' ');
            snake.removeBody();

            board.add(snake.tail().getY(), snake.tail().getX(), ' ');
            snake.removeBody();

            snake.head().setIcon('#');
            board.add(snake.head().getY(), snake.head().getX(), '#');

            snake.addBody(next);
            snake.head().setIcon('@');
            board.add(snake.head().getY(), snake.head().getX(), '@');
        }

        // Wall(= '1')을 만났을 때
        else
        {
            game_over = true;
        }
    }

    // 사과를 없애는(=먹는) 함수
    void eatApple()
    {   
        // 우선 보드에 기존의 사과 위치에다가 ' ' add한다
        board.add(apple->getY(), apple->getX(), ' ');

        // 동적할당 했었던 apple 없애고 apple을 NULL로 하자
        delete apple;
        apple = NULL;

    }

    // 폭탄를 없애는(=먹는) 함수
    void eatBomb()
    {   
        // 우선 보드에 기존의 폭탄 위치에다가 ' ' add한다
        board.add(bomb->getY(), bomb->getX(), ' ');

        // 동적할당 했었던 bomb 없애고 bomb을 NULL로 하자
        delete bomb;
        bomb = NULL;
    }

    // stage 번호에 따라서 게임 창을 초기화하는 함수
    void setStage(int stageNum)
    {
        board.initialize(stageNum);
    }

    // 현재 게임이 스테이지 몇인지 get하는 함수
    int getStageNum()
    {
        return board.getStageNum();
    }

    // 게임 오버 됐는지 확인하는 함수
    bool isOver()
    {
        return game_over;
    }

    // 게임 새로고침
    void redraw()
    {
        board.refresh();
    }

private:
    Board board;
    Snake snake;

    bool game_over = false;

    Apple *apple;
    Bomb *bomb;

};