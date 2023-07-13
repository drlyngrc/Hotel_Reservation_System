#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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

int main() {
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
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> option;
        
        system("cls");
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
            case 0:
                return 0;  
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
            return 0;  
        } else {
            cout << "Invalid option." << endl;
            return 0;  
        }
    }
}
