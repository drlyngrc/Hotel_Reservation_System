#include <iostream>
#include "Account.hpp"
#include <limits>

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

void showLoginPage() {
    Account account;
    system("cls");
    cout << "Login System" << endl;
    int choice;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Change Password" << endl;
    cout << "4. Update Email" << endl;
    cout << "5. Update Contact Number" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
    choice = getIntInput();

    switch (choice) {
        case 1:
            account.registerUser();
            system("pause");
            break;

        case 2: {
            string loggedInUsername = account.loginUser();
            if (!loggedInUsername.empty()) {
                if (loggedInUsername == "admin") {
                    cout << "Admin is logged in." << endl;
                } else {
                    cout << "Logged-in username: " << loggedInUsername << endl;
                }
            }
            system("pause");
            break;
        }

        case 3: {
            string username;
            string currentPassword;
            string newPassword;

            cout << "Enter username: ";
            cin >> username;
            cout << "Enter current password: ";
            cin >> currentPassword;

            if (!account.isCurrentPasswordValid(username, currentPassword)) {
                cout << "Incorrect current password." << endl;
                break;
            }

            cout << "Enter new password: ";
            cin >> newPassword;

            account.changePassword(username, currentPassword, newPassword);
            break;
        }

        case 4: {
            string username;
            string currentPassword;
            string newEmail;

            cout << "Enter username: ";
            cin >> username;
            cout << "Enter current password: ";
            cin >> currentPassword;

            if (!account.isCurrentPasswordValid(username, currentPassword)) {
                cout << "Incorrect current password." << endl;
                break;
            }

            cout << "Enter new email: ";
            cin >> newEmail;

            account.updateEmail(username, currentPassword, newEmail);
            break;
        }

        case 5: {
            string username;
            string currentPassword;
            string newContactNumber;

            cout << "Enter username: ";
            cin >> username;
            cout << "Enter current password: ";
            cin >> currentPassword;

            if (!account.isCurrentPasswordValid(username, currentPassword)) {
                cout << "Incorrect current password." << endl;
                break;
            }

            cout << "Enter new contact number: ";
            cin >> newContactNumber;

            account.updateContactNumber(username, currentPassword, newContactNumber);
            break;
        }

        case 6:
            cout << "Exiting..." << endl;
            exit(0);

        default:
            cout << endl << "Invalid Input" << endl;
            break;
    }
}

int main() {
    while (true) {
        showLoginPage();
    }
}
