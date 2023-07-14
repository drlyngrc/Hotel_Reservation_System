#define MAIN_HPP

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
