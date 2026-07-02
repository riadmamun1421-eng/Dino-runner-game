#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 70
#define GROUND 20

int dinoY = GROUND;
int jump = 0;
int velocity = 0;

int obstacleX = WIDTH;
int score = 0;
int gameOver = 0;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 100;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void drawBorder()
{
    int i;

    for(i = 0; i < WIDTH; i++)
    {
        gotoxy(i, GROUND + 1);
        printf("_");
    }
}

void drawDino()
{
    gotoxy(5, dinoY - 1);
    printf(" O ");

    gotoxy(5, dinoY);
    printf("/|\\");

    gotoxy(5, dinoY + 1);
    printf("/ \\");
}

void eraseDino()
{
    gotoxy(5, dinoY - 1);
    printf("   ");

    gotoxy(5, dinoY);
    printf("   ");

    gotoxy(5, dinoY + 1);
    printf("   ");
}

void drawObstacle()
{
    gotoxy(obstacleX, GROUND);
    printf("|");

    gotoxy(obstacleX, GROUND - 1);
    printf("|");
}

void eraseObstacle()
{
    gotoxy(obstacleX, GROUND);
    printf(" ");

    gotoxy(obstacleX, GROUND - 1);
    printf(" ");
}

void drawScore()
{
    gotoxy(WIDTH + 5, 5);
    printf("SCORE : %d", score);
}

void physics()
{
    if(jump)
    {
        dinoY += velocity;
        velocity++;

        if(dinoY >= GROUND)
        {
            dinoY = GROUND;
            jump = 0;
        }
    }
}

void input()
{
    if(kbhit())
    {
        char ch = getch();

        if(ch == 32 && !jump) // SPACE
        {
            jump = 1;
            velocity = -3;
        }

        if(ch == 27) // ESC
        {
            gameOver = 1;
        }
    }
}

void obstacleLogic()
{
    obstacleX--;

    if(obstacleX < 0)
    {
        obstacleX = WIDTH;
        score++;
    }
}

void collision()
{
    if(obstacleX >= 5 && obstacleX <= 7)
    {
        if(dinoY >= GROUND - 1)
        {
            gameOver = 1;
        }
    }
}

void gameOverScreen()
{
    system("cls");

    gotoxy(30, 10);
    printf("GAME OVER!");

    gotoxy(28, 12);
    printf("FINAL SCORE: %d", score);

    gotoxy(22, 14);
    printf("Press any key to exit...");

    getch();
}

int main()
{
    hideCursor();

    while(!gameOver)
    {
        eraseDino();
        eraseObstacle();

        input();
        physics();
        obstacleLogic();
        collision();

        drawDino();
        drawObstacle();
        drawBorder();
        drawScore();

        Sleep(50);

        gotoxy(0, 0);
    }

    gameOverScreen();

    return 0;
}
