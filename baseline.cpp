#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "unistd.h"
#include "Maze.h"
#include "characterMonster.h"
#include "fight.h"

using namespace std;

const int delay = 2;
void printInstruction();
bool printFileContents();
bool achievementGet(const string achievementName);

int main()
{
    // game.exe execute 開頭台詞
    cout << endl;
    cout << "輸入\"start\"開始遊戲\n";
    sleep(1);

    // type "start" to start game, "achievement" to check the previous made cuisine, "delete" to delete game history
    //, "exit" to exit game, cout "invalid command" if the cin command matches none of these

    //=============="start"===============

    string menuCmd;
    cin >> std::ws;
    while (getline(cin, menuCmd))
    {
        if (menuCmd == "start")
        {
            // type "easy", "normal", "hard" to switch difficulty, and change parameters depends on difficulty
            int difficulty, characterLife, size, prizeChance, monsterChance;
            cout << "請輸入難易度: " << "\n";
            cout << "簡單：1" << "\n";
            cout << "正常：2" << "\n";
            cout << "困難：3" << "\n";
            
            while (difficulty != 1 && difficulty != 2 && difficulty != 3)
            {
                cin >> difficulty;
                if (difficulty != 1 && difficulty != 2 && difficulty != 3)
                    cout << "請重新輸入難易度！";
            }

            switch (difficulty) {
                case 1:
                    characterLife = 1;
                    size = 11;
                    prizeChance = 8;
                    monsterChance = 8;
                    break;
                case 2:
                    characterLife = 18;
                    size = 15;
                    prizeChance = 5;
                    monsterChance = 10;
                    break;
                case 3:
                    characterLife = 15;
                    size = 19;
                    prizeChance = 3;
                    monsterChance = 12;
                    break;
            }

            //創建角色
            string characterName;
            cout << "請輸入名字： " << endl;
            cin >> std::ws;
            getline(cin, characterName);
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
            cout << "你在總圖轟轟烈烈地讀了12個小時的書" << endl;
            sleep(delay);
            cout << "突然感覺到一陣暈眩!!!" << endl;
            sleep(delay);
            cout << "你想著: 好餓喔...午餐吃什麼" << endl;
            sleep(delay);
            cout << "此時你已經進入了神秘且險惡的迷宮!" << endl;
            sleep(delay);
            cout << "試著在迷宮裡收集食材、打敗怪物、並決定你的午餐吧!" << endl;
            sleep(delay);
            cout << "需要任何幫忙請輸入help" << endl;
            sleep(delay);
            //以輸入 wasd 控制玩家移動，每次移動都會更新terminal所顯示的地圖
            //也有其他指令可以輸入，"help"為顯示操作說明，"backpack"為打開背包，"exit"為離開遊戲
            int currLevel = 0;
            bool gameEnd = false;
            bool metMonster = false;
            dungeons[currLevel]->display();

            string inGameCmd;
            cout << "輸入指令w/s/a/d來控制上/下/左/右： \n";
            cin >> std::ws;
            while (getline(cin, inGameCmd))
            {              
                if (gameEnd == false && currLevel < 3) {
                    if (inGameCmd == "w" || inGameCmd == "a" || inGameCmd == "s" || inGameCmd == "d")
                    {
                        char moveCmd = inGameCmd[0];
                        dungeons[currLevel]->movePlayer(moveCmd, gameEnd, player);
                        dungeons[currLevel]->didWeMeetMonster(metMonster);
                        if (metMonster){
                            cout << "遇到怪物！\n";
                            srand(time(nullptr));
                            player.fight(*monsterArray[rand() % 6]);
                            metMonster = false;
                        }
                    }
                    else if (inGameCmd == "help") 
                    {
                        printInstruction();
                    }
                    else if (inGameCmd == "achievement") 
                    {
                        printFileContents();
                    }
                    else if (inGameCmd == "backpack") 
                    {
                        player.seeTheBackPackStatus();
                    }
                    else if (inGameCmd == "exit") 
                    {
                        cout << "遊戲歷史不會被儲存，但是所得成就會，確認要退出嗎？" << endl;
                        cout << "輸入\"yes\"離開遊戲，或輸入其他東西回到主畫面。" << endl;
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
                            cout << "Get achievement- \"Seriously?\" " << endl;
                            achievementGet("Seriously?");
                        }
                    }
                    else 
                    {
                        cout << "不明指令。再輸入一次！" << endl;
                    }

                    dungeons[currLevel]->display();

                    if (gameEnd && currLevel < 3) 
                    {
                        cout << "恭喜過關！" << endl;
                        currLevel++;   
                        gameEnd = false;
                        if (currLevel < 3) dungeons[currLevel]->display();
                    }
                    else {
                        cin >> std::ws;
                    }
                }
                else {
                    break;
                }
            }

            cout << "..." << endl;
            sleep(2.5);
            cout << "(你似乎來到了一個房間，中間擺著一個鍋釜，牆上的水晶發出微弱又溫和的光線，地板不再粗糙而是經過打磨，看來終於來到了終點的寶物間)" << endl;
            sleep(5.5);
            cout << "乾，都已經夠餓了，還要走迷宮打怪，結果甚至不是拿到煮好的料理，這是什麼鬼餐廳啊" << endl;
            sleep(4.5);
            cout << "這是什麼? \"魔法鍋子 將食材放進以自動料理\"" << endl;
            sleep(4);
            cout << "什麼鬼，不就自動料理機，這旁邊甚至有插電哎，這算什麼寶物間啊" << endl;
            sleep(4.2);
            cout << "算了真的好餓，把背包的食材丟進去看看吧" << endl;
            sleep(4);
            player.cooking();
            cout << "回到主畫面。\n";
        }

        //================"achievement"=====================
        else if (menuCmd == "achievement")
        {
            printFileContents();
        }

        //=================="exit"=======================
        else if (menuCmd == "exit")
        {
            cout << "遊戲歷史不會被儲存，但是所得成就會，確認要退出嗎？" << endl;
            cout << "輸入\"yes\"離開遊戲，或輸入其他東西回到主畫面。" << endl;
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
                cout << "Get achievement- \"Seriously?\" " << endl;
                achievementGet("Seriously?");
                continue;
            }
            else continue;
        }
    }
    
}

void printInstruction()
{
    cout << "you can type in: "<< endl;
    cout << "-help- show this instruction" << endl;
    cout << "-backpack- open your backpack and see your stuff" << endl;
    cout << "-achievement- show your achievement" << endl;
    cout << "-w- move upward" << endl;
    cout << "-a- move left" << endl;
    cout << "-s- move backward" << endl;
    cout << "-d- move right" << endl;
    cout << "-exit- exit the game" << endl;
}

//獲得成就(generated by chatgpt)
bool achievementGet(const string achievementName)
{
    const string fileName = "achievements.txt";

    // Open the file for reading
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return false;
    }

    vector<string> lines;
    string line;

    // Read each line and store it in a vector
    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    // Close the input file
    inFile.close();

    // Modify the specific boolean value
    for (size_t i = 0; i < lines.size() - 1; i += 2) { // Iterate only over even lines containing the boolean
        if (lines[i].find(achievementName) != string::npos) { // Replace "Ending" with the achievement you want to change
            if (lines[i][0] == '0') {
                lines[i][0] = '1'; // Change '0' to '1' to mark as completed
            } 
        }
    }

    // Open the file for writing (overwrite mode)
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    // Write the modified content back to the file
    for (const auto &modifiedLine : lines) {
        outFile << modifiedLine << "\n";
    }

    // Close the output file
    outFile.close();

    // cout << "Achievement status successfully modified." << endl;
    return true;
}

bool printFileContents() 
{
    const string fileName = "achievements.txt";

    // Open the file for reading
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return false;
    }

    string line1, line2;
    while (getline(inFile, line1)) {
        // Skip the boolean flag (first element of each pair of lines)
        bool achievementComplete = false;
        if (line1[0] == '1') {
            achievementComplete = true;
            line1 = line1.substr(2); // Remove the leading boolean and space
        }
        else if (line1[0] == '0')
        {
            line1 = line1.substr(2);
        }

        // Read the description line
        if (getline(inFile, line2)) {
            if (achievementComplete)
            {
                cout << line1 << " - " << line2 << endl;
            }
            else
            {
                cout << "??? - ???" << endl;
            }         
            inFile.close();
            return true;
        }
        else 
        {
            inFile.close();
            return false;
        }
        
    }

}
