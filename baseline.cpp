#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include "unistd.h"
#include "Maze.cpp"
#include "characterMonster.cpp"
#include "functions.cpp"

using namespace std;

const int delay = 2;

int main()
{
    // game.exe execute 開頭台詞
    cout << "歡迎來到迷宮飯餐廳！" << endl;
    sleep(delay);
    cout << "..." << endl;
    sleep(delay);
    cout << "輸入任何按鍵以開始" << endl;

    // type "start" to start game, "achievement" to check the previous made cuisine, "delete" to delete game history
    //, "exit" to exit game, cout "invalid command" if the cin command matches none of these

    //=============="start"===============

    string menuCmd;
    bool gameStart = false;
    cin >> std::ws;
    while (getline(cin, menuCmd))
    {
        if (menuCmd == "start")
        {
            // type "easy", "normal", "hard" to switch difficulty, and change parameters depends on difficulty
            int difficulty = 0, characterLife, size, prizeChance, monsterChance;
            cout << "請輸入難易度: " << "\n";
            cout << "簡單：1" << "\n";
            cout << "正常：2" << "\n";
            cout << "困難：3" << "\n";
            sleep(1);
            
            while (difficulty != 1 && difficulty != 2 && difficulty != 3)
            {
                cin >> difficulty;
                if (cin.fail())
                {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "無效輸入！請輸入數字 1, 2 或 3。\n";
                    continue;
                }

                if (difficulty != 1 && difficulty != 2 && difficulty != 3)
                    cout << "請重新輸入難易度！" << endl;
            }

            switch (difficulty) {
                case 1:
                    characterLife = 5;
                    size = 11;
                    prizeChance = 8;
                    monsterChance = 7;
                    break;
                case 2:
                    characterLife = 5;
                    size = 13;
                    prizeChance = 8;
                    monsterChance = 9;
                    break;
                case 3:
                    characterLife = 5;
                    size = 15;
                    prizeChance = 8;
                    monsterChance = 11;
                    break;
            }

            //創建角色
            string characterName;
            cout << "請輸入名字： " << endl;
            cin >> std::ws;
            getline(cin, characterName);
            sleep(delay);
            Position pos;
            pos.x = 0;
            pos.y = 0;
            Character player = Character(characterName, characterLife, pos, 20);
            Tomato tomato("番茄");
            Egg egg("蛋");
            Apple apple("蘋果");
            Lettuce lettuce("生菜");
            Pork pork("豬肉");
            Beef beef("牛肉");
            Monster* monsterArray[] = {&tomato, &egg, &apple, &lettuce, &pork, &beef};

            // 生成地圖
            Maze* dungeons[3];
            for (int i = 0; i < 3; i++)
            {
                dungeons[i] = new Maze(player, size, prizeChance, monsterChance);
                dungeons[i]->generate(i);
            }

            // cout the background story and instruction to the player
            cout << "..." << endl;
            sleep(delay);
            cout << "你在總圖轟轟烈烈地de了12個小時的bug" << endl;
            sleep(delay);
            cout << "你想著: 好餓喔...午餐吃什麼" << endl;
            sleep(delay);
            cout << "突然感覺到一陣暈眩!!!" << endl;
            sleep(delay);
            cout << "此時你已經進入了神秘且險惡的迷宮!" << endl;
            sleep(delay);
            cout << "試著在迷宮裡收集食材、打敗怪物、並決定你的午餐吧!" << endl;
            sleep(delay);
            cout << "..." << endl;
            sleep(3);
            printInstruction();
            sleep(delay);

            //以輸入 wasd 控制玩家移動，每次移動都會更新terminal所顯示的地圖
            //也有其他指令可以輸入，"help"為顯示操作說明，"backpack"為打開背包，"exit"為離開遊戲
            int currLevel = 0;
            bool gameEnd = false;
            bool metMonster = false;
            dungeons[currLevel]->display();

            string inGameCmd;
            cin >> std::ws;
            while (getline(cin, inGameCmd))
            {              
                if (gameEnd == false && currLevel < 2) {
                    if (inGameCmd == "w" || inGameCmd == "a" || inGameCmd == "s" || inGameCmd == "d")
                    {
                        char moveCmd = inGameCmd[0];
                        dungeons[currLevel]->movePlayer(moveCmd, gameEnd, player);
                        dungeons[currLevel]->didWeMeetMonster(metMonster);
                        if (metMonster){
                            cout << "遇到怪物！\n";
                            srand(time(nullptr));
                            int r = rand() % 6;
                            monsterArray[r]->print();
                            player.fight(*monsterArray[r]);
                            metMonster = false;
                        }
                    }
                    else if (inGameCmd == "help") 
                    {
                        printInstruction();
                    }
                    else if (inGameCmd == "achievement") 
                    {
                        printAchievements();
                    }
                    else if (inGameCmd == "backpack") 
                    {
                        player.seeTheBackPackStatus();
                    }
                    else if (inGameCmd == "menu") 
                    {
                        cout << "遊戲紀錄不會被儲存，但是所得成就會，確認要退出本局遊戲嗎？" << endl;
                        cout << "輸入\"yes\"離開遊戲，或輸入其他東西回到主畫面。" << endl;
                        string exitCmd;
                        cin >> std::ws;
                        getline(cin, exitCmd);
                        if (exitCmd == "yes") 
                        {
                            cout << "輸入任何按鍵返回主選單" << endl;
                            break;
                        }
                        else if (exitCmd == "其他東西")
                        {
                            achievementGet("Seriously?");
                            gameStart = false;
                        }
                    }
                    else 
                    {
                        cout << "不明指令。再輸入一次！" << endl;
                    }

                    dungeons[currLevel]->display();

                    if (gameEnd && currLevel < 3) 
                    {
                        cout << "==================================" << endl;
                        cout << "恭喜來到下一層！" << endl;
                        sleep(delay);
                        currLevel++;   
                        if (currLevel < 2) 
                        {
                            dungeons[currLevel]->display();
                            gameEnd = false;
                        }
                        else break;
                    }
                    else {
                        cin >> std::ws;
                    }
                }
                else {
                    break;
                }

            }

            if (gameEnd)
            {
                cout << "..." << endl;
                sleep(3);
                cout << "(你似乎來到了一個房間，中間擺著一個鍋釜，牆上的水晶發出微弱又溫和的光線，地板不再粗糙而是經過打磨，看來終於來到了終點的寶物間)" << endl;
                sleep(6);
                cout << "乾，都已經夠餓了，還要走迷宮打怪，結果甚至不是拿到煮好的料理，這是什麼鬼餐廳啊" << endl;
                sleep(5);
                cout << "這是什麼? \"魔法鍋子 將食材放進以自動料理\"" << endl;
                sleep(4);
                cout << "什麼鬼，不就自動料理機，這旁邊甚至有插電哎，這算什麼寶物間啊" << endl;
                sleep(4);
                cout << "算了真的好餓，把背包的食材丟進去看看吧" << endl;
                sleep(4);
                player.cooking();
                cout << "謝謝完成本遊戲！希望你會喜歡！\n";
                sleep(delay);
                achievementGet("The End");
                sleep(delay);
                cout << "...\n";
                sleep(delay);

                cout << "輸入任何按鍵返回主選單" << endl;
                gameStart = false;
            }
            
        }

        //================"achievement"=====================
        else if (menuCmd == "achievement")
        {
            printAchievements();

            cout << "輸入任何按鍵返回主選單" << endl;
            gameStart = false;
        }

        //=================="exit"=======================
        else if (menuCmd == "exit")
        {
            cout << "遊戲歷史不會被儲存，但是所得成就會被保存，確認要退出嗎？" << endl;
            cout << "輸入\"yes\"離開遊戲，或輸入其他東西以取消。" << endl;
            string exitCmd;
            cin >> std::ws;
            getline(cin, exitCmd);
            if (exitCmd == "yes") 
            {
                cout << "餓了再見~" << endl;
                return 0;
            }
            else if (exitCmd == "其他東西")
            {
                achievementGet("Seriously?");
            }
        }
        else
        {
            if (!gameStart) gameStart = true;
            else cout << "不明輸入！請重新輸入" << endl;
            
            cout << "輸入\"start\"開始遊戲" << endl;
            cout << "輸入\"achievement\"檢視獲得的成就" << endl;
            cout << "輸入\"exit\"離開遊戲" << endl;

        }
    }
    
}


