#include <iostream>  
#include <vector>    
#include <string>    
#include <fstream>   
#include <limits>    
#include <sstream>   
#include <algorithm> 

using namespace std; 

// Define a class representing a pupil (student)
class Pupil {
public:
    int student_id; // Unique identifier for the pupil
    string name;    // Pupil's full name
    int age;        // Pupil's age
    int grade;      // Pupil's grade (e.g., 1 to 5)

    // Constructor to initialize all member variables
    Pupil(int id, string n, int a, int g) : student_id(id), name(n), age(a), grade(g) {}
};

// Function to save a list of pupils to a file
void saveToFile(const vector<Pupil>& pupils, const string& filename = "database.txt") {
    ofstream outFile(filename); // Create an output file stream
    if (outFile.is_open()) {    // Check if the file was successfully opened
        for (const auto& pupil : pupils) { // Loop through each pupil
            // Write each pupil’s details to the file, separated by spaces
            outFile << pupil.student_id << " " << pupil.name << " " << pupil.age << " " << pupil.grade << "\n";
        }
        outFile.close(); // Close the file
        cout << "Data successfully saved to file " << filename << endl;
    } else {
        // If file couldn't be opened, print error
        cerr << "Error: Could not open file for saving: " << filename << endl;
    }
}

// Function to load a list of pupils from a file
vector<Pupil> readFromFile(const string& filename = "database.txt") {
    vector<Pupil> pupils;         // Create a vector to hold loaded pupils
    ifstream inFile(filename);    // Create an input file stream
    if (inFile.is_open()) {       // Check if the file opened successfully
        string line;              // Variable to hold each line from the file
        while (getline(inFile, line)) { // Read file line-by-line
            stringstream ss(line); // Use stringstream to parse the line
            int id, age, grade;    // Variables to hold parsed values
            string name;           // Variable to hold name
            // Try to parse the line into variables
            if (ss >> id >> name >> age >> grade) {
                // If successful, add the pupil to the vector
                pupils.emplace_back(id, name, age, grade);
            } else {
                // If line is malformed, print a warning
                cerr << "Warning: Skipping malformed line in file: " << line << endl;
            }
        }
        inFile.close(); // Close the file
        cout << "Data successfully loaded from file " << filename << endl;
    } else {
        // If file couldn't be opened, print error
        cerr << "Could not open file " << filename << " for reading." << endl;
    }
    return pupils; // Return the list of pupils read from the file
}

// Function to add a new pupil to the list
void addObject(vector<Pupil>& pupils) {
    int id;       // To store user-entered ID
    string name;  // To store user-entered name
    int age;      // To store user-entered age
    int grade;    // To store user-entered grade

    while (true) { // Loop until a valid and unique ID is entered
        cout << "Enter pupil ID: ";
        cin >> id; // Input ID
        if (cin.fail()) { // Check for invalid input
            cout << "Invalid ID. Please enter an integer." << endl;
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue; // Restart loop
        }

        bool idExists = false; // Flag to check if ID is already used
        for (const auto& s : pupils) {
            if (s.student_id == id) {
                idExists = true; // Set flag if ID exists
                break;
            }
        }
        if (idExists) {
            cout << "A pupil with this ID already exists. Please enter a different ID." << endl;
        } else {
            break; // Exit loop if ID is valid and unique
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    cout << "Enter pupil name: ";
    getline(cin, name); // Read full line for name

    while (true) { // Validate age input
        cout << "Enter pupil age: ";
        cin >> age;
        if (cin.fail() || age <= 0) {
            cout << "Invalid age. Please enter a positive integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    while (true) { // Validate grade input
        cout << "Enter pupil grade (1 to 5): ";
        cin >> grade;
        if (cin.fail() || grade < 1 || grade > 5) {
            cout << "Invalid grade. Please enter an integer between 1 and 5." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    // Add the new pupil to the vector
    pupils.emplace_back(id, name, age, grade);
    cout << "Pupil " << name << " added to the system." << endl;
}

// Function to display all pupils in the list
void displayObjects(const vector<Pupil>& pupils) {
    if (pupils.empty()) { // Check if list is empty
        cout << "Database is empty." << endl;
        return;
    }
    cout << "\n--- List of Pupils ---" << endl;
    for (const auto& pupil : pupils) {
        // Print each pupil’s details
        cout << "ID: " << pupil.student_id << ", Name: " << pupil.name
             << ", Age: " << pupil.age << ", Grade: " << pupil.grade << endl;
    }
    cout << "----------------------" << endl;
}

// Entry point of the program
int main() {
    string filename = "database.txt"; // File to store pupil data
    vector<Pupil> pupilsData = {      // Initial list of pupils
        {1001, "Ivan", 17, 4},
        {1002, "Elena", 15, 3},
        {1003, "Maksim", 16, 5},
        {1004, "Tatiana", 17, 4},
        {1005, "Nikolai", 18, 3},
    };

    // Load additional pupils from file and merge without duplicates
    vector<Pupil> loadedPupils = readFromFile(filename);
    for (const auto& lp : loadedPupils) {
        // Check if the ID already exists in the main list
        bool exists = any_of(pupilsData.begin(), pupilsData.end(), [&](const Pupil& p) {
            return p.student_id == lp.student_id;
        });
        if (!exists) {
            pupilsData.push_back(lp); // Add pupil if ID not found
        }
    }

    // Main program loop
    while (true) {
        cout << "\n--- Menu ---" << endl;
        cout << "1. Add Pupil" << endl;
        cout << "2. View All Pupils" << endl;
        cout << "3. Save Data to File" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cout << "Select an action: ";
        cin >> choice;

        if (cin.fail()) { // Validate menu input
            cout << "Invalid choice. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: // Add new pupil
                addObject(pupilsData);
                break;
            case 2: // Display all pupils
                displayObjects(pupilsData);
                break;
            case 3: // Save data to file
                saveToFile(pupilsData, filename);
                break;
            case 4: // Exit program
                saveToFile(pupilsData, filename); // Save before exiting
                cout << "Program terminated." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0; // End of program
}

