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
            string storedPassword = line.substr(commaPos + 1);

            if (storedUsername == username && storedPassword == encryptPassword(password)) {
                return true;
            }
        }
        return false;
    }

    void createUser(const string& username, const string& password) {
        ofstream file("credentials.txt", ios_base::app);
        file << username << "," << encryptPassword(password) << endl;
        cout << "User created successfully." << endl;
    }

public:
    void registerUser() {
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
	    if (username == "admin"){
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
};

int getMenuChoice() {
    int choice;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int main() {
    Account account;
    while (true) {
        system("cls");
        cout << "Login System" << endl;
        int choice = getMenuChoice();

        switch (choice) {
            case 1:
                account.registerUser();
                system("pause");
                break;

            case 2: {
                string loggedInUsername = account.loginUser();
                if (!loggedInUsername.empty()) {
                	if(loggedInUsername == "admin"){
                		cout << "Admin na dito" << endl;
					}
					else{
						cout << "Logged-in username: " << loggedInUsername << endl;
					}
                }
                system("pause");
                break;
            }

            case 3:
                cout << "Exiting..." << endl;
                system("pause");
                return 0;

            default:
                break;
        }
    }
}
