#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student
 {
private:
    int rollNo;
    string name;
    float marks;

public:
    Student() : rollNo(0), marks(0.0) {}

    void inputDetails()
     {
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin>>name;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void displayDetails() const 
    {
        cout << "Roll Number: " << rollNo << "\nName: " << name << "\nMarks: " << marks << endl;
    }

    void saveToFile(ofstream &outfile) const 
    {
        outfile << rollNo << "\n" << name << "\n" << marks << "\n";
    }

    void loadFromFile(ifstream &infile)
     {
        infile >> rollNo;
        infile>>name;
        infile >> marks;
    }

    int getRollNo() const 
    {
        return rollNo;
    }
};

void addStudent(const string &filename)
 {
    Student s;
    s.inputDetails();

    ofstream outfile(filename, ios::app);
    if (!outfile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    s.saveToFile(outfile);
    outfile.close();
    cout << "Student added successfully!" << endl;
}

void displayAllStudents(const string &filename) 
{
    ifstream infile(filename);
    if (!infile)
     {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    Student s;
    bool hasRecords = false;

    while (true)
     {
        s.loadFromFile(infile);
        if (infile.eof()) 
        break; 

        s.displayDetails();
        cout << "-----------------------\n";
        hasRecords = true;
    }

    infile.close();

    if (!hasRecords) 
    {
        cout << "No records found in the file." << endl;
    }
}

void searchStudent(const string &filename)
 {
    int rollNo;
    cout << "Enter Roll Number to search: ";
    cin >> rollNo;

    ifstream infile(filename);
    if (!infile) 
    {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    Student s;
    bool found = false;
    while (infile.peek() != EOF)
     {
        s.loadFromFile(infile);
        if (s.getRollNo() == rollNo)
         {
            cout << "Student Found:\n";
            s.displayDetails();
            found = true;
            break;
        }
    }
    infile.close();

    if (!found)
     {
        cout << "Student with Roll Number " << rollNo << " not found." << endl;
    }
}

int main() 
{
    string filename = "students.txt";
    int choice;

    do 
    {
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                addStudent(filename);
                break;
            case 2:
                displayAllStudents(filename);
                break;
            case 3:
                searchStudent(filename);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}