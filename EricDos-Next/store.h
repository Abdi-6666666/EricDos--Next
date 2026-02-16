#pragma once
#ifndef STORE_H
#define STORE_H

#include "bitcpp.h"

bool STORE = true; 
bool SETTINGS = true; 
bool CALCULATOR = false; 
bool CALENDAR = false; 

void add_apps() {
    clear_screen();
    cout << "=== Add Apps ===" << endl;

    std::vector<int> map;
    int idx = 1;
    if (!CALCULATOR) {
        cout << idx << ". Calculator" << endl;
        map.push_back(0);
        ++idx;
    }
    if (!CALENDAR) {
        cout << idx << ". Calendar" << endl;
        map.push_back(1);
        ++idx;
    }
    cout << idx << ". Back to Store" << endl;

    int choice = 0;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (choice == idx) return; // back

    int mapIndex = choice - 1;
    if (mapIndex < 0 || mapIndex >= (int)map.size()) {
        wait_for_enter("Invalid option! Press Enter to return...");
        return;
    }

    int app = map[mapIndex];
    if (app == 0) {
        CALCULATOR = true;
        wait_for_enter("Calculator added! Press Enter to return...");
    } else if (app == 1) {
        CALENDAR = true;
        wait_for_enter("Calendar added! Press Enter to return...");
    }
}

void remove_apps() {
    clear_screen();
    cout << "=== Remove Apps ===" << endl;

    // Build dynamic list of removable apps
    std::vector<int> map; // maps displayed index -> app id
    int idx = 1;
    if (CALCULATOR) {
        cout << idx << ". Calculator" << endl;
        map.push_back(0);
        ++idx;
    }
    if (CALENDAR) {
        cout << idx << ". Calendar" << endl;
        map.push_back(1);
        ++idx;
    }
    cout << idx << ". Back to Store" << endl;

    int choice = 0;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (choice == idx) return; // back

    int mapIndex = choice - 1;
    if (mapIndex < 0 || mapIndex >= (int)map.size()) {
        wait_for_enter("Invalid option! Press Enter to return...");
        return;
    }

    int app = map[mapIndex];
    if (app == 0) {
        CALCULATOR = false;
        wait_for_enter("Calculator removed! Press Enter to return...");
    } else if (app == 1) {
        CALENDAR = false;
        wait_for_enter("Calendar removed! Press Enter to return...");
    }
}

void store() {
    while (true) {
        clear_screen();
        cout << "=== Store ===" << endl;
        cout << "Calculator - " << (CALCULATOR ? "On" : "Off") << endl;
        cout << "Calendar - " << (CALENDAR ? "On" : "Off") << endl;
        cout << "===============" << endl;
        cout << "1. Add apps" << endl;
        cout << "2. Remove apps" << endl;
        cout << "3. Back to main menu" << endl;
        cout << "Select an option: ";

        int choice = 0;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        switch (choice) {
            case 1:
                add_apps();
                break;
            case 2:
                remove_apps();
                break;
            case 3:
                return;
            default:
                wait_for_enter("Invalid option! Press Enter to return...");
                break;
        }
    }
}

#endif // STORE_H
