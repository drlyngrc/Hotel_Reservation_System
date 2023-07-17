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
};

struct RoomType {
    string type;
    int count;
    int price; // Added the price field for each room type
};

struct Reservation {
    string roomType;
    string referenceNumber;
    int month;
    int fromDate; // Changed date to fromDate to represent the start date of the reservation
    int toDate; // Added toDate to represent the end date of the reservation
    bool confirmed;
};

vector<RoomType> roomTypes = {
    {"Standard Room", 15, 5000},
    {"Deluxe Room", 10, 9000},
    {"Suite Room", 10, 12000},
    {"Executive Room", 7, 20000},
    {"Penthouse", 3, 35000}
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

bool isDateUnavailable(int month, int day) {
    ifstream inFile("unavailable_date.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            int lineMonth, lineDay, lineYear;
            string status;
            istringstream iss(line);
            if (iss >> lineMonth >> lineDay >> lineYear >> status) {
                if (lineMonth == month && lineDay == day && lineYear == 2024) {
                    inFile.close();
                    return (status == "DATE_UNAVAILABLE");
                }
            }
        }
        inFile.close();
    }
    return false;
}

void markDateUnavailable(int month, int day) {
    if (isDateUnavailable(month, day)) {
        cout << "The date is already marked as unavailable." << endl;
        return;
    }

    ofstream outFile("unavailable_date.txt", ios::app);
    if (outFile.is_open()) {
        outFile << month << " " << day << " " << 2024 << " DATE_UNAVAILABLE" << endl;
        outFile.close();
        cout << "Date marked as unavailable: " << month << "/" << day << endl;
    } else {
        cout << "Unable to open the file for writing." << endl;
    }
}

void markDateAvailable(int month, int day) {
    ifstream inFile("unavailable_date.txt");
    ofstream outFile("temp.txt");
    if (inFile.is_open() && outFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            int lineMonth, lineDay, lineYear;
            string status;
            istringstream iss(line);
            if (iss >> lineMonth >> lineDay >> lineYear >> status) {
                if (lineMonth == month && lineDay == day && lineYear == 2024 && status == "DATE_UNAVAILABLE") {
                    continue; // Skip the line if it matches the provided date
                }
            }
            outFile << line << endl; // Write the line to the temporary file
        }
        inFile.close();
        outFile.close();
        remove("unavailable_date.txt"); // Remove the original file
        rename("temp.txt", "unavailable_date.txt"); // Rename the temporary file to the original file name
        cout << "Date marked as available: " << month << "/" << day << endl;
    } else {
        cout << "Unable to open the file for writing." << endl;
    }
}

void Roomreserve(int chosenMonth, int chosenFromDate, int chosenToDate) {
    string roomreserve_opt;
    cout << endl;
    cout << "Please select your preferred room type:\n";
    for (int i = 0; i < roomTypes.size(); i++) {
        cout << "[" << static_cast<char>('A' + i) << "] " << roomTypes[i].type << " (" << roomTypes[i].count << " available)" << endl;
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
        case 'E': {
            int roomIndex = roomreserve_opt[0] - 'A';
            if (roomTypes[roomIndex].count > 0) {
                // Check if any date within the chosen range is marked as unavailable
                for (int day = chosenFromDate; day <= chosenToDate; day++) {
                    if (isDateUnavailable(chosenMonth, day)) {
                        cout << "At least one date within the chosen range is unavailable. Please select different dates.\n";
                        return;
                    }
                }

                roomTypes[roomIndex].count--;
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
                if(numDays == 0){
                    numDays = 1;
                }
                int totalAmount = roomTypes[roomIndex].price * numDays ;

                cout << "\nRoom reserved successfully. Reference number: " << referenceNumber << endl;
                cout << "Total amount: Php" << totalAmount << endl;
            } else {
                cout << "Sorry, no rooms of this type are available.\n";
            }
            break;
        }
        case 'F':
            return;
        case 'G':
            cout << "Thank you for using the Reservation System. Goodbye!\n";
            exit(0);
        default:
            cout << "Invalid entry.\n";
    }
}

void confirmReservation() {
    string referenceNumber;
    cout << "Enter the reference number of the reservation to confirm: ";
    cin >> referenceNumber;

    bool reservationFound = false;
    for (Reservation& reservation : reservations) {
        if (reservation.referenceNumber == referenceNumber) {
            reservationFound = true;
            // Update the reservation status to "Confirmed"
            reservation.confirmed = true;
            break;
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
            reservations.erase(reservations.begin() + i);
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

void markDateUnavailableMenu() {
    Calendar calendar;
    int chosenMonth, chosenDate;

    cout << "Enter the month number (1-12): ";
    cin >> chosenMonth;

    if (chosenMonth < 1 || chosenMonth > NUM_MONTHS) {
        cout << "Invalid month number. Exiting..." << endl;
        return;
    }

    int numDays = calendar.getMonthDays(chosenMonth, 2024);

    // Display the calendar for the chosen month
    calendar.displayMonth(chosenMonth, 2024, 1);

    cout << "Enter the date to mark as unavailable (1-" << numDays << "): ";
    cin >> chosenDate;

    if (chosenDate < 1 || chosenDate > numDays) {
        cout << "Invalid date. Exiting..." << endl;
        return;
    }

    markDateUnavailable(chosenMonth, chosenDate);
}

void markDateAvailableMenu() {
    Calendar calendar;
    int chosenMonth, chosenDate;

    cout << "Enter the month number (1-12): ";
    cin >> chosenMonth;

    if (chosenMonth < 1 || chosenMonth > NUM_MONTHS) {
        cout << "Invalid month number. Exiting..." << endl;
        return;
    }

    int numDays = calendar.getMonthDays(chosenMonth, 2024);

    // Display the calendar for the chosen month
    calendar.displayMonth(chosenMonth, 2024, 1);

    cout << "Enter the date to mark as available (1-" << numDays << "): ";
    cin >> chosenDate;

    if (chosenDate < 1 || chosenDate > numDays) {
        cout << "Invalid date. Exiting..." << endl;
        return;
    }

    markDateAvailable(chosenMonth, chosenDate);
}

void sched() {
    Calendar calendar;
    int chosenMonth, chosenFromDate, chosenToDate;

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

    // Check if any date within the chosen range is marked as unavailable
    for (int day = chosenFromDate; day <= chosenToDate; day++) {
        if (isDateUnavailable(chosenMonth, day)) {
            cout << "At least one date within the chosen range is unavailable. Please select different dates.\n";
            return;
        }
    }

    int numDaysStayed = chosenToDate - chosenFromDate;

    Roomreserve(chosenMonth, chosenFromDate, chosenToDate);
}

void maintab() {
    char maintab_opt;
    cout << endl;
    cout << "Reservation System\n";
    cout << "[a] Schedule room reservation\n";
    cout << "[b] Display reservation(s)\n";
    cout << "[c] Exit\n";
    cout << "[d] Confirm a Reservation\n";
    cout << "[e] Mark date as unavailable\n";
    cout << "[f] Mark date as available\n";
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
            confirmReservation();
            break;
        case 'E':
            markDateUnavailableMenu();
            break;
        case 'F':
            markDateAvailableMenu();
            break;
        default:
            cout << "Invalid entry.\n";
    }
}

int main() {
    while (true) {
        maintab();
    }

    return 0;
}
