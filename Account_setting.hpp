#define ACCOUNT_SETTING_HPP

#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <sstream>

using namespace std;

void Account_setting(HotelReservationSystem& sys, const string& loggedInUsername) {
    Account settings;
    system("cls");
    cout << "=== Account Settings ===" << endl;
    char choice;
    cout << "[a] User Info" << endl;
    cout << "[b] Change Password" << endl;
    cout << "[c] Update Email" << endl;
    cout << "[d] Update Contact Number" << endl;
    cout << "[e] Back" << endl;
    cout << "[f] Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 'a': {
            string uname = loggedInUsername;
            system("cls");

            if (!loggedInUsername.empty()) {
                // User logged in successfully
                settings.printUserInfo(uname);
            }
            cout << endl;
            cout << "[a]Back     [b]Exit: ";
            cin >> choice;
            if (choice == 'a') {
                break;
            } else if (choice == '0') {
                exit(0);
            }
            break;
        }

        case 'b': {
            string currentPassword;
            string newPassword;

            cout << "Enter current password: ";
            cin >> currentPassword;

            if (!settings.isCurrentPasswordValid(loggedInUsername, currentPassword)) {
                cout << "Incorrect current password." << endl;
                break;
            }

            cout << "Enter new password: ";
            cin >> newPassword;

            settings.changePassword(loggedInUsername, currentPassword, newPassword);
            break;
        }

        case 'c': {
            string currentPassword;
            string newEmail;

            cout << "Enter current password: ";
            cin >> currentPassword;

            if (!settings.isCurrentPasswordValid(loggedInUsername, currentPassword)) {
                cout << "Incorrect current password." << endl;
                break;
            }

            cout << "Enter new email: ";
            cin >> newEmail;

            settings.updateEmail(loggedInUsername, currentPassword, newEmail);
            break;
        }

        case 'd': {
            string currentPassword;
            string newContactNumber;

            cout << "Enter current password: ";
            cin >> currentPassword;

            if (!settings.isCurrentPasswordValid(loggedInUsername, currentPassword)) {
                cout << "Incorrect current password." << endl;
                system("pause");
                break;
            }

            cout << "Enter new contact number: ";
            cin >> newContactNumber;

            settings.updateContactNumber(loggedInUsername, currentPassword, newContactNumber);
            break;
        }

        case 'e':
            return;

        case 'f':
            exit(0);

        default:
            cout << endl << "Invalid Input" << endl;
            break;
    }
}
