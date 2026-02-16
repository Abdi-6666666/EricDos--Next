#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H

#include "bitcpp.h"
#ifdef _WIN32
#include <windows.h>
#endif

void setting();
void theme_settings();
void set_light_theme() {
    // 白底绿字
    system("color 7A");
}
void set_dark_theme() {
    // 黑底绿字
    system("color 0A");
}

// 默认使用深色主题
namespace {
    struct ThemeInitializer {
        ThemeInitializer() {
            set_dark_theme();
        }
    } _theme_initializer_instance;
}

void setting() {
    while (true) {
        clear_screen();
        cout << "=== Settings ===" << endl;
        cout << "1. Themes" << endl;
        cout << "2. Back to main menu" << endl;
        cout << "Select an option: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                theme_settings();
                wait_for_enter("press any key to return");
                break;
            case 2:
                return;
            default:
                cout << "Invalid option!" << endl;
                wait_for_enter("press any key to return");
        }
    }
}

void theme_settings() {
    while (true) {
        clear_screen();
        cout << "=== Theme Settings ===" << endl;
        cout << "1. Light Theme" << endl;
        cout << "2. Dark Theme" << endl;
        cout << "3. Back to Settings" << endl;
        cout << "Select a theme: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                set_light_theme();
                cout << "Light theme applied!" << endl;
                wait_for_enter("press any key to return");
                break;
            case 2:
                set_dark_theme();
                cout << "Dark theme applied!" << endl;
                wait_for_enter("press any key to return");
                break;
            case 3:
                return;
            default:
                cout << "Invalid option!" << endl;
                wait_for_enter("press any key to return");
        }
    }
}

#endif
