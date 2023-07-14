#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include "Account.hpp"
#include "Main.hpp"

using namespace std;

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

// Function to handle the main admin menu
void AdminMenu(HotelReservationSystem& sys) {

    int choice;
    do {
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
                Account_setting(sys);
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
                    getch();
                    AdminMenu(sys);
                } else {
                    //cout << "Logged-in username: " << loggedInUsername << endl;
                    cout << "Logged in successfully." << endl;
					getch();
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
