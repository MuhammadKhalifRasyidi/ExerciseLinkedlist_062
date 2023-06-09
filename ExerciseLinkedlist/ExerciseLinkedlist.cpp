#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode();
    bool search(int rollno, Node** rasyidi, Node** khalif);
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() {
    int rollno;
    string name;
    cout << "\nEnter roll number: ";
    cin >> rollno;
    cout << "Enter name: ";
    cin >> name;

    Node* newNode = new Node();
    newNode->rollNumber = rollno;
    newNode->name = name;

    if (listEmpty()) {
        // Beginning of the list
        newNode->next = newNode;
        LAST = newNode;
    }
    else {
        Node* rasyidi = LAST;
        Node* khalif = LAST->next;

        while (khalif != LAST && khalif->rollNumber < rollno) {
            rasyidi = khalif;
            khalif = khalif->next;
        }

        if (khalif == LAST && khalif->rollNumber < rollno) {
            // End of the list
            newNode->next = khalif->next;
            khalif->next = newNode;
            LAST = newNode;
        }
        else {
            // Between two nodes in the list
            rasyidi->next = newNode;
            newNode->next = khalif;
        }
    }
}

bool CircularLinkedList::search(int rollno, Node** rasyidi, Node** khalif) {
    *rasyidi = LAST->next;
    *khalif = LAST->next;

    while (*khalif != LAST) {
        if (rollno == (*khalif)->rollNumber) {
            return true;
        }
        *rasyidi = *khalif;
        *khalif = (*khalif)->next;
    }

    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode() {
    if (listEmpty()) {
        cout << "List is empty. Deletion failed." << endl;
        return false;
    }

    int rollno;
    cout << "\nEnter the roll number to delete: ";
    cin >> rollno;

    Node* rasyidi;
    Node* khalif;
    bool found = search(rollno, &rasyidi, &khalif);

    if (!found) {
        cout << "Node not found. Deletion failed." << endl;
        return false;
    }

    if (khalif == LAST) {
        // Beginning of the list
        if (khalif->next == LAST) {
            // If LAST points to itself
            delete khalif;
            LAST = NULL;
        }
        else {
            LAST->next = khalif->next;
            delete khalif;
        }
    }
    else {
        // Between two nodes in the list or end of the list
        rasyidi->next = khalif->next;

        if (khalif == LAST) {
            LAST = rasyidi;
        }

        delete khalif;
    }

    cout << "Node with roll number " << rollno << " deleted." << endl;
    return true;
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
    }
    else {
        cout << "\nRecords in the list are:\n";
        Node* khalifNode = LAST->next;
        while (khalifNode != LAST) {
            cout << khalifNode->rollNumber << " " << khalifNode->name << endl;
            khalifNode = khalifNode->next;
        }
        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}
int main() {
    CircularLinkedList obj;
    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-4): ";
            char ch;
            cin >> ch;
            switch (ch) { 
            case '1': {
                obj.addNode();
            }
            case '2': {
                obj.listEmpty();
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                cout << "Invalid option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}
