#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "characterMonster.h"

const int MAX_MONSTER_CNT = 50;
const char PLAYER_SYMBOL = 'P';


class Maze {
private:
    Character player;
    int mazeSize;
    int prizeChance;// Percentage chance to place a prize on the path
    int monsterChance; // Percentage chance to meet a monster on the map
    int playerX, playerY;  // Player position
    int** grid;
    Monster* monsters[6];

    bool isInBounds(int x, int y);
    void shuffleDirections(int directions[4]);
    void generateMaze(int x, int y);
    void placePrize(int x, int y);

public:
    Maze(Character& _player, int _mazeSize, int _prizeChance, int _monsterChance);
    ~Maze();

    void generate(int randNum);
    void display();
    void movePlayer(char direction, bool &gameEnd, Character& player);
    void didWeMeetMonster(bool &metMonster);
};
