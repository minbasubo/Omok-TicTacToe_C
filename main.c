#include <stdio.h>
#include <Windows.h> //Gotoxt()����� ���� ������� ����
#include <stdlib.h>  //exit()����� ���� ������� ����
#include <conio.h>   //getch()�Լ� ����� ����

void info();    //���ӱ�Ģ
void Setmap();    //�ٵ��� �׸���
void Keydown(char key, int(*Map)[20], int* x, int* y);      //Ű���� �Է¿� ���� ����
void Bd();
void DrawBd(int(*Map)[20]);
void Delete_Stone(int x, int y);
void Gotoxy(int x, int y); //Ư�����ڴ� x��2, y�� 1�� ����
void Printwinner(int num);
int ChoiceGame(); //���� ���� �޴�
int intro();  //����ȭ��
int Win(int(*Map)[20]);  //�¸��� üũ
int Player = 1; // 1=�浹, 2=�鵹
void TicMap();
void Keydown_T(char key, int(*Map)[20], int* x, int* y, int* count);
int Check_Winner_T(int(*Map)[20], int count);
void Printwinner_T(int num);
int Player_T = 1; //1=X, 2=O


int main(void)  //������ ���� �Լ�
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
            printf("�̵� : �����, �α� : SPACE, ���� : ESC\n\n");
            printf("ENTER�� ������ �� �� ���� �� �ֽ��ϴ�.");
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
        case 2: //ƽ���� ���ý�
        {
            system("cls");
            int board[20][20] = { 0 };
            int count = 0;

            TicMap();
            Gotoxy(0, 8);
            printf("�̵� : �����, �α� : SPACE, ���� : ESC\n\n");
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
        case 4: {//����ȭ������ ���ư��� ���ý�
            main();
        }
        default: { //�̿��� �Է��� ����
            break;
        }
        }

    }
    case 1: //���ӱ�Ģȭ������
    {
        info();
    }
    case 2: //��������
    {
        exit(0);
    }
    default: //�̿��� �Է� ó��
    {
        break;
    }
    }
}

int intro()  //���� ���۽� �ߴ� ��Ʈ�� ȭ�� �Լ�
{
    int x = 17, y = 0;

    Gotoxy(x, y);      printf("������������������������\n");
    Gotoxy(x, y + 1);  printf("��                                          ��\n");
    Gotoxy(x, y + 2);  printf("��          ��             �����         ��\n");
    Gotoxy(x, y + 3);  printf("��        ��  ��           ��    ��         ��\n");
    Gotoxy(x, y + 4);  printf("��      ��      ��         �����         ��\n");
    Gotoxy(x, y + 5);  printf("��        ��  ��                            ��\n");
    Gotoxy(x, y + 6);  printf("��          ��                ��            ��\n");
    Gotoxy(x, y + 7);  printf("��                        ������        ��\n");
    Gotoxy(x, y + 8);  printf("��          ��                              ��\n");
    Gotoxy(x, y + 9);  printf("��          ��              ����          ��\n");
    Gotoxy(x, y + 10); printf("��      ������              ��          ��\n");
    Gotoxy(x, y + 11); printf("��                              ��          ��\n");
    Gotoxy(x, y + 12); printf("��                                          ��\n");
    Gotoxy(x, y + 13); printf("��   ����  : ��� C ���α׷��� �� ����      ��\n");
    Gotoxy(x, y + 14); printf("��  ������ : ������ ������                  ��\n");
    Gotoxy(x, y + 15); printf("��    ��   : 7��                            ��\n");
    Gotoxy(x, y + 16); printf("��   ����  : �ڻ�õ, ������, ���μ�, ��â�� ��\n");
    Gotoxy(x, y + 17); printf("��                                          ��\n");
    Gotoxy(x, y + 18); printf("������������������������\n");
    int a = 34, b = 20;
    Gotoxy(a - 2, b); printf(">  ���� ���� \n");
    Gotoxy(a, b + 1); printf(" ���� ��Ģ \n");
    Gotoxy(a, b + 2); printf(" ���� ���� \n");

    while (1)//���� �ݺ�
    {
        char temp = _getch();//�Է°� �޴� ����
        switch (temp)
        {
        case 72://ȭ��ǥ ��Ű�϶�
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
        case 80://ȭ��ǥ �Ʒ�Ű�϶�
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
        case 32://�����̽� �϶�
            return b - 20;
        }
    }
}
int ChoiceGame()
{
    system("cls");
    int x = 17, y = 5;

    Gotoxy(x, y);      printf("������������������������\n");
    Gotoxy(x, y + 1);  printf("��                                          ��\n");
    Gotoxy(x, y + 2);  printf("��              **���� ����**               ��\n");
    Gotoxy(x, y + 3);  printf("��                                          ��\n");
    Gotoxy(x, y + 4);  printf("��       >  1. ����(5X5)                    ��\n");
    Gotoxy(x, y + 5);  printf("��                                          ��\n");
    Gotoxy(x, y + 6);  printf("��          2. ƽ����(3X3)                  ��\n");
    Gotoxy(x, y + 7);  printf("��                                          ��\n");
    Gotoxy(x, y + 8);  printf("��          3. ����ȭ������ ���ư���        ��\n");
    Gotoxy(x, y + 9);  printf("��                                          ��\n");
    Gotoxy(x, y + 10); printf("��      Esc�� ������ ������ ����˴ϴ�.     ��\n");
    Gotoxy(x, y + 11); printf("��                                          ��\n");
    Gotoxy(x, y + 12); printf("������������������������\n");

    int a = 28, b = 9;
    Gotoxy(a, b);
    while (1)//���� �ݺ� 9~13 ->return���� 0,2,4
    {
        char temp = _getch();//�Է°� �޴� ����
        switch (temp)
        {
        case 72://ȭ��ǥ ��Ű�϶�
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
        case 80://ȭ��ǥ �Ʒ�Ű�϶�
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

        case 32://�����̽� �϶�
            return b - 9;
        }
    }
}


void info()  //���� ��Ģ�� ���� �Լ�
{
    system("cls");
    printf("\n");
    printf("<���� ��Ģ>\n\n");
    printf("1. ȭ��ǥ ����鸦 ���� ������� ���ϴ� ��ġ�� ��ġ��Ű����.\n\n");
    printf("2. �����̽��ٸ� ���� ���ϴ� ��ġ�� ������� �μ���.\n\n");
    printf("4. ����Ű�� ������ ���� ����Ű�� ���� ���� ���� �� �ֽ��ϴ�.(���� �ش�)\n\n");
    printf("5. ����, ����, �밢������ ���� 5���� ���� ���� ���� �� ���� �¸��մϴ�.\n\n");
    printf("   ƽ������ ��� ���� 3���� �̾����� �� ���� �¸��մϴ�.\n\n");
    printf("6. ��� ���� �����ϼ̴ٸ� ������ ���� �ٶ��ϴ�!\n\n");
    Gotoxy(17, 20);
    printf("*�����̽��� ������ ���� ȭ������ ���ư��ϴ�.*");

    while (1)
    {
        char tem = _getch();
        if (tem == 32) //�����̽��� ������ �� ����ȭ������
        {
            system("cls");
            main();
        }
    }
}

void Gotoxy(int x, int y)  //���콺 Ŀ���� ������ ȭ�鿡 ���� �Լ�(���¼ҽ�)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void Keydown(char key, int(*Map)[20], int* x, int* y)  //�Է¹��� Ű�� ���� �Լ�
{
    int checking3x3;
    switch (key)
    {
    case 72: //���� ����Ű�� ���� ����
        if (*y - 1 < 0)
        {
            break;
        }
        else
        {
            *y -= 1;
        }
        break;
    case 75: //���� ����Ű�� ���� ����
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
    case 77: //������ ����Ű�� ���� ����
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
    case 80: //�Ʒ��� ����Ű�� ���� ����
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
    case 32: //�����̽� �Է½� �ٵϵ� �α�
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
    case 13: // ����Ű �Է½� Ŀ���� �ִ� �ٵϵ��� ������ �÷��̾� �ٲ�
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
    default: //�̿��� Ű���� ������ ���� �ʵ��� ����
    {
        break;
    }
    }

}

void Bd()  //���� �迭�ӿ� �ִ� ���� �´� ���� ��½�Ű��, ������ �ٲٴ� �Լ�
{
    if (Player == 1)
    {
        printf("��");
    }
    else if (Player == 2)
    {
        printf("��");
    }
}

void DrawBd(int(*Map)[20])  //�ٵϾ��� �ξ����� �װ��� ���������� ȭ�鿡 �������� �Լ�
{
    int i, j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (Map[i][j] == 1)
            {
                Gotoxy(2 * j, i);
                printf("��");
            }
            else if (Map[i][j] == 2)
            {
                Gotoxy(2 * j, i);
                printf("��");
            }
        }
    }
}

void Delete_Stone(int x, int y)  //�ٵϵ��� ������ �� ������ �濡 ���� �ٵϵ��� �����ϴ� �Լ�
{
    Gotoxy(x, y);
    if (x == 0 && y == 0)
    {
        printf("��");
    }
    else if (x == 36 && y == 0)
    {
        printf("��");
    }
    else if (x == 0 && y == 18)
    {
        printf("��");
    }
    else if (x == 36 && y == 18)
    {
        printf("��");
    }
    else if (x == 0)
    {
        printf("��");
    }
    else if (y == 0)
    {
        printf("��");
    }
    else if (x == 36)
    {
        printf("��");
    }
    else if (y == 18)
    {
        printf("��");
    }
    else
    {
        printf("��");
    }
}

void Setmap()  //�ٵ����� �׸��� �Լ�
{
    int i, j;
    printf("��");
    for (i = 0; i < 17; i++)
    {
        printf("��");
    }
    printf("��\n");
    for (i = 0; i < 17; i++)
    {
        printf("��");
        for (j = 0; j < 17; j++)
        {
            printf("��");
        }
        printf("��\n");
    }
    printf("��");
    for (i = 0; i < 17; i++)
    {
        printf("��");
    }
    printf("��");
}

int Win(int(*Map)[20])  //�ٵϵ��� 5���� �̾��� �ִ��� �˻��ϴ� �Լ�(�翷, ���Ʒ�, ������ �밢��, ���� �밢��)
{
    int i;
    int j;
    for (i = 2; i < 18; i++)
    {
        for (j = 0; j < 20; j++)
        {

            if (Map[j][i - 2] == 1 && Map[j][i - 1] == 1 && Map[j][i] == 1 && Map[j][i + 1] == 1 && Map[j][i + 2] == 1) //�翷���� �˻�
            {
                Printwinner(1);
                return 1;
            }
            else if (Map[j][i - 2] == 2 && Map[j][i - 1] == 2 && Map[j][i] == 2 && Map[j][i + 1] == 2 && Map[j][i + 2] == 2)
            {
                Printwinner(2);
                return 1;
            }

            else if (Map[i - 2][j] == 1 && Map[i - 1][j] == 1 && Map[i][j] == 1 && Map[i + 1][j] == 1 && Map[i + 2][j] == 1) //���Ʒ��� �˻�
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
            if (Map[j - 2][i - 2] == 1 && Map[j - 1][i - 1] == 1 && Map[j][i] == 1 && Map[j + 1][i + 1] == 1 && Map[j + 2][i + 2] == 1) //������ �밢������ �˻�
            {
                Printwinner(1);
                return 1;
            }

            else if (Map[j - 2][i - 2] == 2 && Map[j - 1][i - 1] == 2 && Map[j][i] == 2 && Map[j + 1][i + 1] == 2 && Map[j + 2][i + 2] == 2)
            {
                Printwinner(2);
                return 1;
            }

            else if (Map[j + 2][i - 2] == 1 && Map[j + 1][i - 1] == 1 && Map[j][i] == 1 && Map[j - 1][i + 1] == 1 && Map[j - 2][i + 2] == 1) //���� �밢������ �˻�
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

void Printwinner(int num) //�Լ��� �Է¹��� ���� ���� �¸��ڸ� ǥ���ϴ� �Լ�
{
    int x = 17, y = 5;
    char re = 0;
    if (num == 1)  //�Լ��� �Է¹��� ���� 1�̸� �浹�� �¸�
    {
        system("cls");
        Gotoxy(x, y);    printf("������������������������\n");
        Gotoxy(x, y + 1);  printf("��                                          ��\n");
        Gotoxy(x, y + 2);  printf("��              **�����մϴ�**              ��\n");
        Gotoxy(x, y + 3);  printf("��                                          ��\n");
        Gotoxy(x, y + 4);  printf("��            �浹�� �¸��Դϴ�!            ��\n");
        Gotoxy(x, y + 5);  printf("��                                          ��\n");
        Gotoxy(x, y + 6);  printf("��      Esc�� ������ ������ ����˴ϴ�.     ��\n");
        Gotoxy(x, y + 7);  printf("��                                          ��\n");
        Gotoxy(x, y + 8);  printf("�ὺ���̽��� ������ ����ȭ������ ���ư��ϴ�.��\n");
        Gotoxy(x, y + 9);  printf("��                                          ��\n");
        Gotoxy(x, y + 10); printf("������������������������\n");
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
    else if (num == 2)  //�Լ��� �Է¹��� ���� 2�̸� �鵹�� �¸�
    {
        system("cls");
        Gotoxy(x, y);      printf("������������������������\n");
        Gotoxy(x, y + 1);  printf("��                                          ��\n");
        Gotoxy(x, y + 2);  printf("��              **�����մϴ�**              ��\n");
        Gotoxy(x, y + 3);  printf("��                                          ��\n");
        Gotoxy(x, y + 4);  printf("��            �鵹�� �¸��Դϴ�!            ��\n");
        Gotoxy(x, y + 5);  printf("��                                          ��\n");
        Gotoxy(x, y + 6);  printf("��      Esc�� ������ ������ ����˴ϴ�.     ��\n");
        Gotoxy(x, y + 7);  printf("��                                          ��\n");
        Gotoxy(x, y + 8);  printf("�ὺ���̽��� ������ ����ȭ������ ���ư��ϴ�.��\n");
        Gotoxy(x, y + 9);  printf("��                                          ��\n");
        Gotoxy(x, y + 10); printf("������������������������\n");
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

void TicMap() {   //������ ������¸� ȭ�鿡 ����ϴ� �Լ�

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
    switch (key) //72��, 80�Ʒ�, 75����, 77������
    {
    case 72: //��
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
    case 75: //����
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
    case 77: //������
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
    case 80: //�Ʒ���
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
    case 32: //�����̽� �Է½� �ٵϵ� �α�, ī��Ʈ 1�� ����
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

int Check_Winner_T(int(*Map)[20], int count) {   //���ڸ� ����ϴ� �Լ�

    int i;
    char winner = 'U';
    for (i = 1; i <= 5; i += 2) //���� üũ �Լ�
    {
        if (Map[1][i] == 1 && Map[5][i] == 1 && Map[9][i] == 1) winner = 'X';
        if (Map[1][i] == 2 && Map[5][i] == 2 && Map[9][i] == 2) winner = 'O';
    }

    for (i = 1; i <= 9; i += 4) //���� üũ �Լ�
    {
        if (Map[i][1] == 1 && Map[i][3] == 1 && Map[i][5] == 1) winner = 'X';
        if (Map[i][1] == 2 && Map[i][3] == 2 && Map[i][5] == 2) winner = 'O';
    }

    //�밢�� üũ �Լ�
    if (Map[1][1] == 1 && Map[5][3] == 1 && Map[9][5] == 1) winner = 'X';
    if (Map[1][1] == 2 && Map[5][3] == 2 && Map[9][5] == 2) winner = 'O';
    if (Map[9][1] == 1 && Map[5][3] == 1 && Map[1][5] == 1) winner = 'X';
    if (Map[9][1] == 2 && Map[5][3] == 2 && Map[1][5] == 2) winner = 'O';

    // ī��Ʈ�� ���ڷ� �޾Ƽ� ���� �� ä���µ��� if ������ �۵����� ���� ��� ���º� ǥ��
    if (winner == 'X') //���� X�� �̰��� ��
    {
        Printwinner_T(1);
        return 1;
    }
    else if (winner == 'O') //���� O�� �̰��� ��
    {
        Printwinner_T(2);
        return 1;
    }
    else if (count == 9) //���ºν�
    {
        Printwinner_T(3);
        return 1;
    }
}



void Printwinner_T(int num) //X�¸��� ǥ��
{
    int x = 17, y = 5;
    char re = 0;
    if (num == 1)
    {
        system("cls");
        Gotoxy(x, y);      printf("������������������������\n");
        Gotoxy(x, y + 1);  printf("��                                          ��\n");
        Gotoxy(x, y + 2);  printf("��              **�����մϴ�**              ��\n");
        Gotoxy(x, y + 3);  printf("��                                          ��\n");
        Gotoxy(x, y + 4);  printf("��             X�� �¸��Դϴ�!              ��\n");
        Gotoxy(x, y + 5);  printf("��                                          ��\n");
        Gotoxy(x, y + 6);  printf("��      Esc�� ������ ������ ����˴ϴ�.     ��\n");
        Gotoxy(x, y + 7);  printf("��                                          ��\n");
        Gotoxy(x, y + 8);  printf("�ὺ���̽��� ������ ����ȭ������ ���ư��ϴ�.��\n");
        Gotoxy(x, y + 9);  printf("��                                          ��\n");
        Gotoxy(x, y + 10); printf("������������������������\n");
        Gotoxy(0, 22);
        re = _getch();
        switch (re)
        {
        case 32: //����ȭ������ ���ư���
            main();
        case 27: //��������
            exit(0);
        default: //�����Է¿� ���� ó��
            break;
        }
    }
    else if (num == 2) //O�¸��� ǥ��
    {
        system("cls");
        Gotoxy(x, y);      printf("������������������������\n");
        Gotoxy(x, y + 1);  printf("��                                          ��\n");
        Gotoxy(x, y + 2);  printf("��              **�����մϴ�**              ��\n");
        Gotoxy(x, y + 3);  printf("��                                          ��\n");
        Gotoxy(x, y + 4);  printf("��             O�� �¸��Դϴ�!              ��\n");
        Gotoxy(x, y + 5);  printf("��                                          ��\n");
        Gotoxy(x, y + 6);  printf("��      Esc�� ������ ������ ����˴ϴ�.     ��\n");
        Gotoxy(x, y + 7);  printf("��                                          ��\n");
        Gotoxy(x, y + 8);  printf("�ὺ���̽��� ������ ����ȭ������ ���ư��ϴ�.��\n");
        Gotoxy(x, y + 9);  printf("��                                          ��\n");
        Gotoxy(x, y + 10); printf("������������������������\n");
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
    else if (num == 3) //���ºν� ǥ��
    {
        system("cls");
        Gotoxy(x, y);      printf("������������������������\n");
        Gotoxy(x, y + 1);  printf("��                                          ��\n");
        Gotoxy(x, y + 2);  printf("��                                          ��\n");
        Gotoxy(x, y + 3);  printf("��             **���º��Դϴ�.**            ��\n");
        Gotoxy(x, y + 4);  printf("��                                          ��\n");
        Gotoxy(x, y + 5);  printf("��       Esc�� ������ ������ ����˴ϴ�.    ��\n");
        Gotoxy(x, y + 6);  printf("��                                          ��\n");
        Gotoxy(x, y + 7);  printf("�ེ���̽��� ������ ����ȭ������ ���ư��ϴ�.��\n");
        Gotoxy(x, y + 8);  printf("��                                          ��\n");
        Gotoxy(x, y + 9);  printf("��                                          ��\n");
        Gotoxy(x, y + 10); printf("������������������������\n");
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