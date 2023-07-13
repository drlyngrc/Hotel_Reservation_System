#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
using namespace std;

// Structure for client information
struct Client {
    string name;
    string email;
    string contactNo;
    string username;
    string password;
};

// Structure for reservation information
struct Reservation {
    int month;
    int date;
    string roomType;
    string paymentMethod;
};

// Linked list node
struct Node {
    Reservation reservation;
    Node* next;
};

class HotelReservationSystem {
private:
    Node* head;

public:
    HotelReservationSystem() {
        head = nullptr;
    }

    // Function to add a reservation to the linked list
    void addReservation(Reservation res) {
        Node* newNode = new Node;
        newNode->reservation = res;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Function to display all reservations
    void displayReservations() {
        Node* current = head;
        while (current != nullptr) {
            // Display reservation details
            cout << "Month: " << current->reservation.month << endl;
            cout << "Date: " << current->reservation.date << endl;
            cout << "Room Type: " << current->reservation.roomType << endl;
            cout << "Payment Method: " << current->reservation.paymentMethod << endl;
            cout << endl;
            
            current = current->next;
        }
    }

    // Function to delete a reservation
    void deleteReservation(Reservation res) {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->reservation.month == res.month && current->reservation.date == res.date &&
                current->reservation.roomType == res.roomType && current->reservation.paymentMethod == res.paymentMethod) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                break;
            }

            prev = current;
            current = current->next;
        }
    }
};


class Account {
private:
    string name;
    string email;
    string contactNo;
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
    	
    	cout << "Enter your name: ";
    	cin.ignore();
    	getline (cin, name);
    	cout << "Enter your email: ";
    	cin >> email;
    	cout << "Enter your contact number: ";
    	cin >> contactNo;
        cout << "Enter username: ";
        cin >> username;
        if (isUserExists(username)) {
            cout << "Username already exists." << endl;
            return;
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

// Function to display the client menu
void displayClientMenu() {
    cout << "=== Client Menu ===" << endl;
    cout << "1. Choose a schedule" << endl;
    cout << "2. View room types and amenities" << endl;
    cout << "3. View bookings" << endl;
    cout << "4. Account settings" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to display the admin menu
void displayAdminMenu() {
    cout << "=== Admin Menu ===" << endl;
    cout << "1. Manage reservation schedules" << endl;
    cout << "2. Client account management" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to handle client login
void clientLogin(HotelReservationSystem& system) {
    // Your code for client login here
}

// Function to handle client registration
void clientRegistration(HotelReservationSystem& system) {
    Account client_register;
    client_register.registerUser();
}

// Function to handle the main client menu
void handleClientMenu(HotelReservationSystem& system) {
    int choice;
    do {
        displayClientMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                // Your code for choosing a schedule here
                break;
            case 2:
                // Your code for viewing room types and amenities here
                break;
            case 3:
                // Your code for viewing bookings here
                break;
            case 4:
                // Your code for account settings here
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}

// Function to handle admin login
bool adminLogin() {
    string username, password;

    // Predefined admin credentials
    string adminUsername = "admin";
    string adminPassword = "admin123";

    while(true){
    	system("cls");
    	cout << "=== Admin Login ===" << endl;
	    cout << "Enter username: ";
	    cin >> username;
	    if (username == adminUsername){
			cout << "Password: ";
			cin >> password;
			if (password == adminPassword){
				cout << "Login successfully! \n";
				getch();
				return true;
			} else {
				cout << "Incorrect password! \n";
				getch();
			}
				
		} else {
			cout << "Incorrect username! \n";
			getch();
		}
		
	}
	
}

// Function to handle the main admin menu
void handleAdminMenu(HotelReservationSystem& system) {
    bool loggedIn = adminLogin();

    if (!loggedIn) {
        return;
    }

    int choice;
    do {
        displayAdminMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                // Your code for managing reservation schedules here
                break;
            case 2:
                // Your code for client account management here
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
}


// Function to handle the main menu
void handleMainMenu(HotelReservationSystem& system) {
    int userType;
    cout << "=== Hotel and Event Place Reservation System ===" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Client" << endl;
    cout << "Enter user type: ";
    cin >> userType;

    if (userType == 1) {
        // Handle admin login here
        handleAdminMenu(system);
    } else if (userType == 2) {
        int loginChoice;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "Enter your choice: ";
        cin >> loginChoice;

        if (loginChoice == 1) {
            // Handle client login here
            clientLogin(system);
            handleClientMenu(system);
        } else if (loginChoice == 2) {
            // Handle client registration here
            clientRegistration(system);
            handleClientMenu(system);
        } else {
            cout << "Invalid choice. Exiting..." << endl;
        }
    } else {
        cout << "Invalid user type. Exiting..." << endl;
    }
}

int main() {
    HotelReservationSystem system;
    handleMainMenu(system);

    return 0;
}
