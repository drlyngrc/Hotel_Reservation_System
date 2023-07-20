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
    cout << "=== Manage Reservation Schedule === " << endl;
    cout << "[a] Display reservation/s" << endl;
    cout << "[b] Confirm reservation/s" << endl;
    cout << "[c] Back" << endl;
    cout << "Enter your choice: " << endl;
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
    cout << "[c] Show available rooms" << endl;
    cout << "[d] Back" << endl;
    cout << "[e] Exit" << endl;
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
				while(true){
					cout << "[a]Back: ";
					cin >> choice;
					if(choice == 'a'){
						break;
					} else{
						cout << "Invalid. Try again." << endl;
					}
				}
				break;
			case 'c':
				int chosenMonth, chosenFromDate;
	            cout << "Enter the month number (1-12): ";
	            cin >> chosenMonth;
	            cout << "Enter the date (1-" << calendar.getMonthDays(chosenMonth, 2024) << "): ";
	            cin >> chosenFromDate;
	            DisplayRoomAvailability(chosenMonth, chosenFromDate);
	            while(true){
	            	cout << endl;
					cout << "[a]Back: ";
					cin >> choice;
					if(choice == 'a'){
						break;
					} else{
						cout << "Invalid. Try again." << endl;
					}
				}
				system("pause");
	            break;
	        case 'd':
				return;
			case 'e':
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
            	Display_reservation();
            	break;
            case 'b':
            	confirmSelectedReservation();
            	system("pause");
            	break;
            case 'c':
                cout << "Exiting..." << endl;
          		break;
            default:
              	cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 'c');
}

void ClientMenu(HotelReservationSystem& sys, const string& loggedInUsername) {
    char choice;
    do {
        system("cls");
        //loadReservationsFromFile();
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
        //saveReservationsToFile();
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
    loadReservationsFromFile();
    while (true) {
        showLoginPage(sys);
        saveReservationsToFile();
    }
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}