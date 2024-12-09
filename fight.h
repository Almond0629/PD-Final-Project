#pragma once
#include <iostream>
#include "characterMonster.h"
using namespace std;

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
    cout << "野生的 " << monster.name << " 突然跳出來擋著你！" << endl;
    cout << "他決定以剪刀石頭布來對戰！" << endl;
    if(playOrPay()){ // accept the challenge
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
                cout << "你獲勝！ 已收服了 " << monster.name << " 進你的背包！" << endl;
                cout << "繼續冒險下去，並找到更多食材吧！" << endl;
                break;
            } 
            // player lost
            else if ((monsterChoice == 5 && playerChoice == "0") || 
                    (monsterChoice == 2 && playerChoice == "5") || 
                    (monsterChoice == 0 && playerChoice == "2")) {
                cout << "啊！你輸了！" << endl;
                life--;
                if(life == 0) { break; }
                else{
                    cout << "剩餘的生命值：" << life << endl;
                    break;
                }
            } 
            else {
                cout << "平手！再輸入一次！" << endl;
                continue;
            }
            
            if (life == 0) {
                cout << "你被煮了！" << endl;
                break;
            }
        }
    }
    if (life == 0) {
        cout << "你被煮了！" << endl;
    }

}
