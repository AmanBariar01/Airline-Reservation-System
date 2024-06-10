#include <iostream>
#include <iomanip> // Include for setw()
#include <unordered_map>
#include <windows.h>
#include <vector>
#include <algorithm> // Include for sorting

using namespace std;

struct Flight {
    string location;
    string timing;
    int totalSeats;
    vector<bool> seats;
};

unordered_map<int, Flight> flights;

void initializeFlights() {
    // Sample flights data
    flights[101] = {"Mumbai to Delhi", "10:00 AM", 50, vector<bool>(50, true)};
    flights[102] = {"Bangalore to Kolkata", "12:00 PM", 40, vector<bool>(40, true)};
    flights[103] = {"Chennai to Ahemdabad", "2:00 PM", 60, vector<bool>(60, true)};
    flights[104] = {"Raipur to Bangalore", "9:00 AM", 60, vector<bool>(60, true)};
    flights[105] = {"Kolkata to Mumbai", "5:00 PM", 70, vector<bool>(70, true)};
}

void displayMenu() {
    cout << "Welcome to Airline reservation" << endl;
    cout << "1. View available flights" << endl;
    cout << "2. Book your Flight" << endl;
    cout << "3. Exit" << endl;
}

void displayFlights() {
    cout << "Available Flights:" << endl;
    cout << "+--------------+----------------------+----------+-------------+----------------+" << endl;
    cout << "| Flight Number|     Location         |  Timing  | Total Seats | Available Seats|" << endl;
    cout << "+--------------+----------------------+----------+-------------+----------------+" << endl;
    
    // Sort flights by flight number
    vector<int> sortedFlightNumbers;
    for (const auto& pair : flights) {
        sortedFlightNumbers.push_back(pair.first);
    }
    sort(sortedFlightNumbers.begin(), sortedFlightNumbers.end());
    
    for (int flightNumber : sortedFlightNumbers) {
        const Flight& flight = flights[flightNumber];
        int availableSeats = 0;
        for (bool seat : flight.seats) {
            if (seat) {
                availableSeats++;
            }
        }
        cout << "| " << setw(12) << flightNumber << " | " << setw(20) << flight.location << " | " << setw(8) << flight.timing << " | " << setw(11) << flight.totalSeats << " | " << setw(14) << availableSeats << " |" << endl;
    }
    cout << "+--------------+-------------------+----------+-------------+----------------+" << endl;
}

void bookFlight(int flightNumber) {
    while (true) {
        auto it = flights.find(flightNumber);
        if (it == flights.end()) {
            cout << "There is no flight with number " << flightNumber << ". Please enter a valid flight number." << endl;
            cout << "Enter flight number: ";
            cin >> flightNumber;
        } else {
            break; // Exit the loop if the flight number is valid
        }
    }

    Flight& flight = flights[flightNumber];

    cout << "Seats available for Flight " << flightNumber << " (" << flight.location << " at " << flight.timing << "):" << endl;
    for (int i = 0; i < flight.totalSeats; ++i) {
        if (i > 0 && i % 8 == 0) {
            cout << endl;
        }
        if (flight.seats[i]) {
            cout << i + 1 << ". Available\t";
        } else {
            cout << i + 1 << ". Booked\t";
        }
    }
    cout << endl;

    int seatNumber;
    while (true) {
        cout << "Enter seat number you want to book: ";
        cin >> seatNumber;

        if (seatNumber < 1 || seatNumber > flight.totalSeats) {
            cout << "Invalid seat number. Please enter a valid seat number." << endl;
        } else if (!flight.seats[seatNumber - 1]) {
            cout << "Seat is already booked. Please select another seat." << endl;
        } else {
            flight.seats[seatNumber - 1] = false;
            cout << "Seat booked successfully." << endl;
            Sleep(2000);
            break; // Exit the loop if a valid seat number is provided
        }
    }
}


int main() {
    initializeFlights();
    
    int choice;
    do {
        if (choice != 1) {
            system("cls");
        }
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayFlights();
                break;
            case 2:
                int flightNumber;
                cout << "Enter flight number: ";
                cin >> flightNumber;
                bookFlight(flightNumber);
                break;
            case 3:
                cout << "Thank You For  Using Our Services! Looking Forward  To Serving You Again!" << endl;
                break;
            default:
                cout << "Please select a correct option." << endl;
                Sleep(2000);
                break;
        }
    } while (choice != 3);

    return 0;
}
