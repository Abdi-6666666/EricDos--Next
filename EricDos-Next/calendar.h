#pragma once
#ifndef CALENDAR_H
#define CALENDAR_H

#include "bitcpp.h"
#include <ctime>
#include <iomanip>

using std::setw;
using std::min;

void calendar() {
    auto isLeap = [](int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        };
    auto daysInMonth = [&](int m, int y) {
        static int mdays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if (m == 2) return mdays[1] + (isLeap(y) ? 1 : 0);
        return mdays[m - 1];
        };

    // 初始化为今天（使用线程安全/安全接口）
    time_t t = time(nullptr);
    tm now{};
#if defined(_MSC_VER)
    localtime_s(&now, &t);    // MSVC 推荐的安全版本
#else
    // 在非 MSVC 环境回退到 localtime
    if (auto pnow = localtime(&t)) now = *pnow;
#endif

    int year = now.tm_year + 1900;
    int month = now.tm_mon + 1;
    int day = now.tm_mday;

    while (true) {
        clear_screen();
        cout << "---calendar---" << endl;
        cout << "press 'q' to return." << endl;
        cout << month << "/" << day << "/" << year << " " << endl;
        cout << "MON TUE WED THU FRI SAT SUN" << endl;

        // 计算本月第一天是星期几（tm_wday: 0=Sun ... 6=Sat）
        tm first = {};
        first.tm_year = year - 1900;
        first.tm_mon = month - 1;
        first.tm_mday = 1;
        mktime(&first);
        int wday = first.tm_wday;               // 0=Sun
        int start = (wday + 6) % 7;             // 转为 Monday=0 ... Sunday=6

        // 打印前置空格
        for (int i = 0; i < start; ++i) {
            cout << "    ";
        }

        int dim = daysInMonth(month, year);
        for (int d = 1; d <= dim; ++d) {
            cout << setw(3) << d << ' ';
            if ((start + d) % 7 == 0) cout << endl; // 每到星期天换行
        }
        cout << endl << endl;

        cout << "[p] previous month  [n] next month  [q] quit : ";
        string cmd;
        if (!getline(cin, cmd)) return; // 在异常输入时返回
        if (!cmd.empty()) {
            char c = cmd[0];
            if (c == 'q' || c == 'Q') return;
            if (c == 'n' || c == 'N') {
                month++;
                if (month > 12) { month = 1; year++; }
                // 把 day 限制到新月最大天数
                day = min(day, daysInMonth(month, year));
            }
            else if (c == 'p' || c == 'P') {
                month--;
                if (month < 1) { month = 12; year--; }
                day = min(day, daysInMonth(month, year));
            }
        }
        cout << endl;
    }
}

#endif