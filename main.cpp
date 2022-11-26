#include <bits/stdc++.h>
#include <windows.h>
#include <unistd.h>
#include <ctime>
#include "DesignSrc.cpp"

using namespace std;

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

    void display_all_cars();
    void display_all_bus();
    void display_all_bikes();

    void display_all_available();
    void display_available_cars();
    void display_available_bus();
    void display_available_bikes();

    void addVaahan();
    void RepairVaahan();
    ~Vaahan(){};
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

    if (head_user == NULL)
    {
        cout << "List empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        cout << "Name - " << temp->NameofUser << endl;
        cout << "Password - " << temp->Password << endl;
        cout << "Balance - Rs." << temp->balance << endl;
        cout << "License number - " << temp->LicenseNumber << endl;
        cout << "Phone number - " << temp->PhoneNumber << endl;
        cout << "*************************************" << endl;
        temp = temp->next;
    }
    cout << "\n";
}

void User::display_my_details(string username)
{

    Node_User *temp = head_user;

    if (head_user == NULL)
    {
        cout << "List empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        if (temp->NameofUser == username)
        {
            cout << "Name - " << temp->NameofUser << endl;
            cout << "Password - " << temp->Password << endl;
            cout << "Balance - Rs." << temp->balance << endl;
            cout << "License number - " << temp->LicenseNumber << endl;
            cout << "Phone number - " << temp->PhoneNumber << endl;
            cout << "*************************************" << endl;
        }
        temp = temp->next;
    }
    cout << "\n";
}

void User::rent(string username)
{
    int choice;
    do
    {
        cout << "Which Vaahan would you to rent ?" << endl;
        cout << "1.car\n2.bus\n3.bike\n99.back\n>>";
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
            break;
        default:
            cout << "Please enter valid input !" << endl;
            break;
        }
    } while (choice != 99);
}

void User::rentCar(string username)
{
    cout << "\nWhich car would you like to rent ?\n>>";
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
                if (ptr->charges < ptr2->balance)
                {
                    cout << "Dear customer your Vaahan is booked." << endl;
                    cout << "Details - \nName - " << ptr->NameofVaahan << endl;
                    cout << "Number - " << ptr->NumberPlate << "\n"
                         << ptr->Ventilation << endl;
                    ptr2->balance = ptr2->balance - ptr->charges;
                    cout << "Rs." << ptr->charges << " were deducted from your account." << endl;
                    cout << "Current balance - Rs." << ptr2->balance << endl;
                    ptr->Count--;

                    ofstream fout;
                    fout.open("CarsOnRent.txt", ios::app);
                    fout << ptr2->NameofUser << endl;
                    fout << ptr->NameofVaahan << endl;
                    fout << ptr->NumberPlate << endl;
                    fout << ltm->tm_mday << endl;
                    fout << 1 + ltm->tm_mon << endl;
                    fout << 1900 + ltm->tm_year << endl;
                    fout.close();
                }
                else
                    cout << "Insufficient funds !\nAdd money to your account and try again..." << endl;
            }
            else
                cout << ptr->NameofVaahan << " is crrently unavailable." << endl;
        }
        ptr = ptr->next;
    }
    if (!flag)
        cout << "Car not found !" << endl;
}

void User::rentBus(string username)
{
    cout << "\nWhich bus would you like to rent ?\n>>";
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
                if (ptr->charges < ptr2->balance)
                {
                    cout << bold_on << "Dear customer your Vaahan is booked." << reset << endl;
                    cout << "Details - \nName - " << ptr->NameofVaahan << endl;
                    cout << "Number - " << ptr->NumberPlate << "\n"
                         << ptr->Ventilation << endl;
                    ptr2->balance = ptr2->balance - ptr->charges;
                    cout << "Rs." << ptr->charges << " were deducted from your account." << endl;
                    cout << "Current balance - Rs." << ptr2->balance << endl;
                    ptr->Count--;

                    ofstream fout;
                    fout.open("BusOnRent.txt", ios::app);
                    fout << ptr2->NameofUser << endl;
                    fout << ptr->NameofVaahan << endl;
                    fout << ptr->NumberPlate << endl;
                    fout << ltm->tm_mday << endl;
                    fout << 1 + ltm->tm_mon << endl;
                    fout << 1900 + ltm->tm_year << endl;
                    fout.close();
                }
                else
                    cout << "Insufficient funds !\nAdd money to your account and try again..." << endl;
            }
            else
                cout << ptr->NameofVaahan << " is crrently unavailable." << endl;
        }
        ptr = ptr->next;
    }
    if (!flag)
        cout << "Bus not found !" << endl;
}

void User::rentBike(string username)
{
    cout << "\nWhich bike would you like to rent ?\n>>";
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
                if (ptr->charges < ptr2->balance)
                {
                    cout << bold_on << "Dear customer your Vaahan is booked." << reset << endl;
                    cout << "Details - \nName - " << ptr->NameofVaahan << endl;
                    cout << "Number - " << ptr->NumberPlate << "\n"
                         << ptr->Ventilation << endl;
                    ptr2->balance = ptr2->balance - ptr->charges;
                    cout << "Rs." << ptr->charges << " were deducted from your account." << endl;
                    cout << "Current balance - Rs." << ptr2->balance << endl;
                    ptr->Count--;

                    ofstream fout;
                    fout.open("BikesOnRent.txt", ios::app);
                    fout << ptr2->NameofUser << endl;
                    fout << ptr->NameofVaahan << endl;
                    fout << ptr->NumberPlate << endl;
                    fout << ltm->tm_mday << endl;
                    fout << 1 + ltm->tm_mon << endl;
                    fout << 1900 + ltm->tm_year << endl;
                    fout.close();
                }
                else
                    cout << "Insufficient funds !\nAdd money to your account and try again..." << endl;
            }
            else
                cout << ptr->NameofVaahan << " is crrently unavailable." << endl;
        }
        ptr = ptr->next;
    }
    if (!flag)
        cout << "Bike not found !" << endl;
}

void User::add_money(string username)
{
    Node_User *ptr = head_user;
    int addmoney;
    while (ptr != NULL)
    {
        if (ptr->NameofUser == username)
        {
            cout << "Enter the amount you want to add (in rupees)\n>>";
            cin >> addmoney;
            ptr->balance = ptr->balance + addmoney;
            cout << "Money added to your account successfully !" << endl;
            cout << "Balance - Rs." << bold_on << ptr->balance << reset << endl;
        }
        ptr = ptr->next;
    }
}

void User::returnVaahan(string username)
{
    int choice;
    do
    {
        cout << "Select the type of vaahan you want to return - " << endl;
        cout << "1.car\n2.bus\n3.bike\n99.back\n>>";
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
            cout << "Please enter valid input !" << endl;
            break;
        }
    } while (choice != 99);
}

void User::returnCar(string username)
{
    string NameofVaahan1;
    string NumberPlate1;
    cout << "Enter the name of car : \n>>" << endl;
    cin >> NameofVaahan1;
    cout << "Enter the number plate of car : \n>>" << endl;
    cin >> NumberPlate1;

    ifstream fin;
    string chkNameofVaahan;
    string chkNumberPlate;
    string chkusername;
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
        if (chkusername == username)
        {
            if (chkNameofVaahan == NameofVaahan1 && chkNumberPlate == NumberPlate1)
            {
                int dateIssue[3] = {day2, month2, year2};
                cout << NameofVaahan1 << " - " << NumberPlate1 << "return successfull with no fine !" << endl;

                Node_User *ptr1 = head_user;
                while (ptr1 != NULL)
                {
                    if (ptr1->NameofUser == username)
                    {
                        ptr1->balance = ptr1->balance + 20;
                        cout << "Yayyy! Rs.20 bonus added to your account !" << endl;
                        cout << "Balance - Rs." << ptr1->balance << endl;
                    }
                    ptr1 = ptr1->next;
                }

                Node_Vaahan *ptr2 = head_car;
                while (ptr2 != NULL)
                {
                    if (ptr2->NameofVaahan == NameofVaahan1)
                    {
                        ptr2->Count++;
                    }
                    ptr2 = ptr2->next;
                }

                if (countNoOfDays(dateIssue, dateReturn) > 1)
                    fine(countNoOfDays(dateIssue, dateReturn));
            }
            else
                cout << "Car and its number you are tring to return doesn't match !\nTry again..." << endl;
        }
        else
            cout << "No user found to return any Vaahan type you've chosen." << endl;
    }
}

void User::returnBus(string username)
{
    string NameofVaahan1;
    string NumberPlate1;
    cout << "Enter the name of bus : \n>>" << endl;
    cin >> NameofVaahan1;
    cout << "Enter the number plate of bus : \n>>" << endl;
    cin >> NumberPlate1;

    ifstream fin;
    string chkNameofVaahan;
    string chkNumberPlate;
    string chkusername;
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
        if (chkusername == username)
        {
            if (chkNameofVaahan == NameofVaahan1 && chkNumberPlate == NumberPlate1)
            {
                int dateIssue[3] = {day2, month2, year2};
                cout << NameofVaahan1 << " - " << NumberPlate1 << "return successfull with no fine !" << endl;

                Node_User *ptr1 = head_user;
                while (ptr1 != NULL)
                {
                    if (ptr1->NameofUser == username)
                    {
                        ptr1->balance = ptr1->balance + 20;
                        cout << "Yayyy! Rs.30 bonus added to your account !" << endl;
                        cout << "Balance - Rs." << ptr1->balance << endl;
                    }
                    ptr1 = ptr1->next;
                }

                Node_Vaahan *ptr2 = head_car;
                while (ptr2 != NULL)
                {
                    if (ptr2->NameofVaahan == NameofVaahan1)
                    {
                        ptr2->Count++;
                    }
                    ptr2 = ptr2->next;
                }

                if (countNoOfDays(dateIssue, dateReturn) > 1)
                    fine(countNoOfDays(dateIssue, dateReturn));
            }
            else
                cout << "Bus and its number you are tring to return doesn't match !\nTry again..." << endl;
        }
        else
            cout << "No user found to return any Vaahan type you've chosen." << endl;
    }
}

void User::returnBike(string username)
{
    string NameofVaahan1;
    string NumberPlate1;
    cout << "Enter the name of bike : \n>>" << endl;
    cin >> NameofVaahan1;
    cout << "Enter the number plate of bike : \n>>" << endl;
    cin >> NumberPlate1;

    ifstream fin;
    string chkNameofVaahan;
    string chkNumberPlate;
    string chkusername;
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
        if (chkusername == username)
        {
            if (chkNameofVaahan == NameofVaahan1 && chkNumberPlate == NumberPlate1)
            {
                int dateIssue[3] = {day2, month2, year2};
                cout << NameofVaahan1 << " - " << NumberPlate1 << "return successfull with no fine !" << endl;

                Node_User *ptr1 = head_user;
                while (ptr1 != NULL)
                {
                    if (ptr1->NameofUser == username)
                    {
                        ptr1->balance = ptr1->balance + 20;
                        cout << "Yayyy! Rs.20 bonus added to your account !" << endl;
                        cout << "Balance - Rs." << ptr1->balance << endl;
                    }
                    ptr1 = ptr1->next;
                }

                Node_Vaahan *ptr2 = head_bike;
                while (ptr2 != NULL)
                {
                    if (ptr2->NameofVaahan == NameofVaahan1)
                    {
                        ptr2->Count++;
                    }
                    ptr2 = ptr2->next;
                }

                if (countNoOfDays(dateIssue, dateReturn) > 1)
                    fine(countNoOfDays(dateIssue, dateReturn));
            }
            else
                cout << "Bike and its number you are tring to return doesn't match !\nTry again..." << endl;
        }
        else
            cout << "No user found to return any Vaahan type you've chosen." << endl;
    }
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

void Vaahan::display_all_cars()
{
    Node_Vaahan *temp = head_car;

    if (head_car == NULL)
    {
        cout << "List empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        cout << "Name - " << temp->NameofVaahan << endl;
        cout << "Number plate - " << temp->NumberPlate << endl;
        cout << "ventilation type - " << temp->Ventilation << endl;
        cout << "Charges per hour - Rs." << temp->charges << endl;
        cout << "Count - " << temp->Count << endl;
        temp = temp->next;
        cout << "*************************************" << endl;
    }
    cout << "\n";
}

void Vaahan::display_all_bus()
{
    Node_Vaahan *temp = head_bus;

    if (head_bus == NULL)
    {
        cout << "List empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        cout << "Name - " << temp->NameofVaahan << endl;
        cout << "Number plate - " << temp->NumberPlate << endl;
        cout << "ventilation type - " << temp->Ventilation << endl;
        cout << "Charges per hour - Rs." << temp->charges << endl;
        cout << "Count - " << temp->Count << endl;
        temp = temp->next;
        cout << "*************" << endl;
    }
    cout << "\n";
}

void Vaahan::display_all_bikes()
{
    Node_Vaahan *temp = head_bike;

    if (head_bike == NULL)
    {
        cout << "List empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        cout << "Name - " << temp->NameofVaahan << endl;
        cout << "Number plate - " << temp->NumberPlate << endl;
        cout << "ventilation type - " << temp->Ventilation << endl;
        cout << "Charges per hour - Rs." << temp->charges << endl;
        cout << "Count - " << temp->Count << endl;
        temp = temp->next;
        cout << "*************" << endl;
    }
    cout << "\n";
}

void Vaahan::display_all_available()
{
    int choice;
    do
    {
        cout << "\nChoose type of Vaahan\n1.Car.\n2.Bus.\n3.Bike.\n99.back.\n>>";
        cin >> choice;
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
            cout << "Please enter valid input !" << endl;
            break;
        }

    } while (choice != 99);
}

void Vaahan::display_available_cars()
{
    Node_Vaahan *temp = head_car;

    if (head_car == NULL)
    {
        cout << "List empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        if (temp->Count > 0)
        {
            cout << "Name - " << temp->NameofVaahan << endl;
            cout << "Number plate - " << temp->NumberPlate << endl;
            cout << "ventilation type - " << temp->Ventilation << endl;
            cout << "Charges per hour - Rs." << temp->charges << endl;
            cout << "Count - " << temp->Count << endl;
            temp = temp->next;
            cout << "*************************************" << endl;
        }
    }
    cout << "\n";
}

void Vaahan::display_available_bus()
{
    Node_Vaahan *temp = head_bus;

    if (head_bus == NULL)
    {
        cout << "List empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        if (temp->Count > 0)
        {
            cout << "Name - " << temp->NameofVaahan << endl;
            cout << "Number plate - " << temp->NumberPlate << endl;
            cout << "ventilation type - " << temp->Ventilation << endl;
            cout << "Charges per hour - Rs." << temp->charges << endl;
            cout << "Count - " << temp->Count << endl;
            temp = temp->next;
            cout << "*************" << endl;
        }
    }
    cout << "\n";
}

void Vaahan::display_available_bikes()
{
    Node_Vaahan *temp = head_bike;

    if (head_bike == NULL)
    {
        cout << "List empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        if (temp->Count > 0)
        {
            cout << "Name - " << temp->NameofVaahan << endl;
            cout << "Number plate - " << temp->NumberPlate << endl;
            cout << "ventilation type - " << temp->Ventilation << endl;
            cout << "Charges per hour - Rs." << temp->charges << endl;
            cout << "Count - " << temp->Count << endl;
            temp = temp->next;
            cout << "*************" << endl;
        }
    }
    cout << "\n";
}

void Vaahan::addVaahan()
{
    string NameofVaahan1;
    string NumberPlate1;
    string Ventilation1;
    int Count1 = 1;
    int charges1;

    cout << "Enter the type of Vaahan you want to add ( car / bus / bike )\n>>";
    string choice;
    cin >> choice;

    cout << "Please enter the Name of Vaahan\n>>";
    getline(cin, NameofVaahan1);
    cout << "Please enter the number plate\n>>";
    getline(cin, NumberPlate1);
    cout << "Please enter the ventilation type \n>>";
    getline(cin, Ventilation1);
    cout << "Please enter the charges (in Rs.) per day\n>>";
    cin >> charges1;

    if (choice == "car")
        insertNodecar(NameofVaahan1, NumberPlate1, Ventilation1, Count1, charges1);
    else if (choice == "bus")
        insertNodebus(NameofVaahan1, NumberPlate1, Ventilation1, Count1, charges1);
    else if (choice == "bike")
        insertNodebike(NameofVaahan1, NumberPlate1, Ventilation1, Count1, charges1);
    else
        cout << "Please enter valid argument and try again !" << endl;
}

void Vaahan::RepairVaahan()
{
    string NameofVaahan1;
    string NumberPlate1;
    string choice1;
    string choice2;

    cout << "Enter the type of Vaahan you want to add ( car / bus / bike )\n>>";
    cin >> choice1;
    cout << "Enter the name of Vaahan you want to repair\n>>";
    cin >> NameofVaahan1;
    cout << "Enter the Number plate of Vaahan \n>>";
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
                    cout << ptr->NameofVaahan << "with number " << ptr->NumberPlate
                         << " will be sent to garage for repair." << endl;
                    cout << "Please wait mechanic is checking the condition of car... " << endl;
                    ShowPercentCompleteFast();
                    cout << "\nCheck-up done ! ";
                    // srand(time(0));
                    // int temp = 1 + (rand() % 5);
                    // cout << "Mechanic suggests to keep the car for " << temp << " day(s) in the garage." << endl;

                    cout << "You need to wait for a while untill the car gets repaired. " << endl;
                    cout << "You still want to continue with repair process ( yes / no )?\n>>";
                    cin >> choice2;
                    if (choice2 == "yes")
                    {
                        cout << "Mechanic is repairing your car..." << endl;
                        ShowPercentCompleteSlow();
                        cout << "Car repair success !" << endl;
                    }
                    else if (choice2 == "no")
                    {
                        cout << "Ok ! Car not sent for repair." << endl;
                        break; // so that 'while loop' does not keep on iterating unnecessarily --> to save a bit of time
                    }
                    else
                    {
                        cout << "Enter valid input and try again !" << endl;
                        break; // so that 'while loop' does not keep on iterating unnecessarily --> to save a bit of time
                    }
                }
                else
                    cout << "Dear admin " << NameofVaahan1 << " is " << underline_on << "not" << reset
                         << " available with you currently.\n Check whether it is given for rent or already sent to mechanic." << endl;
            }
            ptr = ptr->next;
        }
        if (flag)
            cout << "Car not found with name " << NameofVaahan1 << " and "
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
                    cout << ptr->NameofVaahan << "with number " << ptr->NumberPlate
                         << " will be sent to garage for repair." << endl;
                    cout << "Please wait mechanic is checking the condition of bus... " << endl;
                    ShowPercentCompleteFast();
                    cout << "\nCheck-up done ! ";
                    // srand(time(0));
                    // int temp = 1 + (rand() % 5);
                    // cout << "Mechanic suggests to keep the car for " << temp << " day(s) in the garage." << endl;

                    cout << "You need to wait for a while untill the bus gets repaired. " << endl;
                    cout << "You still want to continue with repair process ( yes / no )?\n>>";
                    cin >> choice2;
                    if (choice2 == "yes")
                    {
                        cout << "Mechanic is repairing your bus..." << endl;
                        ShowPercentCompleteSlow();
                        cout << "Bus repair success !" << endl;
                    }
                    else if (choice2 == "no")
                    {
                        cout << "Ok ! Bus not sent for repair." << endl;
                        break; // so that 'while loop' does not keep on iterating unnecessarily --> to save a bit of time
                    }
                    else
                    {
                        cout << "Enter valid input and try again !" << endl;
                        break; // so that 'while loop' does not keep on iterating unnecessarily --> to save a bit of time
                    }
                }
                else
                    cout << "Dear admin " << NameofVaahan1 << " is " << underline_on << "not" << reset
                         << " available with you currently.\n Check whether it is given for rent or already sent to mechanic." << endl;
            }
            ptr = ptr->next;
        }
        if (flag)
            cout << "Bus not found with name " << NameofVaahan1 << " and "
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
                    cout << ptr->NameofVaahan << "with number " << ptr->NumberPlate
                         << " will be sent to garage for repair." << endl;
                    cout << "Please wait mechanic is checking the condition of bike... " << endl;
                    ShowPercentCompleteFast();
                    cout << "\nCheck-up done ! ";
                    // srand(time(0));
                    // int temp = 1 + (rand() % 5);
                    // cout << "Mechanic suggests to keep the car for " << temp << " day(s) in the garage." << endl;

                    cout << "You need to wait for a while untill the bike gets repaired. " << endl;
                    cout << "You still want to continue with repair process ( yes / no )?\n>>";
                    cin >> choice2;
                    if (choice2 == "yes")
                    {
                        cout << "Mechanic is repairing your bike..." << endl;
                        ShowPercentCompleteSlow();
                        cout << "bike repair success !" << endl;
                    }
                    else if (choice2 == "no")
                    {
                        cout << "Ok ! Bike not sent for repair." << endl;
                        break; // so that 'while loop' does not keep on iterating unnecessarily --> to save a bit of time
                    }
                    else
                    {
                        cout << "Enter valid input and try again !" << endl;
                        break; // so that 'while loop' does not keep on iterating unnecessarily --> to save a bit of time
                    }
                }
                else
                    cout << "Dear admin " << NameofVaahan1 << " is " << underline_on << "not" << reset
                         << " available with you currently.\n Check whether it is given for rent or already sent to mechanic." << endl;
            }
            ptr = ptr->next;
        }
        if (flag)
            cout << "Bike not found with name " << NameofVaahan1 << " and "
                 << "number " << NumberPlate1 << ", try again later." << endl;
    }

    else
        cout << "Invalid input ,please try again." << endl;
}

//===================Login / sign-up==========================//

void User::PreLogin_Customer()
{
    system("cls");
    int choice;
    do
    {
        cout << "1.Login.\n2.Sign-up.\n99.Exit.\n>>";
        cin >> choice;
        switch (choice)
        {
        case 1:
            Login_customer();
            break;
        case 2:
            Sign_up();
            break;
        case 99:
            break;
        default:
            cout << "Please enter valid input !" << endl;
            break;
        }

    } while (choice != 99);
}

void User::Login_customer()
{
    string username;
    string password;
    cout << "Enter your username\n>>";
    cin >> username;
    cout << "Enter your password\n>>";
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
        cout << "Invalid username or password !" << endl;
}

void User::AfterLoginCustomer(string username)
{
    system("cls");
    int choice;
    do
    {
        cout << "1.Check for available Vaahan.\n2.Rent a Vaahan.\n3.Return Vaahan.\n4.Add Money.\n5.Display my details.\n99.Log-out.\n>>";
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
            cout << "Please enter valid input !" << endl;
            break;
        }

    } while (choice != 99);
}

void User::Login_admin()
{
    system("cls");
    string username;
    string password;
    cout << "Dear admin, to login enter your username \n>>";
    cin >> username;
    cout << "Please enter your password\n>>";
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
        cout << "Invalid username or password !" << endl;
    fin.close();
}

void User::AfterLoginAdmin(string username)
{
    int choice;
    do
    {
        cout << "1.Add Vaahan.\n2.Repair Vaahan.\n3.Display all Vaahans.\n4.Display available Vaahans for rent.\n5.Display all users data.\n99.Exit.\n>>";
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
            display_all_cars();
            break;
        case 4:
            display_available_cars();
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
    cout << "Your Name - " << endl;
    getline(cin, NameofUser1);
    cout << "Choose a strong password - " << endl;
    getline(cin, password1);
    cout << "Add money to your account - Rs." << endl;
    cin >> balance1;
    cout << "License number - " << endl;
    getline(cin, LicenseNumber1);
    cout << "Phone number - " << endl;
    getline(cin, PhoneNumber1);
    insertNodeUser(NameofUser1, password1, balance1, LicenseNumber1, PhoneNumber1);
}

//====================main=============================//

int main()
{
    system("cls");
    // intro();
    // system("cls");
    system("color 5F");
    // first number for bg color and second for font color
    User obj;
    obj.createUserList();
    obj.createcarList();
    obj.createbusList();
    obj.createbikeList();
    int choice;
    do
    {
        cout << "1.Customer.\n2.Admin.\n99.Exit.\n>>";
        cin >> choice;
        switch (choice)
        {
        case 1:
            obj.PreLogin_Customer();
            break;
        case 2:
            obj.Login_admin();
            break;
        case 99:
            break;
        default:
            cout << "Please enter valid input ! \nTry again..." << endl;
            break;
        }
    } while (choice != 99);
}
