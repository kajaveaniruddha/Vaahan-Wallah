#include <bits/stdc++.h>
#include <unistd.h>
#include <windows.h>
using namespace std;

// int main()
// {
//     srand(time(0));
//     int incr_i; // increment i --> random integer between 15 & 25
//     for (int i = 0; i <= 100; i += incr_i)
//     {
//         incr_i = 15 + (rand() % 20);
//         cout << i << "%" << '\r';
//         sleep(1);
//     }
//     cout << "100%";
// }

// #include <stdio.h>
// #include <windows.h>

// void main()
// {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//     SetConsoleTextAttribute(hConsole,
//                             FOREGROUND_RED);
//     printf("red text\n");

//     SetConsoleTextAttribute(hConsole,
//                             FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_BLUE);
//     printf("yellow on blue\n");
// }

// int dateReturn[3] = {ltm->tm_mday, ltm->tm_mon, ltm->tm_year};

// fin.open("IssuedBooksData.txt");
// while (!fin.eof())
// {
//     getline(fin, Username2);
//     getline(fin, bookName2);
//     if (Username2 == Username && bookName2 == bookName)
//     {
//         fin >> day2 >> ws;
//         fin >> month2 >> ws;
//         fin >> year2 >> ws;
//         int dateIssue[3] = {day2, month2, year2};
//         if (countNoOfDays(dateIssue, dateReturn) > 15)
//             fine(countNoOfDays(dateIssue, dateReturn));
//     }
// }