#pragma warning (disable:4996)
#include <iostream> //Allows us to input and output
#include <string> //Allows us to use strings
#include <ctime> //Allows us to get current time

using namespace std;

//Clears screen after user choice
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

//Makes sure that numbers always output with 2 digits
string twoDigitString(unsigned int n) {
    string str = to_string(n);

    if (str.length() != 2) {
        str = "0" + str;
    }

    return str;
}

//Function to fill space with a certain character *same as string() function*
string nCharString(size_t n, char c) {
    string fill = string(n, c);

    return fill;
}

//Formats the time in Military time
string formatTime24(unsigned int h, unsigned int m, unsigned int s) {
    string milTime = twoDigitString(h) + ":" + twoDigitString(m) + ":" + twoDigitString(s);

    return milTime;
}

//Formats the time to a standard 12 hour format
string formatTime12(unsigned int hour, unsigned int minute, unsigned int second) {
    string amPm;
    amPm = "A M";

    if (hour == 0) {
        amPm = "A M";
        hour = 12;
    }
    else if (hour == 12) {
        amPm = "P M";
    }
    else if (hour > 12 && hour < 24) {
        amPm = "P M";
        hour = hour - 12;
    }
    else if (hour == 24) {
        amPm = "A M";
        hour = 0;
    }
    string stdTime = twoDigitString(hour) + ":" + twoDigitString(minute) + ":" + twoDigitString(second) + " " + amPm;

    return stdTime;
}

//Displays the user menu prompts
void printMenu() {
    string strings[] = { "Add One Hour", "Add One Minute", "Add One Second", "Exit Program" };

    cout << nCharString(30, '*') << endl;

    for (unsigned int s = 1; s <= 4; ++s) {
        cout << "* " << s << " - " << strings[s - 1] << nCharString(30 - (size(strings[s - 1]) + 7), ' ') << '*' << endl;
    }

    cout << nCharString(30, '*') << endl;
}

//Gets the user input and keeps asking if a valid one is not chosen
unsigned int getMenuChoice() {
    unsigned int choice = 0;
    bool validNum = false;

    printMenu();

    while (!validNum) {
        cin >> choice;

        if (choice >= 1 && choice <= 4) {
            validNum = true;
        }
        else {
            cout << "That is not a valid choice" << endl;
        }
    }

    clearScreen();

return choice;
}

//Displays bothe the 12 hour and 24 hour clocks simultaneously
void displayClocks(unsigned int hour, unsigned int minute, unsigned int second) {
    cout << nCharString(27, '*') << "   " << nCharString(27, '*') << endl;
    cout << "*      " << "12-Hour Clock" << "      *   ";
    cout << "*      " << "24-Hour Clock" << "      *" << endl;
    cout << endl;
    cout << "*      " << formatTime12(hour, minute, second) << "       *   ";
    cout << "*        " << formatTime24(hour, minute, second) << "         *" << endl;
    cout << nCharString(27, '*') << "   " << nCharString(27, '*') << endl;
}

//Adds one hour to the clocks
unsigned int addOneHour(unsigned int& hour) {
    hour = (hour + 1) % 24;

    return hour;
}

//Adds one minute to the clocks
unsigned int addOneMinute(unsigned int& minute) {
    minute = (minute + 1) % 60;

    return minute;
}

//Adds one second to the clocks
unsigned int addOneSecond(unsigned int& second) {
    second = (second + 1) % 60;

    return second;
}

//Gets current time
unsigned int getTime(unsigned int& hour, unsigned int& minute, unsigned int& second) {
    time_t systemTime;
    struct tm* timeLocal;

    time(&systemTime);
    timeLocal = localtime(&systemTime);

    hour = timeLocal->tm_hour;
    minute = timeLocal->tm_min;
    second = timeLocal->tm_sec;

    return hour;
}

int main() {
    unsigned int hour = 0; //Holds hour
    unsigned int minute = 0; //Holds minute
    unsigned int second = 0; //Holds second
    unsigned int choice; //Holds menu choice
    bool keepGoing = true; //Bool to keep program going

    getTime(hour, minute, second);//Initializes clock to current time

    //Keeps the program going as long as 4 is not selected
    while (keepGoing) {
        displayClocks(hour, minute, second); //Shows the clocks
        choice = getMenuChoice();//Gets menu choice (1-4) 
        switch (choice) {
        case 1:
            addOneHour(hour);
            break;
        case 2:
            if (minute == 59) {
                addOneHour(hour);
            }
            addOneMinute(minute);
            break;
        case 3:
            if (second == 59 && minute == 59) {
                addOneHour(hour);
                addOneMinute(minute);
            }
             else if (second == 59) {
                addOneMinute;
            }
            addOneSecond(second);
            break;
        case 4:
            keepGoing = false;
            cout << "GoodBye!\nMade by Afahri Kerr" << endl;
            break;
        }
    }
}