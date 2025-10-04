#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <cstdlib>

#include "pacMan.h"

#define WIDTH 30
#define HEIGHT 15

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

int x, y, fruitX, fruitY, score;
int enemyX, enemyY;
bool gameOver;
char grid[HEIGHT][WIDTH];

void Setup() {
    gameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % (WIDTH - 2) + 1;
    fruitY = rand() % (HEIGHT - 2) + 1;
    enemyX = rand() % (WIDTH - 2) + 1;
    enemyY = rand() % (HEIGHT - 2) + 1;
    score = 0;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                grid[i][j] = '#';  // Boundary
            } else {
                grid[i][j] = ' ';
            }
        }
    }

    grid[fruitY][fruitX] = '$';
    grid[y][x] = 'P';
    // Note: We do not store the emojis in the grid array directly.
}

void Draw() {
    system("clear");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == y && j == x) {
                cout << "🟡";  // Draw player as yellow ball emoji
            } else if (i == fruitY && j == fruitX) {
                cout << "🍎";  // Draw fruit as food emoji
            } else if (i == enemyY && j == enemyX) {
                cout << "👻";  // Draw enemy as ghost emoji
            } else {
                cout << grid[i][j];
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void EnableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);    // Get the current terminal attributes
    term.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term); // Set the terminal attributes immediately
}

void DisableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);    // Get the current terminal attributes
    term.c_lflag |= ICANON | ECHO;     // Enable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term); // Set the terminal attributes immediately
}

bool kbhit() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    term2.c_cc[VMIN] = 0;
    term2.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSANOW, &term2);

    char ch;
    ssize_t nread = read(STDIN_FILENO, &ch, 1);

    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    if (nread == 1) {
        ungetc(ch, stdin);
        return true;
    }

    return false;
}

void Input() {
    if (kbhit()) {
        switch (cin.get()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'q':
                gameOver = true;
                break;
        }
    }
}

void MoveEnemy() {
    int move = rand() % 4;
    switch (move) {
        case 0:
            if (grid[enemyY][enemyX - 1] != '|')
                enemyX--;
            break;
        case 1:
            if (grid[enemyY][enemyX + 1] != '|')
                enemyX++;
            break;
        case 2:
            if (grid[enemyY - 1][enemyX] != '|')
                enemyY--;
            break;
        case 3:
            if (grid[enemyY + 1][enemyX] != '|')
                enemyY++;
            break;
    }
}

void Logic() {
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    if (x <= 0 || x >= WIDTH - 1 || y <= 0 || y >= HEIGHT - 1) {
        gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % (WIDTH - 2) + 1;
        fruitY = rand() % (HEIGHT - 2) + 1;
        grid[fruitY][fruitX] = '$';
    }

    // Clear the previous position of Pac-Man
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j] == 'P') {
                grid[i][j] = ' ';
            }
        }
    }

    // Move the enemy
    MoveEnemy();

    // Check if the player collides with the enemy
    if (x == enemyX && y == enemyY) {
        gameOver = true;
    }

    grid[y][x] = 'P';
}

void playPacMan() {

    cout << endl << endl;
    cout << "+------------------------Welcome to Pac Man-------------------------+" << endl << endl;
    cout << "\t\t💀 Jahan Zaib 💀👁" << endl << endl;
    EnableRawMode();
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(100000); // Sleep for 100 milliseconds
    }
    DisableRawMode();
}
