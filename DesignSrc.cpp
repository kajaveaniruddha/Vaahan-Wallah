#include <bits/stdc++.h>
#include <windows.h>
#include <unistd.h>
using namespace std;

void fine(int LateDays)
{
    cout << "You have to pay fine of Rs." << LateDays * 200 << "/- for " << LateDays << " days of late return." << endl;
}

void ShowPercentCompleteFast()
{
    srand(time(0));
    int incr_i; // increment i --> random integer between 15 & 25
    for (int i = 0; i <= 100; i += incr_i)
    {
        incr_i = 12 + (rand() % 20);
        cout << i << "%" << '\r';
        sleep(1);
    }
    cout << "100% " << endl;
}

void ShowPercentCompleteSlow()
{
    srand(time(0));
    int incr_i; // increment i --> random integer between 15 & 25
    for (int i = 0; i <= 100; i += incr_i)
    {
        incr_i = 7 + (rand() % 12);
        cout << i << "%" << '\r';
        sleep(1);
    }
    cout << "100% " << endl;
}

ostream &bold_on(ostream &os)
{
    return os << "\e[1m";
}

ostream &underline_on(ostream &os)
{
    return os << "\e[4m";
}

ostream &reset(ostream &os)
{
    return os << "\e[0m";
}

void SetTextColorRED()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    // how to use --> cout << SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4) << "colour changed";
}
void SetTextColorWHITE()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void intro()
{
    char ch;
    system("COLOR 0F");
    while (1)
    {
        system("cls");
        cout << endl
             << endl;
        Sleep(10);
        system("COLOR 0");
        char a[] = "\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb TRANSPORTATION SYSTEM \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
        int size;
        size = strlen(a);
        for (int i = 0; i < size; i++)
        {
            Sleep(1);
            cout << a[i];
        }

        cout << endl
             << endl;
        Sleep(0);
        cout << "\n                    \t\t1.Customer \n                    \t\t2.Admin \n                    \t\t99.Exit \n"
             << "                    \n";
        for (int i = 0; i < 1; i++)
        {
            int x, y;
            for (y = 4; y < 27; y++)
            {
                cout << " ";
                Sleep(1);
            }
            for (x = 16; x < 56; x++)
            {
                cout << "\xdb";
                Sleep(20);
            }
            for (y = 4; y < 14; y++)
            {
                cout << "\xdb";
                Sleep(100);
            }
        }
        cout << "\n";
        int ch;
        cout << "\nSelect Your Option :";
        cin >> ch;
    }
}