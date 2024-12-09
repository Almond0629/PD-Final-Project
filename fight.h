#pragma once
#include <iostream>
#include <cstdlib> 
#include <chrono>
#include <thread>
#include "characterMonster.h"
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

bool Character::restart(){
    string answer;
    cout << "這時有個神祕的聲音出現!" << endl;
    sleep(delayTime);
    cout << "我是迷宮陰間的掌管者" << endl;
    sleep(delayTime);
    cout << "現在你可以選擇是否要復活" << endl;
    cout << "在險惡的迷宮中，復活的代價就是..." << endl;
    sleep(delayTime);
    cout << "一條命10元!如果你沒錢了..." << endl;
    sleep(delayTime);
    cout << "就烹調背包中的食材並吃下營養的番茄牛肉燉湯吧!" << endl;
    cout << "這樣一來你一樣可以恢復一條命" << endl;
    cout << "想要復活並繼續冒險嗎？(Y/N)" << endl;
    cin >> std::ws;
    getline(cin, answer);
    
    if (answer == "Y" || answer == "y") {
        if(backpack.money < 10 && (backpack.beefCnt == 0 || backpack.tomatoCnt == 0)){
            cout << "你的錢包餘額: " << backpack.money << endl;
            cout << "錢包餘額不足!" << endl;
            cout << "你剩下 " << backpack.tomatoCnt << " 顆番茄與" << backpack.beefCnt << " 塊牛肉。" << endl;
            cout << "食材不足!" << endl;
            sleep(delayTime);
            gameOver();
        }
        else {
            cout << "你的錢包餘額: " << backpack.money << endl;
            if(backpack.money < 10) {
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
                backpack.money -= 10;
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
        sleep(delayTime);
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
                continue;
            }
            
            if (life == 0) {
                cout << "你被煮了！" << endl;
                sleep(delayTime);
                if(this->restart()) continue;
                else gameOver();
            }
        }
    }
    if (life == 0) {
        cout << "你被煮了！" << endl;
        sleep(delayTime);
        if(!this->restart()) gameOver();
    }

}
