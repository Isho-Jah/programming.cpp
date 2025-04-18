#include <iostream>
#include <string>

using namespace std;

// Class representing a person (a node in the linked list)
class Person {
public:
    string name;       // Person's name
    int age;           // Person's age
    double salary;     // Person's salary
    Person* next;      // Pointer to the next person in the list

    // Constructor to initialize the person object
    Person(string name, int age, double salary)
        : name(name), age(age), salary(salary), next(nullptr) {}
};

// Class representing the linked list of people
class PersonList {
private:
    Person* head;  // Pointer to the first element of the list

public:
    // Constructor initializes the list to be empty
    PersonList() : head(nullptr) {}

    // Destructor to free memory of all nodes
    ~PersonList() {
        while (head != nullptr) {
            Person* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Add a person to the beginning of the list
    void addToBeginning(string name, int age, double salary) {
        Person* newNode = new Person(name, age, salary);
        newNode->next = head;
        head = newNode;
    }

    // Add a person to the end of the list
    void addToEnd(string name, int age, double salary) {
        Person* newNode = new Person(name, age, salary);

        if (head == nullptr) {
            // If list is empty, new node becomes the head
            head = newNode;
        }
        else {
            // Traverse to the last node
            Person* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Add a person after a given person's name
    void addAfter(string targetName, string name, int age, double salary) {
        Person* temp = head;

        // Search for the target name
        while (temp != nullptr && temp->name != targetName) {
            temp = temp->next;
        }

        if (temp != nullptr) {
            // Target found, insert new node after it
            Person* newNode = new Person(name, age, salary);
            newNode->next = temp->next;
            temp->next = newNode;
        }
        else {
            cout << "Person with the name " << targetName << " not found." << endl;
        }
    }

    // Add a person before a given person's name
    void addBefore(string targetName, string name, int age, double salary) {
        if (head == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }

        // If the target is the head, add to beginning
        if (head->name == targetName) {
            addToBeginning(name, age, salary);
            return;
        }

        // Traverse the list looking for the node before the target
        Person* temp = head;
        while (temp->next != nullptr && temp->next->name != targetName) {
            temp = temp->next;
        }

        if (temp->next != nullptr) {
            // Target found, insert new node before it
            Person* newNode = new Person(name, age, salary);
            newNode->next = temp->next;
            temp->next = newNode;
        }
        else {
            cout << "Person with the name " << targetName << " not found." << endl;
        }
    }

    // Delete a person by their name
    void deleteByName(string targetName) {
        if (head == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }

        // If the head is the target
        if (head->name == targetName) {
            Person* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Search for the node before the one to delete
        Person* temp = head;
        while (temp->next != nullptr && temp->next->name != targetName) {
            temp = temp->next;
        }

        if (temp->next != nullptr) {
            // Target found, delete it
            Person* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            delete nodeToDelete;
        }
        else {
            cout << "Person with the name " << targetName << " not found." << endl;
        }
    }

    // Print the entire list
    void printList() const {
        Person* temp = head;
        while (temp != nullptr) {
            cout << "Name: " << temp->name
                 << ", Age: " << temp->age
                 << ", Salary: " << temp->salary << endl;
            temp = temp->next;
        }
    }
};

// Main function
int main() {
    PersonList list;  // Create a list of persons

    // Add persons to the list
    list.addToEnd("Nikolay", 30, 50500);
    list.addToBeginning("Anton", 25, 45000);
    list.addToEnd("Konstantin", 23, 25000);

    // Display the list after adding elements
    cout << "List after adding people:" << endl;
    list.printList();

    // Add a new person after "Anton"
    list.addAfter("Anton", "Alexey", 22, 40000);
    cout << "\nList after adding a person after Anton:" << endl;
    list.printList();

    // Add a new person before "Konstantin"
    list.addBefore("Konstantin", "Olga", 27, 52000);
    cout << "\nList after adding a person before Konstantin:" << endl;
    list.printList();

    // Delete a person by name
    list.deleteByName("Anton");
    cout << "\nList after deleting Anton:" << endl;
    list.printList();

    return 0;
}
