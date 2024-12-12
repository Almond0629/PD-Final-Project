#include "Maze.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

// Directions for moving in the grid (up, down, left, right)
const int DX[4] = {-1, 1, 0, 0}; 
const int DY[4] = {0, 0, -1, 1};

Maze::Maze(Character& _player, int _mazeSize, int _prizeChance, int _monsterChance)
    : player(_player), mazeSize(_mazeSize), prizeChance(_prizeChance), 
      monsterChance(_monsterChance), playerX(1), playerY(1) {
    // Initialize the maze with walls
    grid = new int*[mazeSize + 2];
    for (int i = 0; i < mazeSize + 2; i++) {
        grid[i] = new int[mazeSize + 2];
        for (int j = 0; j < mazeSize + 2; j++) {
            grid[i][j] = 1;
        }
    }
    monsters[0] = new Tomato("番茄");
    monsters[1] = new Egg("蛋");
    monsters[2] = new Apple("蘋果");
    monsters[3] = new Lettuce("生菜");
    monsters[4] = new Pork("豬肉");
    monsters[5] = new Beef("牛肉");
}

Maze::~Maze() {
    for (int i = 0; i < mazeSize + 2; i++) {
        delete grid[i];
    }
    delete[] grid;
}

bool Maze::isInBounds(int x, int y) {
    return x > 0 && y > 0 && x <= mazeSize && y <= mazeSize;
}

void Maze::shuffleDirections(int directions[4]) {
    for (int i = 3; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(directions[i], directions[j]);
    }
}

void Maze::generateMaze(int x, int y) {
    grid[y][x] = 0; // Mark the current cell as a path
    placePrize(x, y);

    int directions[4] = {0, 1, 2, 3};
    shuffleDirections(directions);

    for (int i = 0; i < 4; ++i) {
        int nx = x + DX[directions[i]] * 2;
        int ny = y + DY[directions[i]] * 2;

        if (isInBounds(nx, ny) && grid[ny][nx] == 1) {
            grid[y + DY[directions[i]]][x + DX[directions[i]]] = 0;
            placePrize(x + DX[directions[i]], y + DY[directions[i]]);
            generateMaze(nx, ny);   // Recursively generate the maze from the next cell
        }
    }
}

void Maze::placePrize(int x, int y) {
    if (rand() % 100 < prizeChance) {
        if (x != 1 && y != 2) {
            grid[y][x] = 2; // Ingredient
        }
    }
    if (rand() % 100 < prizeChance) {
        if (x != 1 && y != 2 && grid[y][x] != 2) {
            grid[y][x] = 3; // Money
        }
    }
}

void Maze::generate(int randNum) {
    srand(randNum + time(nullptr));
    generateMaze(1, 1);
    grid[playerY][playerX] = 0;
    grid[mazeSize][mazeSize + 1] = 0; // Exit path
}

void Maze::display() {
    for (int i = 0; i < mazeSize + 2; i++) {
        for (int j = 0; j < mazeSize + 2; j++) {
            if (i == playerY && j == playerX) {
                cout << "\033[31m" << PLAYER_SYMBOL << "\033[0m" << " ";
            } 
            else if (grid[i][j] == 1) {
                cout << "▧ "; // Wall
            } 
            else if (grid[i][j] == 2) {
                cout << "* "; // Prize
            } 
            else if (grid[i][j] == 3) {
                cout << "$ ";
            } 
            else {
                cout << "　"; // Path
            }
        }
        cout << "\n";
    }
}

void Maze::movePlayer(char direction, bool &gameEnd, Character& player) {
    int dx = 0, dy = 0;

    if (direction == 'W' || direction == 'w') {
        dy = -1;
    } else if (direction == 'S' || direction == 's') {
        dy = 1;
    } else if (direction == 'A' || direction == 'a') {
        dx = -1;
    } else if (direction == 'D' || direction == 'd') {
        dx = 1;
    } else {
        cout << "不明指令。請輸入w/a/s/d！\n";
        return;
    }

    int newX = playerX + dx;
    int newY = playerY + dy;

    if (newX == mazeSize + 1 && newY == mazeSize) {
        gameEnd = true;
    } 
    else {
        if (isInBounds(newX, newY) && grid[newY][newX] != 1) {
            if (grid[newY][newX] == 2) {
                int randInt = rand() % 6;
                player.putIntoBackPack(*monsters[randInt]);
                cout << "你蒐集到一個" << monsters[randInt]->getName() << "！\n";
                grid[newY][newX] = 0;
            } else if (grid[newY][newX] == 3) {
                int randInt = 1 + rand() % 10;
                cout << "你撿到" << randInt << "元！\n";
                player.putIntoBackPack(randInt);
                grid[newY][newX] = 0;
            }
            playerX = newX;
            playerY = newY;
        } else {
            cout << "撞牆！\n";
        }
    }
}

void Maze::didWeMeetMonster(bool &metMonster) {
    if (rand() % 100 < monsterChance) {
        metMonster = true;
    }
}
