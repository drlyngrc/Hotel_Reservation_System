#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <sstream>

using namespace std;

class Account {
private:
    string username;
    string password;
    string name;
    string email;
    string contactNumber;

    string encryptPassword(const string& password) {
        string encryptedPassword = password;
        // Perform a simple hash by reversing the password
        reverse(encryptedPassword.begin(), encryptedPassword.end());
        return encryptedPassword;
    }

    bool isUserExists(const string& username) {
        ifstream file("credentials.txt");
        string line;
        while (getline(file, line)) {
            if (line.substr(0, line.find(',')) == username) {
                return true;
            }
        }
        return false;
    }

    bool isLoginValid(const string& username, const string& password) {
        ifstream file("credentials.txt");
        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            string storedUsername = line.substr(0, commaPos);
            string storedPassword = line.substr(commaPos + 1, line.find(',', commaPos + 1) - commaPos - 1);

            if (storedUsername == username && storedPassword == encryptPassword(password)) {
                return true;
            }
        }
        return false;
    }

    void createUser(const string& username, const string& password) {
        ofstream file("credentials.txt", ios_base::app);
        file << username << "," << encryptPassword(password) << "," << name << "," << email << "," << contactNumber << endl;
        cout << "User created successfully." << endl;
    }

public:
    void registerUser() {
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter email: ";
        cin >> email;

        bool validContactNumber = false;
        while (!validContactNumber) {
            cout << "Enter contact number (11 digits): ";
            cin >> contactNumber;
            if (contactNumber.length() == 11) {
                bool allDigits = true;
                for (char c : contactNumber) {
                    if (!isdigit(c)) {
                        allDigits = false;
                        break;
                    }
                }
                if (allDigits) {
                    validContactNumber = true;
                }
            }
            if (!validContactNumber) {
                cout << "Invalid contact number. Please enter a valid 11-digit number." << endl;
            }
        }

        cout << "Enter username: ";
        cin >> username;

        if (isUserExists(username)) {
            cout << "Username already exists." << endl;
        } else {
            cout << "Enter password: ";
            cin >> password;
            createUser(username, password);
        }
    }

    string loginUser() {
        cout << "Enter username: ";
        cin >> username;
        if (username == "admin") {
            cout << "Enter password: ";
            cin >> password;
            if (password == "admin") {
                return "admin";
            } else {
                cout << "Invalid password." << endl;
                return "";
            }
        }
        if (!isUserExists(username)) {
            cout << "User does not exist." << endl;
            return "";
        } else {
            cout << "Enter password: ";
            cin >> password;
            if (isLoginValid(username, password)) {
                return username;
            } else {
                cout << "Invalid username or password." << endl;
                return "";
            }
        }
    }

    bool isCurrentPasswordValid(const string& username, const string& currentPassword) {
        ifstream file("credentials.txt");
        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            string storedUsername = line.substr(0, commaPos);
            string storedPassword = line.substr(commaPos + 1, line.find(',', commaPos + 1) - commaPos - 1);

            if (storedUsername == username && storedPassword == encryptPassword(currentPassword)) {
                return true;
            }
        }
        return false;
    }

    void changePassword(const string& username, const string& currentPassword, const string& newPassword) {
        if (!isCurrentPasswordValid(username, currentPassword)) {
            cout << "Incorrect current password." << endl;
            return;
        }

        // Read the credentials file
        ifstream file("credentials.txt");
        string line;
        stringstream newFileContents;

        // Process each line in the file
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            string storedUsername = line.substr(0, commaPos);
            string storedPassword = line.substr(commaPos + 1, line.find(',', commaPos + 1) - commaPos - 1);

            if (storedUsername == username && storedPassword == encryptPassword(currentPassword)) {
                // Found the line with the user's credentials and the correct current password,
                // update the password with the new password
                newFileContents << username << "," << encryptPassword(newPassword) << line.substr(commaPos) << endl;
                cout << "Password changed successfully." << endl;
            } else {
                // Keep the line unchanged
                newFileContents << line << endl;
            }
        }

        // Write the updated contents back to the file
        ofstream outFile("credentials.txt");
        outFile << newFileContents.str();
    }

    void updateEmail(const string& username, const string& currentPassword, const string& newEmail) {
        if (!isCurrentPasswordValid(username, currentPassword)) {
            cout << "Incorrect current password." << endl;
            return;
        }

        // Read the credentials file
        ifstream file("credentials.txt");
        string line;
        stringstream newFileContents;

        // Process each line in the file
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            string storedUsername = line.substr(0, commaPos);
            string storedPassword = line.substr(commaPos + 1, line.find(',', commaPos + 1) - commaPos - 1);

            if (storedUsername == username && storedPassword == encryptPassword(currentPassword)) {
                // Found the line with the user's credentials and the correct current password,
                // update the email with the new email
                newFileContents << username << "," << storedPassword << "," << name << "," << newEmail << "," << contactNumber << endl;
                cout << "Email updated successfully." << endl;
            } else {
                // Keep the line unchanged
                newFileContents << line << endl;
            }
        }

        // Write the updated contents back to the file
        ofstream outFile("credentials.txt");
        outFile << newFileContents.str();
    }

    void updateContactNumber(const string& username, const string& currentPassword, const string& newContactNumber) {
        if (!isCurrentPasswordValid(username, currentPassword)) {
            cout << "Incorrect current password." << endl;
            return;
        }

        // Read the credentials file
        ifstream file("credentials.txt");
        string line;
        stringstream newFileContents;

        // Process each line in the file
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            string storedUsername = line.substr(0, commaPos);
            string storedPassword = line.substr(commaPos + 1, line.find(',', commaPos + 1) - commaPos - 1);

            if (storedUsername == username && storedPassword == encryptPassword(currentPassword)) {
                // Found the line with the user's credentials and the correct current password,
                // update the contact number with the new contact number
                newFileContents << username << "," << storedPassword << "," << name << "," << email << "," << newContactNumber << endl;
                cout << "Contact number updated successfully." << endl;
            } else {
                // Keep the line unchanged
                newFileContents << line << endl;
            }
        }

        // Write the updated contents back to the file
        ofstream outFile("credentials.txt");
        outFile << newFileContents.str();
    }
};

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
                system("pause");
                break;
            }

            cout << "Enter new password: ";
            cin >> newPassword;

            account.changePassword(username, currentPassword, newPassword);
            system("pause");
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
                system("pause");
                break;
            }

            cout << "Enter new email: ";
            cin >> newEmail;

            account.updateEmail(username, currentPassword, newEmail);
            system("pause");
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
                system("pause");
                break;
            }

            cout << "Enter new contact number: ";
            cin >> newContactNumber;

            account.updateContactNumber(username, currentPassword, newContactNumber);
            system("pause");
            break;
        }

        case 6:
            cout << "Exiting..." << endl;
            system("pause");
            exit(0);

        default:
            cout << endl << "Invalid Input" << endl;
            system("pause");
            break;
    }
}

int main() {
    while (true) {
        showLoginPage();
    }
}
