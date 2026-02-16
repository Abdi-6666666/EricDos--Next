#pragma once
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "bitcpp.h"
#include "calculator.h"
#include "calendar.h"
#include "settings.h"
#include "store.h"
#include "tools.h"
#include <conio.h>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>

void main_menu() {
    set_dark_theme();
    while (true) {
        // Build menu lines and option map first
        int item_idx = 1;
        std::vector<int> opt_map; // 0:Calculator 1:Calendar 2:Store 3:Settings
        std::vector<std::string> menu_lines;

        if (!CALCULATOR && !CALENDAR && !STORE && !SETTINGS) {
            wait_for_enter("No available applications! Press Enter to exit...");
            return;
        }

        if (CALCULATOR) {
            menu_lines.push_back(std::to_string(item_idx) + ". Calculator");
            opt_map.push_back(0);
            item_idx++;
        }
        if (CALENDAR) {
            menu_lines.push_back(std::to_string(item_idx) + ". Calendar");
            opt_map.push_back(1);
            item_idx++;
        }
        if (STORE) {
            menu_lines.push_back(std::to_string(item_idx) + ". Store");
            opt_map.push_back(2);
            item_idx++;
        }
        if (SETTINGS) {
            menu_lines.push_back(std::to_string(item_idx) + ". Settings");
            opt_map.push_back(3);
            item_idx++;
        }
        menu_lines.push_back(std::to_string(item_idx) + ". Exit");
        int exit_code = item_idx;

        // input buffer for user's selection (allow editing while time updates)
        std::string input_buf;

        auto get_time_str = []() {
            using namespace std::chrono;
            auto now = system_clock::now();
            time_t t = system_clock::to_time_t(now);
            std::tm tm{};
#if defined(_MSC_VER)
            localtime_s(&tm, &t);
#else
            if (auto p = localtime(&t)) tm = *p;
#endif
            std::ostringstream oss;
            oss << std::put_time(&tm, "%m/%d/%Y,%H:%M:%S");
            return oss.str();
        };

        auto redraw = [&](const std::string &time_str, const std::string &buf) {
            clear_screen();
            cout << "Welcome to EricDos-Next-Windows!" << endl;
            cout << "Now is " << time_str << endl;
            cout << "=== Start Menu ===" << endl;
            for (const auto &ln : menu_lines) cout << ln << endl;
            cout << "Select an option: " << buf;
            cout.flush();
        };

        // Interactive input loop: update time once per second, allow typing with _kbhit/_getch
        using clock = std::chrono::steady_clock;
        auto last_tick = clock::now();
        std::string time_str = get_time_str();
        redraw(time_str, input_buf);
        while (true) {
            // handle keypresses
            if (_kbhit()) {
                int ch = _getch();
                if (ch == 13) { // Enter
                    break;
                }
                else if (ch == 8) { // Backspace
                    if (!input_buf.empty()) {
                        input_buf.pop_back();
                        redraw(time_str, input_buf);
                    }
                }
                else if (ch == 0 || ch == 224) { // special keys (arrows, function keys)
                    // discard next code
                    _getch();
                }
                else if (isprint(ch)) {
                    input_buf.push_back((char)ch);
                    redraw(time_str, input_buf);
                }
            }

            // update time every second
            auto now = clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - last_tick).count() >= 1) {
                last_tick = now;
                time_str = get_time_str();
                redraw(time_str, input_buf);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        // Parse input_buf into choice
        int choice = -1;
        try {
            if (!input_buf.empty()) choice = std::stoi(input_buf);
        }
        catch (...) { choice = -1; }

        if (choice == exit_code) {
            return;
        }
        else if (choice > 0 && choice < exit_code) {
            int func = opt_map[choice - 1];
            switch (func) {
            case 0:
                calculator();
                break;
            case 1:
                calendar();
                break;
            case 2:
                store();
                break;
            case 3:
                setting();
                break;
            }
        }
        else {
            wait_for_enter("Invalid option! Press Enter to continue...");
        }
    }
}

#endif
