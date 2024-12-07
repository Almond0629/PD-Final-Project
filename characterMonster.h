#include<iostream>
#include <cstdlib>
#include <ctime>
//#include<vector>
using namespace std;

void fight(){}

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

class Character
{
    friend void fight();
private:
    string name;
    int life;
    Position position;
public:
    Character(string name, int life,  Position position);
    ~Character();
    void move(Position position);
    void winOrLoseTheGame(bool winCharacter);
    Position getCharacterPosition(const Character& c);

};
Character::Character(string name, int life,  Position position)
{
    this -> name = name;
    this -> life = life;
    this->position = position;
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
        //cout << name << " wins the game!" << endl;
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



// int main()
// {
//     Position pos = {0, 5};
//     Apple tomato("hihi", pos, 100);
//     tomato.print();
//     return 0;
// }
