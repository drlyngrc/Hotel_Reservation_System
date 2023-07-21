#define ACCOUNT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <Windows.h>
#include <conio.h>
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
        ifstream file("credentials");
        string line;
        while (getline(file, line)) {
            if (line.substr(0, line.find(',')) == username) {
                return true;
            }
        }
        return false;
    }

    bool isLoginValid(const string& username, const string& password) {
        ifstream file("credentials");
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
        ofstream file("credentials", ios_base::app);
        file << username << "," << encryptPassword(password) << "," << name << "," << email << "," << contactNumber << endl;
        cout << "User created successfully." << endl;
    }

public:
	bool isValidEmail(const string& email) {
	    // Check for the presence of '@' symbol
	    size_t atPos = email.find('@');
	    if (atPos == string::npos)
	        return false;
	    // Check for the presence of '.' after the '@' symbol
	    size_t dotPos = email.find('.', atPos);
	    if (dotPos == string::npos)
	        return false;
	    // Check if there are at least two characters after the last dot
	    if (dotPos >= email.length() - 2)
	        return false;
	
	    return true;
	}

    void registerUser() {
    	system("pause");
    	system("cls");
    	cout << "=== Register ===" << endl;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);

        bool validEmail = false;

		while (!validEmail) {
		    cout << "Enter email: ";
		    cin >> email;
		
		    if (!isValidEmail(email)) {
		        cout << "Invalid email format. Please enter a valid email." << endl;
		    } else {
		        validEmail = true;
		    }
		}


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

        bool usernameExists = false;
		
		while (!usernameExists) {
		    cout << "Enter username: ";
		    cin >> username;
		
		    if (isUserExists(username)) {
		        cout << "Username already exists. Please try again." << endl;
		    } else if (username == "admin") {
		        cout << "'admin' is restricted as a username. Please try again." << endl;
		    } else {
		        cout << "Enter password: ";
		        cin >> password;
		        createUser(username, password);
		        usernameExists = true;
		    }
		}

    }

    string getMaskedInput() {
		const char maskChar = '*';
	    string input;
		char ch;
		    
		while ((ch = _getch()) != '\r') {
	        if (ch == '\b') {
	            if (!input.empty()) {
		            input.pop_back();
		            cout << "\b \b";
		        }
		    } else {
		        input.push_back(ch);
		        cout << maskChar;
		    }
		}    
		cout << endl;    
		return input;
	}

    string loginUser() {
    	system("cls");
    	cout << "=== Log In ===" << endl;
        cout << "Enter username: ";
        cin >> username;
        if (username == "admin") {
            cout << "Enter password: ";
            string password = getMaskedInput();
            if (password == "hrsadmin") {
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
            string password = getMaskedInput();
            if (isLoginValid(username, password)) {
                return username;
            } else {
                cout << "Invalid username or password." << endl;
                return "";
            }
        }
    }

    bool isCurrentPasswordValid(const string& username, const string& currentPassword) {
        ifstream file("credentials");
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
        ifstream file("credentials");
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
        ofstream outFile("credentials");
        outFile << newFileContents.str();
    }

    void updateEmail(const string& username, const string& currentPassword, const string& newEmail) {
        if (!isCurrentPasswordValid(username, currentPassword)) {
            cout << "Incorrect current password." << endl;
            return;
        }

        // Read the credentials file
        ifstream file("credentials");
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
        ofstream outFile("credentials");
        outFile << newFileContents.str();
    }

    void updateContactNumber(const string& username, const string& currentPassword, const string& newContactNumber) {
        if (!isCurrentPasswordValid(username, currentPassword)) {
            cout << "Incorrect current password." << endl;
            return;
        }

        // Read the credentials file
        ifstream file("credentials");
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
        ofstream outFile("credentials");
        outFile << newFileContents.str();
    }
    void printUserInfo(const string& username) {
	    ifstream file("credentials");
	    string line;
	    while (getline(file, line)) {
	        size_t commaPos = line.find(',');
	        string storedUsername = line.substr(0, commaPos);
	        if (storedUsername == username) {
	            string storedPassword = line.substr(commaPos + 1, line.find(',', commaPos + 1) - commaPos - 1);
	            string storedName = line.substr(line.find(',', commaPos + 1) + 1, line.find(',', line.find(',', commaPos + 1) + 1) - line.find(',', commaPos + 1) - 1);
	            string storedEmail = line.substr(line.find(',', line.find(',', commaPos + 1) + 1) + 1, line.find(',', line.find(',', line.find(',', commaPos + 1) + 1) + 1) - line.find(',', line.find(',', commaPos + 1) + 1) - 1);
	            string storedContactNumber = line.substr(line.find(',', line.find(',', line.find(',', commaPos + 1) + 1) + 1) + 1);
				cout << "=== User Info ===" << endl << endl;
	            cout << "Username: " << username << endl;
	            cout << "Name: " << storedName << endl;
	            cout << "Email: " << storedEmail << endl;
	            cout << "Contact Number: " << storedContactNumber << endl;
	
	            return;
	        }
	    }
	
	    cout << "User information not found." << endl;
	}

	

};

