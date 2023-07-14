#define ACCOUNT_SETTING_HPP

#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <sstream>

using namespace std;

int getIntInput() {
    int value;
    while (true) {
        if (cin >> value) {
            // Input is a valid integer
            break;
        } else {
            // Clear the error flag and discard the invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid input. Please enter an integer: ";
        }
    }
    return value;
}

void Account_setting(HotelReservationSystem& sys){
	Account settings;
    system("cls");
    cout << "=== Account Settings ===" << endl;
    int choice;
    cout << "1. User Info" << endl;
    cout << "2. Change Password" << endl;
    cout << "3. Update Email" << endl;
    cout << "4. Update Contact Number" << endl;
    cout << "5. Back" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
    choice = getIntInput();

	switch (choice) {
        case 1: {
            //display user info
            break;
        }

        case 2: {
            string username;
            string currentPassword;
            string newPassword;

            cout << "Enter username: ";
            cin >> username;
            cout << "Enter current password: ";
            cin >> currentPassword;

            if (!settings.isCurrentPasswordValid(username, currentPassword)) {
                cout << "Incorrect current password." << endl;
                system("pause");
                break;
            }

            cout << "Enter new password: ";
            cin >> newPassword;

           settings.changePassword(username, currentPassword, newPassword);
            system("pause");
            break;
        }

        case 3: {
            string username;
            string currentPassword;
            string newEmail;

            cout << "Enter username: ";
            cin >> username;
            cout << "Enter current password: ";
            cin >> currentPassword;

            if (!settings.isCurrentPasswordValid(username, currentPassword)) {
                cout << "Incorrect current password." << endl;
                system("pause");
                break;
            }

            cout << "Enter new email: ";
            cin >> newEmail;

            settings.updateEmail(username, currentPassword, newEmail);
            system("pause");
            break;
        }

        case 4: {
            string username;
            string currentPassword;
            string newContactNumber;

            cout << "Enter username: ";
            cin >> username;
            cout << "Enter current password: ";
            cin >> currentPassword;

            if (!settings.isCurrentPasswordValid(username, currentPassword)) {
                cout << "Incorrect current password." << endl;
                system("pause");
                break;
            }

            cout << "Enter new contact number: ";
            cin >> newContactNumber;

            settings.updateContactNumber(username, currentPassword, newContactNumber);
            system("pause");
            break;
        }

        case 5:
            return;
        
        case 0:
        	exit(0);

        default:
            cout << endl << "Invalid Input" << endl;
            system("pause");
            break;
    }
}