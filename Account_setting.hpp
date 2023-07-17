#define ACCOUNT_SETTING_HPP

#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <sstream>

using namespace std;

void Account_setting(HotelReservationSystem& sys){
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
            Account account;
			string loggedInUser = account.loginUser();
			system("pause");
			system("cls");

			if (!loggedInUser.empty()) {
			    // User logged in successfully
			    account.printUserInfo(loggedInUser);
			}
			cout << endl;
	            	cout << "[a]Back     [b]Exit: ";
			cin >> choice;
			if(choice == 'a'){
				break;
			} else if (choice == '0'){
				exit(0);
			}
			system("pause");
            break;
        }

        case 'b': {
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

        case 'c': {
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

        case 'd': {
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

        case 'e':
            return;
        
        case'f':
        	exit(0);

        default:
            cout << endl << "Invalid Input" << endl;
            system("pause");
            break;
    }
}
