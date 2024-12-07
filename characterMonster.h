#include<iostream>
#include<string>
#include <cstdlib>
#include <ctime>
#include <vector>
//#include<vector>
using namespace std;

void fight(){}

class Monster;

struct Position
{
    int x;
    int y;

    bool operator==(const Position& pos2) const
    {
        if (this->x == pos2.x && this->y == pos2.y) return true;
        else return false;
    }
};


class Monster
{
    friend void fight();
protected:
    string name;
    bool alive;
    Position position;
    //int attack;

public:
    Monster(string name,  Position position);
    ~Monster();
    
    int RPSchoiceAndPrint();
    void winOrLoseTheGame(bool winMonster);
    virtual void print() = 0;

};
Monster::Monster(string name,  Position position)
{
    this -> name = name;
    this -> alive = true;
    this->position = position;

}
Monster::~Monster()
{
}
int Monster::RPSchoiceAndPrint()
{
    int choices[] = {0, 2, 5};
    int makeChoice = choices[rand() % 3];
    // Generate random choice: 0 (Rock), 2 (Scissors), 5 (Paper)
    if (makeChoice == 0) {
        cout << this->name << " chose Rock!" << endl;
    } else if (makeChoice == 2) {
        cout << this->name << " chose Scissors!" << endl;
    } else if (makeChoice == 5) {
        cout << this->name << " chose Paper!" << endl;
    }

    return makeChoice;
}
void Monster::winOrLoseTheGame(bool winMonster)
{
    if (winMonster)
    {

    }
    else
    {
        alive = false;//damageOnLose 應該會包在monster的屬性
    }
}



class MonsterTeam
{
private:
    const int maxMonsterCnt ;
    int monsterCnt;
    Monster** monsterTeamArray;

public:
    MonsterTeam(int maxMonsterCnt);
    ~MonsterTeam();
    void addMonster(Monster& mosnter);
    Monster* operator[](int i) const;
};
MonsterTeam::MonsterTeam(int maxMonsterCnt) : maxMonsterCnt(maxMonsterCnt), monsterCnt(0) 
{
    monsterTeamArray = new Monster*[maxMonsterCnt];
    for (int i = 0; i < maxMonsterCnt; i++) {
        monsterTeamArray[i] = nullptr;
    }
}
MonsterTeam::~MonsterTeam()
{
    for (int i = 0; i < maxMonsterCnt; i++)
    {
        delete monsterTeamArray[i];
    }
    delete [] monsterTeamArray;
}
void MonsterTeam::addMonster(Monster& monster) 
{
    // 確保不超過上限
    if (monsterCnt < maxMonsterCnt) {
        // 建立新的 Monster 複製物件，並存到陣列中
        monsterTeamArray[monsterCnt++] = &monster;
    } else {
        std::cerr << "Monster team is full!" << std::endl;
    }
}
Monster* MonsterTeam::operator[](int i) const
{
    return monsterTeamArray[i];
}



class Tomato : public Monster
{
private:
    int attackPower; // Tomato 專屬屬性
public:
    Tomato(string name, Position position, int attackPower);
    ~Tomato();
    void print();
    //void RPSWith(const Character& oppenent);
    void specialAttack();    // Tomato 專屬方法
};
Tomato::Tomato(string name, Position position, int attackPower)
    : Monster(name, position)
{
    this ->attackPower = attackPower;
}
Tomato::~Tomato()
{
}
void Tomato::print(){
    cout << "            _              " <<endl;
    cout << "      /\\  | | / \\          " <<endl;
    cout << "     /  \\    /   \\         " <<endl;
    cout << "   --                --       " <<endl;
    cout << "  |                    |    " <<endl;
    cout << "  |     ^        ^     |   " <<endl;
    cout << "  |                    |   " <<endl;
    cout << "  |      (  v v   )    |  " <<endl;
    cout << "  |                    |   " <<endl;
    cout << "  ----------------------  " <<endl;
}


class Egg : public Monster
{
private:
    int attackPower; 
public:
    Egg(string name,Position position, int attackPower);
    ~Egg();
    void print();
    void specialAttack();  
};
Egg::Egg(string name, Position position, int attackPower)
    : Monster(name, position)
{
    this ->attackPower = attackPower;
}
Egg::~Egg()
{
}
void Egg::print(){
    cout << "   --------------------    " <<endl;
    cout << "  |                    |   " <<endl;
    cout << "  |     >        <     |   " <<endl;
    cout << "  |                    |   " <<endl;
    cout << "  |           0         |    " <<endl;
    cout << "  |                    |   " <<endl;
    cout << "  |          ___       |   " <<endl;
    cout << "  |          |_|       |    "    <<endl;
    cout << "  |                    |   " <<endl;
    cout << "  ----------------------  " <<endl;
}


class Apple:public Monster
{
private:
    /* data */
public:
    Apple(string name, Position position, int attackPower);
    ~Apple();
    void print();
};
Apple::Apple(string name, Position position, int attackPower): Monster(name, position)
{
}
Apple::~Apple()
{
}
void Apple::print()
{
    cout << "            /\\    " <<endl;
    cout << "           | | /\\   " <<endl;
    cout << "    /------   -----\\   " <<endl;
    cout << "   /                \\    " <<endl;
    cout << "  |     $       $     |   " <<endl;
    cout << "  |          >        |    " <<endl;
    cout << "  |          3        |   " <<endl;
    cout << "  \\                  /   " <<endl;
    cout << "    \\-------------  /  " <<endl;
}


class Lettuce:public Monster
{
private:
    /* data */
public:
    Lettuce(string name, Position position, int attackPower);
    ~Lettuce();
    void print();
};
Lettuce::Lettuce(string name, Position position, int attackPower): Monster(name, position)
{
}
Lettuce::~Lettuce()
{
}
void Lettuce::print()
{
    cout << "       /\\  /\\            " << endl;
    cout << "     /\\  /\\  /\\      " <<endl;
    cout << "    /  \\/  \\/  \\     " <<endl;
    cout << "    \\  /\\  /\\  /      " <<endl;
    cout << "     \\/  \\/  \\/  " <<endl;
    cout << "     |        |   " <<endl;
    cout << "     |   3  3 |    " <<endl;
    cout << "     |        |   " <<endl;
    cout << "     |    lettuce)   " <<endl;
    cout << "     \\       /   " <<endl;
    cout << "      -------   " <<endl;
}


class Pork:public Monster
{
private:
    /* data */
public:
    Pork(string name, Position position, int attackPower);
    ~Pork();
    void print();
};
Pork::Pork(string name, Position position, int attackPower): Monster(name, position)
{
}
Pork::~Pork()
{
}
void Pork::print()
{
    cout << "         /\\    / \\    " <<endl;
    cout << "      --/  \\--/   \\--   " <<endl;
    cout << "    /                  \\   " <<endl;
    cout << "   /                    \\    " <<endl;
    cout << "  |     x         x      |    " <<endl;
    cout << "  |                      |    " <<endl;
    cout << "  |          O O         |   " <<endl;
    cout << "   \\          -         /   " <<endl;
    cout << "    \\------------------/  " <<endl;
}


class Beef:public Monster
{
private:
    /* data */
public:
    Beef(string name, Position position, int attackPower);
    ~Beef();
    void print();
};
Beef::Beef(string name, Position position, int attackPower): Monster(name, position)
{
}
Beef::~Beef()
{
}
void Beef::print()
{
    cout << "                " <<endl;
    cout << "                " <<endl;
    cout << "     /- ^---^-\\   " <<endl;
    cout << "    /   o   o  \\    " <<endl;
    cout << "    |           |   " <<endl;
    cout << "  /-             -\\  " <<endl;
    cout << " /      Mooooooo   \\    " <<endl;
    cout << "  \\                /  " <<endl;
    cout << "   \\ ------------ /  " <<endl;
}


/////////////////////////////////////////////////////////////////////////////////////

struct Backpack {
    int money;
    vector<Monster*> monsterVector;

    Backpack(int initialMoney = 0) : money(initialMoney) {}
};

class Character
{
    friend void fight();
private:
    string name;
    int life;
    Position position;
    Backpack backpack;

public:
    Character(string name, int life,  Position position, int money);
    ~Character();
    void move(Position position);
    void winOrLoseTheGame(bool winCharacter);
    Position getCharacterPosition(const Character& c);
    void reduceMoneyAndPrint(int amount);
    void putIntoBackPack(int money);
    void putIntoBackPack(Monster& monster);
    void seeTheBackPackStatus();

};
Character::Character(string name, int life, Position position, int money)
    : name(name), life(life), position(position), backpack(money) {
}
Character::~Character()
{
}
void Character::move(Position position)
{
    this->position.x += position.x;
    this->position.y += position.y;
}
void Character::winOrLoseTheGame(bool winCharacter)
{
    if (winCharacter)
    {
        //putIntoBackPack(Monster& monster)
    }
    else
    {
        life -- ;//damageOnLose 應該會包在monster的屬性

        if (life <= 0)
        {
            cout << name << " has been defeated!" << endl;
        }
        else
        {
            cout  << " remaining life: " << life << endl;
        }
    }
}
Position Character::getCharacterPosition(const Character& c)
{
    return this->position;
}
void Character::reduceMoneyAndPrint(int amount)
{
    this->backpack.money -= 10;
    cout << name << " still have " << backpack.money << " Dollar." << endl;
}
void Character::putIntoBackPack(int moneyAmount)
{
    this->backpack.money += moneyAmount;
    cout << name << " now have " << backpack.money << " Dollar." << endl;
}
void Character::putIntoBackPack(Monster& monster)
{
    this->backpack.monsterVector.push_back(&monster);
}
void Character::seeTheBackPackStatus()
{
    cout << "Do you want to check money or monster? type in \"money\" or \"monster\""
            " or \"quit\" to stop searching" << endl;
    string command;
    getline(cin, command);

    if (command == "money") {
        cout << "You still have " << backpack.money << " dollar." << endl;
    } else if (command == "monster") {
        int tomatoCnt = 0, eggCnt = 0, appleCnt = 0, lettuceCnt = 0, porkCnt = 0, beefCnt = 0;

        for (Monster* monster : backpack.monsterVector) {
            if (dynamic_cast<Tomato*>(monster)) {
                tomatoCnt++;
            } else if (dynamic_cast<Egg*>(monster)) {
                eggCnt++;
            } else if (dynamic_cast<Apple*>(monster)) {
                appleCnt++;
            } else if (dynamic_cast<Lettuce*>(monster)) {
                lettuceCnt++;
            } else if (dynamic_cast<Pork*>(monster)) {
                porkCnt++;
            }
            else if (dynamic_cast<Beef*>(monster)) {
                beefCnt++;
            }
        }
        
        cout << "You have " << tomatoCnt << " tomato." << endl;
        cout << "You have " << eggCnt << " egg." << endl;
        cout << "You have " << appleCnt << " apple." << endl;
        cout << "You have " << lettuceCnt << " lettuce." << endl;
        cout << "You have " << porkCnt << " pork." << endl;
        cout << "You have " << beefCnt << " beef." << endl;

    } else if (command == "quit") {
        cout << "Exiting backpack check." << endl;
    } else {
        cout << "Invalid command. Try again!" << endl;
    }
}

