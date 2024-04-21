#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class library
{
private:
    struct book
    {
        string title;
        string author;
        int isbn;
        bool issued;
        string studentName;
        string studentRollNo;
        book *next;
    };

    book *head;

public:
    library()
    {
        head = NULL;
    }
    ~library() {}
    void printList();
    void insertNode();
    void deleteNode(string title1);
    int searchbook(int isbn);
    void returnBook(int isbn);
};

class Student
{
    struct Node
    {
        string name;
        string rollNo;
        int isbn;
        struct Node *next;
    };

    Node *head;

public:
    void insertNode(int isbn);
    
};

void library::insertNode()
{
    book *newNode, *nodePtr, *previousNode;
    newNode = new book;

    cout << "Title: ";
    cin.ignore(500, '\n');
    getline(cin, newNode->title);
    cout << "Author: ";
    getline(cin, newNode->author);
    cout << "ISBN: ";
    cin >> newNode->isbn;
    newNode->issued = false;

    if (!head)
    {
        head = newNode;
        newNode->next = NULL;
    }
    else
    {
        nodePtr = head;

        while ((nodePtr != NULL))
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }

        if (previousNode == NULL)
        {
            head = newNode;
            newNode->next = nodePtr;
        }
        else
        {
            previousNode->next = newNode;
            newNode->next = nodePtr;
        }
    }
}

int library::searchbook(int isbn)
{
    book *temp = head;
    int found = 0;

    while (temp != NULL)
    {
        if (isbn == temp->isbn)
        {
            cout << "Title: " << temp->title << "\n";
            cout << "Author: " << temp->author << "\n";
            cout << "ISBN: " << temp->isbn << "\n";
            cout << "Status: " << (temp->issued ? "Issued" : "Available") << "\n";
            if (temp->issued)
            {
                cout << "Issued to: " << temp->studentName << " (" << temp->studentRollNo << ")\n";
            }
            cout << endl;
            found = 1;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "Book not found in Database." << endl;
    }

    return found;
}

void library::deleteNode(string title1)
{
    book *nodePtr, *previousNode;

    if (!head)
    {
        cout << "No Entry." << endl;
        return;
    }

    if (head->title == title1)
    {
        nodePtr = head->next;
        delete head;
        head = nodePtr;
    }
    else
    {
        nodePtr = head;

        while (nodePtr != NULL && nodePtr->title != title1)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }

        if (nodePtr == NULL)
        {
            cout << "Book not found in Database." << endl;
            return;
        }

        previousNode->next = nodePtr->next;
        delete nodePtr;
    }
}

void library::printList()
{
    book *temp = head;

    if (temp == NULL)
    {
        cout << "No books in the library." << endl;
        return;
    }

    while (temp != NULL)
    {
        cout << "Title: " << temp->title << "\n";
        cout << "Author: " << temp->author << "\n";
        cout << "ISBN: " << temp->isbn << "\n";
        cout << "Status: " << (temp->issued ? "Issued" : "Available") << "\n";
        if (temp->issued)
        {
            cout << "Issued to: " << temp->studentName << " (" << temp->studentRollNo << ")\n";
        }
        cout << endl;
        temp = temp->next;
    }
}

void library::returnBook(int isbn)
{
    book *temp = head;

    while (temp != NULL)
    {
        if (temp->isbn == isbn && temp->issued)
        {
            temp->issued = false;
            temp->studentName = "";
            temp->studentRollNo = "";
            cout << "Book returned successfully." << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Book is not issued or not found." << endl;
}

void Student::insertNode(int isbn)
{
    Node *newNode = new Node;

    cout << "Student Name: ";
    cin.ignore(500, '\n');
    getline(cin, newNode->name);
    cout << "Roll No: ";
    getline(cin, newNode->rollNo);
    newNode->isbn = isbn;

    newNode->next = head;
    head = newNode;
}


int main()
{
    Student s;
    library lib;

    int choice;
    int isb;
    string title;
    int found = 0;

    do
    {
        cout << "Menu: Select your option" << endl;
        cout << "(1) Add a book to the list" << endl;
        cout << "(2) Delete a book based on Title" << endl;
        cout << "(3) Search for a book by ISBN" << endl;
        cout << "(4) List all books" << endl;
        cout << "(5) Issue a book" << endl;
        cout << "(6) Return a book" << endl;
        cout << "(7) Quit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (1 <= choice && choice <= 8)
        {
            switch (choice)
            {
            case 1:
                lib.insertNode();
                break;
            case 2:
                cout << "Enter Title of book to delete: ";
                cin.ignore(); // Clear newline character
                getline(cin, title);
                lib.deleteNode(title);
                break;
            case 3:
                cout << "Book ISBN: ";
                cin >> isb;
                found = lib.searchbook(isb);
                break;
            case 4:
                lib.printList();
                break;
            case 5:
                cout << "Enter Book ISBN: ";
                cin >> isb;
                found = lib.searchbook(isb);
                if (found == 0)
                {
                    cout << "Book not found in Database." << endl;
                }
                else
                {
                    s.insertNode(isb);
                }
                break;
            case 6:
                cout << "Enter Book ISBN: ";
                cin >> isb;
                lib.returnBook(isb);
                break;
            case 7:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Enter again." << endl;
                break;
            }
        } 
        else
        {
            cout << "Invalid choice. Enter again." << endl;
        }
        cin.ignore(); 
    } while (choice != 7);

    return 0;
}