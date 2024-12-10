#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
using namespace std;

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
friend class Character;
protected:
    string name;
    bool alive;

public:
    Monster(string name);
    virtual ~Monster() {}
    
    int RPSchoiceAndPrint();
    void winOrLoseTheGame(bool winMonster);
    virtual void print() = 0;
    string getName(){ return name; };

};
Monster::Monster(string name)
{
    this -> name = name;
    this -> alive = true;

}
int Monster::RPSchoiceAndPrint()
{
    int choices[] = {0, 2, 5};
    int makeChoice = choices[rand() % 3];
    // Generate random choice: 0 (Rock), 2 (Scissors), 5 (Paper)
    if (makeChoice == 0) {
        cout << this->name << "選擇出石頭！" << endl;
    } else if (makeChoice == 2) {
        cout << this->name << "選擇出剪刀！" << endl;
    } else if (makeChoice == 5) {
        cout << this->name << "選擇出布！" << endl;
    }

    return makeChoice;
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

public:
    Tomato(string name);
    ~Tomato();
    void print();
    //void RPSWith(const Character& opponent);
};
Tomato::Tomato(string name)
    : Monster(name)
{

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
    Egg(string name);
    ~Egg();
    void print(); 
};
Egg::Egg(string name)
    : Monster(name)
{
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


class Apple: public Monster
{
private:
    /* data */
public:
    Apple(string name);
    ~Apple();
    void print();
};
Apple::Apple(string name): Monster(name)
{
}
Apple::~Apple()
{
}
void Apple::print(){
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


class Lettuce: public Monster
{
private:
    /* data */
public:
    Lettuce(string name);
    ~Lettuce();
    void print();
};
Lettuce::Lettuce(string name): Monster(name)
{
}
Lettuce::~Lettuce()
{
}
void Lettuce::print(){
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


class Pork: public Monster
{
private:
    /* data */
public:
    Pork(string name);
    ~Pork();
    void print();
};
Pork::Pork(string name): Monster(name)
{
}
Pork::~Pork()
{
}
void Pork::print(){
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


class Beef: public Monster
{
private:
    /* data */
public:
    Beef(string name);
    ~Beef();
    void print();
};
Beef::Beef(string name): Monster(name)
{
}
Beef::~Beef()
{
}
void Beef::print(){
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

    int tomatoCnt;
    int eggCnt;
    int appleCnt;
    int lettuceCnt;
    int porkCnt;
    int beefCnt;

    vector<Monster*> monsterVector;

    Backpack(int initialMoney = 0): money(initialMoney), tomatoCnt(0), eggCnt(0), appleCnt(0), lettuceCnt(0), porkCnt(0), beefCnt(0)
    {
        this -> money = initialMoney;
        this -> appleCnt = 0;
        this -> beefCnt = 0;
        this -> eggCnt = 0;
        this -> lettuceCnt = 0;
        this -> porkCnt = 0;
        this -> tomatoCnt = 0;
    }

    void addMonster(Monster* monster) {
        monsterVector.push_back(monster);

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
        } else if (dynamic_cast<Beef*>(monster)) {
            beefCnt++;
        }
    }
};

struct Recipe {
    string dishName;          // Dish name
    vector<string> ingredients; // ingredients needed

    Recipe(string _dishName, vector<string> _ingredients) : dishName(_dishName), ingredients(_ingredients) {}
};


class Character
{
    // friend struct Recipe;
private:
    string name;
    int life;
    Position position;
    Backpack backpack;
    vector<Recipe> recipes;
    vector<string> dishes; // save all the made dishes
    // are there enough ingredients for you to cook
    bool canCook(const Recipe& recipe) {
        for (int i = 0; i < recipe.ingredients.size(); i++) {
            const string& ingredient = recipe.ingredients[i]; // get the ingredients needed now

            // check if the backpack has enough ingredients
            if (ingredient == "tomato" && backpack.tomatoCnt <= 0) return false;
            if (ingredient == "egg" && backpack.eggCnt <= 0) return false;
            if (ingredient == "apple" && backpack.appleCnt <= 0) return false;
            if (ingredient == "lettuce" && backpack.lettuceCnt <= 0) return false;
            if (ingredient == "pork" && backpack.porkCnt <= 0) return false;
            if (ingredient == "beef" && backpack.beefCnt <= 0) return false;
        }
        return true;
    }

    // reduce the ingredients in the backpack
    void consumeIngredients(const Recipe& recipe) {
        for (int i = 0; i < recipe.ingredients.size(); i++){
            const string& ingredient = recipe.ingredients[i];
            if (ingredient == "tomato") backpack.tomatoCnt --;
            if (ingredient == "egg") backpack.eggCnt --;
            if (ingredient == "apple") backpack.appleCnt --;
            if (ingredient == "lettuce") backpack.lettuceCnt --;
            if (ingredient == "pork") backpack.porkCnt --;
            if (ingredient == "beef") backpack.beefCnt --;
        }
    }
    // get all the dishes you can make
    vector<Recipe> getAvailableDishes() {
        vector<Recipe> availableDishes;
        for (int i = 0; i < recipes.size(); i++){
            if (canCook(recipes[i])) {
                availableDishes.push_back(recipes[i]);
            }
        }
        return availableDishes;
    }

public:
    Character(string name, int life,  Position position, int money);
    ~Character();
    bool restart();
    bool playOrPay();
    void fight(Monster& monster);
    void move(Position position);
    void winOrLoseTheGame(bool winCharacter);
    Position getCharacterPosition(const Character& c);
    void reduceMoneyAndPrint(int amount);
    void putIntoBackPack(int money);
    void putIntoBackPack(Monster& monster);
    void seeTheBackPackStatus();
    void cooking();

};
Character::Character(string name, int life, Position position, int money)
    : name(name), life(life), position(position), backpack(money), 
    recipes({Recipe("番茄糖葫蘆", {"tomato"}), Recipe("煎蛋", {"egg"}), Recipe("蘋果切片", {"apple"}), Recipe("生菜沙拉", {"lettuce"}), 
    Recipe("鹽烤豬排", {"pork"}), Recipe("牛排", {"beef"}), Recipe("番茄炒蛋", {"tomato", "egg"}), Recipe("蘋果生菜沙拉", {"apple", "lettuce"}), 
    Recipe("蘋果燒豬肉", {"apple", "pork"}), Recipe("生菜包牛肉", {"lettuce", "beef"}), Recipe("番茄牛肉燉湯", {"tomato", "beef"}), 
    Recipe("塔塔牛肉", {"egg", "beef"}), Recipe("豬肉凱薩沙拉", {"egg", "lettuce", "pork"})}) {}
Character::~Character()
{
}
void Character::move(Position position)
{
    this->position.x += position.x;
    this->position.y += position.y;
}
Position Character::getCharacterPosition(const Character& c)
{
    return this->position;
}
void Character::reduceMoneyAndPrint(int amount)
{
    this->backpack.money -= 10;
    cout << name << "還有" << backpack.money << "元。" << endl;
}
void Character::putIntoBackPack(int moneyAmount)
{
    this->backpack.money += moneyAmount;
    cout << name << " 現在有" << backpack.money << "元。" << endl;
}
void Character::putIntoBackPack(Monster& monster)
{
    this->backpack.addMonster(&monster);
}
void Character::seeTheBackPackStatus()
{
    cout << "你想要看你有多少錢還是你有什麼食材？輸入\"money\"或\"monster\""
            "或\"quit\"停止輸入" << endl;
    string command;
    cin >> std::ws;
    getline(cin, command);

    if (command == "money") {
        cout << "你還有 " << backpack.money << " 元。" << endl;
    } 
    else if (command == "monster") {

        cout << "==================================" << endl;
        cout << "你有 " << backpack.tomatoCnt << " 顆番茄。" << endl;
        cout << "你有 " << backpack.eggCnt << " 顆蛋。" << endl;
        cout << "你有 " << backpack.appleCnt << " 顆蘋果。" << endl;
        cout << "你有 " << backpack.lettuceCnt << " 頭生菜。" << endl;
        cout << "你有 " << backpack.porkCnt << " 塊豬肉。" << endl;
        cout << "你有 " << backpack.beefCnt << " 塊牛肉。" << endl;
        cout << "==================================" << endl;

    } else if (command == "quit") {
        cout << "背包拉鍊拉起中。" << endl;
    } else {
        cout << "不明指令。再輸入一次！" << endl;
    }
}
void Character::cooking() {
    for(int i = 0; i < 30; i++) {
        vector<Recipe> availableDishes = getAvailableDishes();//把可以做的菜 放到該vector裡面

        if (availableDishes.empty()) {
            cout << "沒有足夠的食材來製作任何菜品。" << endl;
            break;
        }

        cout << "你可以製作以下菜品：" << endl;
        for (int i = 0; i < availableDishes.size(); ++i) {
            cout << i + 1 << ". " << availableDishes[i].dishName << endl;
        }
        cout << "請輸入一項菜品名稱來選擇要製作的菜，或者輸入\"quit\"退出：\n";

        string wannaCookDish;
        getline(cin, wannaCookDish);

        if (wannaCookDish == "quit") {
            cout << "退出烹飪模式。\n";
            break;
        }

        bool dishFound = false;
        for (size_t i = 0; i < availableDishes.size(); ++i) {
            if (wannaCookDish == availableDishes[i].dishName) {
                dishFound = true;

                // 將選擇的菜加入已製作列表
                dishes.push_back(availableDishes[i].dishName);

                // 消耗食材
                consumeIngredients(availableDishes[i]);

                cout << "成功製作了 " << availableDishes[i].dishName << "！" << endl;

                // 更新 availableDishes
                availableDishes = getAvailableDishes();
                break;
            }
        }
        if (!dishFound) {
            cout << "沒有找到匹配的菜品，請重新輸入。\n";
        }
        
    }
}
