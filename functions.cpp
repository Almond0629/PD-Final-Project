#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <string>
#include <chrono>
#include <thread>
#include "characterMonster.h"
using namespace std;

void printInstruction()
{
    cout << "==================================" << endl;
    cout << "輸入\"w\"向上移動" << endl;
    cout << "輸入\"a\"向左移動" << endl;
    cout << "輸入\"s\"向下移動" << endl;
    cout << "輸入\"d\"向右移動" << endl;
    cout << "輸入\"help\"呼叫出此選單" << endl;
    cout << "輸入\"achievement\"查看獲得的成就" << endl;
    cout << "輸入\"backpack\"打開背包" << endl;
    cout << "輸入\"menu\"返回主選單" << endl;
    cout << endl;
    cout << "P - 玩家" << endl;
    cout << "▧ - 障礙物" << endl;
    cout << "$ - 金幣(可拾取)" << endl;
    cout << "* - 食材(可拾取)" << endl;
    cout << "使用w/a/s/d操作玩家移動，突破迷宮吧！" << endl;
    cout << "==================================" << endl;
}

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
                cout << "Get achievement- \"" << achievementName << "\"" << endl;
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
    for (const string &modifiedLine : lines) {
        outFile << modifiedLine << "\n";
    }

    // Close the output file
    outFile.close();

    // cout << "Achievement status successfully modified." << endl;
    return true;
}

void printAchievements() 
{
    const string fileName = "achievements.txt";

    // Open the file for reading
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
    }

    cout << "=========================" << endl;

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
        }
        else 
        {
            inFile.close();
        }
        
    }

    cout << "=========================" << endl;

}