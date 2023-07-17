#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include "Account.hpp"
#include "HRS.hpp"
#include "Account_setting.hpp"
#include "Sorted_roomprice.hpp"
#include "ReservationSystem.hpp"


using namespace std;

// Function to display the admin menu
void displayAdminMenu() {
	
    cout << "=== Admin Menu ===" << endl;
    cout << "[a] Manage reservation schedules" << endl;
    cout << "[b] Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to display the client menu
void displayClientMenu() {
    cout << "=== Client Menu ===" << endl;
    cout << "[a] Room Reservation" << endl;
    cout << "[b] Display reservation/s" << endl;
    cout << "[c] Account settings" << endl;
    cout << "[d] Log Out" << endl;
    cout << "[e] Exit" << endl;
    cout << "Enter your choice: ";
}

void RoomReserve(){
	cout << "=== Room Reservation ===" << endl;
    cout << "[a] Schedule Room Reservation" << endl;
    cout << "[b] View room types and amenities" << endl;
    cout << "[c] Back" << endl;
    cout << "[d] Exit" << endl;
    cout << "Enter your choice: ";
}

void Reservation(HotelReservationSystem& sys){
	char choice;
	do{
		system("cls");
		RoomReserve();
		cin >> choice;
		switch(choice){
			case 'a':
				sched();
				break;
			case 'b':
				char choice;
				system("cls");
				displayRoomInformation();
				cout << "[a]Back     [b]Exit: ";
				cin >> choice;
				if(choice == 'a'){
					break;
				} else if (choice == '0'){
					exit(0);
				}
				break;
			case 'c':
				return;
			case 'd':
				exit(0);
			default:
				cout << "Invalid choice. Please try again." << endl;
		}
	} while(choice != 'd');
}

// Function to handle the main admin menu
void AdminMenu(HotelReservationSystem& sys) {

    char choice;
    do {
    	system("cls");
        displayAdminMenu();
        cin >> choice;
        switch (choice) {
            case 'a':
            	char option;
            	system("cls");
                cout << "=== Manage Reservation Schedule === " << endl;
                cout << "[a] Display reservation/s" << endl;
                cout << "[b] Mark date as Unavailable" << endl;
                cout << "[c] Mark date as Available" << endl;
                cout << "[d] Back" << endl;
                cout << "Enter your choice: " << endl;
                cin >> option;
                switch(option){
                	case 'a':
                		Display_reservation();
                		break;
                	case 'b':
                		markDateUnavailableMenu();
                		break;
                	case 'c':
                		markDateAvailableMenu();
                		break;
                	case 'd':
                		cout << "Exiting..." << endl;
                		break;
                	default:
                		cout << "Invalid choice. Please try again." << endl;
				}
                break;
            case 'b':
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 'c');
}

void ClientMenu(HotelReservationSystem& sys, const string& loggedInUsername) {
    char choice;
    do {
        system("cls");
        displayClientMenu();
        cin >> choice;
        switch (choice) {
	    case 'a':
                Reservation(sys); 
                break;
            case 'b':
                Display_reservation();
                break;
            case 'c':
                Account_setting(sys, loggedInUsername);
                break;
            case 'd':
            	cout << "Logging out..." << endl;
            	break;
			case 'e':
				cout << "Exiting..." << endl;
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 'd');
}

// Function to login
void showLoginPage(HotelReservationSystem& sys){
    Account account;
    system("cls");
    cout << "Login System" << endl;
    char choice;
    cout << "[a] Register" << endl;
    cout << "[b] Login" << endl;
    cout << "[c] Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 'a':
            account.registerUser();
            system("pause");
            break;
        case 'b': {
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
                    ClientMenu(sys, loggedInUsername); // Pass loggedInUsername to ClientMenu
                }
            }
            system("pause");
            break;
        }
        case 'c':
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
