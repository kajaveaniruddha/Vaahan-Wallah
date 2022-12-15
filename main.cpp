#include <bits/stdc++.h>
#include <iomanip>
#include <windows.h>
#include <unistd.h>
#include <ctime>
#include "DesignSrc.cpp"

using namespace std;

//=======================border===========================//

COORD CursorPosition;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoXY(int x, int y)
{
    CursorPosition.X = x;                              // Locates column
    CursorPosition.Y = y;                              // Locates Row
    SetConsoleCursorPosition(console, CursorPosition); // Sets position for next thing to be printed
}

//=======================time difference===========================//

time_t now = time(0);
tm *ltm = localtime(&now);

const int monthDays[12] = {31, 59, 90, 120, 151, 181, 212, 243,
                           273, 304, 334, 365};
int countLeapYearDays(int d[])
{
    int years = d[2];
    if (d[1] <= 2)
        years--;
    return ((years / 4) - (years / 100) + (years / 400));
}

int countNoOfDays(int date1[], int date2[])
{
    long int dayCount1 = (date1[2] * 365);
    dayCount1 += monthDays[date1[1]];
    dayCount1 += date1[0];
    dayCount1 += countLeapYearDays(date1);
    long int dayCount2 = (date2[2] * 365);
    dayCount2 += monthDays[date2[1]];
    dayCount2 += date2[0];
    dayCount2 += countLeapYearDays(date2);
    return (abs(dayCount1 - dayCount2 - 693991));
}

//===============classes===================================//

class Node_Vaahan
{
public:
    string NameofVaahan;
    string NumberPlate;
    string Ventilation;
    int Count;
    int charges;
    Node_Vaahan *next;
    // Parameterised Constructor
    Node_Vaahan(string NameofVaahan, string NumberPlate, string Ventilation, int Count, int charges)
    {
        this->NameofVaahan = NameofVaahan;
        this->NumberPlate = NumberPlate;
        this->Ventilation = Ventilation;
        this->Count = Count;
        this->charges = charges;
        this->next = NULL;
    }
};

class Vaahan
{
protected:
    Node_Vaahan *head_car;
    Node_Vaahan *head_bus;
    Node_Vaahan *head_bike;

public:
    Vaahan()
    {
        head_car = NULL;
        head_bus = NULL;
        head_bike = NULL;
    }
    void insertNodecar(string, string, string, int, int);
    void insertNodebus(string, string, string, int, int);
    void insertNodebike(string, string, string, int, int);

    void createcarList();
    void createbusList();
    void createbikeList();

    void display_all_Vaahan();
    void display_all_cars();
    void display_all_bus();
    void display_all_bikes();

    void display_all_available();
    void display_available_cars();
    void display_available_bus();
    void display_available_bikes();

    void addVaahan();
    void RepairVaahan();
};

class Node_User
{
public:
    string NameofUser;
    string Password;
    int balance;
    string LicenseNumber;
    string PhoneNumber;
    Node_User *next;
    // Parameterised Constructor
    Node_User(string NameofUser, string Password, int balance, string LicenseNumber, string PhoneNumber)
    {
        this->NameofUser = NameofUser;
        this->Password = Password;
        this->balance = balance;
        this->LicenseNumber = LicenseNumber;
        this->PhoneNumber = PhoneNumber;
        this->next = NULL;
    }
};

class User : public Vaahan
{
private:
    Node_User *head_user;

public:
    User()
    {
        head_user = NULL;
    }
    void insertNodeUser(string, string, int, string, string);
    void createUserList();
    void Sign_up();
    void display_all_users();
    void display_my_details(string);
    void Login_admin();
    void AfterLoginAdmin(string);
    void PreLogin_Customer();
    void Login_customer();
    void AfterLoginCustomer(string);
    void add_money(string);

    void rent(string);
    void rentCar(string);
    void rentBus(string);
    void rentBike(string);
    void returnVaahan(string);
    void returnCar(string);
    void returnBus(string);
    void returnBike(string);

    ~User()
    {
        ofstream fout;
        fout.open("cars.txt");
        Node_Vaahan *ptr1 = head_car;
        while (ptr1 != NULL)
        {
            fout << ptr1->NameofVaahan << endl;
            fout << ptr1->NumberPlate << endl;
            fout << ptr1->Ventilation << endl;
            fout << ptr1->Count << endl;
            fout << ptr1->charges << endl;
            ptr1 = ptr1->next;
        }
        fout.close();
        fout.open("bus.txt");
        Node_Vaahan *ptr2 = head_bus;
        while (ptr2 != NULL)
        {
            fout << ptr2->NameofVaahan << endl;
            fout << ptr2->NumberPlate << endl;
            fout << ptr2->Ventilation << endl;
            fout << ptr2->Count << endl;
            fout << ptr2->charges << endl;
            ptr2 = ptr2->next;
        }
        fout.close();
        fout.open("bikes.txt");
        Node_Vaahan *ptr3 = head_bike;
        while (ptr3 != NULL)
        {
            fout << ptr3->NameofVaahan << endl;
            fout << ptr3->NumberPlate << endl;
            fout << ptr3->Ventilation << endl;
            fout << ptr3->Count << endl;
            fout << ptr3->charges << endl;
            ptr3 = ptr3->next;
        }
        fout.close();
        fout.open("Users.txt");
        Node_User *ptr4 = head_user;
        while (ptr4 != NULL)
        {
            fout << ptr4->NameofUser << endl;
            fout << ptr4->Password << endl;
            fout << ptr4->balance << endl;
            fout << ptr4->LicenseNumber << endl;
            fout << ptr4->PhoneNumber << endl;
            ptr4 = ptr4->next;
        }
        fout.close();
    };
};

//========================User class functions========================//

void User::insertNodeUser(string NameofUser, string Password, int balance, string LicenseNumber, string PhoneNumber)
{
    Node_User *newNode = new Node_User(NameofUser, Password, balance, LicenseNumber, PhoneNumber);

    if (head_user == NULL)
    {
        head_user = newNode;
        return;
    }

    Node_User *temp = head_user;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void User::createUserList()
{
    ifstream fin;
    string NameofUser1;
    string Password1;
    int balance1;
    string LicenseNumber1;
    string PhoneNumber1;
    fin.open("Users.txt");
    while (!fin.eof())
    {
        getline(fin >> ws, NameofUser1);
        getline(fin >> ws, Password1);
        fin >> balance1 >> ws;
        getline(fin >> ws, LicenseNumber1);
        getline(fin >> ws, PhoneNumber1);
        insertNodeUser(NameofUser1, Password1, balance1, LicenseNumber1, PhoneNumber1);
    }
}

void User::display_all_users()
{
    Node_User *temp = head_user;
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb USERS LIST \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    if (head_user == NULL)
    {
        cout << "\n\t\t\t\t\t\t\tList empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        cout << "\n\t\t\t\t\t\t\tName - " << temp->NameofUser << endl;
        cout << "\n\t\t\t\t\t\t\tPassword - " << temp->Password << endl;
        cout << "\n\t\t\t\t\t\t\tBalance - Rs." << temp->balance << endl;
        cout << "\n\t\t\t\t\t\t\tLicense number - " << temp->LicenseNumber << endl;
        cout << "\n\t\t\t\t\t\t\tPhone number - " << temp->PhoneNumber << endl;
        cout << "\n\t\t\t\t\t\t\t*************************************" << endl;
        temp = temp->next;
    }
    cout << "\n";
}

void User::display_my_details(string username)
{

    Node_User *temp = head_user;

    if (head_user == NULL)
    {
        cout << "\n\n\t\t\t\t\t\t\tList empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        if (temp->NameofUser == username)
        {
            system("cls");
            cout << endl
                 << endl;
            char a[] = "\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb MY DETAILS \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
            int size;
            size = strlen(a);
            for (int i = 0; i < size; i++)
            {
                Sleep(1);
                cout << a[i];
            }
            cout << "\n\t\t\t\t\t\t\tName - " << temp->NameofUser << endl;
            cout << "\t\t\t\t\t\t\tPassword - " << temp->Password << endl;
            cout << "\t\t\t\t\t\t\tBalance - Rs." << temp->balance << endl;
            cout << "\t\t\t\t\t\t\tLicense number - " << temp->LicenseNumber << endl;
            cout << "\t\t\t\t\t\t\tPhone number - " << temp->PhoneNumber << endl;
            cout << "\t\t\t\t\t\t\t*************************************" << endl;
        }
        temp = temp->next;
    }
    cout << "\n";
}

void User::rent(string username)
{
    system("cls");
    int choice;
    int rent_days;
    do
    {
        cout << endl
             << endl;
        char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb RENT A VAAHAN \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
        int size;
        size = strlen(a);
        for (int i = 0; i < size; i++)
        {
            Sleep(1);
            cout << a[i];
        }
        cout << "\n\t\t\t\t\t\t\tWhich Vaahan would you to rent ?" << endl;
        cout << "\t\t\t\t\t\t\t1.car\n\t\t\t\t\t\t\t2.bus\n\t\t\t\t\t\t\t3.bike\n\t\t\t\t\t\t\t99.back\n\n\t\t\t\t\t\t\tYour choice : ";

        cin >> choice;
        switch (choice)
        {
        case 1:
            rentCar(username);
            break;
        case 2:
            rentBus(username);
            break;
        case 3:
            rentBike(username);
            break;
        case 99:
            system("cls");
            break;
        default:
            system("cls");
            cout << "\n\n\t\t\t\t\t\t\tPlease enter valid input !" << endl;
            break;
        }
    } while (choice != 99);
}

void User::rentCar(string username)
{

    system("cls");
    cout << endl
         << endl;
    char a[] = "\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb RENT CAR \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    int rent_days;
    cout << "\n\t\t\t\t\t\t\tEnter the no of days for which you would like to rent the car : ";
    cin >> rent_days;
    cout << "\n\t\t\t\t\t\t\tEnter car name which you would like to rent : ";
    string chkcar;
    cin >> chkcar;

    Node_Vaahan *ptr = head_car;
    Node_User *ptr2 = head_user;
    while (ptr2 != NULL)
    {
        if (ptr2->NameofUser == username)
            break;
        ptr2 = ptr2->next;
    }

    bool flag = 0;

    while (ptr != NULL)
    {
        if (ptr->NameofVaahan == chkcar)
        {
            flag = 1;
            if (ptr->Count > 0)
            {
                if ((rent_days * ptr->charges) < ptr2->balance)
                {
                    cout << "\t\t\t\t\t\t\tDear customer your Vaahan is booked." << endl;
                    cout << "\n\t\t\t\t\t\t\tDetails - \n\t\t\t\t\t\t\tName - " << ptr->NameofVaahan << endl;
                    cout << "\t\t\t\t\t\t\tNumber - " << ptr->NumberPlate << "\n\t\t\t\t\t\t\tVentilation type - "
                         << ptr->Ventilation << endl;
                    ptr2->balance = ptr2->balance - (rent_days * ptr->charges);
                    cout << "\t\t\t\t\t\t\tRs." << (rent_days * ptr->charges) << " were deducted from your account." << endl;
                    cout << "\t\t\t\t\t\t\tCurrent balance - Rs." << ptr2->balance << endl;
                    ptr->Count--;

                    ofstream fout;
                    fout.open("CarsOnRent.txt", ios::app);
                    fout << ptr2->NameofUser << endl;
                    fout << ptr->NameofVaahan << endl;
                    fout << ptr->NumberPlate << endl;
                    fout << ltm->tm_mday << endl;
                    fout << 1 + ltm->tm_mon << endl;
                    fout << 1900 + ltm->tm_year << endl;
                    fout << rent_days << endl;
                    fout.close();
                }
                else
                    cout << "\n\t\t\t\t\t\t\tInsufficient funds !\n\t\t\t\t\t\t\tAdd money to your account and try again..." << endl;
            }
            else
                cout << "\n\t\t\t\t\t\t\t" << ptr->NameofVaahan << " is currently unavailable." << endl;
        }
        ptr = ptr->next;
    }
    if (!flag)
        cout << "\n\t\t\t\t\t\t\tCar not found !" << endl;
}

void User::rentBus(string username)
{
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb RENT BUS \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    int rent_days;
    cout << "\n\t\t\t\t\t\t\tEnter the no of days for which you would like to rent the bus :";
    cin >> rent_days;
    cout << "\n\t\t\t\t\t\t\tEnter bus name which you would like to rent : ";
    string chkbus;
    cin >> chkbus;

    Node_Vaahan *ptr = head_bus;
    Node_User *ptr2 = head_user;
    while (ptr2 != NULL)
    {
        if (ptr2->NameofUser == username)
            break;
        ptr2 = ptr2->next;
    }

    bool flag = 0;

    while (ptr != NULL)
    {
        if (ptr->NameofVaahan == chkbus)
        {
            flag = 1;
            if (ptr->Count > 0)
            {
                if ((rent_days * ptr->charges) < ptr2->balance)
                {
                    cout << "\n\t\t\t\t\t\t\tDear customer your Vaahan is booked." << endl;
                    cout << "\t\t\t\t\t\t\tDetails - \n\t\t\t\t\t\t\tName - " << ptr->NameofVaahan << endl;
                    cout << "\t\t\t\t\t\t\tNumber - " << ptr->NumberPlate << "\n\t\t\t\t\t\t\tVentilation type -"
                         << ptr->Ventilation << endl;
                    ptr2->balance = ptr2->balance - (rent_days * ptr->charges);
                    cout << "\n\t\t\t\t\t\t\tRs." << rent_days * ptr->charges << " were deducted from your account." << endl;
                    cout << "\t\t\t\t\t\t\tCurrent balance - Rs." << ptr2->balance << endl;
                    ptr->Count--;

                    ofstream fout;
                    fout.open("BusOnRent.txt", ios::app);
                    fout << ptr2->NameofUser << endl;
                    fout << ptr->NameofVaahan << endl;
                    fout << ptr->NumberPlate << endl;
                    fout << ltm->tm_mday << endl;
                    fout << 1 + ltm->tm_mon << endl;
                    fout << 1900 + ltm->tm_year << endl;
                    fout << rent_days << endl;
                    fout.close();
                }
                else
                    cout << "\n\t\t\t\t\t\t\tInsufficient funds !\n\t\t\t\t\t\t\tAdd money to your account and try again..." << endl;
            }
            else
                cout << "\n\t\t\t\t\t\t\t" << ptr->NameofVaahan << " is currently unavailable." << endl;
        }
        ptr = ptr->next;
    }
    if (!flag)
        cout << "\n\t\t\t\t\t\t\tBus not found !" << endl;
}

void User::rentBike(string username)
{
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb RENT BIKE \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    int rent_days;
    cout << "\n\t\t\t\t\t\t\tEnter the no of days for which you would like to rent the bike :";
    cin >> rent_days;
    cout << "\n\t\t\t\t\t\t\tEnter bike name which you would like to rent : ";
    string chkbike;
    cin >> chkbike;

    Node_Vaahan *ptr = head_bike;
    Node_User *ptr2 = head_user;
    while (ptr2 != NULL)
    {
        if (ptr2->NameofUser == username)
            break;
        ptr2 = ptr2->next;
    }

    bool flag = 0;

    while (ptr != NULL)
    {
        if (ptr->NameofVaahan == chkbike)
        {
            flag = 1;
            if (ptr->Count > 0)
            {
                if ((rent_days * ptr->charges) < ptr2->balance)
                {
                    cout << "\t\t\t\t\t\t\tDear customer your Vaahan is booked." << reset << endl;
                    cout << "\t\t\t\t\t\t\tDetails - \n\t\t\t\t\t\t\tName - " << ptr->NameofVaahan << endl;
                    cout << "\t\t\t\t\t\t\tNumber - " << ptr->NumberPlate;
                    ptr2->balance = ptr2->balance - (rent_days * ptr->charges);
                    cout << "\n\t\t\t\t\t\t\tRs." << rent_days * ptr->charges << " were deducted from your account." << endl;
                    cout << "\t\t\t\t\t\t\tCurrent balance - Rs." << ptr2->balance << endl;
                    ptr->Count--;

                    ofstream fout;
                    fout.open("BikesOnRent.txt", ios::app);
                    fout << ptr2->NameofUser << endl;
                    fout << ptr->NameofVaahan << endl;
                    fout << ptr->NumberPlate << endl;
                    fout << ltm->tm_mday << endl;
                    fout << 1 + ltm->tm_mon << endl;
                    fout << 1900 + ltm->tm_year << endl;
                    fout << rent_days << endl;
                    fout.close();
                }
                else
                    cout << "\n\t\t\t\t\t\t\tInsufficient funds !\n\t\t\t\t\t\t\tAdd money to your account and try again..." << endl;
            }
            else
                cout << "\n\t\t\t\t\t\t\t" << ptr->NameofVaahan << " is currently unavailable." << endl;
        }
        ptr = ptr->next;
    }
    if (!flag)
        cout << "\n\t\t\t\t\t\t\tBike not found !" << endl;
}

// void User::rent(string username)
// {
//     int choice;
//     int rent_days;
//     do
//     {
//         cout << "Which Vaahan would you to rent ?" << endl;
//         cout << "1.car\n2.bus\n3.bike\n99.back\n>>";
//         cin >> choice;
//         switch (choice)
//         {
//         case 1:
//             rentCar(username);
//             break;
//         case 2:
//             rentBus(username);
//             break;
//         case 3:
//             rentBike(username);
//             break;
//         case 99:
//             break;
//         default:
//             cout << "Please enter valid input !" << endl;
//             break;
//         }
//     } while (choice != 99);
// }

// void User::rentCar(string username)
// {
//     int rent_days;
//     cout << "For how many days would you like to rent ?\n>>";
//     cin >> rent_days;
//     cout << "\nWhich car would you like to rent ?\n>>";
//     string chkcar;
//     cin >> chkcar;
//     Node_Vaahan *ptr = head_car;
//     Node_User *ptr2 = head_user;
//     while (ptr2 != NULL)
//     {
//         if (ptr2->NameofUser == username)
//             break;
//         ptr2 = ptr2->next;
//     }
//     bool flag = 0;
//     while (ptr != NULL)
//     {
//         if (ptr->NameofVaahan == chkcar)
//         {
//             flag = 1;
//             if (ptr->Count > 0)
//             {
//                 if ((rent_days * ptr->charges) < ptr2->balance)
//                 {
//                     cout << "Dear customer your Vaahan is booked." << endl;
//                     cout << "Details - \nName - " << ptr->NameofVaahan << endl;
//                     cout << "Number - " << ptr->NumberPlate << "\n"
//                          << ptr->Ventilation << endl;
//                     ptr2->balance = ptr2->balance - (rent_days * ptr->charges);
//                     cout << "Rs." << (rent_days * ptr->charges) << " were deducted from your account." << endl;
//                     cout << "Current balance - Rs." << ptr2->balance << endl;
//                     ptr->Count--;
//                     ofstream fout;
//                     fout.open("CarsOnRent.txt", ios::app);
//                     fout << ptr2->NameofUser << endl;
//                     fout << ptr->NameofVaahan << endl;
//                     fout << ptr->NumberPlate << endl;
//                     fout << ltm->tm_mday << endl;
//                     fout << 1 + ltm->tm_mon << endl;
//                     fout << 1900 + ltm->tm_year << endl;
//                     fout << rent_days << endl;
//                     fout.close();
//                 }
//                 else
//                     cout << "Insufficient funds !\nAdd money to your account and try again..." << endl;
//             }
//             else
//                 cout << ptr->NameofVaahan << " is crrently unavailable." << endl;
//         }
//         ptr = ptr->next;
//     }
//     if (!flag)
//         cout << "Car not found !" << endl;
// }

// void User::rentBus(string username)
// {
//     int rent_days;
//     cout << "For how many days would you like to rent ?\n>>";
//     cin >> rent_days;
//     cout << "\nWhich bus would you like to rent ?\n>>";
//     string chkbus;
//     cin >> chkbus;
//     Node_Vaahan *ptr = head_bus;
//     Node_User *ptr2 = head_user;
//     while (ptr2 != NULL)
//     {
//         if (ptr2->NameofUser == username)
//             break;
//         ptr2 = ptr2->next;
//     }
//     bool flag = 0;
//     while (ptr != NULL)
//     {
//         if (ptr->NameofVaahan == chkbus)
//         {
//             flag = 1;
//             if (ptr->Count > 0)
//             {
//                 if ((rent_days * ptr->charges) < ptr2->balance)
//                 {
//                     cout << "Dear customer your Vaahan is booked." << reset << endl;
//                     cout << "Details - \nName - " << ptr->NameofVaahan << endl;
//                     cout << "Number - " << ptr->NumberPlate << "\n"
//                          << ptr->Ventilation << endl;
//                     ptr2->balance = ptr2->balance - (rent_days * ptr->charges);
//                     cout << "Rs." << (rent_days * ptr->charges) << " were deducted from your account." << endl;
//                     cout << "Current balance - Rs." << ptr2->balance << endl;
//                     ptr->Count--;
//                     ofstream fout;
//                     fout.open("BusOnRent.txt", ios::app);
//                     fout << ptr2->NameofUser << endl;
//                     fout << ptr->NameofVaahan << endl;
//                     fout << ptr->NumberPlate << endl;
//                     fout << ltm->tm_mday << endl;
//                     fout << 1 + ltm->tm_mon << endl;
//                     fout << 1900 + ltm->tm_year << endl;
//                     fout << rent_days << endl;
//                     fout.close();
//                 }
//                 else
//                     cout << "Insufficient funds !\nAdd money to your account and try again..." << endl;
//             }
//             else
//                 cout << ptr->NameofVaahan << " is crrently unavailable." << endl;
//         }
//         ptr = ptr->next;
//     }
//     if (!flag)
//         cout << "Bus not found !" << endl;
// }

// void User::rentBike(string username)
// {
//     int rent_days;
//     cout << "For how many days would you like to rent ?\n>>";
//     cin >> rent_days;
//     cout << "\nWhich bike would you like to rent ?\n>>";
//     string chkbike;
//     cin >> chkbike;
//     Node_Vaahan *ptr = head_bike;
//     Node_User *ptr2 = head_user;
//     while (ptr2 != NULL)
//     {
//         if (ptr2->NameofUser == username)
//             break;
//         ptr2 = ptr2->next;
//     }
//     bool flag = 0;
//     while (ptr != NULL)
//     {
//         if (ptr->NameofVaahan == chkbike)
//         {
//             flag = 1;
//             if (ptr->Count > 0)
//             {
//                 if ((rent_days * ptr->charges) < ptr2->balance)
//                 {
//                     cout <<  "Dear customer your Vaahan is booked." << reset << endl;
//                     cout << "Details - \nName - " << ptr->NameofVaahan << endl;
//                     cout << "Number - " << ptr->NumberPlate << "\n"
//                          << ptr->Ventilation << endl;
//                     ptr2->balance = ptr2->balance - (rent_days * ptr->charges);
//                     cout << "Rs." << (rent_days * ptr->charges) << " were deducted from your account." << endl;
//                     cout << "Current balance - Rs." << ptr2->balance << endl;
//                     ptr->Count--;
//                     ofstream fout;
//                     fout.open("BikesOnRent.txt", ios::app);
//                     fout << ptr2->NameofUser << endl;
//                     fout << ptr->NameofVaahan << endl;
//                     fout << ptr->NumberPlate << endl;
//                     fout << ltm->tm_mday << endl;
//                     fout << 1 + ltm->tm_mon << endl;
//                     fout << 1900 + ltm->tm_year << endl;
//                     fout << rent_days << endl;
//                     fout.close();
//                 }
//                 else
//                     cout << "Insufficient funds !\nAdd money to your account and try again..." << endl;
//             }
//             else
//                 cout << ptr->NameofVaahan << " is crrently unavailable." << endl;
//         }
//         ptr = ptr->next;
//     }
//     if (!flag)
//         cout << "Bike not found !" << endl;
// }

void User::add_money(string username)
{
    Node_User *ptr = head_user;
    int addmoney;
    while (ptr != NULL)
    {
        if (ptr->NameofUser == username)
        {
            system("cls");
            cout << endl
                 << endl;
            char a[] = "\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb ADD MONEY \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
            int size;
            size = strlen(a);
            for (int i = 0; i < size; i++)
            {
                Sleep(1);
                cout << a[i];
            }
            cout << "\n\t\t\t\t\t\t\tEnter the amount you want to add (in rupees): ";
            cin >> addmoney;
            ptr->balance = ptr->balance + addmoney;
            cout << "\t\t\t\t\t\t\tMoney added to your account successfully !" << endl;
            cout << "\t\t\t\t\t\t\tBalance - Rs." << ptr->balance << reset << endl;
        }
        ptr = ptr->next;
    }
}

void User::returnVaahan(string username)
{
    system("cls");
    int choice;
    do
    {
        cout << endl
             << endl;
        char a[] = "\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb RETURN VAAHAN \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
        int size;
        size = strlen(a);
        for (int i = 0; i < size; i++)
        {
            Sleep(1);
            cout << a[i];
        }
        cout << "\n\t\t\t\t\t\t\tSelect the type of vaahan you want to return - " << endl;
        cout << "\t\t\t\t\t\t\t1.car\n\t\t\t\t\t\t\t2.bus\n\t\t\t\t\t\t\t3.bike\n\t\t\t\t\t\t\t99.back\n\n\t\t\t\t\t\t\tYour choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            returnCar(username);
            break;
        case 2:
            returnBus(username);
            break;
        case 3:
            returnBike(username);
            break;
        case 99:
            break;
        default:
            system("cls");
            cout << "\t\t\t\t\t\t\tPlease enter valid input !" << endl;
            break;
        }
    } while (choice != 99);
}

void User::returnCar(string username)
{
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb RETURN CAR \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    string NameofVaahan1;
    string NumberPlate1;
    cout << "\n\t\t\t\t\t\t\tEnter the name of car : ";
    cin >> NameofVaahan1;
    cout << "\n\t\t\t\t\t\t\tEnter the number plate of car : ";
    cin >> NumberPlate1;
    bool flag = 1, flag2 = 1;
    ifstream fin;
    string chkNameofVaahan;
    string chkNumberPlate;
    string chkusername;
    int rent_days2;
    int day2, month2, year2;
    int dateReturn[3] = {ltm->tm_mday, ltm->tm_mon, ltm->tm_year};
    fin.open("CarsOnRent.txt");
    while (!fin.eof())
    {
        getline(fin >> ws, chkusername);
        getline(fin >> ws, chkNameofVaahan);
        getline(fin >> ws, chkNumberPlate);
        fin >> day2 >> ws;
        fin >> month2 >> ws;
        fin >> year2 >> ws;
        fin >> rent_days2 >> ws;
        if (chkusername == username)
        {
            flag = 0;
            if (chkNameofVaahan == NameofVaahan1 && chkNumberPlate == NumberPlate1)
            {
                flag2 = 0;
                int dateIssue[3] = {day2, month2, year2};
                Node_User *ptr1 = head_user;
                Node_Vaahan *ptr2 = head_car;

                cout << "\n\t\t\t\t\t\t\t" << NameofVaahan1 << " - " << NumberPlate1 << " returned successfully !" << endl;

                while (ptr2 != NULL)
                {
                    if (ptr2->NameofVaahan == NameofVaahan1)
                    {
                        ptr2->Count++;
                    }
                    ptr2 = ptr2->next;
                }

                // fine for late return
                if (countNoOfDays(dateIssue, dateReturn) > rent_days2)
                {
                    int LateDays = countNoOfDays(dateIssue, dateReturn) - rent_days2;
                    cout << "\t\t\t\t\t\t\tYou have to pay fine of Rs." << LateDays * 300 << "/- for " << LateDays << " days of late return." << endl;
                    ptr1->balance = ptr1->balance - (LateDays)*300;
                    cout << "\t\t\t\t\t\t\tBalance - Rs." << ptr1->balance << endl;
                }
                else
                {
                    while (ptr1 != NULL)
                    {
                        if (ptr1->NameofUser == username)
                        {
                            ptr1->balance = ptr1->balance + 20;
                            cout << "\t\t\t\t\t\t\tYayyy! You earned Rs.20 Loyalty bonus !" << endl;
                            cout << "\t\t\t\t\t\t\tBalance - Rs." << ptr1->balance << endl;
                        }
                        ptr1 = ptr1->next;
                    }
                }
            }
        }
    }
    if (flag2)
        cout << "\t\t\t\t\t\t\tCar and its number you are trying to return doesn't match !\n\t\t\t\t\t\t\tTry again..." << endl;
    if (flag)
        cout << "\t\t\t\t\t\t\tNo user found to return any Vaahan type you've chosen." << endl;
}

void User::returnBus(string username)
{
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb RETURN BUS \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }

    string NameofVaahan1;
    string NumberPlate1;
    cout << "\t\t\t\t\t\t\tEnter the name of bus : ";
    cin >> NameofVaahan1;
    cout << "\t\t\t\t\t\t\tEnter the number plate of bus : ";
    cin >> NumberPlate1;
    bool flag = 1, flag2 = 1;
    ifstream fin;
    string chkNameofVaahan;
    string chkNumberPlate;
    string chkusername;
    int rent_days2;
    int day2, month2, year2;
    int dateReturn[3] = {ltm->tm_mday, ltm->tm_mon, ltm->tm_year};
    fin.open("BusOnRent.txt");
    while (!fin.eof())
    {
        getline(fin >> ws, chkusername);
        getline(fin >> ws, chkNameofVaahan);
        getline(fin >> ws, chkNumberPlate);
        fin >> day2 >> ws;
        fin >> month2 >> ws;
        fin >> year2 >> ws;
        fin >> rent_days2 >> ws;
        if (chkusername == username)
        {
            flag = 0;
            if (chkNameofVaahan == NameofVaahan1 && chkNumberPlate == NumberPlate1)
            {
                flag2 = 0;
                int dateIssue[3] = {day2, month2, year2};
                Node_User *ptr1 = head_user;
                Node_Vaahan *ptr2 = head_bus;

                cout << "\n\t\t\t\t\t\t\t" << NameofVaahan1 << " - " << NumberPlate1 << " returned successfully !" << endl;

                while (ptr2 != NULL)
                {
                    if (ptr2->NameofVaahan == NameofVaahan1)
                    {
                        ptr2->Count++;
                    }
                    ptr2 = ptr2->next;
                }

                // fine for late return
                if (countNoOfDays(dateIssue, dateReturn) > rent_days2)
                {
                    int LateDays = countNoOfDays(dateIssue, dateReturn) - rent_days2;
                    cout << "\t\t\t\t\t\t\tYou have to pay fine of Rs." << LateDays * 400 << "/- for " << LateDays << " days of late return." << endl;
                    ptr1->balance = ptr1->balance - (LateDays)*300;
                    cout << "\t\t\t\t\t\t\tBalance - Rs." << ptr1->balance << endl;
                }
                else
                {
                    while (ptr1 != NULL)
                    {
                        if (ptr1->NameofUser == username)
                        {
                            ptr1->balance = ptr1->balance + 30;
                            cout << "\t\t\t\t\t\t\tYayyy! You earned Rs.30 Loyalty bonus !" << endl;
                            cout << "\t\t\t\t\t\t\tBalance - Rs." << ptr1->balance << endl;
                        }
                        ptr1 = ptr1->next;
                    }
                }
            }
        }
    }
    if (flag)
        cout << "\t\t\t\t\t\t\tNo user found to return any Vaahan type you've chosen." << endl;
    if (flag2)
        cout << "\t\t\t\t\t\t\tBus and its number you are trying to return doesn't match !\n\t\t\t\t\t\t\tTry again..." << endl;
}

void User::returnBike(string username)
{
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb RETURN BIKE \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    string NameofVaahan1;
    string NumberPlate1;
    cout << "\n\t\t\t\t\t\t\tEnter the name of bike : ";
    cin >> NameofVaahan1;
    cout << "\t\t\t\t\t\t\tEnter the number plate of bike : ";
    cin >> NumberPlate1;
    bool flag = 1, flag2 = 1;
    ifstream fin;
    string chkNameofVaahan;
    string chkNumberPlate;
    string chkusername;
    int rent_days2;
    int day2, month2, year2;
    int dateReturn[3] = {ltm->tm_mday, ltm->tm_mon, ltm->tm_year};
    fin.open("BikesOnRent.txt");
    while (!fin.eof())
    {
        getline(fin >> ws, chkusername);
        getline(fin >> ws, chkNameofVaahan);
        getline(fin >> ws, chkNumberPlate);
        fin >> day2 >> ws;
        fin >> month2 >> ws;
        fin >> year2 >> ws;
        fin >> rent_days2 >> ws;

        if (chkusername == username)
        {
            flag = 0;
            if (chkNameofVaahan == NameofVaahan1 && chkNumberPlate == NumberPlate1)
            {
                flag2 = 0;
                int dateIssue[3] = {day2, month2, year2};
                Node_User *ptr1 = head_user;
                Node_Vaahan *ptr2 = head_bike;

                cout << "\n\t\t\t\t\t\t\t" << NameofVaahan1 << " - " << NumberPlate1 << " returned successfully !" << endl;

                while (ptr2 != NULL)
                {
                    if (ptr2->NameofVaahan == NameofVaahan1)
                    {
                        ptr2->Count++;
                    }
                    ptr2 = ptr2->next;
                }

                // fine for late return
                if (countNoOfDays(dateIssue, dateReturn) > rent_days2)
                {
                    int LateDays = countNoOfDays(dateIssue, dateReturn) - rent_days2;
                    cout << "\t\t\t\t\t\t\tYou have to pay fine of Rs." << LateDays * 200 << "/- for " << LateDays << " days of late return." << endl;
                    ptr1->balance = ptr1->balance - (LateDays)*300;
                    cout << "\t\t\t\t\t\t\tBalance - Rs." << ptr1->balance << endl;
                }
                else
                {
                    while (ptr1 != NULL)
                    {
                        if (ptr1->NameofUser == username)
                        {
                            ptr1->balance = ptr1->balance + 20;
                            cout << "\t\t\t\t\t\t\tYayyy! You earned Rs.10 Loyalty bonus !" << endl;
                            cout << "\t\t\t\t\t\t\tBalance - Rs." << ptr1->balance << endl;
                        }
                        ptr1 = ptr1->next;
                    }
                }
            }
        }
    }
    if (flag)
        cout << "\t\t\t\t\t\t\tNo user found to return any Vaahan type you've chosen." << endl;
    if (flag2)
        cout << "\t\t\t\t\t\t\tBike and its number you are trying to return doesn't match !\n\t\t\t\t\t\t\tTry again..." << endl;
}

//========================Vaahan class functions=======================//

void Vaahan::insertNodecar(string NameofVaahan, string NumberPlate, string Ventilation, int Count, int charges)
{
    Node_Vaahan *newNode = new Node_Vaahan(NameofVaahan, NumberPlate, Ventilation, Count, charges);
    if (head_car == NULL)
    {
        head_car = newNode;
        return;
    }
    Node_Vaahan *temp = head_car;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void Vaahan::insertNodebus(string NameofVaahan, string NumberPlate, string Ventilation, int Count, int charges)
{
    Node_Vaahan *newNode = new Node_Vaahan(NameofVaahan, NumberPlate, Ventilation, Count, charges);
    if (head_bus == NULL)
    {
        head_bus = newNode;
        return;
    }
    Node_Vaahan *temp = head_bus;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void Vaahan::insertNodebike(string NameofVaahan, string NumberPlate, string Ventilation, int Count, int charges)
{
    Node_Vaahan *newNode = new Node_Vaahan(NameofVaahan, NumberPlate, Ventilation, Count, charges);
    if (head_bike == NULL)
    {
        head_bike = newNode;
        return;
    }
    Node_Vaahan *temp = head_bike;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void Vaahan::createcarList()
{
    ifstream fin;
    string NameofVaahan1;
    string NumberPlate1;
    string Ventilation1;
    int Count1;
    int charges1;
    fin.open("cars.txt");
    while (!fin.eof())
    {
        getline(fin >> ws, NameofVaahan1);
        getline(fin >> ws, NumberPlate1);
        getline(fin >> ws, Ventilation1);
        fin >> Count1 >> ws;
        fin >> charges1 >> ws;
        insertNodecar(NameofVaahan1, NumberPlate1, Ventilation1, Count1, charges1);
    }
    fin.close();
}

void Vaahan::createbusList()
{
    ifstream fin;
    string NameofVaahan1;
    string NumberPlate1;
    string Ventilation1;
    int Count1;
    int charges1;
    fin.open("bus.txt");
    while (!fin.eof())
    {
        getline(fin >> ws, NameofVaahan1);
        getline(fin >> ws, NumberPlate1);
        getline(fin >> ws, Ventilation1);
        fin >> Count1 >> ws;
        fin >> charges1 >> ws;
        insertNodebus(NameofVaahan1, NumberPlate1, Ventilation1, Count1, charges1);
    }
    fin.close();
}

void Vaahan::createbikeList()
{
    ifstream fin;
    string NameofVaahan1;
    string NumberPlate1;
    string Ventilation1;
    int Count1;
    int charges1;
    fin.open("bikes.txt");
    while (!fin.eof())
    {
        getline(fin >> ws, NameofVaahan1);
        getline(fin >> ws, NumberPlate1);
        getline(fin >> ws, Ventilation1);
        fin >> Count1 >> ws;
        fin >> charges1 >> ws;
        insertNodebike(NameofVaahan1, NumberPlate1, Ventilation1, Count1, charges1);
    }
    fin.close();
}

void Vaahan::display_all_Vaahan()
{
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb ALL VAAHAN LIST \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    int choice;
    do
    {
        cout << "\n\t\t\t\t\t\t\tChoose type of Vaahan\n\t\t\t\t\t\t\t1.Car.\n\t\t\t\t\t\t\t2.Bus.\n\t\t\t\t\t\t\t3.Bike.\n\t\t\t\t\t\t\t99.back.\n\n\t\t\t\t\t\t\tYour choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            display_all_cars();
            break;
        case 2:
            display_all_bus();
            break;
        case 3:
            display_all_bikes();
            break;
        case 99:
            break;
        default:
            system("cls");
            cout << "\t\t\t\t\t\t\tPlease enter valid input !" << endl;
            break;
        }

    } while (choice != 99);
}

void Vaahan::display_all_cars()
{
    Node_Vaahan *temp = head_car;
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb ALL CARS \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    if (head_car == NULL)
    {
        cout << "\n\t\t\t\t\t\t\tList empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        cout << "\n\t\t\t\t\t\t\tName - " << temp->NameofVaahan << endl;
        cout << "\t\t\t\t\t\t\tNumber plate - " << temp->NumberPlate << endl;
        cout << "\t\t\t\t\t\t\tventilation type - " << temp->Ventilation << endl;
        cout << "\t\t\t\t\t\t\tCharges per hour - Rs." << temp->charges << endl;
        temp = temp->next;
        cout << "\t\t\t\t\t\t\t*************************************" << endl;
    }
    cout << "\n";
}

void Vaahan::display_all_bus()
{
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb ALL BUSES \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    Node_Vaahan *temp = head_bus;

    if (head_bus == NULL)
    {
        cout << "\t\t\t\t\t\t\tList empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        cout << "\n\t\t\t\t\t\t\tName - " << temp->NameofVaahan << endl;
        cout << "\t\t\t\t\t\t\tNumber plate - " << temp->NumberPlate << endl;
        cout << "\t\t\t\t\t\t\tventilation type - " << temp->Ventilation << endl;
        cout << "\t\t\t\t\t\t\tCharges per hour - Rs." << temp->charges << endl;
        temp = temp->next;
        cout << "\t\t\t\t\t\t\t*************" << endl;
    }
    cout << "\n";
}

void Vaahan::display_all_bikes()
{
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb ALL BIKES \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    Node_Vaahan *temp = head_bike;

    if (head_bike == NULL)
    {
        cout << "\t\t\t\t\t\t\tList empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        cout << "\n\t\t\t\t\t\t\tName - " << temp->NameofVaahan << endl;
        cout << "\t\t\t\t\t\t\tNumber plate - " << temp->NumberPlate << endl;
        cout << "\t\t\t\t\t\t\tCharges per hour - Rs." << temp->charges << endl;
        temp = temp->next;
        cout << "\t\t\t\t\t\t\t*************" << endl;
    }
    cout << "\n";
}

void Vaahan::display_all_available()
{
    system("cls");
    int choice;
    do
    {

        cout << endl
             << endl;
        char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb CHOOSE VAAHAN \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
        int size;
        size = strlen(a);
        for (int i = 0; i < size; i++)
        {
            Sleep(1);
            cout << a[i];
        }

        cout << "\n\t\t\t\t\t\t\tChoose type of Vaahan\n\t\t\t\t\t\t\t1.Car.\n\t\t\t\t\t\t\t2.Bus.\n\t\t\t\t\t\t\t3.Bike.\n\t\t\t\t\t\t\t99.back.\n\n\t\t\t\t\t\t\tYour choice : ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:

            display_available_cars();
            break;
        case 2:

            display_available_bus();
            break;
        case 3:

            display_available_bikes();
            break;
        case 99:
            break;
        default:
            cout << "\n\n\t\t\t\t\t\t\tPlease enter valid input !" << endl;
            break;
        }

    } while (choice != 99);
}

void Vaahan::display_available_cars()
{
    system("cls");

    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb AVAILABLE CARS \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    Node_Vaahan *temp = head_car;

    if (head_car == NULL)
    {
        cout << "\n\t\t\t\t\t\t\tList empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        if (temp->Count > 0)
        {
            cout << "\n\t\t\t\t\t\t\tName - " << temp->NameofVaahan << endl;
            cout << "\t\t\t\t\t\t\tNumber plate - " << temp->NumberPlate << endl;
            cout << "\t\t\t\t\t\t\tventilation type - " << temp->Ventilation << endl;
            cout << "\t\t\t\t\t\t\tCharges per hour - Rs." << temp->charges << endl;
            cout << "\t\t\t\t\t\t\t*************************************" << endl;
        }
        temp = temp->next;
    }
    cout << "\n";
}

void Vaahan::display_available_bus()
{
    Node_Vaahan *temp = head_bus;
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb AVAILABLE BUSES \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    if (head_bus == NULL)
    {
        cout << "\n\t\t\t\t\t\t\tList empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        if (temp->Count > 0)
        {
            cout << "\n\t\t\t\t\t\t\tName - " << temp->NameofVaahan << endl;
            cout << "\t\t\t\t\t\t\tNumber plate - " << temp->NumberPlate << endl;
            cout << "\t\t\t\t\t\t\tventilation type - " << temp->Ventilation << endl;
            cout << "\t\t\t\t\t\t\tCharges per hour - Rs." << temp->charges << endl;
                        cout << "\t\t\t\t\t\t\t*****" << endl;
        }
        temp = temp->next;
    }
    cout << "\n";
}

void Vaahan::display_available_bikes()
{
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb AVAILABLE BIKES \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    Node_Vaahan *temp = head_bike;

    if (head_bike == NULL)
    {
        cout << "\n\t\t\t\t\t\t\tList empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        if (temp->Count > 0)
        {
            cout << "\n\t\t\t\t\t\t\tName - " << temp->NameofVaahan << endl;
            cout << "\t\t\t\t\t\t\tNumber plate - " << temp->NumberPlate << endl;
            cout << "\t\t\t\t\t\t\tCharges per hour - Rs." << temp->charges << endl;
            cout << "\t\t\t\t\t\t\t*************" << endl;
        }
        temp = temp->next;
    }
    cout << "\n";
}

void Vaahan::addVaahan()
{
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb ADD VAAHAN DETAILS \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    string NameofVaahan1;
    string NumberPlate1;
    string Ventilation1;
    int Count1 = 1;
    int charges1;

    cout << "\n\t\t\t\t\t\t\tEnter the type of Vaahan you want to add ( car / bus / bike ): ";
    string choice;
    cin >> choice;

    cout << "\n\t\t\t\t\t\t\tPlease enter the Name of Vaahan: ";
    cin >> NameofVaahan1;
    cout << "\t\t\t\t\t\t\tPlease enter the number plate: ";
    cin >> NumberPlate1;
    cout << "\t\t\t\t\t\t\tPlease enter the ventilation type : ";
    cin >> Ventilation1;
    cout << "\t\t\t\t\t\t\tPlease enter the charges (in Rs.) per day: ";
    cin >> charges1;

    if (choice == "car")
    {
        insertNodecar(NameofVaahan1, NumberPlate1, Ventilation1, Count1, charges1);
        cout << "\n\t\t\t\t\t\t\tCar added successfully to list." << endl;
    }
    else if (choice == "bus")
    {
        insertNodebus(NameofVaahan1, NumberPlate1, Ventilation1, Count1, charges1);
        cout << "\n\t\t\t\t\t\t\tBus added successfully to list." << endl;
    }
    else if (choice == "bike")
    {
        insertNodebike(NameofVaahan1, NumberPlate1, Ventilation1, Count1, charges1);
        cout << "\n\t\t\t\t\t\t\tBike added successfully to list." << endl;
    }
    else
        cout << "\n\t\t\t\t\t\t\tPlease enter valid argument and try again !" << endl;
}

void Vaahan::RepairVaahan()
{
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb REPAIR VAAHAN \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    string NameofVaahan1;
    string NumberPlate1;
    string choice1;
    string rent_days;

    cout << "\n\t\t\t\t\t\t\tEnter the type of Vaahan you want to add ( car / bus / bike ): ";
    cin >> choice1;
    cout << "\n\t\t\t\t\t\t\tEnter the name of Vaahan you want to repair: ";
    cin >> NameofVaahan1;
    cout << "\n\t\t\t\t\t\t\tEnter the Number plate of Vaahan : ";
    cin >> NumberPlate1;
    if (choice1 == "car")
    {
        bool flag = 1;
        Node_Vaahan *ptr = head_car;
        while (ptr != NULL)
        {
            if (ptr->NameofVaahan == NameofVaahan1 && ptr->NumberPlate == NumberPlate1)
            {
                flag = 0;
                if (ptr->Count > 0)
                {
                    flag = 0;
                    cout << "\n\t\t\t\t\t\t\t" << ptr->NameofVaahan << "with number " << ptr->NumberPlate
                         << " will be sent to garage for repair." << endl;
                    cout << "\n\t\t\t\t\t\t\tPlease wait mechanic is checking the condition of car... \n\t\t\t\t\t\t\t";
                    ShowPercentCompleteFast();
                    cout << "\n\n\t\t\t\t\t\t\tCheck-up done ! ";
                    // srand(time(0));
                    // int temp = 1 + (rand() % 5);
                    // cout << "Mechanic suggests to keep the car for " << temp << " day(s) in the garage." << endl;

                    cout << "\n\t\t\t\t\t\t\tYou need to wait for a while untill the car gets repaired. " << endl;
                    cout << "\n\t\t\t\t\t\t\tYou still want to continue with repair process ( yes / no )?: ";
                    cin >> rent_days;
                    if (rent_days == "yes")
                    {
                        cout << "\n\t\t\t\t\t\t\tMechanic is repairing your car...";
                        ShowPercentCompleteSlow();
                        cout << "\n\t\t\t\t\t\t\tCar repair success !" << endl;
                    }
                    else if (rent_days == "no")
                    {
                        cout << "\n\t\t\t\t\t\t\tOk ! Car not sent for repair." << endl;
                        break; // so that 'while loop' does not keep on iterating unnecessarily --> to save a bit of time
                    }
                    else
                    {
                        cout << "\n\t\t\t\t\t\t\tEnter valid input and try again !" << endl;
                        break; // so that 'while loop' does not keep on iterating unnecessarily --> to save a bit of time
                    }
                }
                else
                    cout << "\n\t\t\t\t\t\t\tDear admin " << NameofVaahan1 << " is " << underline_on << "not" << reset
                         << " available with you currently.\n \n\t\t\t\t\t\t\tCheck whether it is given for rent or already sent to mechanic." << endl;
            }
            ptr = ptr->next;
        }
        if (flag)
            cout << "\n\t\t\t\t\t\t\tCar not found with name " << NameofVaahan1 << " and "
                 << "number " << NumberPlate1 << ", try again later." << endl;
    }
    else if (choice1 == "bus")
    {
        bool flag = 1;
        Node_Vaahan *ptr = head_bus;
        while (ptr != NULL)
        {
            if (ptr->NameofVaahan == NameofVaahan1 && ptr->NumberPlate == NumberPlate1)
            {
                flag = 0;
                if (ptr->Count > 0)
                {
                    flag = 0;
                    cout << "\n\t\t\t\t\t\t\t" << ptr->NameofVaahan << "with number " << ptr->NumberPlate
                         << " will be sent to garage for repair." << endl;
                    cout << "\n\t\t\t\t\t\t\tPlease wait mechanic is checking the condition of bus... " << endl;
                    ShowPercentCompleteFast();
                    cout << "\n\n\t\t\t\t\t\t\tCheck-up done ! ";
                    // srand(time(0));
                    // int temp = 1 + (rand() % 5);
                    // cout << "Mechanic suggests to keep the car for " << temp << " day(s) in the garage." << endl;

                    cout << "\n\t\t\t\t\t\t\tYou need to wait for a while untill the bus gets repaired. " << endl;
                    cout << "\n\t\t\t\t\t\t\tYou still want to continue with repair process ( yes / no )?: ";
                    cin >> rent_days;
                    if (rent_days == "yes")
                    {
                        cout << "\n\t\t\t\t\t\t\tMechanic is repairing your bus..." << endl;
                        ShowPercentCompleteSlow();
                        cout << "\n\t\t\t\t\t\t\tBus repair success !" << endl;
                    }
                    else if (rent_days == "no")
                    {
                        cout << "\n\t\t\t\t\t\t\tOk ! Bus not sent for repair." << endl;
                        break; // so that 'while loop' does not keep on iterating unnecessarily --> to save a bit of time
                    }
                    else
                    {
                        cout << "\n\t\t\t\t\t\t\tEnter valid input and try again !" << endl;
                        break; // so that 'while loop' does not keep on iterating unnecessarily --> to save a bit of time
                    }
                }
                else
                    cout << "\n\t\t\t\t\t\t\tDear admin " << NameofVaahan1 << " is " << underline_on << "not" << reset
                         << " available with you currently.\n\n\t\t\t\t\t\t\t Check whether it is given for rent or already sent to mechanic." << endl;
            }
            ptr = ptr->next;
        }
        if (flag)
            cout << "\n\t\t\t\t\t\t\tBus not found with name " << NameofVaahan1 << " and "
                 << "number " << NumberPlate1 << ", try again later." << endl;
    }
    else if (choice1 == "bike")
    {
        bool flag = 1;
        Node_Vaahan *ptr = head_bike;
        while (ptr != NULL)
        {
            if (ptr->NameofVaahan == NameofVaahan1 && ptr->NumberPlate == NumberPlate1)
            {
                flag = 0;
                if (ptr->Count > 0)
                {
                    flag = 0;
                    cout << "\n\t\t\t\t\t\t\t" << ptr->NameofVaahan << "with number " << ptr->NumberPlate
                         << " will be sent to garage for repair." << endl;
                    cout << "\n\t\t\t\t\t\t\tPlease wait mechanic is checking the condition of bike... " << endl;
                    ShowPercentCompleteFast();
                    cout << "\n\n\t\t\t\t\t\t\tCheck-up done ! ";
                    // srand(time(0));
                    // int temp = 1 + (rand() % 5);
                    // cout << "Mechanic suggests to keep the car for " << temp << " day(s) in the garage." << endl;

                    cout << "\n\t\t\t\t\t\t\tYou need to wait for a while untill the bike gets repaired. " << endl;
                    cout << "\n\t\t\t\t\t\t\tYou still want to continue with repair process ( yes / no )?: ";
                    cin >> rent_days;
                    if (rent_days == "yes")
                    {
                        cout << "\n\t\t\t\t\t\t\tMechanic is repairing your bike..." << endl;
                        ShowPercentCompleteSlow();
                        cout << "\n\t\t\t\t\t\t\tbike repair success !" << endl;
                    }
                    else if (rent_days == "no")
                    {
                        cout << "\n\t\t\t\t\t\t\tOk ! Bike not sent for repair." << endl;
                        break; // so that 'while loop' does not keep on iterating unnecessarily --> to save a bit of time
                    }
                    else
                    {
                        cout << "\n\t\t\t\t\t\t\tEnter valid input and try again !" << endl;
                        break; // so that 'while loop' does not keep on iterating unnecessarily --> to save a bit of time
                    }
                }
                else
                    cout << "\n\t\t\t\t\t\t\tDear admin " << NameofVaahan1 << " is " << underline_on << "not" << reset
                         << " available with you currently.\n\n\t\t\t\t\t\t\t Check whether it is given for rent or already sent to mechanic." << endl;
            }
            ptr = ptr->next;
        }
        if (flag)
            cout << "\n\t\t\t\t\t\t\tBike not found with name " << NameofVaahan1 << " and "
                 << "number " << NumberPlate1 << ", try again later." << endl;
    }

    else
        cout << "\n\t\t\t\t\t\t\tInvalid input ,please try again." << endl;
}

//===================Login / sign-up==========================//

void User::PreLogin_Customer()
{
    system("cls");
    int choice;
    do
    {
        system("cls");

        cout << endl
             << endl;

        char a[] = "\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb CUSTOMER \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
        int size;
        size = strlen(a);
        for (int i = 0; i < size; i++)
        {
            Sleep(1);
            cout << a[i];
        }
        cout << "\n\t\t\t\t\t\t\t1.Login.\n\t\t\t\t\t\t\t2.Sign-up.\n\t\t\t\t\t\t\t99.Exit.\n\n\t\t\t\t\t\t\tYour option : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            Login_customer();
            break;
        case 2:
            Sign_up();
            break;
        case 99:
            break;
        default:
            cout << "\n\t\t\t\t\t\t\tPlease enter valid input !" << endl;
            break;
        }
    } while (choice != 99);
}

void User::Login_customer()
{
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb LOGIN DETAILS \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    string username;
    string password;
    cout << "\n\t\t\t\t\t\t\tEnter your username : ";
    cin >> username;
    cout << "\n\t\t\t\t\t\t\tEnter your password : ";
    cin >> password;
    bool flag = 1;
    Node_User *ptr = head_user;
    while (ptr != NULL)
    {
        if (ptr->NameofUser == username && ptr->Password == password)
        {
            flag = 0;
            AfterLoginCustomer(username);
        }
        ptr = ptr->next;
    }
    if (flag)
    {
        cout << "\n\t\t\t\t\t\t\tInvalid username or password !" << endl;
        sleep(3);
    }
}

void User::AfterLoginCustomer(string username)
{
    system("cls");
    int choice;
    do
    {

        cout << endl
             << endl;
        char a[] = "\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb DASHBOARD \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
        int size;
        size = strlen(a);
        for (int i = 0; i < size; i++)
        {
            Sleep(1);
            cout << a[i];
        }
        cout << "\n\t\t\t\t\t\t\t1.Check for available Vaahan.\n\t\t\t\t\t\t\t2.Rent a Vaahan.\n\t\t\t\t\t\t\t3.Return Vaahan.\n\t\t\t\t\t\t\t4.Add Money.\n\t\t\t\t\t\t\t5.Display my details.\n\t\t\t\t\t\t\t99.Log-out.\n\n\t\t\t\t\t\t\tYour option : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            display_all_available();
            break;
        case 2:
            rent(username);
            break;
        case 3:
            returnVaahan(username);
            break;
        case 4:
            add_money(username);
            break;
        case 5:
            display_my_details(username);
            break;
        case 99:
            break;
        default:
            system("cls");
            cout << "\n\t\t\t\t\t\t\tPlease enter valid input !" << endl;
            break;
        }

    } while (choice != 99);
}

void User::Login_admin()
{
    system("cls");
    cout << endl
         << endl;
    char a[] = "\n\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb ADMIN \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    int size;
    size = strlen(a);
    for (int i = 0; i < size; i++)
    {
        Sleep(1);
        cout << a[i];
    }
    string username;
    string password;
    cout << "\n\t\t\t\t\t\t\tDear admin, to login enter your username : ";
    cin >> username;
    cout << "\n\t\t\t\t\t\t\tPlease enter your password : ";
    cin >> password;
    string chk_username;
    string chk_password;

    ifstream fin;
    bool flag = 1;
    fin.open("admin.txt");
    while (!fin.eof())
    {
        getline(fin >> ws, chk_username);
        getline(fin >> ws, chk_password);

        if (username == chk_username && password == chk_password)
        {
            flag = 0;
            AfterLoginAdmin(username);
        }
    }
    if (flag)
        cout << "\n\t\t\t\t\t\t\tInvalid username or password !" << endl;
    system("cls");
    fin.close();
}

void User::AfterLoginAdmin(string username)
{
    system("cls");
    int choice;
    do
    {
        cout << endl
             << endl;
        char a[] = "\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb LOGIN DASHBOARD \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
        int size;
        size = strlen(a);
        for (int i = 0; i < size; i++)
        {
            Sleep(1);
            cout << a[i];
        }
        cout << "\n\t\t\t\t\t\t\t1.Add Vaahan.\n\t\t\t\t\t\t\t2.Repair Vaahan.\n\t\t\t\t\t\t\t3.Display all Vaahans.\n\t\t\t\t\t\t\t4.Display available Vaahans for rent.\n\t\t\t\t\t\t\t5.Display all users data.\n\t\t\t\t\t\t\t99.Exit.\n\n\t\t\t\t\t\t\t Your Choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addVaahan();
            break;
        case 2:
            RepairVaahan();
            break;
        case 3:
            display_all_Vaahan();
            break;
        case 4:
            display_all_available();
            break;
        case 5:
            display_all_users();
            break;
        case 99:
            break;
        default:
            cout << "Please enter valid input !" << endl;
            break;
        }
    } while (choice != 99);
}

void User::Sign_up()
{
    string NameofUser1;
    string password1;
    int balance1;
    string LicenseNumber1;
    string PhoneNumber1;
    cout << "\n\t\t\t\t\t\t\tYour Name : ";
    cin >> NameofUser1;
    cout << "\t\t\t\t\t\t\tChoose a strong password : ";
    cin >> password1;
    cout << "\t\t\t\t\t\t\tAdd money to your account : Rs.";
    cin >> balance1;
    cout << "\t\t\t\t\t\t\tLicense number : ";
    cin >> LicenseNumber1;
    cout << "\t\t\t\t\t\t\tPhone number - ";
    cin >> PhoneNumber1;
    insertNodeUser(NameofUser1, password1, balance1, LicenseNumber1, PhoneNumber1);
}

//====================main=============================//

int main()
{
    system("cls");

    // intro();
    //  system("cls");
    system("color F0");
    // first number for bg color and second for font color
    User obj;
    obj.createUserList();
    obj.createcarList();
    obj.createbusList();
    obj.createbikeList();
    int choice;
    do
    {
        system("cls");
        // for (int k = 0; k < 160; k++)
        // {
        //     cout << char(177);
        // }
        // system("color 08");
        cout << endl
             << endl;
        for (int i = 0; i < 1; i++)
        {
            int x = 0;
            int y = 1;
            for (y = 1; y < 20; y++)
            {
                gotoXY(x, y);
                cout << "\xB1\xB1";
                Sleep(1);
                // gotoXY(x,y);
                // cout << "                                                     ";
            }
            y = 19;
            for (x = 2; x < 160; x++)
            {
                gotoXY(x, y);
                cout << "\xB1";
                Sleep(1);
                // gotoXY(x,y);
                // cout << "                                                     ";
            }
            x = 158;
            for (y = 18; y > 0; y--)
            {
                gotoXY(x, y);
                cout << "\xB1\xB1";
                Sleep(1);

                // cout << "                                                     ";
            }
            y = 0;

            for (x = 159; x > -1; x--)
            {
                gotoXY(x, y);
                cout << "\xB1";
                Sleep(1);
                // gotoXY(x,y);
                // cout << "                                                     ";
            }
            y = 3, x = 5;
            gotoXY(x, y);
        }
        char a[] = "\n\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb VAAHAN WALLAH \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
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
        cout << "\t\t\t\t\t\t\t\t\t     Welcome\n";
        cout << "\t\t\t\t\t\t\t1.Customer.\n\t\t\t\t\t\t\t2.Admin.\n\t\t\t\t\t\t\t99.Exit.\n\n\t\t\t\t\t\t\t";
        cout << "Select Your Option : ";

        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            obj.PreLogin_Customer();
            break;
        case 2:
            system("cls");
            obj.Login_admin();
            break;
        case 99:
            system("cls");
            break;
        default:
            system("cls");
            cout << "Please enter valid input ! \nTry again..." << endl;
            break;
        }
    } while (choice != 99);
}
