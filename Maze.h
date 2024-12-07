#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "characterMonster.h"

using namespace std;

const int PRIZE_CHANCE = 10; // Percentage chance to place a prize on the path
const int MONSTER_CHANCE = 10; // Percentage chance to meet a monater on the map
const int MAX_MONSTER_CNT = 40;
const char PLAYER_SYMBOL = 'P';

// Directions for moving in the grid (up, down, left, right)
const int DX[4] = {-1, 1, 0, 0};
const int DY[4] = {0, 0, -1, 1};

class Maze {
private:
    int mazeSize;
    int playerX, playerY;   // Player position
    int** grid;
public:
    MonsterTeam monsterTeam = MonsterTeam(MAX_MONSTER_CNT);
    int collectedPrizes;
    Maze(int _mazeSize) : playerX(1), playerY(1), collectedPrizes(0), mazeSize(_mazeSize) {
        // Initialize the maze with walls
        grid = new int*[mazeSize + 2];
        for (int i = 0; i < mazeSize + 2; i++) {
            grid[i] = new int[mazeSize + 2];
            for (int j = 0; j < mazeSize + 2; j++) {
                grid[i][j] = 1;
            }
        }
    }
    ~Maze() {
        for (int i = 0; i < mazeSize + 2; i++){
            delete grid[i];
        }
        delete[] grid;
    }

    bool isInBounds(int x, int y) {
        return x > 0 && y > 0 && x <= mazeSize && y <= mazeSize;
    }

    void shuffleDirections(int directions[4]) {
        for (int i = 3; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(directions[i], directions[j]);
        }
    }

    void generateMaze(int x, int y) {
        grid[y][x] = 0; // Mark the current cell as a path
        placePrize(x, y); // Possibly place a prize here

        // Create an array of indices to shuffle directions
        int directions[4] = {0, 1, 2, 3};
        shuffleDirections(directions);

        for (int i = 0; i < 4; ++i) {
            int nx = x + DX[directions[i]] * 2;
            int ny = y + DY[directions[i]] * 2;

            if (isInBounds(nx, ny) && grid[ny][nx] == 1) {
                // Remove the wall between the current cell and the next cell
                grid[y + DY[directions[i]]][x + DX[directions[i]]] = 0;
                placePrize(x + DX[directions[i]], y + DY[directions[i]]); // Possibly place a prize here
                // Recursively generate the maze from the next cell
                generateMaze(nx, ny);
            }
        }
    }

    void placePrize(int x, int y){
        if (rand() % 100 < PRIZE_CHANCE){ // Place a prize with a certain chance
            if (x != 1 && y != 2){
                grid[y][x] = 2;
            }
        }
    }


    void generate(int rdnum){
        srand(rdnum + time(nullptr));
        generateMaze(1, 1); // Start maze generation from the top-left corner
        grid[playerY][playerX] = 0; // Ensure the player's starting position is a path
    }

    void display() {
        for (int i = 0; i < mazeSize + 2; i++){
            for (int j = 0; j < mazeSize + 2; j++){
                if (i == playerY && j == playerX){
                    cout << PLAYER_SYMBOL << " "; // Show the player's position
                } 
                else if (grid[i][j] == 1){
                    cout << "▧ "; // Wall
                } 
                else if (grid[i][j] == 2){
                    cout << "* "; // Prize
                } 
                else {
                    cout << "　"; // Path
                }
            }
            cout << "\n";
        }
        cout << "Prizes collected: " << collectedPrizes << "\n\n";
    }

    void movePlayer(char direction, bool &gameEnd){
        int dx = 0, dy = 0;

        if (direction == 'W' || direction == 'w'){
            dy = -1;
        } 
        else if (direction == 'S' || direction == 's'){
            dy = 1;
        } 
        else if (direction == 'A' || direction == 'a'){
            dx = -1;
        } 
        else if (direction == 'D' || direction == 'd'){
            dx = 1;
        } 
        else {
            cout << "Invalid input. Use W/A/S/D to move.\n";
            return;
        }

        int newX = playerX + dx;
        int newY = playerY + dy;

        if (newX == mazeSize && newY == mazeSize){
            gameEnd = true;
        }
        else {
            if (isInBounds(newX, newY) && grid[newY][newX] != 1) { // Check for walls
                if (grid[newY][newX] == 2) {
                    cout << "You collected a prize!\n";
                    collectedPrizes++;
                    grid[newY][newX] = 0;
                }
                playerX = newX;
                playerY = newY;
            } 
            else {
                cout << "You can't move there!\n";
            }
        }
    }

    void didWeMeetMonster(bool &metMonster){
        if (rand() % 100 < MONSTER_CHANCE){
            metMonster = true;
        }
    }
};