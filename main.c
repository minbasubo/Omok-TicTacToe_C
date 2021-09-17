#include <stdio.h>
#include <Windows.h> //Gotoxt()사용을 위한 헤더파일 선언
#include <stdlib.h>  //exit()사용을 위한 헤더파일 선언
#include <conio.h>   //getch()함수 사용을 위해

void info();    //게임규칙
void Setmap();    //바둑판 그리기
void Keydown(char key, int(*Map)[20], int* x, int* y);      //키보드 입력에 대한 반응
void Bd();
void DrawBd(int(*Map)[20]);
void Delete_Stone(int x, int y);
void Gotoxy(int x, int y); //특수문자는 x가2, y는 1씩 증가
void Printwinner(int num);
int ChoiceGame(); //게임 선택 메뉴
int intro();  //시작화면
int Win(int(*Map)[20]);  //승리자 체크
int Player = 1; // 1=흑돌, 2=백돌
void TicMap();
void Keydown_T(char key, int(*Map)[20], int* x, int* y, int* count);
int Check_Winner_T(int(*Map)[20], int count);
void Printwinner_T(int num);
int Player_T = 1; //1=X, 2=O


int main(void)  //오목의 메인 함수
{
    switch (intro())
    {
    case 0:
    {
        switch (ChoiceGame())
        {
        case 0:
        {
            system("cls");
            int Map[20][20] = { 0 };
            char key = 0;
            int x = 0, y = 0;
            Setmap();
            Gotoxy(0, 20);
            printf("이동 : →←↑↓, 두기 : SPACE, 종료 : ESC\n\n");
            printf("ENTER를 누르면 한 수 무를 수 있습니다.");
            Gotoxy(x, y);
            Bd();
            while (key != 27)
            {
                key = _getch();
                Delete_Stone(x, y);
                Keydown(key, Map, &x, &y);
                DrawBd(Map);
                if (Win(Map))
                {
                    return 1;
                }
                Gotoxy(x, y);
                Bd();
            }
            Gotoxy(0, 19);
            return 1;
        }
        case 2: //틱택토 선택시
        {
            system("cls");
            int board[20][20] = { 0 };
            int count = 0;

            TicMap();
            Gotoxy(0, 8);
            printf("이동 : →←↑↓, 두기 : SPACE, 종료 : ESC\n\n");
            char key1 = 0;
            int a = 1, b = 1;

            Gotoxy(a, b);
            while (key1 != 27)
            {
                key1 = _getch();
                Keydown_T(key1, board, &a, &b, &count);
                Check_Winner_T(board, count);
                Gotoxy(a, b);
            }
            Gotoxy(0, 19);
            return 1;
        }
        case 4: {//메인화면으로 돌아가기 선택시
            main();
        }
        default: { //이외의 입력은 무시
            break;
        }
        }

    }
    case 1: //게임규칙화면으로
    {
        info();
    }
    case 2: //게임종료
    {
        exit(0);
    }
    default: //이외의 입력 처리
    {
        break;
    }
    }
}

int intro()  //게임 시작시 뜨는 인트로 화면 함수
{
    int x = 17, y = 0;

    Gotoxy(x, y);      printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
    Gotoxy(x, y + 1);  printf("□                                          □\n");
    Gotoxy(x, y + 2);  printf("■          ■             ■■■■         ■\n");
    Gotoxy(x, y + 3);  printf("□        ■  ■           ■    ■         □\n");
    Gotoxy(x, y + 4);  printf("■      ■      ■         ■■■■         ■\n");
    Gotoxy(x, y + 5);  printf("□        ■  ■                            □\n");
    Gotoxy(x, y + 6);  printf("■          ■                ■            ■\n");
    Gotoxy(x, y + 7);  printf("□                        ■■■■■        □\n");
    Gotoxy(x, y + 8);  printf("■          ■                              ■\n");
    Gotoxy(x, y + 9);  printf("□          ■              ■■■          □\n");
    Gotoxy(x, y + 10); printf("■      ■■■■■              ■          ■\n");
    Gotoxy(x, y + 11); printf("□                              ■          □\n");
    Gotoxy(x, y + 12); printf("■                                          ■\n");
    Gotoxy(x, y + 13); printf("□   강의  : 고급 C 프로그래밍 및 설계      □\n");
    Gotoxy(x, y + 14); printf("■  교수님 : 이윤구 교수님                  ■\n");
    Gotoxy(x, y + 15); printf("□    조   : 7조                            □\n");
    Gotoxy(x, y + 16); printf("■   조원  : 박상천, 구본관, 서민수, 허창민 ■\n");
    Gotoxy(x, y + 17); printf("□                                          □\n");
    Gotoxy(x, y + 18); printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
    int a = 34, b = 20;
    Gotoxy(a - 2, b); printf(">  게임 시작 \n");
    Gotoxy(a, b + 1); printf(" 게임 규칙 \n");
    Gotoxy(a, b + 2); printf(" 게임 종료 \n");

    while (1)//무한 반복
    {
        char temp = _getch();//입력값 받는 변수
        switch (temp)
        {
        case 72://화살표 윗키일때
        {
            if (b > 20)
            {
                Gotoxy(a - 2, b);
                printf(" ");
                Gotoxy(a - 2, --b);
                printf(">");
            }
            break;

        }
        case 80://화살표 아래키일때
        {
            if (b < 22)
            {
                Gotoxy(a - 2, b);
                printf(" ");
                Gotoxy(a - 2, ++b);
                printf(">");
            }
            break;
        }
        case 32://스페이스 일때
            return b - 20;
        }
    }
}
int ChoiceGame()
{
    system("cls");
    int x = 17, y = 5;

    Gotoxy(x, y);      printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
    Gotoxy(x, y + 1);  printf("□                                          □\n");
    Gotoxy(x, y + 2);  printf("■              **게임 선택**               ■\n");
    Gotoxy(x, y + 3);  printf("□                                          □\n");
    Gotoxy(x, y + 4);  printf("■       >  1. 오목(5X5)                    ■\n");
    Gotoxy(x, y + 5);  printf("□                                          □\n");
    Gotoxy(x, y + 6);  printf("■          2. 틱택토(3X3)                  ■\n");
    Gotoxy(x, y + 7);  printf("□                                          □\n");
    Gotoxy(x, y + 8);  printf("■          3. 메인화면으로 돌아가기        ■\n");
    Gotoxy(x, y + 9);  printf("□                                          □\n");
    Gotoxy(x, y + 10); printf("■      Esc를 누르면 게임이 종료됩니다.     ■\n");
    Gotoxy(x, y + 11); printf("□                                          □\n");
    Gotoxy(x, y + 12); printf("■□■□■□■□■□■□■□■□■□■□■□■\n");

    int a = 28, b = 9;
    Gotoxy(a, b);
    while (1)//무한 반복 9~13 ->return값이 0,2,4
    {
        char temp = _getch();//입력값 받는 변수
        switch (temp)
        {
        case 72://화살표 윗키일때
        {
            if (b > 9)
            {
                Gotoxy(a - 2, b);
                printf(" ");
                --b; --b;
                Gotoxy(a - 2, b);
                printf(">");
            }
            break;

        }
        case 80://화살표 아랫키일때
        {
            if (b < 13)
            {
                Gotoxy(a - 2, b);
                printf(" ");
                ++b; ++b;
                Gotoxy(a - 2, b);
                printf(">");
            }
            break;
        }
        case 27:
            Gotoxy(0, 20);
            exit(0);

        case 32://스페이스 일때
            return b - 9;
        }
    }
}


void info()  //게임 규칙을 띄우는 함수
{
    system("cls");
    printf("\n");
    printf("<게임 규칙>\n\n");
    printf("1. 화살표 →←↑↓를 눌러 오목알을 원하는 위치에 위치시키세요.\n\n");
    printf("2. 스페이스바를 눌러 원하는 위치에 오목알을 두세요.\n\n");
    printf("4. 엔터키를 누르면 현재 가리키는 곳의 수를 무를 수 있습니다.(오목만 해당)\n\n");
    printf("5. 가로, 세로, 대각선으로 먼저 5개의 돌을 끊김 없이 둔 쪽이 승리합니다.\n\n");
    printf("   틱택토의 경우 먼저 3개를 이어지게 한 쪽이 승리합니다.\n\n");
    printf("6. 모든 룰을 이해하셨다면 게임을 즐기실 바랍니다!\n\n");
    Gotoxy(17, 20);
    printf("*스페이스를 누르면 메인 화면으로 돌아갑니다.*");

    while (1)
    {
        char tem = _getch();
        if (tem == 32) //스페이스가 눌렸을 시 메인화면으로
        {
            system("cls");
            main();
        }
    }
}

void Gotoxy(int x, int y)  //마우스 커서를 움직여 화면에 띄우는 함수(오픈소스)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void Keydown(char key, int(*Map)[20], int* x, int* y)  //입력받은 키에 따른 함수
{
    int checking3x3;
    switch (key)
    {
    case 72: //위쪽 방향키에 대한 반응
        if (*y - 1 < 0)
        {
            break;
        }
        else
        {
            *y -= 1;
        }
        break;
    case 75: //왼쪽 방향키에 대한 반응
    {
        if (*x - 2 < 0)
        {
            break;
        }
        else
        {
            *x -= 2;
        }
        break;
    }
    case 77: //오른쪽 방향키에 대한 반응
    {
        if (*x + 2 > 36)
        {
            break;
        }
        else
        {
            *x += 2;
        }
        break;
    }
    case 80: //아랫쪽 방향키에 대한 반응
    {
        if (*y + 1 > 18)
        {
            break;
        }
        else
        {
            *y += 1;
        }
        break;
    }
    case 32: //스페이스 입력시 바둑돌 두기
    {
        if (Map[*y][*x / 2] == 0)
        {
            if (Player == 1)
            {
                Map[*y][*x / 2] = 1;
                Player = 2;
            }
            else
            {
                Map[*y][*x / 2] = 2;
                Player = 1;
            }
        }
        break;
    }
    case 13: // 엔터키 입력시 커서에 있는 바둑돌을 무른뒤 플레이어 바꿈
    {
        if (Player == 1 || Map[*y][*x / 2] == 1)
        {
            Map[*y][*x / 2] = 0;
            Player = 2;
        }
        else if (Player == 2 || Map[*y][*x / 2] == 2)
        {
            Map[*y][*x / 2] = 0;
            Player = 1;
        }
        break;
    }
    default: //이외의 키들은 오류가 뜨지 않도록 제외
    {
        break;
    }
    }

}

void Bd()  //현재 배열속에 있는 값에 맞는 돌을 출력시키고, 순서를 바꾸는 함수
{
    if (Player == 1)
    {
        printf("○");
    }
    else if (Player == 2)
    {
        printf("●");
    }
}

void DrawBd(int(*Map)[20])  //바둑알을 두었을때 그것을 지속적으로 화면에 띄우기위한 함수
{
    int i, j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (Map[i][j] == 1)
            {
                Gotoxy(2 * j, i);
                printf("○");
            }
            else if (Map[i][j] == 2)
            {
                Gotoxy(2 * j, i);
                printf("●");
            }
        }
    }
}

void Delete_Stone(int x, int y)  //바둑돌이 움직일 때 지나온 길에 남는 바둑돌을 제거하는 함수
{
    Gotoxy(x, y);
    if (x == 0 && y == 0)
    {
        printf("┌");
    }
    else if (x == 36 && y == 0)
    {
        printf("┐");
    }
    else if (x == 0 && y == 18)
    {
        printf("└");
    }
    else if (x == 36 && y == 18)
    {
        printf("┘");
    }
    else if (x == 0)
    {
        printf("├");
    }
    else if (y == 0)
    {
        printf("┬");
    }
    else if (x == 36)
    {
        printf("┤");
    }
    else if (y == 18)
    {
        printf("┴");
    }
    else
    {
        printf("┼");
    }
}

void Setmap()  //바둑판을 그리는 함수
{
    int i, j;
    printf("┌");
    for (i = 0; i < 17; i++)
    {
        printf("┬");
    }
    printf("┐\n");
    for (i = 0; i < 17; i++)
    {
        printf("├");
        for (j = 0; j < 17; j++)
        {
            printf("┼");
        }
        printf("┤\n");
    }
    printf("└");
    for (i = 0; i < 17; i++)
    {
        printf("┴");
    }
    printf("┘");
}

int Win(int(*Map)[20])  //바둑돌이 5개가 이어져 있는지 검사하는 함수(양옆, 위아래, 오른쪽 대각선, 왼쪽 대각선)
{
    int i;
    int j;
    for (i = 2; i < 18; i++)
    {
        for (j = 0; j < 20; j++)
        {

            if (Map[j][i - 2] == 1 && Map[j][i - 1] == 1 && Map[j][i] == 1 && Map[j][i + 1] == 1 && Map[j][i + 2] == 1) //양옆으로 검사
            {
                Printwinner(1);
                return 1;
            }
            else if (Map[j][i - 2] == 2 && Map[j][i - 1] == 2 && Map[j][i] == 2 && Map[j][i + 1] == 2 && Map[j][i + 2] == 2)
            {
                Printwinner(2);
                return 1;
            }

            else if (Map[i - 2][j] == 1 && Map[i - 1][j] == 1 && Map[i][j] == 1 && Map[i + 1][j] == 1 && Map[i + 2][j] == 1) //위아래로 검사
            {
                Printwinner(1);
                return 1;
            }

            else if (Map[i - 2][j] == 2 && Map[i - 1][j] == 2 && Map[i][j] == 2 && Map[i + 1][j] == 2 && Map[i + 2][j] == 2)
            {
                Printwinner(2);
                return 1;
            }
        }
    }

    for (i = 2; i < 18; i++)
    {
        for (j = 2; j < 18; j++)
        {
            if (Map[j - 2][i - 2] == 1 && Map[j - 1][i - 1] == 1 && Map[j][i] == 1 && Map[j + 1][i + 1] == 1 && Map[j + 2][i + 2] == 1) //오른쪽 대각선으로 검사
            {
                Printwinner(1);
                return 1;
            }

            else if (Map[j - 2][i - 2] == 2 && Map[j - 1][i - 1] == 2 && Map[j][i] == 2 && Map[j + 1][i + 1] == 2 && Map[j + 2][i + 2] == 2)
            {
                Printwinner(2);
                return 1;
            }

            else if (Map[j + 2][i - 2] == 1 && Map[j + 1][i - 1] == 1 && Map[j][i] == 1 && Map[j - 1][i + 1] == 1 && Map[j - 2][i + 2] == 1) //왼쪽 대각선으로 검사
            {
                Printwinner(1);
                return 1;
            }

            else if (Map[j + 2][i - 2] == 2 && Map[j + 1][i - 1] == 2 && Map[j][i] == 2 && Map[j - 1][i + 1] == 2 && Map[j - 2][i + 2] == 2)
            {
                Printwinner(2);
                return 1;
            }
        }
    }
    return 0;
}

void Printwinner(int num) //함수에 입력받은 수에 따라 승리자를 표시하는 함수
{
    int x = 17, y = 5;
    char re = 0;
    if (num == 1)  //함수에 입력받은 수가 1이면 흑돌의 승리
    {
        system("cls");
        Gotoxy(x, y);    printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
        Gotoxy(x, y + 1);  printf("□                                          □\n");
        Gotoxy(x, y + 2);  printf("■              **축하합니다**              ■\n");
        Gotoxy(x, y + 3);  printf("□                                          □\n");
        Gotoxy(x, y + 4);  printf("■            흑돌의 승리입니다!            ■\n");
        Gotoxy(x, y + 5);  printf("□                                          □\n");
        Gotoxy(x, y + 6);  printf("■      Esc를 누르면 게임이 종료됩니다.     ■\n");
        Gotoxy(x, y + 7);  printf("□                                          □\n");
        Gotoxy(x, y + 8);  printf("■스페이스를 누르면 메인화면으로 돌아갑니다.■\n");
        Gotoxy(x, y + 9);  printf("□                                          □\n");
        Gotoxy(x, y + 10); printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
        Gotoxy(0, 22);
        re = _getch();
        switch (re)
        {
        case 32:
            main();
        case 27:
            exit(0);
        default:
            break;
        }
    }
    else if (num == 2)  //함수에 입력받은 수가 2이면 백돌의 승리
    {
        system("cls");
        Gotoxy(x, y);      printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
        Gotoxy(x, y + 1);  printf("□                                          □\n");
        Gotoxy(x, y + 2);  printf("■              **축하합니다**              ■\n");
        Gotoxy(x, y + 3);  printf("□                                          □\n");
        Gotoxy(x, y + 4);  printf("■            백돌의 승리입니다!            ■\n");
        Gotoxy(x, y + 5);  printf("□                                          □\n");
        Gotoxy(x, y + 6);  printf("■      Esc를 누르면 게임이 종료됩니다.     ■\n");
        Gotoxy(x, y + 7);  printf("□                                          □\n");
        Gotoxy(x, y + 8);  printf("■스페이스를 누르면 메인화면으로 돌아갑니다.■\n");
        Gotoxy(x, y + 9);  printf("□                                          □\n");
        Gotoxy(x, y + 10); printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
        Gotoxy(0, 22);
        re = _getch();
        switch (re)
        {
        case 32:
            main();
        case 27:
            exit(0);
        default:
            break;
        }
    }
}

void TicMap() {   //보드의 현재상태를 화면에 출력하는 함수

    int i;
    for (i = 0; i < 3; i++)
    {
        printf("-----------\n");
        fflush(stdout);
        printf("   |   |  \n");
        fflush(stdout);
    }
    printf("-----------\n");
    fflush(stdout);
}

void Keydown_T(char key, int(*Map)[20], int* x, int* y, int* count)
{
    switch (key) //72위, 80아래, 75왼쪽, 77오른쪽
    {
    case 72: //위
    {
        if (*y - 2 < 0)
        {
            break;
        }
        else
        {
            *y -= 2;
        }
        break;
    }
    case 75: //왼쪽
    {
        if (*x - 4 < 0)
        {
            break;
        }
        else
        {
            *x -= 4;
        }
        break;
    }
    case 77: //오른쪽
    {
        if (*x + 4 > 11)
        {
            break;
        }
        else
        {
            *x += 4;
        }
        break;
    }
    case 80: //아랫쪽
    {
        if (*y + 2 > 6)
        {
            break;
        }
        else
        {
            *y += 2;
        }
        break;
    }
    case 32: //스페이스 입력시 바둑돌 두기, 카운트 1씩 증가
    {
        if (Map[*x][*y] == 0)
        {
            if (Player == 1)
            {
                Map[*x][*y] = 1;
                printf("X");
                Player = 2;
                *count += 1;
            }
            else
            {
                Map[*x][*y] = 2;
                printf("O");
                Player = 1;
                *count += 1;
            }
        }
        break;
    }
    default:
    {
        break;
    }
    }

}

int Check_Winner_T(int(*Map)[20], int count) {   //승자를 출력하는 함수

    int i;
    char winner = 'U';
    for (i = 1; i <= 5; i += 2) //가로 체크 함수
    {
        if (Map[1][i] == 1 && Map[5][i] == 1 && Map[9][i] == 1) winner = 'X';
        if (Map[1][i] == 2 && Map[5][i] == 2 && Map[9][i] == 2) winner = 'O';
    }

    for (i = 1; i <= 9; i += 4) //세로 체크 함수
    {
        if (Map[i][1] == 1 && Map[i][3] == 1 && Map[i][5] == 1) winner = 'X';
        if (Map[i][1] == 2 && Map[i][3] == 2 && Map[i][5] == 2) winner = 'O';
    }

    //대각선 체크 함수
    if (Map[1][1] == 1 && Map[5][3] == 1 && Map[9][5] == 1) winner = 'X';
    if (Map[1][1] == 2 && Map[5][3] == 2 && Map[9][5] == 2) winner = 'O';
    if (Map[9][1] == 1 && Map[5][3] == 1 && Map[1][5] == 1) winner = 'X';
    if (Map[9][1] == 2 && Map[5][3] == 2 && Map[1][5] == 2) winner = 'O';

    // 카운트를 인자로 받아서 판을 다 채웠는데도 if 구문이 작동하지 않을 경우 무승부 표시
    if (winner == 'X') //만약 X가 이겼을 시
    {
        Printwinner_T(1);
        return 1;
    }
    else if (winner == 'O') //만약 O가 이겼을 시
    {
        Printwinner_T(2);
        return 1;
    }
    else if (count == 9) //무승부시
    {
        Printwinner_T(3);
        return 1;
    }
}



void Printwinner_T(int num) //X승리자 표시
{
    int x = 17, y = 5;
    char re = 0;
    if (num == 1)
    {
        system("cls");
        Gotoxy(x, y);      printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
        Gotoxy(x, y + 1);  printf("□                                          □\n");
        Gotoxy(x, y + 2);  printf("■              **축하합니다**              ■\n");
        Gotoxy(x, y + 3);  printf("□                                          □\n");
        Gotoxy(x, y + 4);  printf("■             X의 승리입니다!              ■\n");
        Gotoxy(x, y + 5);  printf("□                                          □\n");
        Gotoxy(x, y + 6);  printf("■      Esc를 누르면 게임이 종료됩니다.     ■\n");
        Gotoxy(x, y + 7);  printf("□                                          □\n");
        Gotoxy(x, y + 8);  printf("■스페이스를 누르면 메인화면으로 돌아갑니다.■\n");
        Gotoxy(x, y + 9);  printf("□                                          □\n");
        Gotoxy(x, y + 10); printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
        Gotoxy(0, 22);
        re = _getch();
        switch (re)
        {
        case 32: //메인화면으로 돌아가기
            main();
        case 27: //게임종료
            exit(0);
        default: //예외입력에 대한 처리
            break;
        }
    }
    else if (num == 2) //O승리자 표시
    {
        system("cls");
        Gotoxy(x, y);      printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
        Gotoxy(x, y + 1);  printf("□                                          □\n");
        Gotoxy(x, y + 2);  printf("■              **축하합니다**              ■\n");
        Gotoxy(x, y + 3);  printf("□                                          □\n");
        Gotoxy(x, y + 4);  printf("■             O의 승리입니다!              ■\n");
        Gotoxy(x, y + 5);  printf("□                                          □\n");
        Gotoxy(x, y + 6);  printf("■      Esc를 누르면 게임이 종료됩니다.     ■\n");
        Gotoxy(x, y + 7);  printf("□                                          □\n");
        Gotoxy(x, y + 8);  printf("■스페이스를 누르면 메인화면으로 돌아갑니다.■\n");
        Gotoxy(x, y + 9);  printf("□                                          □\n");
        Gotoxy(x, y + 10); printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
        Gotoxy(0, 22);
        re = _getch();
        switch (re)
        {
        case 32:
            main();
        case 27:
            exit(0);
        default:
            break;
        }
    }
    else if (num == 3) //무승부시 표시
    {
        system("cls");
        Gotoxy(x, y);      printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
        Gotoxy(x, y + 1);  printf("□                                          □\n");
        Gotoxy(x, y + 2);  printf("■                                          ■\n");
        Gotoxy(x, y + 3);  printf("□             **무승부입니다.**            □\n");
        Gotoxy(x, y + 4);  printf("■                                          ■\n");
        Gotoxy(x, y + 5);  printf("□       Esc를 누르면 게임이 종료됩니다.    □\n");
        Gotoxy(x, y + 6);  printf("■                                          ■\n");
        Gotoxy(x, y + 7);  printf("□스페이스를 누르면 메인화면으로 돌아갑니다.□\n");
        Gotoxy(x, y + 8);  printf("■                                          ■\n");
        Gotoxy(x, y + 9);  printf("□                                          □\n");
        Gotoxy(x, y + 10); printf("■□■□■□■□■□■□■□■□■□■□■□■\n");
        Gotoxy(0, 22);
        re = _getch();
        switch (re)
        {
        case 32:
            main();
        case 27:
            exit(0);
        default:
            break;
        }
    }
}