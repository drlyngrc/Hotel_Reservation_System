#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

void confirmSelectedReservation();
void Roomreserve(int chosenMonth, int chosenFromDate, int chosenToDate);
void confirmSelectedReservation();
void cancelReservation();
void Display_reservation() ;
void sched();
void DisplayRoomAvailability(int chosenMonth, int chosenFromDate) ;


const int NUM_MONTHS = 12;
const int NUM_DAYS_PER_WEEK = 7;

class Calendar {
private:
    string monthNames[NUM_MONTHS] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    int startingDays[NUM_MONTHS] = {
        1, 4, 5, 1, 3, 6, 1, 4, 0, 2, 5, 0 // Starting days for January to December 2024
    };

public:
    Calendar() {}

    void displayMonth(int month, int year, int startingDay) const {
        string monthName = monthNames[month - 1];
        cout << endl << setw(20) << monthName << " " << year << endl;
        cout << "-----------------------------" << endl;
        cout << "Sun Mon Tue Wed Thu Fri Sat" << endl;

        int numDaysInMonth;

        if (month == 2) {
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
                numDaysInMonth = 29;
            else
                numDaysInMonth = 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            numDaysInMonth = 30;
        } else {
            numDaysInMonth = 31;
        }

        int day = 1;
        int currentDayOfWeek = startingDay;
        cout << setw(currentDayOfWeek * 4) << "";

        while (day <= numDaysInMonth) {
            cout << setw(3) << day << " ";

            day++;
            currentDayOfWeek++;

            if (currentDayOfWeek == NUM_DAYS_PER_WEEK) {
                cout << endl;
                currentDayOfWeek = 0;
            }
        }

        cout << endl;
    }

    int getMonthDays(int month, int year) const {
        if (month == 2) {
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
                return 29;
            else
                return 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30;
        } else {
            return 31;
        }
    }

    string getMonthName(int month) const {
        return monthNames[month - 1];
    }
};

struct RoomAvailability {
    int count;
    vector<int> availability;

    RoomAvailability(int c, int days) : count(c), availability(days, c) {}
};

struct RoomType {
    string type;
    vector<RoomAvailability> availabilityByMonth;
    int price;

    RoomType(string t, int c, int days, int p) : type(t), availabilityByMonth(NUM_MONTHS, RoomAvailability(c, days)), price(p) {}
};


struct Reservation {
    string roomType;
    string referenceNumber;
    int month;
    int fromDate; // Changed date to fromDate to represent the start date of the reservation
    int toDate; // Added toDate to represent the end date of the reservation
    bool confirmed;
};

Calendar calendar;

vector<RoomType> roomTypes = {
    {"Standard Room", 15, calendar.getMonthDays(1, 2024), 5000},
    {"Deluxe Room", 10, calendar.getMonthDays(1, 2024), 9000},
    {"Suite Room", 10, calendar.getMonthDays(1, 2024), 12000},
    {"Executive Room", 7, calendar.getMonthDays(1, 2024), 20000},
    {"Penthouse", 3, calendar.getMonthDays(1, 2024), 35000}
};

vector<Reservation> reservations;

string generateReferenceNumber() {
    string referenceNumber;
    static const char alphanumeric[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    const int alphanumericLength = sizeof(alphanumeric) - 1;

    srand(time(0));
    for (int i = 0; i < 6; i++) {
        referenceNumber += alphanumeric[rand() % alphanumericLength];
    }

    return referenceNumber;
}

// Global variable to hold the chosen month
int chosenMonth, chosenFromDate, chosenToDate;
vector<vector<RoomType>> roomTypesByMonth(NUM_MONTHS, vector<RoomType>());


void initializeRoomAvailability(int chosenMonth) {
    // Check if the roomTypes for the chosen month are already initialized
    if (roomTypesByMonth[chosenMonth - 1].empty()) {
        // Initialize the availability vectors for each room type for the chosen month
        for (RoomType& roomType : roomTypes) {
            roomType.availabilityByMonth[chosenMonth - 1].availability = vector<int>(calendar.getMonthDays(chosenMonth, 2024), roomType.availabilityByMonth[chosenMonth - 1].count);
        }
        // Add the roomTypes for the chosen month to the nested vector
        roomTypesByMonth[chosenMonth - 1] = roomTypes;
    } else {
        // If the roomTypes for the chosen month are already initialized,
        // copy them back to the original roomTypes vector to avoid duplication.
        roomTypes = roomTypesByMonth[chosenMonth - 1];
    }
}

void Roomreserve(int chosenMonth, int chosenFromDate, int chosenToDate) {
    string roomreserve_opt;
    cout << endl;
    cout << "Please select your preferred room type:\n";
    for (int i = 0; i < roomTypes.size(); i++) {
        cout << "[" << static_cast<char>('A' + i) << "] " << roomTypes[i].type << endl;
    }
    cout << "\n[" << static_cast<char>('A' + roomTypes.size()) << "] Back\n";
    cout << "[" << static_cast<char>('A' + roomTypes.size() + 1) << "] Exit\n";
    cout << "Enter your preferred room: ";
    cin >> roomreserve_opt;

    // Convert the input to uppercase
    transform(roomreserve_opt.begin(), roomreserve_opt.end(), roomreserve_opt.begin(), ::toupper);

    int roomIndex = -1;

    switch (roomreserve_opt[0]) {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
            roomIndex = roomreserve_opt[0] - 'A'; // Assigning value to roomIndex
            break;
        case 'F':
            return;
        case 'G':
            cout << "Thank you for using the Reservation System. Goodbye!\n";
            exit(0);
        default:
            cout << "Invalid entry.\n";
            return;
    }

    if (roomIndex == -1) {
        cout << "Invalid room selection.\n";
        return;
    }

    if (roomTypes[roomIndex].availabilityByMonth[chosenMonth - 1].availability[chosenFromDate - 1] > 0) {
        string referenceNumber = generateReferenceNumber();
        reservations.push_back({roomTypes[roomIndex].type, referenceNumber, chosenMonth, chosenFromDate, chosenToDate, false});
        // Store the reservation details in unavailable_date.txt
        ofstream outFile("unavailable_date.txt", ios::app);
        if (outFile.is_open()) {
            outFile << chosenMonth << " " << chosenFromDate << " " << chosenToDate << " 2024 " << referenceNumber << endl;
            outFile.close();
        } else {
            cout << "Unable to open the file for writing." << endl;
        }

        // Calculate the total amount based on the price, the duration of the stay, and the priceMultiplier
        int numDays = chosenToDate - chosenFromDate;
        if (numDays == 0) {
            numDays = 1;
        }
        int totalAmount = roomTypes[roomIndex].price * numDays;

        cout << "\nRoom reserved successfully. Reference number: " << referenceNumber << endl;
        cout << "Total amount: PHP " << totalAmount << ".00" << endl;

    } else {
        cout << "Sorry, no rooms of this type are available.\n";
    }
}


void confirmSelectedReservation() {
    string referenceNumber;
    cout << "Enter the reference number of the reservation to confirm: ";
    cin >> referenceNumber;

    bool reservationFound = false;
    for (Reservation& reservation : reservations) {
        if (reservation.referenceNumber == referenceNumber) {
            reservationFound = true;

            // Check if the reservation is already confirmed
            if (reservation.confirmed) {
                cout << "This reservation is already confirmed.\n";
                return;
            }

            // Find the room type index
            int roomIndex = -1;
            for (int i = 0; i < roomTypes.size(); i++) {
                if (roomTypes[i].type == reservation.roomType) {
                    roomIndex = i;
                    break;
                }
            }

            if (roomIndex == -1) {
                cout << "Invalid room type for the reservation.\n";
                return;
            }

            // Call DisplayRoomAvailability to check the number of available rooms
            int chosenMonth = reservation.month;
            int chosenFromDate = reservation.fromDate; 
            // DisplayRoomAvailability(chosenMonth, chosenFromDate);

            // Check if the rooms are available for the reservation dates
            int chosenToDate = reservation.toDate;
            for (int i = chosenFromDate; i <= chosenToDate; i++) {
                if (roomTypes[roomIndex].availabilityByMonth[chosenMonth - 1].availability[i - 1] <= 0) {
                    cout << "Sorry, the rooms are not available for the reservation dates.\n";
                    return;
                }
            }

            // Mark the reservation as confirmed
            reservation.confirmed = true;

            // Adjust room availability for the chosen date range of the selected room type
            for (int i = chosenFromDate; i <= chosenToDate; i++) {
                roomTypes[roomIndex].availabilityByMonth[chosenMonth - 1].availability[i - 1]--;
            }

            cout << "Reservation confirmed successfully.\n";
            return;
        }
    }

    if (!reservationFound) {
        cout << "Invalid reference number. Reservation not found.\n";
    }
}



void cancelReservation() {
    string referenceNumber;
    cout << "Enter the reference number of the reservation to cancel: ";
    cin >> referenceNumber;

    bool reservationFound = false;
    for (int i = 0; i < reservations.size(); i++) {
        if (reservations[i].referenceNumber == referenceNumber) {
            reservationFound = true;
            Reservation canceledReservation = reservations[i];

            // Find the room type index
            int roomIndex = -1;
            for (int j = 0; j < roomTypes.size(); j++) {
                if (roomTypes[j].type == canceledReservation.roomType) {
                    roomIndex = j;
                    break;
                }
            }

            if (roomIndex == -1) {
                cout << "Invalid room type for the reservation.\n";
                return;
            }

            // Adjust room availability for the canceled reservation dates
            int chosenMonth = canceledReservation.month;
            int chosenFromDate = canceledReservation.fromDate;
            int chosenToDate = canceledReservation.toDate;
            for (int day = chosenFromDate; day <= chosenToDate; day++) {
                roomTypes[roomIndex].availabilityByMonth[chosenMonth - 1].availability[day - 1]++;
            }

            // Mark the reservation as canceled
            reservations[i].confirmed = false;
            cout << "Reservation successfully canceled.\n";
            break;
        }
    }

    if (!reservationFound) {
        cout << "Invalid reference number. Reservation not found.\n";
    }
}


void Display_reservation() {
    cout << "\nMY RESERVATIONS:\n";
    for (int i = 0; i < reservations.size(); i++) {
        Reservation reservation = reservations[i];
        cout << "[" << (i + 1) << "] " << reservation.roomType << " (Date booked: " << reservation.month << "/" << reservation.fromDate << "-" << reservation.toDate << ", Reference number: " << reservation.referenceNumber << ")";
        cout << "  Status: " << (reservation.confirmed ? "CONFIRMED" : "PENDING") << endl;
    }

    string display_opt;
    cout << "\n[a] Cancel reservation\n";
    cout << "[b] Back\n";
    cout << "[c] Exit\n";
    cout << "Enter your choice: ";
    cin >> display_opt;

    // Convert the input to uppercase
    transform(display_opt.begin(), display_opt.end(), display_opt.begin(), ::toupper);

    switch (display_opt[0]) {
        case 'A':
            cancelReservation();
            break;
        case 'B':
            return;
        case 'C':
            cout << "Thank you for using the Reservation System. Goodbye!\n";
            exit(0);
        default:
            cout << "Invalid entry.\n";
    }
}

void sched() {
    Calendar calendar;
    int chosenFromDate, chosenToDate;

    cout << "Enter the month number (1-12): ";
    cin >> chosenMonth;

    if (chosenMonth < 1 || chosenMonth > NUM_MONTHS) {
        cout << "Invalid month number. Exiting..." << endl;
        return;
    }

    int numDays = calendar.getMonthDays(chosenMonth, 2024);

    // Display the calendar for the chosen month
    calendar.displayMonth(chosenMonth, 2024, 1);

    cout << "Enter the starting date (1-" << numDays << "): ";
    cin >> chosenFromDate;

    if (chosenFromDate < 1 || chosenFromDate > numDays) {
        cout << "Invalid date. Exiting..." << endl;
        return;
    }

    cout << "Enter the ending date (1-" << numDays << "): ";
    cin >> chosenToDate;

    if (chosenToDate < chosenFromDate || chosenToDate > numDays) {
        cout << "Invalid date. Exiting..." << endl;
        return;
    }

    initializeRoomAvailability(chosenMonth); // Initialize the room availability vector

    Roomreserve(chosenMonth, chosenFromDate, chosenToDate);
}

void DisplayRoomAvailability(int chosenMonth, int chosenFromDate) {
    if (chosenMonth < 1 || chosenMonth > NUM_MONTHS) {
        cout << "Invalid month number. Exiting..." << endl;
        return;
    }

    int numDays = calendar.getMonthDays(chosenMonth, 2024);

    cout << "\nROOM AVAILABILITY on " << calendar.getMonthName(chosenMonth) << " " << chosenFromDate << ":\n";
    cout << "Room Type\tAvailable Rooms\n";

    for (const RoomType& roomType : roomTypes) {
        int availableRooms = roomType.availabilityByMonth[chosenMonth - 1].availability[chosenFromDate - 1];
        cout << roomType.type << "\t\t" << availableRooms << endl;
    }
}

vector<RoomType> getAvailableRooms(int chosenMonth, int chosenFromDate) {
    vector<RoomType> availableRooms = roomTypesByMonth[chosenMonth - 1];

    // Adjust room availability based on reservations for the chosen date
    for (const Reservation& reservation : reservations) {
        if (reservation.month == chosenMonth && reservation.fromDate <= chosenFromDate && reservation.toDate >= chosenFromDate) {
            for (RoomType& roomType : availableRooms) {
                if (roomType.type == reservation.roomType) {
                    roomType.availabilityByMonth[chosenMonth - 1].availability[chosenFromDate - 1]--;
                }
            }
        }
    }

    return availableRooms;
}

void maintab() {
    char maintab_opt;
    cout << endl;
    cout << "Reservation System\n";
    cout << "[a] Schedule room reservation\n";
    cout << "[b] Display reservation(s)\n";
    cout << "[c] Exit\n";
    cout << "[d] Confirm a Reservation\n";
    cout << "[e] Show available rooms\n";
    cout << "Enter your choice: ";
    cin >> maintab_opt;

    // Convert the input to uppercase
    maintab_opt = toupper(maintab_opt);

    switch (maintab_opt) {
        case 'A':
            sched();
            break;
        case 'B':
            Display_reservation();
            break;
        case 'C':
            cout << "Thank you for using the Reservation System. Goodbye!\n";
            exit(0);
        case 'D':
            confirmSelectedReservation();
            break;
        case 'E':
            int chosenMonth, chosenFromDate;
            cout << "Enter the month number (1-12): ";
            cin >> chosenMonth;
            cout << "Enter the date (1-" << calendar.getMonthDays(chosenMonth, 2024) << "): ";
            cin >> chosenFromDate;
            DisplayRoomAvailability(chosenMonth, chosenFromDate);
            break;

        default:
            cout << "Invalid entry.\n";
    }

    // Clear the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    while (true) {
        maintab();
    }

    return 0;
}
