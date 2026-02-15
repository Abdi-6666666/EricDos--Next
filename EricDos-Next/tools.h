#pragma once
#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <limits>
#include <string>
#include <cstdlib> // for system()

using namespace std;

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait_for_enter(const string& prompt) {
    if (!prompt.empty()) {
        cout << prompt;
        cout.flush();
    }
    // 清除可能残留的输入并等待用户按回车
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

#endif // !TOOLS_H