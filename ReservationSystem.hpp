#define RESERVATIONSYSTEM_HPP

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
void sched(const string& loggedInUsername);
void displayRoomInformation();
void DisplayRoomAvailability(int chosenMonth, int chosenFromDate) ;
string generateReferenceNumber();

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


Calendar calendar;

vector<RoomType> roomTypes = {
    {"Standard Room", 15, calendar.getMonthDays(1, 2024), 5000},
    {"Deluxe Room", 10, calendar.getMonthDays(1, 2024), 9000},
    {"Suite Room", 10, calendar.getMonthDays(1, 2024), 12000},
    {"Executive Room", 7, calendar.getMonthDays(1, 2024), 20000},
    {"Penthouse", 3, calendar.getMonthDays(1, 2024), 35000}
};

vector<Reservation> reservations;

void Roomreserve(int chosenMonth, int chosenFromDate, int chosenToDate, const string& loggedInUsername) {
    string roomreserve_opt;
    int roomIndex = -1;

    while (true) {
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
                cout << "Invalid entry. Please try again.\n";
                break; // Loop to re-ask for valid input
        }

        if (roomIndex != -1)
            break; // Exit the loop if a valid room selection is made
    }

    if (roomTypes[roomIndex].availabilityByMonth[chosenMonth - 1].availability[chosenFromDate - 1] > 0) {
        string referenceNumber = generateReferenceNumber();
        reservations.push_back({roomTypes[roomIndex].type, referenceNumber, chosenMonth, chosenFromDate, chosenToDate, false, loggedInUsername});
        // Store the reservation details in unavailable_date.txt
        ofstream outFile("reservations.txt");
    if (outFile.is_open()) {
        for (const Reservation& reservation : reservations) {
            outFile << reservation.roomType << "," << reservation.referenceNumber << ","
                    << reservation.month << "," << reservation.fromDate << ","
                    << reservation.toDate << "," << reservation.confirmed << "," << reservation.loggedInUsername << endl;
        }
        outFile.close();
        cout << "Reservations saved successfully." << endl;
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
        
        system("pause");

    } else {
        cout << "Sorry, no rooms of this type are available.\n";
    }
}

// Function to load reservations from a file
void loadReservationsFromFile() {
    ifstream inFile("reservations.txt");
    if (inFile.is_open()) {
        reservations.clear();
        string line;
        while (getline(inFile, line)) {
        	//std::cout << line << std::endl;
            istringstream iss(line);
            string roomType, referenceNumber, loggedInUsername, confirmedStr;
            int month, fromDate, toDate;
            bool confirmed;
            if (getline(iss, roomType, ',') &&
                getline(iss, referenceNumber, ',') &&
                (iss >> month) && (iss.ignore()) &&
                (iss >> fromDate) && (iss.ignore()) &&
                (iss >> toDate) && (iss.ignore()) &&
                getline(iss, confirmedStr, ',') &&
                getline(iss, loggedInUsername)) {
                confirmed = (confirmedStr == "1");
                reservations.push_back({roomType, referenceNumber, month, fromDate, toDate, confirmed, loggedInUsername});
            }
        }
        inFile.close();
    }
}


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
            //DisplayRoomAvailability(chosenMonth, chosenFromDate);

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

void deleteReservation() {
    string referenceNumber;
    cout << "Enter the reference number of the reservation to cancel: ";
    cin >> referenceNumber;

    bool reservationFound = false;
    for (int i = 0; i < reservations.size(); i++) {
        if (reservations[i].referenceNumber == referenceNumber) {
            reservationFound = true;
            reservations.erase(reservations.begin() + i);
            cout << "Reservation successfully cancelled.\n";
            break;
        }
    }

    if (!reservationFound) {
        cout << "Invalid reference number. Reservation not found.\n";
    }
}

void Display_reservation_admin() {
    string display_opt;
	do{
	system("cls");
    cout << "=== Manage Reservation Schedule ===" << endl << endl;
    
    if(reservations.size() == 0) {
    	cout << "No reservations found." << endl;
	}
    for (int i = 0; i < reservations.size(); i++) {
        Reservation reservation = reservations[i];
        cout << "[" << (i + 1) << "] " << "[Username: " << reservation.loggedInUsername << "] " << "[Room Type: " << reservation.roomType << "] " << " (Date booked: " << reservation.month << "/" << reservation.fromDate << "-" << reservation.toDate << ", Reference number: " << reservation.referenceNumber << ")";
        cout << "  Status: " << (reservation.confirmed ? "CONFIRMED" : "PENDING") << endl;
    }

    cout << "\n[a] Confirm reservation";
    cout << "\n[b] Delete reservation\n";
    cout << "[c] Show Available Rooms\n";
    cout << "[d] Logout\n";
    cout << "[e] Exit\n";
    cout << "Enter your choice: ";
    cin >> display_opt;
    cout << endl;

    // Convert the input to uppercase
    transform(display_opt.begin(), display_opt.end(), display_opt.begin(), ::toupper);

    switch (display_opt[0]) {
    	case 'A':
            confirmSelectedReservation();
            system("pause");
            break;
        case 'B':
            deleteReservation();
            system("pause");
            break;
        case 'C':
        		char choice;
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
        case 'D':
			cout << "Logging out..." << endl;
            break;
        case 'E':
            cout << "Thank you for using the Reservation System. Goodbye!\n";
            exit(0);
        default:
            cout << "Invalid entry.\n";
    }
	} while (display_opt[0] != 'D');
}

void Display_reservation_client(const string& loggedInUsername) {
	system("cls");
    cout << "\nMY RESERVATIONS:\n";
    int reservationCount = 0;

    for (int i = 0; i < reservations.size(); i++) {
        Reservation reservation = reservations[i];
        if (reservation.loggedInUsername == loggedInUsername) {
            reservationCount++;
            cout << "[" << reservationCount << "] " << reservation.roomType << " (Date booked: " << reservation.month << "/" << reservation.fromDate << "-" << reservation.toDate << ", Reference number: " << reservation.referenceNumber << ")";
            cout << "  Status: " << (reservation.confirmed ? "CONFIRMED" : "PENDING") << endl;
        }
    }

    if (reservationCount == 0) {
        cout << "You have no reservations." << endl;
    }

    string display_opt;
    cout << "\n[a] Cancel reservation\n";
    cout << "[b] Back\n";
    cout << "[c] Exit\n";
    cout << "Enter your choice: ";
    cin >> display_opt;
	cout << endl;
    // Convert the input to uppercase
    transform(display_opt.begin(), display_opt.end(), display_opt.begin(), ::toupper);

    switch (display_opt[0]) {
        case 'A':
            deleteReservation();
            system("pause");
            break;
        case 'B':
            return;
        case 'C':
            cout << "Thank you for using the Reservation System. Goodbye!\n";
            exit(0);
        default:
            cout << "Invalid entry.\n";
    }

    // Clear the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void sched(const string& loggedInUsername) {
    Calendar calendar;
    int chosenFromDate, chosenToDate;

    while (true) {
        cout << "Enter the month number (1-12): ";
        cin >> chosenMonth;

        if (cin.fail() || chosenMonth < 1 || chosenMonth > NUM_MONTHS) {
            cout << "Invalid month number. Please try again." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        } else {
            break;
        }
    }

    int numDays = calendar.getMonthDays(chosenMonth, 2024);

    // Display the calendar for the chosen month
    calendar.displayMonth(chosenMonth, 2024, 1);

    while (true) {
        cout << "Enter the starting date (1-" << numDays << "): ";
        cin >> chosenFromDate;

        if (chosenFromDate < 1 || chosenFromDate > numDays) {
            cout << "Invalid date." << endl;
        } else {
            break;
        }
    }

    while (true) {
        cout << "Enter the ending date (1-" << numDays << "): ";
        cin >> chosenToDate;

        if (chosenToDate <= chosenFromDate || chosenToDate > numDays) {
            cout << "Invalid date." << endl;
        } else {
            break;
        }
    }
    
    system("cls");
    
    cout << "\nROOM AVAILABILITY on " << calendar.getMonthName(chosenMonth) << " " << chosenFromDate << ":\n";
    cout << "Room Type\tAvailable Rooms\n";

    for (const RoomType& roomType : roomTypes) {
        int availableRooms = roomType.availabilityByMonth[chosenMonth - 1].availability[chosenFromDate - 1];
        cout << roomType.type << "\t\t" << availableRooms << endl;
    }
    

    initializeRoomAvailability(chosenMonth); // Initialize the room availability vector

    Roomreserve(chosenMonth, chosenFromDate, chosenToDate, loggedInUsername);
}

void DisplayRoomAvailability(int chosenMonth, int chosenFromDate) {
    if (chosenMonth < 1 || chosenMonth > NUM_MONTHS) {
        cout << "Invalid month number." << endl;
        return;
    }

    int numDays = calendar.getMonthDays(chosenMonth, 2024);
    cout << endl << "Room Type\tAvailable Rooms\n";

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