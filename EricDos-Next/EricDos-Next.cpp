#include "main_menu.h"
using namespace std;

int main() {
    main_menu();
    return 0;
}



/*

*************************************************************************************************************
* EricDos-Next-Windows
* Author: Eric
* Description: A simple console-based application that simulates a basic operating system interface with a main menu, calculator, calendar, store, and settings. Users can add/remove apps from the store and switch themes in settings.
* Features:
* - Main menu with dynamic options based on installed apps
* - Real-time clock display in the main menu
* - Calculator supporting +, -, *, /, parentheses, and unary +/- with proper operator precedence
* - Calendar showing the current month with correct weekday alignment and leap year handling
* - Store to add/remove Calculator and Calendar apps
* - Settings to switch between light and dark themes (using Windows console color codes)
* - Robust input handling with _kbhit/_getch for interactive menu selection and editing
* - Clean code structure with separate headers for each module and a common bitcpp.h for utilities
************************************************************************************************************

*/