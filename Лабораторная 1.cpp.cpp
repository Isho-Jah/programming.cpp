#include <iostream>
#include <string>

using namespace std;

// Structure definition
struct Node {
    string name;
    int age;
    double score;
    Node* next;
};

// Function to add a node at the beginning
void addToBeginning(Node*& head, string name, int age, double score) {
    Node* newNode = new Node{name, age, score, head};
    head = newNode;
}

// Function to add a node at the end
void addToEnd(Node*& head, string name, int age, double score) {
    Node* newNode = new Node{name, age, score, nullptr};
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to display the list
void displayList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << "Name: " << temp->name << ", Age: " << temp->age << ", Score: " << temp->score << endl;
        temp = temp->next;
    }
}

// Function to delete a node by name
void deleteByName(Node*& head, string name) {
    if (!head) return;
    
    if (head->name == name) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    
    Node* current = head;
    while (current->next && current->next->name != name) {
        current = current->next;
    }
    
    if (current->next) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;
    
    addToBeginning(head, "Alice", 25, 85.5);
    addToEnd(head, "Bob", 30, 90.0);
    addToEnd(head, "Charlie", 22, 78.3);
    
    cout << "Initial List:\n";
    displayList(head);
    
    deleteByName(head, "Bob");
    cout << "\nList after deleting Bob:\n";
    displayList(head);
    
    return 0;
}
