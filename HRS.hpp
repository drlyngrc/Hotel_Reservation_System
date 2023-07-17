#define HRS_HPP

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
    string roomType;
    string referenceNumber;
    int month;
    int fromDate; // Changed date to fromDate to represent the start date of the reservation
    int toDate; // Added toDate to represent the end date of the reservation
    bool confirmed;
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
};
