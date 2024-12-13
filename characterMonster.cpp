#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <unistd.h>
#include"characterMonster.h"
#include "functions.cpp"
using namespace std;

const int delayTime = 2;

void gameOver(){

    cout << "告別的時間總是來得特別快..." << endl;
    sleep(delayTime);
    cout << "離開迷宮之前，我有個忠告要給你" << endl;
    sleep(delayTime);
    cout << "今天午餐就吃活大自助餐吧!還有..." << endl;
    sleep(delayTime);
    cout << "吃飽之後就快去讀書!" << endl;
    cout << "為你的GPA奮鬥!" << endl;
    sleep(delayTime);
    cout << "Game Over!" << endl;
    exit(0);
}


// Position methods
bool Position::operator==(const Position& pos2) const
{
    return this->x == pos2.x && this->y == pos2.y;
}

// Monster methods
Monster::Monster(string name) : name(name), alive(true) {}

int Monster::RPSchoiceAndPrint()
{
    int choices[] = {0, 2, 5};
    int makeChoice = choices[rand() % 3];
    if (makeChoice == 0) cout << this->name << "選擇出石頭！" << endl;
    else if (makeChoice == 2) cout << this->name << "選擇出剪刀！" << endl;
    else if (makeChoice == 5) cout << this->name << "選擇出布！" << endl;
    return makeChoice;
}

string Monster::getName() { return name; }

// Derived Monsters' methods
Tomato::Tomato(string name) : Monster(name) {}
Tomato::~Tomato() {}
void Tomato::print() { 
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

Egg::Egg(string name) : Monster(name) {}
Egg::~Egg() {}
void Egg::print() { 
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

Apple::Apple(string name) : Monster(name) {}
Apple::~Apple() {}
void Apple::print() {    
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

Lettuce::Lettuce(string name) : Monster(name) {}
Lettuce::~Lettuce() {}
void Lettuce::print() { 
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

Pork::Pork(string name) : Monster(name) {}
Pork::~Pork() {}
void Pork::print() { 
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

Beef::Beef(string name) : Monster(name) {}
Beef::~Beef() {}
void Beef::print() {     cout << "                " <<endl;
    cout << "                " <<endl;
    cout << "     /- ^---^-\\   " <<endl;
    cout << "    /   o   o  \\    " <<endl;
    cout << "    |           |   " <<endl;
    cout << "  /-             -\\  " <<endl;
    cout << " /      Mooooooo   \\    " <<endl;
    cout << "  \\                /  " <<endl;
    cout << "   \\ ------------ /  " <<endl;
}

// Backpack methods
Backpack::Backpack(int initialMoney) : money(initialMoney), tomatoCnt(0), eggCnt(0), appleCnt(0), lettuceCnt(0), porkCnt(0), beefCnt(0) {}

void Backpack::addMonster(Monster* monster)
{
    monsterVector.push_back(monster);
    if (dynamic_cast<Tomato*>(monster)) tomatoCnt++;
    else if (dynamic_cast<Egg*>(monster)) eggCnt++;
    else if (dynamic_cast<Apple*>(monster)) appleCnt++;
    else if (dynamic_cast<Lettuce*>(monster)) lettuceCnt++;
    else if (dynamic_cast<Pork*>(monster)) porkCnt++;
    else if (dynamic_cast<Beef*>(monster)) beefCnt++;
}

// Recipe methods
Recipe::Recipe(string _dishName, vector<string> _ingredients) : dishName(_dishName), ingredients(_ingredients), beingCooked(false) {}

// Character methods
Character::Character(string name, int life, Position position, int money)
    : name(name), life(life), position(position), backpack(money), 
    recipes({Recipe("番茄糖葫蘆", {"tomato"}), Recipe("煎蛋", {"egg"}), Recipe("蘋果切片", {"apple"}), Recipe("生菜沙拉", {"lettuce"}), 
    Recipe("鹽烤豬排", {"pork"}), Recipe("牛排", {"beef"}), Recipe("番茄炒蛋", {"tomato", "egg"}), Recipe("蘋果生菜沙拉", {"apple", "lettuce"}), 
    Recipe("蘋果燒豬肉", {"apple", "pork"}), Recipe("生菜包牛肉", {"lettuce", "beef"}), Recipe("番茄牛肉燉湯", {"tomato", "beef"}), 
    Recipe("塔塔牛肉", {"egg", "beef"}), Recipe("豬肉凱薩沙拉", {"egg", "lettuce", "pork"})})
{}
Character::~Character() {}

void Character::vo(Position position)
{
    this->position.x += position.x;
    this->position.y += position.y;
}

bool Character::canCook(const Recipe& recipe) {
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

void Character::consumeIngredients(const Recipe& recipe) {
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

vector<Recipe>Character::getAvailableDishes() {
    vector<Recipe> availableDishes;
    for (int i = 0; i < recipes.size(); i++){
        if (canCook(recipes[i]) && recipes[i].beingCooked == false) {
            availableDishes.push_back(recipes[i]);
        }
    }
    return availableDishes;
}

Position Character::getCharacterPosition(const Character& c)
{
    return this->position;
}

void Character::reduceMoneyAndPrint(int amount)
{
    backpack.money -= amount;
    cout << name << "還有" << backpack.money << "元。" << endl;
}

void Character::putIntoBackPack(int moneyAmount)
{
    backpack.money += moneyAmount;
    cout << name << " 現在有" << backpack.money << "元。" << endl;
}

void Character::putIntoBackPack(Monster& monster)
{
    backpack.addMonster(&monster);
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
        vector<Recipe> availableDishes = getAvailableDishes();   // get all the available dishes

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
            sleep(delayTime);

            if (dishes.size() == 0)
            {
                cout << "你什麼料理都沒做出來，看來今天註定只能在飢餓中debug了\n";
            }
            else 
            {
                for (size_t i = 0; i < dishes.size(); ++i) {
                    cout << "你總共製作了: " << i + 1 << ". " << dishes[i] << endl;
                }
                sleep(delayTime);
                cout << "吃著你的午餐，你又充滿了活力，又有能量可以繼續de 12小時的bug了\n";
                sleep(4);

                bool masterChef = true;
                for (size_t i = 0; i < recipes.size(); i++)
                {
                    if (recipes[i].beingCooked == 0) masterChef = false;
                }
                if (masterChef) 
                {
                    achievementGet("Master Chef");
                    sleep(delayTime);
                }
            }

            break;
        }

        bool dishFound = false;
        for (size_t i = 0; i < availableDishes.size(); ++i) {
            if (wannaCookDish == availableDishes[i].dishName) {
                dishFound = true;

                // 將選擇的菜加入已製作列表
                dishes.push_back(availableDishes[i].dishName);
                recipes[i].beingCooked = true;

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

bool Character::restart(){
    string answer;
    cout << "這時有個神祕的聲音出現!" << endl;
    sleep(delayTime);
    cout << "我是迷宮陰間的掌管者" << endl;
    sleep(delayTime);
    cout << "現在你可以選擇是否要復活" << endl;
    cout << "在險惡的迷宮中，復活的代價就是..." << endl;
    sleep(delayTime);
    cout << "一條命15元!如果你沒錢了..." << endl;
    sleep(delayTime);
    cout << "就烹調背包中的食材並吃下營養的番茄牛肉燉湯吧!" << endl;
    cout << "這樣一來你一樣可以恢復一條命" << endl;
    cout << "想要復活並繼續冒險嗎？(Y/N)" << endl;
    cin >> std::ws;
    getline(cin, answer);
    
    if (answer == "Y" || answer == "y") {
        if(backpack.money < 15 && (backpack.beefCnt == 0 || backpack.tomatoCnt == 0)){
            cout << "你的錢包餘額: " << backpack.money << endl;
            cout << "錢包餘額不足!" << endl;
            cout << "你剩下 " << backpack.tomatoCnt << " 顆番茄與" << backpack.beefCnt << " 塊牛肉。" << endl;
            cout << "食材不足!" << endl;
            sleep(delayTime);
            gameOver();
        }
        else {
            cout << "你的錢包餘額: " << backpack.money << endl;
            if(backpack.money < 15) {
                cout << "錢包餘額不足!" << endl;
                cout << "你剩下 " << backpack.tomatoCnt << " 顆番茄與" << backpack.beefCnt << " 塊牛肉。" << endl;
                cout << "大廚使用了一顆番茄與一塊牛肉做成營養的番茄牛肉燉湯!" << endl;
                cout << "吃下營養的番茄牛肉燉湯並恢復元氣吧!" << endl;
                backpack.tomatoCnt--;
                backpack.beefCnt--;
                cout << "你剩下 " << backpack.tomatoCnt << " 顆番茄與" << backpack.beefCnt << " 塊牛肉。" << endl;
                sleep(delayTime);
            }
            else{
                cout << "太棒了!辛苦賺來的錢足以讓你復活!" << endl;
                sleep(delayTime);
                backpack.money -= 15;
                cout << "你的錢包餘額: " << backpack.money << endl;
            }
            this->life++;
            cout << "現在你擁有1條新生命!"<< endl;
            cout << "回到陽間繼續冒險吧!" << endl;
            sleep(delayTime);
        }

        return true;
    }

    else {
        return false;
    }
}


bool Character::playOrPay(){
    while (backpack.money >= 10) {
        cout << "要對戰還是要賄賂怪物？ (1: 接受挑戰，2: 付10元賄賂怪物)" << endl;
        cout << "請輸入選擇：";
        string startChoice;
        cin >> std::ws;
        getline(cin, startChoice);
        
        if (startChoice == "1") {
            cout << "你接受挑戰！" << endl;
            return true;
        } else if (startChoice == "2") {
            cout << "你選擇賄賂。已從錢包扣10元。Shame on you!" << endl;
            reduceMoneyAndPrint(10);
            return false;
        } else {
            cout << "不明輸入，請輸入1或2！" << endl;
            continue;
        }
    }
    
    if(backpack.money < 10) {
        cout << "你已經沒錢了！接受挑戰吧！" << endl;
        return true;
    }
}


void Character::fight(Monster& monster){
    sleep(delayTime);
    cout << "野生的 " << monster.name << " 突然跳出來擋著你！" << endl;
    sleep(delayTime);
    cout << "他決定以剪刀石頭布來對戰！" << endl;
    sleep(delayTime);
    if(playOrPay()){ // accept the challenge
    int tiedCnt = 0;
        while (life > 0) {
            cout << "輸入 5 (布)，2 (剪刀)，0 (石頭) 來對戰。" << endl;
            cout << "輸入你的選擇： ";
            string playerChoice;
            cin >> std::ws;
            getline(cin, playerChoice);
    
            if (playerChoice != "5" && playerChoice != "2" && playerChoice != "0") {
                cout << "不明的輸入，請輸入 5 (布)，2 (剪刀)，0 (石頭)！" << endl;
                continue;
            }
    
            int monsterChoice = monster.RPSchoiceAndPrint();
            // player wins
            if ((playerChoice == "5" && monsterChoice == 0) || 
                (playerChoice == "2" && monsterChoice == 5) || 
                (playerChoice == "0" && monsterChoice == 2)) {
                putIntoBackPack(monster);
                cout << this->name << " 你贏了！ 已收服 " << monster.name << " 進你的背包！" << endl;
                sleep(delayTime);
                cout << "繼續冒險下去，並找到更多食材吧！" << endl;
                sleep(delayTime);
                break;
            } 
            // player lost
            else if ((monsterChoice == 5 && playerChoice == "0") || 
                    (monsterChoice == 2 && playerChoice == "5") || 
                    (monsterChoice == 0 && playerChoice == "2")) {
                cout << "啊！你輸了！" << endl;
                life--;
                sleep(delayTime);
                if(life == 0) { break; }
                else{
                    cout << "剩餘的生命值：" << life << endl;
                    sleep(delayTime);
                    break;
                }
            } 
            else {
                cout << "平手！再輸入一次！" << endl;
                tiedCnt++;
                if (tiedCnt == 4) achievementGet("Destiny");
                continue;
            }
            
            if (life == 0) {
                cout << "你被煮了！" << endl;
                sleep(delayTime);
                achievementGet("Monster's lunch");
                sleep(delayTime);
                if(this->restart()) continue;
                else gameOver();
            }
        }
    }
    if (life == 0) {
        cout << "你被煮了！" << endl;
        sleep(delayTime);
        achievementGet("Monster's lunch");
        sleep(delayTime);
        if(!this->restart()) gameOver();
    }

}

