#include "bitcpp.h"
#include "calculator.h"
#include "calendar.h"

#include "tools.h"
using namespace std;


void main_menu() {
    while (true) {
        clear_screen();
        cout << "=== Start Menu ===" << endl;
        cout << "1. Calculator" << endl;
        cout << "2. Calendar" << endl;
        cout << "3. Exit" << endl;
        cout << "Select an option: ";
        string choice;
        if (!getline(cin, choice)) break; // 在异常输入时退出
        if (choice == "1") {
            calculator();
            wait_for_enter("Press Enter to return to menu...");
        }
        else if (choice == "2") {
            calendar();
            wait_for_enter("Press Enter to return to menu...");
        }
        else if (choice == "3") {
            break;
        }
    }

}

int main() {
    main_menu();
    return 0;
}
