#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Position   // for future purposes
{
    int x;
    int y;

    bool operator==(const Position& pos2) const;
};

class Monster
{
    friend class Character;

protected:
    string name;
    bool alive;   // for future purposes

public:
    Monster(string name);
    virtual ~Monster() {}
    int RPSchoiceAndPrint();
    // void winOrLoseTheGame(bool winMonster);
    virtual void print() = 0;
    string getName();
};

class Tomato : public Monster
{
public:
    Tomato(string name);
    ~Tomato();
    void print();
};

class Egg : public Monster
{
public:
    Egg(string name);
    ~Egg();
    void print();
};

class Apple : public Monster
{
public:
    Apple(string name);
    ~Apple();
    void print();
};

class Lettuce : public Monster
{
public:
    Lettuce(string name);
    ~Lettuce();
    void print();
};

class Pork : public Monster
{
public:
    Pork(string name);
    ~Pork();
    void print();
};

class Beef : public Monster
{
public:
    Beef(string name);
    ~Beef();
    void print();
};

struct Backpack
{
    int money;
    int tomatoCnt, eggCnt, appleCnt, lettuceCnt, porkCnt, beefCnt;
    vector<Monster*> monsterVector;

    Backpack(int initialMoney = 0);
    void addMonster(Monster* monster);
};

struct Recipe
{
    string dishName;
    vector<string> ingredients;
    Recipe(string _dishName, vector<string> _ingredients);
    bool beingCooked;
};

class Character
{
private:
    string name;
    int life;
    Position position;
    Backpack backpack;
    vector<Recipe> recipes;
    vector<string> dishes;

    bool canCook(const Recipe& recipe);
    void consumeIngredients(const Recipe& recipe);
    vector<Recipe> getAvailableDishes();

public:
    Character(string name, int life,  Position position, int money);
    ~Character();
    bool restart();
    bool playOrPay();
    void fight(Monster& monster);
    void move(Position position);
    // void winOrLoseTheGame(bool winCharacter);
    Position getCharacterPosition(const Character& c);
    void reduceMoneyAndPrint(int amount);
    void putIntoBackPack(int money);
    void putIntoBackPack(Monster& monster);
    void seeTheBackPackStatus();
    void cooking();
};
