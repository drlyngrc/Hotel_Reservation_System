#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include "Account.hpp"
#include "Main.hpp"
#include "Account_setting.hpp"
#include "Sorted_roomprice.hpp"

using namespace std;

// Function to display the admin menu
void displayAdminMenu() {
    cout << "=== Admin Menu ===" << endl;
    cout << "1. Manage reservation schedules" << endl;
    cout << "2. Client account management" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to display the client menu
void displayClientMenu() {
    cout << "=== Client Menu ===" << endl;
    cout << "1. Room Reservation" << endl;
    cout << "2. View bookings" << endl;
    cout << "3. Account settings" << endl;
    cout << "4. Log Out" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

void RoomReserve(){
	cout << "=== Room Reservation ===" << endl;
    cout << "1. Choose a schedule" << endl;
    cout << "2. View room types and amenities" << endl;
    cout << "3. Back" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

void Reservation(HotelReservationSystem& sys){
	int choice;
	do{
		system("cls");
		RoomReserve();
		cin >> choice;
		switch(choice){
			case 1:
				//choose a schedule
				break;
			case 2:
				//view room type
				char choice;
				system("cls");
				displayRoomInformation();
				cout << "[a]Back     [0]Exit: ";
				cin >> choice;
				if(choice == 'a'){
					break;
				} else if (choice == '0'){
					exit(0);
				}
				break;
			case 3:
				return;
			case 4:
				exit(0);
			default:
				cout << "Invalid choice. Please try again." << endl;
		}
	} while(choice != 4);
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
                Reservation(sys); 
                break;
            case 2:
                // Your code for viewing bookings here
                break;
            case 3:
                // Your code for account settings here
                Account_setting(sys);
                break;
            case 4:
            	cout << "Logging out..." << endl;
            	break;
			case 5:
				cout << "Exiting..." << endl;
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}

// Function to login
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
                    system("pause");
                    AdminMenu(sys);
                } else {
                    //cout << "Logged-in username: " << loggedInUsername << endl;
                    cout << "Logged in successfully." << endl;
					system("pause");
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
    
    while (true) {
        showLoginPage(sys);
    }

    return 0;
}
