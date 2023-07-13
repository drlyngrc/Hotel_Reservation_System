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
    	getch();
    	system("cls");
    	cout << "=== Register ===" << endl;
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
    	getch();
    	system("cls");
    	cout << "=== Log In ===" << endl;
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
};

// Function to display the client menu
void displayClientMenu() {
    cout << "=== Client Menu ===" << endl;
    cout << "1. Choose a schedule" << endl;
    cout << "2. View room types and amenities" << endl;
    cout << "3. View bookings" << endl;
    cout << "4. Account settings" << endl;
    cout << "5. Log Out" << endl;
    cout << "6. Exit" << endl;
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

//Structure for Room Type
struct Room_type{
		
	void displayTopicData(const string& topic) {
	    ifstream file("roomtype.txt");
	    if (!file.is_open()) {
	        cout << "Failed to open the file." << endl;
	        return;
	    }
	    
	    bool topicFound = false;
	    string line;
	    while (getline(file, line)) {
	        if (line.find(topic) != string::npos) {
	            topicFound = true;
	            cout << line << endl;
	            while (getline(file, line) && line.substr(0, 2) != "--") {
	                cout << line << endl;
	            }
	            break;
	        }
	    }
	    
	    file.close();
	    
	    if (!topicFound) {
	        cout << "Topic not found." << endl;
	    }
	}
};

void view_room(HotelReservationSystem& sys){
    int option;
    string topic;
    
    Room_type room;
    
    while (true) {
    	getch();
    	system("cls");
        cout << "ROOM TYPE" << endl;
        cout << "1. Standard Room" << endl;
        cout << "2. Deluxe Room" << endl;
        cout << "3. Suite Room" << endl;
        cout << "4. Executive Room" << endl;
        cout << "5. Penthouse" << endl;
        cout << "6. Back" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> option;
        
        
        switch (option) {
            case 1:
                topic = "STANDARD ROOM";
                break;
            case 2:
                topic = "DELUXE ROOM";
                break;
            case 3:
                topic = "SUITE ROOM";
                break;
            case 4:
                topic = "EXECUTIVE ROOM";
                break;
            case 5:
                topic = "PENTHOUSE";
                break;
            case 6: 
            	return;
            case 0:
                exit(0);
            default:
                cout << "Invalid option." << endl;
                continue;  
        }
        
        room.displayTopicData(topic);
        
        string option1;
        cout << "[a] Back  [0] Exit: ";
        cin >> option1;
        if (option1 == "a") {
            continue;  
        } else if (option1 == "0") {
            break; 
        } else {
            cout << "Invalid option." << endl;
             
        }
    }
}


// Function to handle the main admin menu
void AdminMenu(HotelReservationSystem& sys) {

    int choice;
    do {
    	getch();
    	system("cls");
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

// Function to handle the main client menu
void ClientMenu(HotelReservationSystem& sys) {
    int choice;
    do {
    	getch();
    	system("cls");
        displayClientMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                // Your code for choosing a schedule here
                break;
            case 2:
                // Your code for viewing room types and amenities here
                view_room(sys);
                break;
            case 3:
                // Your code for viewing bookings here
                break;
            case 4:
                // Your code for account settings here
                break;
            case 5:
            	cout << "Logging out..." << endl;
            	break;
			case 6:
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}


// Function to handle the main menu
void showLoginPage(HotelReservationSystem& sys){
    Account account;
    system("cls");
    cout << "Login System" << endl;
    int choice;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

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
                    AdminMenu(sys);
                } else {
                    cout << "Logged-in username: " << loggedInUsername << endl;
                    ClientMenu(sys);
                }
            }
            system("pause");
            break;
        }

        case 3:
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
    HotelReservationSystem sys;
    //view_room(system);
	while (true){
		showLoginPage(sys);
	}

    return 0;
}
