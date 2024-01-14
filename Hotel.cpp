#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <algorithm>

using namespace std;

//Global variable
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
stringstream ss;
int qstate = 0;
int flag = 0;

int admin_id = 0;//Variable to check if login successful or not.
string admin_email, admin_pass;
int housekeeper_id = 0;//Variable to check if login successful or not.
string housekeeper_email, housekeeper_pass;
int cust_id = 0;//Variable to check if login successful or not.
string cust_email, cust_pass;
int room_id, status;
string room_status;
//Global variable end

//Admin function
void header();
int adminLogin(MYSQL*, string, string);
void adminMenu();
void manageCustomer();
void showCustomer();
void searchCustomer();
void manageRoom();
void addRoom();
void showRoom();
void searchRoom();
void updateRoom();
void deleteRoom();
void manageReservation();
void showReservation();
void searchReservation();
int checkin(MYSQL*);
int checkout(MYSQL*);

//Customer function
void updateProfile(MYSQL*, int);
int cancelReservation(MYSQL*, int);
void viewReservation(MYSQL*, int);
void customerRegister(MYSQL*);
int customerLogin(MYSQL*, string, string);
int customerMenu();
int makeReservation(MYSQL*, int);
int validpass(string&, int);
int id_generator(MYSQL*, string);

//Housekeeper function
int housekeeperLogin(MYSQL*, string, string);
void housekeeperMenu();
int cleanRoom(MYSQL*);

//Main header 
void header()
{
    cout << "\t\t\t********************************************************************\n\n";
    cout << "\t\t\t          WELCOME TO SEAVIEW HOTEL ROOM MANAGEMENT SYSTEM                                \n\n";
    cout << "\t\t\t********************************************************************\n\n";
}

int main()
{
    system("title Hotel Room Management System");
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "", "dbhotel", 3306, NULL, 0);

    system("Color E4");//E is background color yellow and 4 is text color red

    if (conn) {
        char choice;
        
        do
        {
            header();
            cout << "\t\t\t\t      N0 20, BATU 12, JALAN PERSINGGAHAN LAMA," << endl;
            cout << "\t\t\t\t\t  LORONG 2, 20400 KUALA TERENGGANU," << endl;
            cout << "\t\t\t\t\t\tTERENGGANU, MALAYSIA.\n" << endl;
            cout << "\t\t\t\t\t      CONTACT NUMBER: 03-5763342\n" << endl;
            time_t now = time(0);
            char str[26] = {};
            ctime_s(str, 26, &now);
            string d = str;
            cout << "\t\t\t\t\t      " << d << endl;

            cout << "\n\n\t\t\t\t_____________________ MAIN MENU ___________________\n" << endl;
            cout << "\t\t\t\t\t\t1.Admin Login" << endl;
            cout << "\t\t\t\t\t\t2.Customer Login" << endl;
            cout << "\t\t\t\t\t\t3.Customer Register" << endl;
            cout << "\t\t\t\t\t\t4.Housekeepeer Login" << endl;
            cout << "\t\t\t\t\t\t0.Exit" << endl;
            cout << "\n\t\t\t\t\t\tEnter your choice :";
            cin >> choice;
            system("cls");
            switch (choice)
            {
            case '1':
                header();
                cout << "\t\t\t\t________________________ LOGIN _________________________\n" << endl;
                cout << "\t\t\t\t\tEnter email address: ";
                cin.ignore();
                getline(cin, admin_email);
                transform(admin_email.begin(), admin_email.end(), admin_email.begin(), ::tolower);//Function to transform the string to lowercase whatever the case input is.

                cout << "\t\t\t\t\tEnter password: ";
                char ch;
                ch = _getch();
                while (ch != 13) {//character 13 is enter
                    admin_pass.push_back(ch);
                    cout << '*';
                    ch = _getch();
                }

                admin_id = adminLogin(conn, admin_email, admin_pass);//returns id number
                if (admin_id != 0)
                {
                    system("cls");
                    adminMenu();
                }
                else cout << "Please Login again..." << endl << endl;
                system("pause");
                system("cls");
                break;
            case '2':
                header();
                cout << "\t\t\t\t________________________ LOGIN _________________________\n" << endl;
                cout << "\t\t\t\t\tEnter email address: ";
                cin.ignore();
                getline(cin, cust_email);
                transform(cust_email.begin(), cust_email.end(), cust_email.begin(), ::tolower);//Function to transform the string to lowercase whatever the case input is.

                cout << "\t\t\t\t\tEnter password: ";
                char ch1;
                ch1 = _getch();
                while (ch1 != 13) {//character 13 is enter
                    cust_pass.push_back(ch1);
                    cout << '*';
                    ch1 = _getch();
                }

                cust_id = customerLogin(conn, cust_email, cust_pass);//returns id number
                if (cust_id != 0)
                {
                    system("cls");
                    customerMenu();

                }
                else cout << "Please Login again..." << endl << endl;
                system("pause");
                system("cls");
                break;
            case '3':
                customerRegister(conn);
                break;
            case '4':
                header();
                cout << "\t\t\t\t________________________ LOGIN _________________________\n" << endl;
                cout << "\t\t\t\t\tEnter email address: ";
                cin.ignore();
                getline(cin, housekeeper_email);
                transform(housekeeper_email.begin(), housekeeper_email.end(), housekeeper_email.begin(), ::tolower);//Function to transform the string to lowercase whatever the case input is.

                cout << "\t\t\t\t\tEnter password: ";
                char ch2;
                ch2 = _getch();
                while (ch2 != 13) {//character 13 is enter
                    housekeeper_pass.push_back(ch2);
                    cout << '*';
                    ch2 = _getch();
                }

                housekeeper_id = housekeeperLogin(conn, housekeeper_email, housekeeper_pass);//returns id number
                if (housekeeper_id != 0)
                {
                    system("cls");
                    housekeeperMenu();
                }
                else cout << "Please Login again..." << endl << endl;
                system("pause");
                system("cls");
                break;
            case '0':
                cout << "Thank You!!!!!" << endl;
                break;
            default:
                cout << "Please Enter a valid input" << endl;
                break;
            }
        } while (choice != '0');
    }
    else
    {
        cout << "Database Not Connected" << endl;
    }
    return 0;
}

//Function to check leap year
int check_leap_year(int year)
{
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)   //if year is a leap year
        return 1;

    else
        return 0;
}

//Function to check how many days in a month
int no_of_days_in_month(int month, int year)
{
    // jan, march, may, july, aug, oct, dec contains 31 days
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;

    // april, jun, sept, nov contains 30 days
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;

    if (month == 2)
    {
        int n = check_leap_year(year);
        if (n == 1)    // if year is a leap year then Feb will contain 29 days, otherwise it contains 28 days
            return 29;

        else
            return 28;
    }
}

//Function to calculate days between two dates
long long int difference_of_days(int day1, int month1, int year1, int day2, int month2, int year2)
{
    if (year1 == year2)
    {
        if (month1 == month2)
        {
            if (day1 == day2)      //for same dates
                return 0;
            else
                return abs(day1 - day2);  //for same year, same month but diff days
        }
        else if (month1 < month2)
        {
            int result = 0;
            for (int i = month1; i < month2; i++)
                result = result + no_of_days_in_month(i, year1);

            if (day1 == day2)      //for same year, same day but diff month 
                return result;
            else if (day1 < day2)
            {
                result = result + (day2 - day1);
                return result;
            }
            else
            {
                result = result - (day1 - day2);
                return result;
            }
        }
        else
        {
            int result = 0;
            for (int i = month2; i < month1; i++)
                result = result + no_of_days_in_month(i, year1);

            if (day1 == day2)
                return result;
            else if (day2 < day1)
            {
                result = result + (day1 - day2);
                return result;
            }
            else
            {
                result = result - (day2 - day1);
                return result;
            }
        }
    }
    else if (year1 < year2)
    {
        int temp = 0;
        for (int i = year1; i < year2; i++)
        {
            if (check_leap_year(i))
                temp = temp + 366;
            else
                temp = temp + 365;
        }

        if (month1 == month2)
        {
            if (day1 == day2)      //for same month, same day but diff year
                return temp;
            else if (day1 < day2)
                return temp + (day2 - day1);
            else
                return temp - (day1 - day2);
        }
        else if (month1 < month2)
        {
            int result = 0;
            for (int i = month1; i < month2; i++)
                result = result + no_of_days_in_month(i, year2);

            if (day1 == day2)      // for same day, diff year and diff month
                return temp + result;
            else if (day1 < day2)
            {
                result = result + (day2 - day1);
                return temp + result;
            }
            else
            {
                result = result - (day1 - day2);
                return temp + result;
            }
        }
        else
        {
            int result = 0;
            for (int i = month2; i < month1; i++)
                result = result + no_of_days_in_month(i, year2);

            if (day1 == day2)
                return temp - result;
            else if (day2 < day1)
            {
                result = result + (day1 - day2);
                return temp - result;
            }
            else
            {
                result = result - (day2 - day1);
                return temp - result;
            }
        }
    }
    else
    {
        int temp = 0;
        for (int i = year2; i < year1; i++)
        {
            if (check_leap_year(i))
                temp = temp + 366;
            else
                temp = temp + 365;
        }

        if (month1 == month2)
        {
            if (day1 == day2)      // for same day, same month but diff year
                return temp;
            else if (day2 < day1)
                return temp + (day1 - day2);
            else
                return temp - (day2 - day1);
        }
        else if (month2 < month1)
        {
            int result = 0;
            for (int i = month2; i < month1; i++)
                result = result + no_of_days_in_month(i, year1);

            if (day1 == day2)
                return temp + result;
            else if (day2 < day1)
            {
                result = result + (day1 - day2);
                return temp + result;
            }
            else
            {
                result = result - (day2 - day1);
                return temp + result;
            }
        }
        else
        {
            int result = 0;
            for (int i = month1; i < month2; i++)
                result = result + no_of_days_in_month(i, year1);

            if (day1 == day2)      // for same day, diff year and diff month
                return temp - result;
            else if (day1 < day2)
            {
                result = result + (day2 - day1);
                return temp - result;
            }
            else
            {
                result = result - (day1 - day2);
                return temp - result;
            }
        }
    }
}

//HOUSEKEEPER
int housekeeperLogin(MYSQL* conn, string housekeeper_email, string housekeeper_pass)
{
    ss << "SELECT housekeeper_id,housekeeper_email,housekeeper_pass FROM housekeeper";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0) {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) { 
            if ((strcmp(row[1], housekeeper_email.c_str()) == 0) && (strcmp(row[2], housekeeper_pass.c_str()) == 0))
            {
                flag = 1;
                cout << "\nLogin Successful..." << endl;
                char* ch = row[0];
                return atoi(ch);
            }
        }
        if (flag == 0)
        {
            cout << "\nInvalid username/password...." << endl;
            return 0;
        }
    }
    else
    {
        cout << "Error Occurred: " << mysql_error(conn) << endl;
        return 0;
    }
    return 0;
}

void housekeeperMenu()
{
    system("cls");

    int choice;
    char exitConfirmation;

    header();
    cout << "\t\t\t\t__________________ HOUSEKEEPER MENU __________________\n" << endl;
    cout << "\t\t\t\t\t\t1.Housekeeping Service" << endl;
    cout << "\t\t\t\t\t\t2.Exit" << endl;
    cout << "\n\t\t\t\t\t\tEnter your choice :";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        cleanRoom(conn);
        break;
    case 2:
    ExitProgram:
        cout << "Are you sure to close this program? (Y/N): ";
        cin >> exitConfirmation;
        if (exitConfirmation == 'y' || exitConfirmation == 'Y') {
            exit(0);
        }
        else if (exitConfirmation == 'n' || exitConfirmation == 'N') {
            system("cls");
            housekeeperMenu();
        }
        else {
            cout << "Choose only Y or N" << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please Enter a valid input" << endl;
        break;
    }
}

//Function for housekeeper to update room status
int cleanRoom(MYSQL* conn)
{
    system("cls");
    header();
    cout << "\t\t\t\t__________________ CHANGE ROOM STATUS __________________\n" << endl;

    // Variables
    string room_id = "";
    char choose;
    char choose2;
    int qstate2 = 0;
    stringstream ss2;

    cout << "\t\t\t\t\tDo you wish to continue? Press(Y/N) : ";
    cin >> choose;
    cout << endl;

    if (choose == 'Y' || choose == 'y')
    {
        cout << "\t\t\t\t\tHave you already clean the room? Press(Y/N) : ";
        cin >> choose2;
        cout << endl;

        if (choose2 == 'Y' || choose2 == 'y')
        {
            cin.ignore(1, '\n');
            cout << "\t\t\t\t\t\tEnter Room No: ";
            getline(cin, room_id);

            ss2 << "UPDATE room SET room_status = 'A' WHERE room_id = " << room_id << "";
            string query2 = ss2.str();
            const char* q2 = query2.c_str();
            qstate2 = mysql_query(conn, q2);
            if (qstate2 == 0)
            {
                time_t now = time(0);
                char str[26] = {};
                ctime_s(str, 26, &now);
                string d = str;
                cout << "Update successful... " << d << endl;
                system("pause");
                housekeeperMenu();
            }
            else cout << "Update failed! Error is : " << mysql_error(conn) << endl;
        }
        else
        {
            cout << "\t\t\t\t\tSorry. You cannot change the status of the room." << endl;
            cout << "\t\t\t\t\tPlease clean the room first.\n" << endl;
            system("pause");
            housekeeperMenu();
        }
    }
    else
    {
        housekeeperMenu();
    }

    return 0;
}

//ADMIN
int adminLogin(MYSQL* conn, string admin_email, string admin_pass)
{
    ss << "SELECT admin_id,admin_email,admin_pass FROM admin";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0) {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) { 
            if ((strcmp(row[1], admin_email.c_str()) == 0) && (strcmp(row[2], admin_pass.c_str()) == 0))
            {
                flag = 1;
                cout << "\nLogin Successful..." << endl;
                char* ch = row[0];
                return atoi(ch);
            }
        }
        if (flag == 0)
        {
            cout << "\nInvalid username/password...." << endl;
            return 0;
        }
    }
    else
    {
        cout << "Error Occurred: " << mysql_error(conn) << endl;
        return 0;
    }
    return 0;
}

void adminMenu()
{
    system("cls");

    int choice;
    char exitConfirmation;

    header();
    cout << "\t\t\t\t______________________ ADMIN MENU ____________________\n" << endl;
    cout << "\t\t\t\t\t\t1.Manage room" << endl;
    cout << "\t\t\t\t\t\t2.Manage customer" << endl;
    cout << "\t\t\t\t\t\t3.Manage reservation" << endl;
    cout << "\t\t\t\t\t\t4.Checkin" << endl;
    cout << "\t\t\t\t\t\t5.Checkout" << endl;
    cout << "\t\t\t\t\t\t6.Exit" << endl;
    cout << "\n\t\t\t\t\t\tEnter your choice :";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        manageRoom();
        break;
    case 2:
        manageCustomer();
        break;
    case 3:
        manageReservation();
        break;
    case 4:
        checkin(conn);
        break;
    case 5:
        checkout(conn);
        break;
    case 6:
    ExitProgram:
        cout << "Are you sure to close this program? (Y/N): ";
        cin >> exitConfirmation;
        if (exitConfirmation == 'y' || exitConfirmation == 'Y') {
            exit(0);
        }
        else if (exitConfirmation == 'n' || exitConfirmation == 'N') {
            system("cls");
            adminMenu();
        }
        else {
            cout << "Choose only Y or N" << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please Enter a valid input" << endl;
        system("pause");
        adminMenu();
    }
}

//Function for admin to manage room
void manageRoom()
{
    system("cls");

    int choice;

    header();
    cout << "\t\t\t\t______________________ MANAGE ROOM ____________________\n" << endl;
    cout << "\t\t\t\t\t\t1.Add room" << endl;
    cout << "\t\t\t\t\t\t2.Show room" << endl;
    cout << "\t\t\t\t\t\t3.Search room" << endl;
    cout << "\t\t\t\t\t\t4.Update room" << endl;
    cout << "\t\t\t\t\t\t5.Delete room" << endl;
    cout << "\t\t\t\t\t\t6.Back" << endl;
    cout << "\n\t\t\t\t\t\tEnter your choice :";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        addRoom();
        break;
    case 2:
        showRoom();
        break;
    case 3:
        searchRoom();
        break;
    case 4:
        updateRoom();
        break;
    case 5:
        deleteRoom();
        break;
    case 6:
        system("cls");
        adminMenu();
        break;
    default:
        cout << "Please Enter a valid input" << endl;
        system("pause");
        adminMenu();
    }
}

//Function for admin to add room
void addRoom()
{
    system("cls");

    char choose;
    
    string room_id = "";
    string room_type = "";
    string room_capacity = "";
    string room_aircond = "";
    string room_tv = "";
    string room_wifi = "";
    string room_price = "";
    string room_status = "";

    header();
    cout << "\t\t\t\t______________________ ADD ROOM ____________________\n" << endl;
    cin.ignore(1, '\n');
    cout << "\t\t\t\t\t\tEnter Room Number: ";
    getline(cin, room_id);
    cout << "\t\t\t\t\t\tEnter Type (S/N): ";
    getline(cin, room_type);
    cout << "\t\t\t\t\t\tEnter Capacity: ";
    getline(cin, room_capacity);
    cout << "\t\t\t\t\t\tEnter Aircond (Y/N): ";
    getline(cin, room_aircond);
    cout << "\t\t\t\t\t\tEnter TV (Y/N): ";
    getline(cin, room_tv);
    cout << "\t\t\t\t\t\tEnter Wifi (Y/N): ";
    getline(cin, room_wifi);
    cout << "\t\t\t\t\t\tEnter Price per night (RM): ";
    getline(cin, room_price);
    cout << "\t\t\t\t\t\tEnter Status (A/NA): ";
    getline(cin, room_status);

    string insert_query = "insert into room (room_id, room_type, room_capacity, room_aircond ,room_tv , room_wifi, room_price, room_status) values ('" + room_id + "','" + room_type + "','" + room_capacity + "','" + room_aircond + "','" + room_tv + "','" + room_wifi + "','" + room_price + "' ,'" + room_status + "')";

    const char* q = insert_query.c_str();

    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        status = 0;
        cout << endl << "Room Created...." << endl;
    }
    else
    {
        cout << "Room Not Created! Error Occurred...." << endl;
        cout << mysql_error(conn) << endl;
    }

ExitMenu:
    cout << "Press 'm' for Menu or any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        manageRoom();
    }
    else
    {
        exit(0);
    }
}

//Function for admin to view room
void showRoom() {
    system("cls");

    char choose;
    int choice;
    string input;
    MYSQL_RES* ress;
    header();
    cout << "\n\t\t\t\t______________________ SHOW ROOM ____________________\n\n" << endl;
    cout << "\t\t\t\t\t\t1.Show all room" << endl;
    cout << "\t\t\t\t\t\t2.Show room at Level 1" << endl;
    cout << "\t\t\t\t\t\t3.Show room at Level 2" << endl;
    cout << "\t\t\t\t\t\t4.Back" << endl;
    cout << "\n\t\t\t\t\t\tEnter your choice :";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        system("cls");
        header();
        cout << "\n\t\t\t\t______________________ ALL ROOM ____________________\n\n" << endl;
        
        qstate = mysql_query(conn, "select * from room");
        if (!qstate)
        {
            ress = mysql_store_result(conn);
            printf("\t\t-----------------------------------------------------------------------------------------\n");
            printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", "Room No", "Type", "Capacity", "Aircond", "TV", "Wifi", "Price", "Status");
            printf("\t\t-----------------------------------------------------------------------------------------\n");
            while ((row = mysql_fetch_row(ress)))
            {
                printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
            }
            printf("\t\t-----------------------------------------------------------------------------------------\n");
            int total = mysql_num_rows(ress);
            cout << "\n\t\t\t\t\tTOTAL NUMBER OF RECORDS MADE SO FAR : " << total << endl << endl;

            cout << "\n\t\t\t\t______________________ SHOW REPORT ____________________\n\n" << endl;
            printf("\t\t\t\t-------------------------------------------------------\n");
            printf("\t\t\t\t| %-15s | %-15s | %-15s |\n", "Status", "Total", "Percentage");
            printf("\t\t\t\t-------------------------------------------------------\n");

            int qstate2 = mysql_query(conn, "select * from room where room_status = 'A'");
            res = mysql_store_result(conn);
            int total2 = mysql_num_rows(res);
            int percentage2 = (total2 * 100) / total;

            if (percentage2 == 100)
            cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "********************" << endl;
            else if (percentage2 >= 90 && percentage2 < 100)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "******************" << endl;
            else if (percentage2 >= 80 && percentage2 < 90)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "****************" << endl;
            else if (percentage2 >= 70 && percentage2 < 80)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "**************" << endl;
            else if (percentage2 >= 60 && percentage2 < 70)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "************" << endl;
            else if (percentage2 >= 50 && percentage2 < 60)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "**********" << endl;
            else if (percentage2 >= 40 && percentage2 < 50)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "********" << endl;
            else if (percentage2 >= 30 && percentage2 < 40)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "******" << endl;
            else if (percentage2 >= 20 && percentage2 < 30)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "****" << endl;
            else if (percentage2 >= 10 && percentage2 < 20)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%" << endl;

            int qstate3 = mysql_query(conn, "select * from room where room_status = 'NA'");
            res = mysql_store_result(conn);
            int total3 = mysql_num_rows(res);
            int percentage3 = (total3 * 100) / total;

            if (percentage3 == 100)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "********************" << endl;
            else if (percentage3 >= 90 && percentage3 < 100)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "******************" << endl;
            else if (percentage3 >= 80 && percentage3 < 90)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "****************" << endl;
            else if (percentage3 >= 70 && percentage3 < 80)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "**************" << endl;
            else if (percentage3 >= 60 && percentage3 < 70)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "************" << endl;
            else if (percentage3 >= 50 && percentage3 < 60)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "**********" << endl;
            else if (percentage3 >= 40 && percentage3 < 50)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "********" << endl;
            else if (percentage3 >= 30 && percentage3 < 40)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "******" << endl;
            else if (percentage3 >= 20 && percentage3 < 30)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "****" << endl;
            else if (percentage3 >= 10 && percentage3 < 20)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%" << endl;

            int qstate4 = mysql_query(conn, "select * from room where room_status = 'BOOKED'");
            res = mysql_store_result(conn);
            int total4 = mysql_num_rows(res);
            int percentage4 = (total4 * 100) / total;

            if (percentage4 == 100)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "********************" << endl;
            else if (percentage4 >= 90 && percentage4 < 100)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "******************" << endl;
            else if (percentage4 >= 80 && percentage4 < 90)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "****************" << endl;
            else if (percentage4 >= 70 && percentage4 < 80)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "**************" << endl;
            else if (percentage4 >= 60 && percentage4 < 70)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "************" << endl;
            else if (percentage4 >= 50 && percentage4 < 60)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "**********" << endl;
            else if (percentage4 >= 40 && percentage4 < 50)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "********" << endl;
            else if (percentage4 >= 30 && percentage4 < 40)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "******" << endl;
            else if (percentage4 >= 20 && percentage4 < 30)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "****" << endl;
            else if (percentage4 >= 10 && percentage4 < 20)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%" << endl;


            int qstate6 = mysql_query(conn, "select * from room where room_status = 'IN'");
            res = mysql_store_result(conn);
            int total6 = mysql_num_rows(res);
            int percentage6 = (total6 * 100) / total;

            if (percentage6 == 100)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "********************" << endl;
            else if (percentage6 >= 90 && percentage6 < 100)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "******************" << endl;
            else if (percentage6 >= 80 && percentage6 < 90)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "****************" << endl;
            else if (percentage6 >= 70 && percentage6 < 80)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "**************" << endl;
            else if (percentage6 >= 60 && percentage6 < 70)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "************" << endl;
            else if (percentage6 >= 50 && percentage6 < 60)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "**********" << endl;
            else if (percentage6 >= 40 && percentage6 < 50)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "********" << endl;
            else if (percentage6 >= 30 && percentage6 < 40)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "******" << endl;
            else if (percentage6 >= 20 && percentage6 < 30)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "****" << endl;
            else if (percentage6 >= 10 && percentage6 < 20)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%" << endl;

            int qstate7 = mysql_query(conn, "select * from room where room_status = 'OUT'");
            res = mysql_store_result(conn);
            int total7 = mysql_num_rows(res);
            int percentage7 = (total7 * 100) / total;

            if (percentage7 == 100)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "********************" << endl;
            else if (percentage7 >= 90 && percentage7 < 100)
                cout << "\t\t\t\t56) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "******************" << endl;
            else if (percentage7 >= 80 && percentage7 < 90)
                cout << "\t\t\t\t56) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "****************" << endl;
            else if (percentage7 >= 70 && percentage7 < 80)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "**************" << endl;
            else if (percentage7 >= 60 && percentage7 < 70)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "************" << endl;
            else if (percentage7 >= 50 && percentage7 < 60)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "**********" << endl;
            else if (percentage7 >= 40 && percentage7 < 50)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "********" << endl;
            else if (percentage7 >= 30 && percentage7 < 40)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "******" << endl;
            else if (percentage7 >= 20 && percentage7 < 30)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "****" << endl;
            else if (percentage7 >= 10 && percentage7 < 20)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%" << endl;
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        goto ExitMenu;
        break;
    case 2:
        system("cls");
        header();
        cout << "\n\t\t\t\t______________________ LEVEL 1 ____________________\n\n" << endl;

        qstate = mysql_query(conn, "select * from room where room_id like '1%'");
        if (!qstate)
        {
            ress = mysql_store_result(conn);
            printf("\t\t-----------------------------------------------------------------------------------------\n");
            printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", "Room No", "Type", "Capacity", "Aircond", "TV", "Wifi", "Price", "Status");
            printf("\t\t-----------------------------------------------------------------------------------------\n");
            while ((row = mysql_fetch_row(ress)))
            {
                printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
            }
            printf("\t\t-----------------------------------------------------------------------------------------\n");
            int total = mysql_num_rows(ress);
            cout << "\n\t\t\t\t\tTOTAL NUMBER OF RECORDS MADE SO FAR : " << total << endl << endl;

            cout << "\n\t\t\t\t______________________ SHOW REPORT ____________________\n\n" << endl;
            printf("\t\t\t\t-------------------------------------------------------\n");
            printf("\t\t\t\t| %-15s | %-15s | %-15s |\n", "Status", "Total", "Percentage");
            printf("\t\t\t\t-------------------------------------------------------\n");

            int qstate2 = mysql_query(conn, "select * from room where room_id like '1%' and room_status = 'A'");
            res = mysql_store_result(conn);
            int total2 = mysql_num_rows(res);
            int percentage2 = (total2 * 100) / total;

            if (percentage2 == 100)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "********************" << endl;
            else if (percentage2 >= 90 && percentage2 < 100)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "******************" << endl;
            else if (percentage2 >= 80 && percentage2 < 90)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "****************" << endl;
            else if (percentage2 >= 70 && percentage2 < 80)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "**************" << endl;
            else if (percentage2 >= 60 && percentage2 < 70)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "************" << endl;
            else if (percentage2 >= 50 && percentage2 < 60)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "**********" << endl;
            else if (percentage2 >= 40 && percentage2 < 50)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "********" << endl;
            else if (percentage2 >= 30 && percentage2 < 40)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "******" << endl;
            else if (percentage2 >= 20 && percentage2 < 30)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "****" << endl;
            else if (percentage2 >= 10 && percentage2 < 20)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%" << endl;

            int qstate3 = mysql_query(conn, "select * from room where room_id like '1%' and room_status = 'NA'");
            res = mysql_store_result(conn);
            int total3 = mysql_num_rows(res);
            int percentage3 = (total3 * 100) / total;

                if (percentage3 == 100)
                    cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "********************" << endl;
                else if (percentage3 >= 90 && percentage3 < 100)
                    cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "******************" << endl;
                else if (percentage3 >= 80 && percentage3 < 90)
                    cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "****************" << endl;
                else if (percentage3 >= 70 && percentage3 < 80)
                    cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "**************" << endl;
                else if (percentage3 >= 60 && percentage3 < 70)
                    cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "************" << endl;
                else if (percentage3 >= 50 && percentage3 < 60)
                    cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "**********" << endl;
                else if (percentage3 >= 40 && percentage3 < 50)
                    cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "********" << endl;
                else if (percentage3 >= 30 && percentage3 < 40)
                    cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "******" << endl;
                else if (percentage3 >= 20 && percentage3 < 30)
                    cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "****" << endl;
                else if (percentage3 >= 10 && percentage3 < 20)
                    cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "**" << endl;
                else
                    cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%" << endl;

            int qstate4 = mysql_query(conn, "select * from room where room_id like '1%' and room_status = 'BOOKED'");
            res = mysql_store_result(conn);
            int total4 = mysql_num_rows(res);
            int percentage4 = (total4 * 100) / total;

            if (percentage4 == 100)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "********************" << endl;
            else if (percentage4 >= 90 && percentage4 < 100)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "******************" << endl;
            else if (percentage4 >= 80 && percentage4 < 90)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "****************" << endl;
            else if (percentage4 >= 70 && percentage4 < 80)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "**************" << endl;
            else if (percentage4 >= 60 && percentage4 < 70)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "************" << endl;
            else if (percentage4 >= 50 && percentage4 < 60)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "**********" << endl;
            else if (percentage4 >= 40 && percentage4 < 50)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "********" << endl;
            else if (percentage4 >= 30 && percentage4 < 40)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "******" << endl;
            else if (percentage4 >= 20 && percentage4 < 30)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "****" << endl;
            else if (percentage4 >= 10 && percentage4 < 20)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%" << endl;


            int qstate6 = mysql_query(conn, "select * from room where room_id like '1%' and room_status = 'IN'");
            res = mysql_store_result(conn);
            int total6 = mysql_num_rows(res);
            int percentage6 = (total6 * 100) / total;

            if (percentage6 == 100)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "********************" << endl;
            else if (percentage6 >= 90 && percentage6 < 100)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "******************" << endl;
            else if (percentage6 >= 80 && percentage6 < 90)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "****************" << endl;
            else if (percentage6 >= 70 && percentage6 < 80)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "**************" << endl;
            else if (percentage6 >= 60 && percentage6 < 70)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "************" << endl;
            else if (percentage6 >= 50 && percentage6 < 60)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "**********" << endl;
            else if (percentage6 >= 40 && percentage6 < 50)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "********" << endl;
            else if (percentage6 >= 30 && percentage6 < 40)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "******" << endl;
            else if (percentage6 >= 20 && percentage6 < 30)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "****" << endl;
            else if (percentage6 >= 10 && percentage6 < 20)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%" << endl;

            int qstate7 = mysql_query(conn, "select * from room where room_id like '1%' and room_status = 'OUT'");
            res = mysql_store_result(conn);
            int total7 = mysql_num_rows(res);
            int percentage7 = (total7 * 100) / total;

            if (percentage7 == 100)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "********************" << endl;
            else if (percentage7 >= 90 && percentage7 < 100)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "******************" << endl;
            else if (percentage7 >= 80 && percentage7 < 90)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "****************" << endl;
            else if (percentage7 >= 70 && percentage7 < 80)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "**************" << endl;
            else if (percentage7 >= 60 && percentage7 < 70)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "************" << endl;
            else if (percentage7 >= 50 && percentage7 < 60)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "**********" << endl;
            else if (percentage7 >= 40 && percentage7 < 50)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "********" << endl;
            else if (percentage7 >= 30 && percentage7 < 40)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "******" << endl;
            else if (percentage7 >= 20 && percentage7 < 30)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "****" << endl;
            else if (percentage7 >= 10 && percentage7 < 20)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%" << endl;

        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        goto ExitMenu;
        break;
    case 3:
        system("cls");
        header();
        cout << "\n\t\t\t\t______________________ LEVEL 2 ____________________\n\n" << endl;

        qstate = mysql_query(conn, "select * from room where room_id like '2%'");
        if (!qstate)
        {
            ress = mysql_store_result(conn);
            printf("\t\t-----------------------------------------------------------------------------------------\n");
            printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", "Room No", "Type", "Capacity", "Aircond", "TV", "Wifi", "Price", "Status");
            printf("\t\t-----------------------------------------------------------------------------------------\n");
            while ((row = mysql_fetch_row(ress)))
            {
                printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
            }
            printf("\t\t-----------------------------------------------------------------------------------------\n");
            int total = mysql_num_rows(ress);
            cout << "\n\t\t\t\t\tTOTAL NUMBER OF RECORDS MADE SO FAR : " << total << endl << endl;

            cout << "\n\t\t\t\t______________________ SHOW REPORT ____________________\n\n" << endl;
            printf("\t\t\t\t-------------------------------------------------------\n");
            printf("\t\t\t\t| %-15s | %-15s | %-15s |\n", "Status", "Total", "Percentage");
            printf("\t\t\t\t-------------------------------------------------------\n");

            int qstate2 = mysql_query(conn, "select * from room where room_id like '2%' and room_status = 'A'");
            res = mysql_store_result(conn);
            int total2 = mysql_num_rows(res);
            int percentage2 = (total2 * 100) / total;

            if (percentage2 == 100)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "********************" << endl;
            else if (percentage2 >= 90 && percentage2 < 100)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "******************" << endl;
            else if (percentage2 >= 80 && percentage2 < 90)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "****************" << endl;
            else if (percentage2 >= 70 && percentage2 < 80)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "**************" << endl;
            else if (percentage2 >= 60 && percentage2 < 70)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "************" << endl;
            else if (percentage2 >= 50 && percentage2 < 60)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "**********" << endl;
            else if (percentage2 >= 40 && percentage2 < 50)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "********" << endl;
            else if (percentage2 >= 30 && percentage2 < 40)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "******" << endl;
            else if (percentage2 >= 20 && percentage2 < 30)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "****" << endl;
            else if (percentage2 >= 10 && percentage2 < 20)
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%\t\t" << "" << endl;
            
            //cout << "\t\t\t\t1) AVAILABLE\t\t" << total2 << "\t\t" << percentage2 << "%" << endl;

            int qstate3 = mysql_query(conn, "select * from room where room_id like '2%' and room_status = 'NA'");
            res = mysql_store_result(conn);
            int total3 = mysql_num_rows(res);
            int percentage3 = (total3 * 100) / total;

            if (percentage3 == 100)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "********************" << endl;
            else if (percentage3 >= 90 && percentage3 < 100)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "******************" << endl;
            else if (percentage3 >= 80 && percentage3 < 90)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "****************" << endl;
            else if (percentage3 >= 70 && percentage3 < 80)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "**************" << endl;
            else if (percentage3 >= 60 && percentage3 < 70)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "************" << endl;
            else if (percentage3 >= 50 && percentage3 < 60)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "**********" << endl;
            else if (percentage3 >= 40 && percentage3 < 50)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "********" << endl;
            else if (percentage3 >= 30 && percentage3 < 40)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "******" << endl;
            else if (percentage3 >= 20 && percentage3 < 30)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "****" << endl;
            else if (percentage3 >= 10 && percentage3 < 20)
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << percentage3 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t2) NOT AVAILABLE\t" << total3 << "\t\t" << (total3 * 100) / total << "%" << endl;

            int qstate4 = mysql_query(conn, "select * from room where room_id like '2%' and room_status = 'BOOKED'");
            res = mysql_store_result(conn);
            int total4 = mysql_num_rows(res);
            int percentage4 = (total4 * 100) / total;

            if (percentage4 == 100)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "********************" << endl;
            else if (percentage4 >= 90 && percentage4 < 100)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "******************" << endl;
            else if (percentage4 >= 80 && percentage4 < 90)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "****************" << endl;
            else if (percentage4 >= 70 && percentage4 < 80)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "**************" << endl;
            else if (percentage4 >= 60 && percentage4 < 70)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "************" << endl;
            else if (percentage4 >= 50 && percentage4 < 60)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "**********" << endl;
            else if (percentage4 >= 40 && percentage4 < 50)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "********" << endl;
            else if (percentage4 >= 30 && percentage4 < 40)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "******" << endl;
            else if (percentage4 >= 20 && percentage4 < 30)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "****" << endl;
            else if (percentage4 >= 10 && percentage4 < 20)
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t3) BOOKED\t\t" << total4 << "\t\t" << percentage4 << "%" << endl;


            int qstate6 = mysql_query(conn, "select * from room where room_id like '2%' and room_status = 'IN'");
            res = mysql_store_result(conn);
            int total6 = mysql_num_rows(res);
            int percentage6 = (total6 * 100) / total;

            if (percentage6 == 100)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "********************" << endl;
            else if (percentage6 >= 90 && percentage6 < 100)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "******************" << endl;
            else if (percentage6 >= 80 && percentage6 < 90)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "****************" << endl;
            else if (percentage6 >= 70 && percentage6 < 80)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "**************" << endl;
            else if (percentage6 >= 60 && percentage6 < 70)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "************" << endl;
            else if (percentage6 >= 50 && percentage6 < 60)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "**********" << endl;
            else if (percentage6 >= 40 && percentage6 < 50)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "********" << endl;
            else if (percentage6 >= 30 && percentage6 < 40)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "******" << endl;
            else if (percentage6 >= 20 && percentage6 < 30)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "****" << endl;
            else if (percentage6 >= 10 && percentage6 < 20)
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t4) CHECKED IN\t\t" << total6 << "\t\t" << percentage6 << "%" << endl;

            int qstate7 = mysql_query(conn, "select * from room where room_id like '2%' and room_status = 'OUT'");
            res = mysql_store_result(conn);
            int total7 = mysql_num_rows(res);
            int percentage7 = (total7 * 100) / total;

            if (percentage7 == 100)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "********************" << endl;
            else if (percentage7 >= 90 && percentage7 < 100)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "******************" << endl;
            else if (percentage7 >= 80 && percentage7 < 90)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "****************" << endl;
            else if (percentage7 >= 70 && percentage7 < 80)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "**************" << endl;
            else if (percentage7 >= 60 && percentage7 < 70)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "************" << endl;
            else if (percentage7 >= 50 && percentage7 < 60)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "**********" << endl;
            else if (percentage7 >= 40 && percentage7 < 50)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "********" << endl;
            else if (percentage7 >= 30 && percentage7 < 40)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "******" << endl;
            else if (percentage7 >= 20 && percentage7 < 30)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "****" << endl;
            else if (percentage7 >= 10 && percentage7 < 20)
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "**" << endl;
            else
                cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%\t\t" << "" << endl;

            //cout << "\t\t\t\t5) CHECKED OUT\t\t" << total7 << "\t\t" << percentage7 << "%" << endl;

        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        goto ExitMenu;
        break;
    case 4:
        system("cls");
        manageRoom();
        break;
    default:
        cout << "\nPlease Enter a valid input" << endl;
        system("pause");
        showRoom();
    }

ExitMenu:
    cout << "\nPress 'm' for Menu or any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        showRoom();
    }
    else
    {
        exit(0);
    }
}

//Function for admin to search room
void searchRoom() {

    system("cls");

    string input = "";
    char choose;

    header();
    cout << "\n\t\t\t\t______________________ SEARCH ROOM ____________________\n\n" << endl;
    cin.ignore(1, '\n');
    cout << "\t\t\t\t\t\tEnter Room No: ";
    getline(cin, input);
    string findbyname_query = "select * from room where room_id like '%" + input + "%'";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("\t\t-----------------------------------------------------------------------------------------\n");
        printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", "Room No", "Type", "Capacity", "Aircond", "TV", "Wifi", "Price", "Status");
        printf("\t\t-----------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
        }
        printf("\t\t-----------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

ExitMenu:
    cout << "\n\nPress 'm' for Menu, 'a' to Search again or any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        manageRoom();
    }
    else if (choose == 'a' || choose == 'A')
    {
        searchRoom();
    }
    else
    {
        exit(0);
    }
}

//Function for admin to update room details
void updateRoom() {
    system("cls");

    // Variables
    string room_type = "";
    string room_capacity = "";
    string room_aircond = "";
    string room_tv = "";
    string room_wifi = "";
    string room_price = "";
    string room_status = "";
    string rooms[5000];
    char choose;
    int roomId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    // Store Variables
    string storeid = "";
    string storetype = "";
    string storecapacity = "";
    string storeaircond = "";
    string storetv = "";
    string storewifi = "";
    string storeprice = "";
    string storestatus = "";

    header();
    qstate = mysql_query(conn, "select * from room");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("\t\t-----------------------------------------------------------------------------------------\n");
        printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", "Room No", "Type", "Capacity", "Aircond", "TV", "Wifi", "Price", "Status");
        printf("\t\t-----------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
            rooms[indexForId] = row[0];
            indexForId++;
        }
        printf("\t\t-----------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        system("pause");
        system("cls");
        header();
        cout << "\n\t\t\t\t______________________ UPDATE ROOM ____________________\n\n" << endl;
        cout << "\n\t\t\t\t\t\tEnter Room No: ";
        cin >> roomId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << roomId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != rooms[i])
            {
                NotInDatabase = true;
            }
            else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string findbyid_query = "select * from room where room_id = '" + strid + "'";
            const char* qi = findbyid_query.c_str();
            qstate = mysql_query(conn, qi);

            if (!qstate)
            {
                res = mysql_store_result(conn);
                printf("\t\t-----------------------------------------------------------------------------------------\n");
                printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", "Room No", "Type", "Capacity", "Aircond", "TV", "Wifi", "Price", "Status");
                printf("\t\t-----------------------------------------------------------------------------------------\n");
                while (row = mysql_fetch_row(res))
                {
                    printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);

                    storeid = row[0];
                    storetype = row[1];
                    storecapacity = row[2];
                    storeaircond = row[3];
                    storetv = row[4];
                    storewifi = row[5];
                    storeprice = row[6];
                    storestatus = row[7];

                }
                printf("\t\t-----------------------------------------------------------------------------------------\n");
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }

            cin.ignore(1, '\n');
            string defaultString = "x";
            string defaultString2 = "X";
            cout << "\n\t\t\t\tEnter Type (" << defaultString << "  to not change) (S/N): ";
            getline(cin, room_type);
            if (room_type == defaultString || room_type == defaultString2)
            {
                room_type = storetype;
            }
            cout << "\t\t\t\tEnter Capacity (" << defaultString << "  to not change): ";
            getline(cin, room_capacity);
            if (room_capacity == defaultString || room_capacity == defaultString2)
            {
                room_capacity = storecapacity;
            }
            cout << "\t\t\t\tEnter Aircond (" << defaultString << "  to not change) (Y/N): ";
            getline(cin, room_aircond);
            if (room_aircond == defaultString || room_aircond == defaultString2)
            {
                room_aircond = storeaircond;
            }
            cout << "\t\t\t\tEnter TV (" << defaultString << "  to not change) (Y/N): ";
            getline(cin, room_tv);
            if (room_tv == defaultString || room_tv == defaultString2)
            {
                room_tv = storetv;
            }
            cout << "\t\t\t\tEnter Wifi (" << defaultString << "  to not change) (Y/N): ";
            getline(cin, room_wifi);
            if (room_wifi == defaultString || room_wifi == defaultString2)
            {
                room_wifi = storewifi;
            }
            cout << "\t\t\t\tEnter Price (" << defaultString << "  to not change) (RM): ";
            getline(cin, room_price);
            if (room_price == defaultString || room_price == defaultString2)
            {
                room_price = storeprice;
            }
            cout << "\t\t\t\tEnter Status (" << defaultString << "  to not change) (A/NA): ";
            getline(cin, room_status);
            if (room_status == defaultString || room_status == defaultString2)
            {
                room_status = storestatus;
            }

            string update_query = "update room set room_type = '" + room_type + "', room_capacity = '" + room_capacity + "', room_aircond = '" + room_aircond + "', room_tv = '" + room_tv + "', room_wifi = '" + room_wifi + "', room_price = '" + room_price + "', room_status = '" + room_status + "' where room_id = '" + strid + "'";
            const char* qu = update_query.c_str();
            qstate = mysql_query(conn, qu);

            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

ExitMenu:
    cout << "Press 'm' for Menu, 'e' to edit another item or any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        manageRoom();
    }
    else if (choose == 'e' || choose == 'E')
    {
        updateRoom();
    }
    else
    {
        exit(0);
    }
}

//Function for admi to delete room
void deleteRoom() {
    system("cls");

    // Variables
    char choose;
    int roomId;
    string rooms[5000];
    int indexForId = 0;
    bool HaveException = false, NotInDatabase = false;

    header();
    qstate = mysql_query(conn, "select * from room");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        cout << "\n\t\t\t\t______________________ DELETE ROOM ____________________\n\n" << endl;
        printf("\t\t-----------------------------------------------------------------------------------------\n");
        printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", "Room No", "Type", "Capacity", "Aircond", "TV", "Wifi", "Price", "Status");
        printf("\t\t-----------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
            rooms[indexForId] = row[0];
            indexForId++;
        }
        printf("\t\t-----------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "\t\t\t\t\t\tEnter Room No: ";
        cin >> roomId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << roomId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != rooms[i])
            {
                NotInDatabase = true;
            }
            else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string delete_query = "delete from room where room_id = '" + strid + "'";
            const char* qd = delete_query.c_str();
            qstate = mysql_query(conn, qd);

            if (!qstate)
            {
                cout << "Successfully Deleted." << endl;
            }
            else
            {
                cout << "Failed To Delete!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

ExitMenu:
    cout << "Press 'm' to Menu, 'd' to delete another item and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        manageRoom();
    }
    else if (choose == 'd' || choose == 'D')
    {
        deleteRoom();
    }
    else
    {
        exit(0);
    }
}

//Function for admin to manage customer
void manageCustomer()
{
    system("cls");

    int choice;

    header();
    cout << "\t\t\t\t______________________ MANAGE CUSTOMER ____________________\n" << endl;
    cout << "\t\t\t\t\t\t1.Show all customer" << endl;
    cout << "\t\t\t\t\t\t2.Search customer" << endl;
    cout << "\t\t\t\t\t\t3.Back" << endl;
    cout << "\n\t\t\t\t\t\tEnter your choice :";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        showCustomer();
        break;
    case 2:
        searchCustomer();
        break;
    case 3:
        system("cls");
        adminMenu();
        break;
    default:
        cout << "Please Enter a valid input" << endl;
        break;
    }
}

//Function for admin to view customer details
void showCustomer() {
    system("cls");

    char choose;
    string input;

    header();
    qstate = mysql_query(conn, "select * from customer");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("\t\t\t-------------------------------------------------------------------------\n");
        printf("\t\t\t| %-5s | %-20s | %-15s | %-20s |\n", "Id", "Name", "Phone", "Address");
        printf("\t\t\t-------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("\t\t\t| %-5s | %-20s | %-15s | %-20s |\n", row[0], row[1], row[2], row[3]);
        }
        printf("\t\t\t-------------------------------------------------------------------------\n");

        cout << "\n\t\t\t\t\tTOTAL NUMBER OF RECORDS SO FAR : " << mysql_num_rows(res) << endl << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

ExitMenu:
    cout << "Press 'm' to Menu any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        manageCustomer();
    }
    else
    {
        exit(0);
    }
}

//Function for admin to serach customer
void searchCustomer() {

    system("cls");

    string input = "";
    char choose;

    header();
    cin.ignore(1, '\n');
    cout << "\t\t\t\t\t\tEnter Customer Name: ";
    getline(cin, input);
    string findbyname_query = "select * from customer where cust_name like '%" + input + "%'";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("\t\t\t-------------------------------------------------------------------------\n");
        printf("\t\t\t| %-5s | %-20s | %-15s | %-20s |\n", "Id", "Name", "Phone", "Address");
        printf("\t\t\t-------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("\t\t\t| %-5s | %-20s | %-15s | %-20s |\n", row[0], row[1], row[2], row[3]);
        }
        printf("\t\t\t-------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

ExitMenu:
    cout << "\n\nPress 'm' to Menu, 'a' to Search again and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        manageCustomer();
    }
    else if (choose == 'a' || choose == 'A')
    {
        searchCustomer();
    }
    else
    {
        exit(0);
    }
}

//Function for admin to manage reservation
void manageReservation()
{
    system("cls");

    int choice;

    header();
    cout << "\t\t\t\t______________________ MANAGE RESERVATION ____________________\n" << endl;
    cout << "\t\t\t\t\t\t1.Show all reservation" << endl;
    cout << "\t\t\t\t\t\t2.Search reservation" << endl;
    cout << "\t\t\t\t\t\t3.Back" << endl;
    cout << "\n\t\t\t\t\t\tEnter your choice :";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        showReservation();
        break;
    case 2:
        searchReservation();
        break;
    case 3:
        system("cls");
        adminMenu();
        break;
    default:
        cout << "Please Enter a valid input" << endl;
        break;
    }
}

//Function for admin to view reservation details
void showReservation() {
    system("cls");

    char choose;
    string input;

    header();
    qstate = mysql_query(conn, "select * from reservation");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("\t---------------------------------------------------------------------------------------------------------\n");
        printf("\t| %-5s | %-10s | %-10s | %-10s | %-10s | %-10s | %-10s | %-15s |\n", "Id", "Room No", "Cust No", "Checkin", "Checkout", "Total", "Deposit", "Status");
        printf("\t---------------------------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("\t| %-5s | %-10s | %-10s | %-10s | %-10s | %-10s | %-10s | %-15s |\n", row[0], row[6], row[7], row[2], row[3], row[4], row[5], row[8]);
        }
        printf("\t---------------------------------------------------------------------------------------------------------\n");

        cout << "\n\t\t\t\t\tTOTAL NUMBER OF RECORDS SO FAR : " << mysql_num_rows(res) << endl << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

ExitMenu:
    cout << "Press 'm' to Menu any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        manageReservation();
    }
    else
    {
        exit(0);
    }
}

//Function for admin to serach reservation
void searchReservation() {

    system("cls");

    string input = "";
    char choose;

    header();
    cin.ignore(1, '\n');
    cout << "\t\t\t\t\t\tEnter Room No: ";
    getline(cin, input);
    string findbyname_query = "select * from reservation where room_id like '%" + input + "%'";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("\t---------------------------------------------------------------------------------------------------------\n");
        printf("\t| %-5s | %-10s | %-10s | %-10s | %-10s | %-10s | %-10s | %-15s |\n", "Id", "Room No", "Cust No", "Checkin", "Checkout", "Total", "Deposit", "Status");
        printf("\t---------------------------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("\t| %-5s | %-10s | %-10s | %-10s | %-10s | %-10s | %-10s | %-15s |\n", row[0], row[6], row[7], row[2], row[3], row[4], row[5], row[8]);
        }
        printf("\t---------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

ExitMenu:
    cout << "\n\nPress 'm' to Menu, 'a' to Search again and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        manageReservation();
    }
    else if (choose == 'a' || choose == 'A')
    {
        searchReservation();
    }
    else
    {
        exit(0);
    }
}

//Function for admin to manage checkin process
int checkin(MYSQL* conn)
{
    system("cls");
    header();
    cout << "\t\t\t\t______________________ CHECK IN ____________________\n" << endl;

    // Variables
    string room_id = "";
    char choose;

    int qstate = 0, qstate2 = 0;
    stringstream ss, ss2;

    cout << "\t\t\t\t\tDo you wish to continue? Press(Y/N) : ";
    cin >> choose;
    cout << endl;

    if (choose == 'Y' || choose == 'y')
    {
        cin.ignore(1, '\n');
        cout << "\t\t\t\t\t\tEnter Room No: ";
        getline(cin, room_id);

        ss << "UPDATE reservation SET status = 'CHECKED IN' WHERE room_id = " << room_id << "";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (qstate == 0)
        {
            cout << "Checkin Confirmed..." << endl;
        }
        else cout << "Error! Error is : " << mysql_error(conn) << endl;

        ss2 << "UPDATE room SET room_status = 'IN' WHERE room_id = " << room_id << "";
        string query2 = ss2.str();
        const char* q2 = query2.c_str();
        qstate2 = mysql_query(conn, q2);
        if (qstate2 == 0)
        {
            system("pause");
            adminMenu();
        }
        else cout << "Error! Error is : " << mysql_error(conn) << endl;

    }
    else
    {
        adminMenu();
    }

    return 0;
}

//Function for admin to manage checkout process
int checkout(MYSQL* conn)
{
    system("cls");
    header();
    cout << "\t\t\t\t______________________ CHECK OUT ____________________\n" << endl;

    // Variables
    string room_id = "";
    char choose;

    int qstate = 0, qstate2 = 0;
    stringstream ss, ss2;

    cout << "\t\t\t\t\tDo you wish to continue? Press (Y/N) : ";
    cin >> choose;
    cout << endl;

    if (choose == 'Y' || choose == 'y')
    {
        cin.ignore(1, '\n');
        cout << "\t\t\t\t\t\tEnter Room No: ";
        getline(cin, room_id);

        ss << "UPDATE reservation SET status = 'CHECKED OUT' WHERE room_id = " << room_id << "";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (qstate == 0)
        {
            cout << "Checkout Confirmed..." << endl;
        }
        else cout << "Error! Error is : " << mysql_error(conn) << endl;

        ss2 << "UPDATE room SET room_status = 'OUT' WHERE room_id = " << room_id << "";
        string query2 = ss2.str();
        const char* q2 = query2.c_str();
        qstate2 = mysql_query(conn, q2);
        if (qstate2 == 0)
        {
            system("pause");
            adminMenu();
        }
        else cout << "Error! Error is : " << mysql_error(conn) << endl;

    }
    else
    {
        adminMenu();
    }

    return 0;
}


//CUSTOMER

//Function to register an account
void customerRegister(MYSQL* conn)
{
    system("cls");

    string cust_name, cust_address;
    string cust_email, cust_pass;
    char cust_phone[20];

    header();
    cout << "\t\t\t\t______________________ REGISTER ____________________\n" << endl;
    cout << "\nEnter Your Name: ";
    cin.ignore();
    getline(cin, cust_name);


    int phonelength = 0;
    while (phonelength == 0)
    {
        cout << "\nEnter Mobile Number: " << endl;
        cin.ignore();
        cin >> cust_phone;
        phonelength = strlen(cust_phone);
        if (phonelength != 10)
        {
            cout << "Invalid Format (10 digit)" << endl;
            phonelength = 0;
        }

    }


    cout << "\nEnter Address:  ";
    cin.ignore();
    getline(cin, cust_address);


    int flag_email = 0;

    while (flag_email == 0)
    {
        cout << "\nEnter Email Address: ";
        getline(cin, cust_email);
        size_t at = cust_email.find('@');//Finds '@' Symbol and if not found returns -1
        size_t dot = cust_email.find('.', at + 1);//Checks '.' present after '@' symbol
        if ((at == string::npos) || (dot == string::npos))//string::npos means -1
        {
            cout << "Missing @ symbol or email should end with '.com'\n";
            
            flag_email = 0;
        }
        else
            flag_email = 1;

    }
    transform(cust_email.begin(), cust_email.end(), cust_email.begin(), ::tolower);//Function to transform the string to lowercase whatever the case input is.

    int flag_pass = 0;
    while (flag_pass == 0)
    {
        cout << "\nEnter Password:  ";
        getline(cin, cust_pass);
        int len_pass = cust_pass.size();//size of password
        flag_pass = validpass(cust_pass, len_pass);
        if (flag_pass == 0)
        {
            cout << "Invalid Input" << endl;
        }
    }

    ss << "INSERT INTO customer (cust_name, cust_phone, cust_address, cust_email, cust_pass) VALUES ('" << cust_name << "', '" << cust_phone << "', '" << cust_address << "', '" << cust_email << "', '" << cust_pass << "')";

    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0) {
        cout << "Account Created...." << endl;
        cout << ": " << id_generator(conn, cust_email) << endl;
        system("cls");
    }
    else {
        cout << "Account Not Created Error Occurred...." << endl;
        cout << mysql_error(conn) << endl;
    }
}

//Function to validate password
int validpass(string& cust_pass, int n)
{
    int c = 0, c1 = 0, c2 = 0, c3 = 0;
    string special = "!#$%&()\"*+,\'-./:;<=>?@[]\\^_`{|}~";// \' represents ' in string and \" represents "
    for (int i = 0; i < n; i++)
    {
        size_t at = special.find(cust_pass[i]);//Finds '@' Symbol and if not found returns -1
        if (at != string::npos)//string::npos means -1
            c2++;
        if (islower(cust_pass[i]))
            c++;
        else if (isdigit(cust_pass[i]))
            c1++;
        else if (isupper(cust_pass[i]))
            c3++;
    }

    if (c > 0 && c1 > 0 && c2 > 0 && c3 > 0 && n >= 8)
        return 1;
    else
    {
        if (c == 0) cout << "Password must contain at least 1 lowercase character" << endl;
        if (c1 == 0) cout << "Password must contain at least 1 digit(0 to 9)" << endl;
        if (c2 == 0) cout << "Password must contain at least 1 special character" << endl;
        if (c3 == 0) cout << "Password must contain at least 1 uppercase character" << endl;
        if (n < 8) cout << "Password must contain at least 8 characters" << endl;
        return 0;
    }
    return 0;
}


//ID Number Generator
//This Function searches database with newly created name to know the ID number as ID number is declared as an auto increment in back-end.
int id_generator(MYSQL* conn, string cust_email)
{
    ss << "SELECT cust_id,cust_email FROM customer";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0) {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) { 
            if (row[1] == cust_email)
            {
                char* ch = row[0];
                return atoi(ch);
            }
        }
    }
    return 0;
}

int customerLogin(MYSQL* conn, string cust_email, string cust_pass)
{
    ss << "SELECT cust_id,cust_email,cust_pass FROM customer";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0) {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) { 
            if ((strcmp(row[1], cust_email.c_str()) == 0) && (strcmp(row[2], cust_pass.c_str()) == 0))
            {
                flag = 1;
                cout << "\nLogin Successful..." << endl;
                char* ch = row[0];
                return atoi(ch);
            }
        }
        if (flag == 0)
        {
            cout << "\nInvalid username/password...." << endl;
            return 0;
        }
    }
    else
    {
        cout << "Error Occurred: " << mysql_error(conn) << endl;
        return 0;
    }
    return 0;
}

int customerMenu()
{
    system("cls");

    int choice;
    char exitConfirmation;

    header();
    cout << "\t\t\t\t______________________ CUSTOMER MENU ____________________\n" << endl;
    cout << "\t\t\t\t\t\t1.Update profile" << endl;
    cout << "\t\t\t\t\t\t2.Make reservation" << endl;
    cout << "\t\t\t\t\t\t3.View reservation" << endl;
    cout << "\t\t\t\t\t\t4.Cancel reservation" << endl;
    cout << "\t\t\t\t\t\t5.Exit" << endl;
    cout << "\n\t\t\t\t\t\tEnter your choice :";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        if (cust_id != 0) updateProfile(conn, cust_id);
        break;
    case 2:
        if (cust_id != 0) makeReservation(conn, cust_id);
        break;
    case 3:
        if (cust_id != 0) viewReservation(conn, cust_id);
        break;
    case 4:
        if (cust_id != 0) cancelReservation(conn, cust_id);
        break;
    case 5:
    ExitProgram:
        cout << "Are you sure to close this program? (y/N): ";
        cin >> exitConfirmation;
        if (exitConfirmation == 'y' || exitConfirmation == 'Y') {
            //return 0;
        }
        else if (exitConfirmation == 'n' || exitConfirmation == 'N') {
            system("cls");
            customerMenu();
        }
        else {
            cout << "Choose only y or n" << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please Enter a valid input" << endl;
        break;
    }
    return 0;
}

//Function for customer to display profile details
void updateProfile(MYSQL* conn, int cust_id)
{
    system("cls");
    header();

    stringstream ss;
    MYSQL_ROW row;
    MYSQL_RES* res;
    int qstate;

    // Variables
    string cust_name = "";
    string cust_phone = "";
    string cust_address = "";
    string cust_email = "";
    char choose;

    // Store Variables
    string storeid = "";
    string storename = "";
    string storephone = "";
    string storeaddress = "";
    string storeemail = "";

    ss << "SELECT cust_id, cust_name, cust_phone, cust_address, cust_email FROM customer";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0) 
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) { 
            char* ch = row[0];
            if (atoi(ch) == cust_id)
            {
                cout << "\n\t\t\t\t______________________ CUSTOMER PROFILE ____________________\n" << endl;
                cout << "\t\t\t\t\t\tID: " << atoi(ch) << endl << "\t\t\t\t\t\tName: " << row[1] << endl << "\t\t\t\t\t\tPhone No: " << row[2] << endl << "\t\t\t\t\t\tAddress: " << row[3] << endl << "\t\t\t\t\t\tEmail: " << row[4] << endl << endl;
            
                storeid = row[0];
                storename = row[1];
                storephone = row[2];
                storeaddress = row[3];
                storeemail = row[4];

                cin.ignore(1, '\n');
                string defaultString = "x";
                string defaultString2 = "X";
                cout << "\t\t\t\tEnter Name (" << defaultString << "  to not change): ";
                getline(cin, cust_name);
                if (cust_name == defaultString || cust_name == defaultString2)
                {
                    cust_name = storename;
                }
                cout << "\t\t\t\tEnter Phone (" << defaultString << "  to not change): ";
                getline(cin, cust_phone);
                if (cust_phone == defaultString || cust_phone == defaultString2)
                {
                    cust_phone = storephone;
                }
                cout << "\t\t\t\tEnter Address (" << defaultString << "  to not change): ";
                getline(cin, cust_address);
                if (cust_address == defaultString || cust_address == defaultString2)
                {
                    cust_address = storeaddress;
                }
                cout << "\t\t\t\tEnter Email (" << defaultString << "  to not change): ";
                getline(cin, cust_email);
                if (cust_email == defaultString || cust_email == defaultString2)
                {
                    cust_email = storeemail;
                }

                stringstream streamid;
                string strid;
                streamid << atoi(ch);
                streamid >> strid;

                string update_query = "update customer set cust_name = '" + cust_name + "', cust_phone = '" + cust_phone + "', cust_address = '" + cust_address + "', cust_email = '" + cust_email + "' where cust_id = '" + strid + "'";
                const char* qu = update_query.c_str();
                qstate = mysql_query(conn, qu);
            }
        }
        cout << endl << "Successfully Updated." << endl;
    }
    else
    {
        cout << "Failed To Update!" << mysql_errno(conn) << endl;
    }

ExitMenu:
    cout << "Press 'm' to Menu, 'e' to edit another item and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        customerMenu();
    }
    else if (choose == 'e' || choose == 'E')
    {
        updateProfile(conn, cust_id);
    }
    else
    {
        exit(0);
    }

}

//Function for customer to make a reservation
int makeReservation(MYSQL* conn, int cust_id)
{
    system("cls");
    header();

    // Variables
    string room_id = "";
    string checkin = "";
    string checkout = "";
    string reservation_date = "";
    string bill = "";
    string deposit = "";
    int days;
    int n;
    int day1, month1, year1;//for checkin date
    int day2, month2, year2;//for checkout date
    char choose;
    
    int qstate = 0, qstate1 = 0, qstate2 = 0;
    stringstream ss, ss1, ss2;

    qstate = mysql_query(conn, "select * from room where room_status = 'A'");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        cout << "\n\t\t\t\t______________________ AVAILABLE ROOM ____________________\n" << endl;
        printf("\t\t-----------------------------------------------------------------------------------------\n");
        printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", "Room No", "Type", "Capacity", "Aircond", "TV", "Wifi", "Price", "Status");
        printf("\t\t-----------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("\t\t| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
        }
        printf("\t\t-----------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    cout << "Do you wish to continue? Press(Y/N)";
    cin >> choose;
    cout << endl;

    if (choose == 'Y' || choose == 'y')
    {
        cin.ignore(1, '\n');
        cout << "Enter Room No: ";
        getline(cin, room_id);

        ss1 << "select room_price FROM room WHERE room_id = " << room_id << "";
        string query1 = ss1.str();
        const char* q1 = query1.c_str();
        qstate1 = mysql_query(conn, q1);
        if (qstate1 == 0)
        {

            cout << "\nCheck In Date " << endl;
            cout << "Enter Date (1 - 31): "; cin >> day1;
            cout << "Enter Month (1 - 12): "; cin >> month1;
            cout << "Enter Year: "; cin >> year1;
            n = no_of_days_in_month(month1, year1);

            if (day1<1 || day1>n || month1 < 1 || month1 >12 || year1 < 1)
            {
                cout << "\nINVALID INPUT\n" << endl;
            }
            else
            {
                stringstream d, m, y;
                string d1, m1, y1;
                d << day1; d >> d1;
                m << month1; m >> m1;
                y << year1; y >> y1;
                checkin = d1 + "/" + m1 + "/" + y1;
            }

            cout << "\nCheck Out Date " << endl;
            cout << "Enter Date of month(1 - 31): "; cin >> day2;
            cout << "Enter Month: "; cin >> month2;
            cout << "Enter Year: "; cin >> year2;
            n = no_of_days_in_month(month2, year2);

            if (day2<1 || day2>n || month2 < 1 || month2 >12 || year2 < 1)
            {
                cout << "\nINVALID INPUT\n" << endl;

            }
            else
            {
                stringstream dd, mm, yy;
                string d2, m2, y2;
                dd << day2; dd >> d2;
                mm << month2; mm >> m2;
                yy << year2; yy >> y2;
                checkout = d2 + "/" + m2 + "/" + y2;
            }

            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            char* ch = row[0];
            int total = atoi(ch);
            int bill;

            // Count the difference between 2 dates in terms of no of days
            long long int diff = difference_of_days(day1, month1, year1, day2, month2, year2);
            total = total * diff;
            bill = total - (total * 0.2);

            string sbill;
            stringstream int_string;
            int_string << bill;
            int_string >> sbill;

            string scust_id;
            stringstream int_string2;
            int_string2 << cust_id;
            int_string2 >> scust_id;

            cout << "\n\nTotal price: RM" << total << endl;
            cout << "Our hotel gives you 20% promotion. Total price after promotion: RM" << bill << endl;
            cin.ignore(1, '\n');
            cout << "Enter Deposit: ";
            getline(cin, deposit);

            time_t now = time(0);
            char str[26] = {};
            ctime_s(str, 26, &now);
            string d = str;

            ss2 << "UPDATE room SET room_status = 'BOOKED' WHERE room_id = " << room_id << "";
            string query2 = ss2.str();
            const char* q2 = query2.c_str();
            qstate2 = mysql_query(conn, q2);
            if (qstate2 == 0)
            {
                cout << "Booking Confirmed..." << endl;
            }
            else cout << "Booking Not Confirmed! Error is : " << mysql_error(conn) << endl;

            ss << "insert into reservation (reservation_date, checkin, checkout, bill, deposit, room_id, cust_id) values ('" + d + "','" + checkin + "','" + checkout + "','" + sbill + "','" + deposit + "','" + room_id + "','" + scust_id + "')";
            //ss << "INSERT INTO reservation (reservation_date, checkin, checkout, bill, deposit, room_id, cust_id) VALUES ('" << d << "', '" << checkin << "', '" << checkout << "', '" << bill << "', '" << deposit << "', '" << room_id << "', '" << cust_id << "')";
            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);
            if (qstate == 0)
            {
                system("pause");
                viewReservation(conn, cust_id);
            }
            else {
                cout << "Reservation error occurred: " << mysql_error(conn);
            }
        }
    }
    else
    {
        customerMenu();
    }

    return 0;
}

//Function for customer to view reservation details 
void viewReservation(MYSQL* conn, int cust_id)
{
    system("cls");
    header();

    stringstream ss, ss2;
    MYSQL_ROW row;
    MYSQL_RES* res;
    int qstate, qstate2;

    char choose;

    ss2 << "SELECT cust_id, cust_name, cust_phone, cust_address, cust_email FROM customer";
    string query2 = ss2.str();
    const char* r = query2.c_str();
    qstate2 = mysql_query(conn, r);
    if (qstate2 == 0)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) { 
            char* ch = row[0];
            if (atoi(ch) == cust_id)
            {
                cout << "\n\t\t\t\t______________________ PROFILE DETAILS ____________________\n" << endl;
                cout << "\t\t\t\t\t\tID: " << atoi(ch) << endl;
                cout << "\t\t\t\t\t\tName: " << row[1] << endl;
                cout << "\t\t\t\t\t\tPhone No: " << row[2] << endl;
                cout << "\t\t\t\t\t\tAddress: " << row[3] << endl;
                cout << "\t\t\t\t\t\tEmail: " << row[4] << endl << endl;

            }
        }
    }
    else
    {
        cout << "Failed To Load!" << mysql_errno(conn) << endl;
    }

    ss << "SELECT cust_id, reservation_date, checkin, checkout, bill, deposit, room_id FROM reservation";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) { 
            char* ch = row[0];
            if (atoi(ch) == cust_id)
            {
                cout << "\n\t\t\t\t______________________ RESERVATION DETAILS ____________________\n" << endl;
                cout << "\t\t\t\t\t\tID: " << atoi(ch) << endl;
                cout << "\t\t\t\t\t\tRoom No: " << row[6] << endl;
                cout << "\t\t\t\t\t\tReservation Date: " << row[1] << endl;
                cout << "\t\t\t\t\t\tCheckin: " << row[2] << endl;
                cout << "\t\t\t\t\t\tCheckout: " << row[3] << endl;
                cout << "\t\t\t\t\t\tTotal: RM" << row[4] << endl;
                cout << "\t\t\t\t\t\tDeposit: RM" << row[5] << endl << endl;

            }
        }
    }
    else
    {
        cout << "Failed To Load!" << mysql_errno(conn) << endl;
    }

ExitMenu:
    cout << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        customerMenu();
    }
    else
    {
        exit(0);
    }

}

//Function for customer to cancel reservation
int cancelReservation(MYSQL* conn, int cust_id)
{
    system("cls");
    header();
    cout << "\t\t\t\t______________________ CANCEL RESERVATION ____________________\n" << endl;

    string room_id = "";
    char choose;

    int qstate = 0, qstate2 = 0;
    stringstream ss, ss2;

    cout << "\t\t\t\t\tDo you wish to cancel your reservation? Press(Y/N) : ";
    cin >> choose;
    cout << endl;

    if (choose == 'Y' || choose == 'y')
    {
        cin.ignore(1, '\n');
        cout << "\t\t\t\t\t\tEnter Room No: ";
        getline(cin, room_id);

        ss << "UPDATE reservation SET status = 'CANCELLED' WHERE room_id = " << room_id << "";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (qstate == 0)
        {
            cout << "Reservation Cancelled..." << endl;
        }
        else cout << "Error! Error is : " << mysql_error(conn) << endl;

        ss2 << "UPDATE room SET room_status = 'A' WHERE room_id = " << room_id << "";
        string query2 = ss2.str();
        const char* q2 = query2.c_str();
        qstate2 = mysql_query(conn, q2);
        if (qstate2 == 0)
        {
            cout << "Room Available..." << endl;
            system("pause");
            customerMenu();
        }
        else cout << "Room Not Available! Error is : " << mysql_error(conn) << endl;
        
    }
    else
    {
        customerMenu();
    }

    return 0;
}
