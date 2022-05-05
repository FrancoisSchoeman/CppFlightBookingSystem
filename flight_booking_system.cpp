#include <iostream>
using namespace std;

const float ECONOMY_CLASS_PRICE = 1600.00;
const int DEP_ARR_ROWS = 5;
const int FIRST_CLASS_ROWS = 4;
const int ECONOMY_CLASS_ROWS = 5;
const float DEPART_ARRIVE_TIMES[DEP_ARR_ROWS][2] = {
        {7.0, 9.3},
        {9.0, 11.3},
        {11.0, 13.3},
        {13.0, 15.3},
        {15.0, 17.3}
    };

struct FlightTimeArrangement{
    string firstClassSeatArrangements[FIRST_CLASS_ROWS][6] = {
        {"A1", "A2", "A3", "A4", "A5", "A6"},
        {"B1", "B2", "B3", "B4", "B5", "B6"},
        {"C1", "C2", "C3", "C4", "C5", "C6"},
        {"D1", "D2", "D3", "D4", "D5", "D6"}
    };
    string econoClassSeatArrangements[ECONOMY_CLASS_ROWS][6] = {
        {"E1", "E2", "E3", "E4", "E5", "E6"},
        {"F1", "F2", "F3", "F4", "F5", "F6"},
        {"G1", "G2", "G3", "G4", "G5", "G6"},
        {"H1", "H2", "H3", "H4", "H5", "H6"},
        {"I1", "I2", "", "", "", ""}
    };
};

void displaySeats(int flightOption, const FlightTimeArrangement flightTimeArrangement);
void validateUserFlightOption(int & flightOption);
void displayTimes(int & flightOption);
void seatInputValidation(string & chosenSeat);
bool validateSeatAvailability(string chosenSeat, const FlightTimeArrangement flightTimeArrangement);
void chooseSeat(string chosenSeat, FlightTimeArrangement & flightTimeArrangement, string & classType);
float calculateTicketPrice(string classType);
void displayBookingTicket(string name, int flightOption, string classType, string chosenSeat);

int main(){
    FlightTimeArrangement flightTimeArrangements[DEP_ARR_ROWS];
    char addBooking;

    do{
        string name, chosenSeat, classType;
        int flightOption;

        cout << "Welcome to COS1511 Flight Booking System\n\n"
        "Enter full name:\n";
        getline(cin, name, '\n');

        cout << "\nThe available travel times for flights are:\n\tDepart\tArrive\n";

        cout.setf(ios::fixed);
        cout.precision(2);

        // Display departure and arrival times menu
        displayTimes(flightOption);

        // Display seating arrangements for all classes
        displaySeats(flightOption, flightTimeArrangements[flightOption - 1]);

        // Asking for seat number
        cout << "Seats that are already taken are indicated with asterisks (**).\n";
        cout << "Please key in a seat number to choose a seat (eg: A2)\n";
        cin >> chosenSeat;

        // Validate seat input
        seatInputValidation(chosenSeat);

        // Validate seat availability
        while(validateSeatAvailability(chosenSeat, flightTimeArrangements[flightOption - 1]) == false){
            cout << "The seat you have chosen is not available. Please key in another seat number (eg: A2)\n";
            cin >> chosenSeat;
            seatInputValidation(chosenSeat);
        }

        // Book available seat
        chooseSeat(chosenSeat, flightTimeArrangements[flightOption - 1], classType);

        //Display flight booking ticket
        displayBookingTicket(name, flightOption, classType, chosenSeat);

        // Loop program again if user wants to add another booking
        cout << "Do you want to make another booking? (Y/N)\n";
        cin >> addBooking;

        // Validate user input
        while(toupper(addBooking) != 'Y' && toupper(addBooking) != 'N'){
            cout << "Incorrect option. Please choose Y or N.\n";
            cin >> addBooking;
        }

        // This method is used to fix an issue where the getline method is not getting the first character
        cin.ignore();
    } while(toupper(addBooking) != 'N');

    cout << "\n";

    // Display the total number of bookings made for each flight time
    for(int i = 0; i < DEP_ARR_ROWS; i++){
        int counter = 0;
        string daytime;

        if(DEPART_ARRIVE_TIMES[i][0] >= 12){
            daytime = "p.m";
        } else {
            daytime = "a.m";
        }

        for(int j = 0; j < FIRST_CLASS_ROWS; j++){
            for(int k = 0; k < 6; k++){
                if(flightTimeArrangements[i].firstClassSeatArrangements[j][k] == "**"){
                    counter++;
                }
            }
        }

        for(int l = 0; l < ECONOMY_CLASS_ROWS; l++){
            for(int m = 0; m < 6; m++){
                if(flightTimeArrangements[i].econoClassSeatArrangements[l][m] == "**"){
                    counter++;
                }
            }
        }
        cout << "Number of bookings made for " << DEPART_ARRIVE_TIMES[i][0] << " " << daytime << ": " << counter << "\n";
    }
    return 0;
}

// Function to display departure and arrival times menu
void displayTimes(int & flightOption){
    for(int i = 0; i < DEP_ARR_ROWS; i++){
        cout << i + 1 << ".\t";
        for(int j = 0; j < 2; j++){
            cout << DEPART_ARRIVE_TIMES[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "Choose the time by entering the option number from the displayed list:\n";
    cin >> flightOption;
    validateUserFlightOption(flightOption);
}

// Function to display seating arrangements for all classes
void displaySeats(int flightOption, const FlightTimeArrangement flightTimeArrangement){
    // Display seating arrangements for First Class
    cout << "\nThe available seats for " << DEPART_ARRIVE_TIMES[flightOption - 1][0] << " are as follows:\n";
    cout << "First Class(" << calculateTicketPrice("First Class") << ")\n";
    for(int i = 0; i < FIRST_CLASS_ROWS; i++){
        for(int j = 0; j < 6; j++){

            switch(j){
                case 3:
                    cout << "|----|" << flightTimeArrangement.firstClassSeatArrangements[i][j];
                    break;
                default:
                    cout << "|" << flightTimeArrangement.firstClassSeatArrangements[i][j];
                }
        }
        cout << "|\n";
    }

    // Display seating arrangements for Economy Class
    cout << "Economy Class(" << ECONOMY_CLASS_PRICE << ")\n";
    for(int i = 0; i < ECONOMY_CLASS_ROWS; i++){
        for(int j = 0; j < 6; j++){
            if(flightTimeArrangement.econoClassSeatArrangements[i][j] != ""){

                switch(j){
                case 3:
                    cout << "|----|" << flightTimeArrangement.econoClassSeatArrangements[i][j];
                    break;
                default:
                    cout << "|" << flightTimeArrangement.econoClassSeatArrangements[i][j];
                }
            }
        }
        cout << "|\n";
    }
}

// Flight option input validation
void validateUserFlightOption(int & flightOption){
    while(flightOption < 1 || flightOption > DEP_ARR_ROWS){
        cout << "Incorrect option! Please choose from 1-5.\n";
        cin >> flightOption;
    }
}

// Seat input validation
void seatInputValidation(string & chosenSeat){
    bool isCorrect = false;
    // Validate chosen letter and number by means of ASCII values
    while(isCorrect != true){
        if(chosenSeat[0] == 'I' && int(chosenSeat[1]) > 50){
            cout << "Incorrect seat number. Please key in a seat number (eg: A2)\n";
            cin >> chosenSeat;
        } else if(int(chosenSeat[0]) < 64 || int(chosenSeat[0] > 73)){
            cout << "Incorrect seat number. Please key in a seat number (eg: A2)\n";
            cin >> chosenSeat;
        } else {
            isCorrect = true;
        }
    }
}

// Validate the availability of the chosen seat
bool validateSeatAvailability(string chosenSeat, const FlightTimeArrangement flightTimeArrangement){
    bool isAvailable = false;
    for(int i = 0; i < FIRST_CLASS_ROWS; i++){
        for(int j = 0; j < 6; j++){
            if(chosenSeat == flightTimeArrangement.firstClassSeatArrangements[i][j]){
                isAvailable = true;
            }
        }
    }
    for(int i = 0; i < ECONOMY_CLASS_ROWS; i++){
        for(int j = 0; j < 6; j++){
            if(chosenSeat == flightTimeArrangement.econoClassSeatArrangements[i][j]){
                isAvailable = true;
            }
        }
    }
    return isAvailable;
}

// Function for choosing seat for particular class
void chooseSeat(string chosenSeat, FlightTimeArrangement & flightTimeArrangement, string & classType){
    if(int(chosenSeat[0] <= 68)){
        for(int i = 0; i < FIRST_CLASS_ROWS; i++){
            for(int j = 0; j < 6; j++){
                if(chosenSeat == flightTimeArrangement.firstClassSeatArrangements[i][j]){
                    flightTimeArrangement.firstClassSeatArrangements[i][j] = "**";
                    classType = "First Class";
                }
            }
        }
    } else if(int(chosenSeat[0]) >= 69){
        for(int i = 0; i < ECONOMY_CLASS_ROWS; i++){
            for(int j = 0; j < 6; j++){
                if(chosenSeat == flightTimeArrangement.econoClassSeatArrangements[i][j]){
                    flightTimeArrangement.econoClassSeatArrangements[i][j] = "**";
                    classType = "Economy Class";
                }
            }
        }
    }
}

// Function to calculate ticket price
float calculateTicketPrice(string classType){
    if(classType == "First Class"){
        return ECONOMY_CLASS_PRICE * 1.2;
    } else if(classType == "Economy Class"){
        return ECONOMY_CLASS_PRICE;
    }
    return 0;
}

// Function to display flight booking ticket
void displayBookingTicket(string name, int flightOption, string classType, string chosenSeat){
    cout << "\n*************************\n";
    cout << "Travel ticket for FLIGHT\n";
    cout << "*************************\n";
    cout << "Name\t\t:\t" << name << "\t";
    cout << "Travel Ticket Class\t:\t" << classType << "\n";
    cout << "\t\t\t\t\tSeat No\t\t\t:\t" << chosenSeat << "\n";
    cout << "Departure\t:\t" << "Johannesburg\t";
    cout << "Departure Time\t\t:\t" << DEPART_ARRIVE_TIMES[flightOption - 1][0] << "\n";
    cout << "Destination\t:\t" << "Cape Town\t";
    cout << "Arrival Time\t\t:\t" << DEPART_ARRIVE_TIMES[flightOption - 1][1] << "\n";
    cout << "*************************\n";
    cout << "Amount: R" << calculateTicketPrice(classType) << ". Thank your for booking with COS1511. Your travel agent for queries is Francois Schoeman.\n";
    cout << "*************************\n\n";
}
