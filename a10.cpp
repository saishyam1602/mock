#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Database
{
    fstream records;

public:
    Database();
    void addEntry();
    void clearFile();
    void deleteEntry();
    void displayRecord();
    void searchRecord();
    void updateEntry();
};

int main()
{
    Database cohort = Database();
    int choice;
    while (true)
    {
        cout << "1.Add Entry\n2.Delete Entry\n3.Display all entries\n4.Search for an entry\n"
             << "5.Update an entry\n6.Exit\n";
        cout << ">>> ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cohort.addEntry();
            break;
        case 2:
            cohort.deleteEntry();
            break;
        case 3:
            cohort.displayRecord();
            break;
        case 4:
            cohort.searchRecord();
            break;
        case 5:
            cohort.updateEntry();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout << "Please select a valid choice!!\n";
            break;
        }
        cout << endl;
    }
}

Database::Database()
{
    remove("stuDB.tsv");
    records.open("stuDB.tsv", ios::out);
    records << "RollNo" << '\t' << "Name" << '\t' << "Division" << '\t' << "Address" << endl;

    if (!records)
        cout << "An error occured while creating the file!\n";

    records.close();
}

void Database::clearFile()
{
    records.open("stuDB.tsv", ios::out | ios::trunc);
    records.close();
}

void Database::addEntry()
{
    int rollNo, div;
    string name, address;

    cout << "\nEnter the details of the student\n";
    cout << "Roll No: ";
    cin >> rollNo;
    while (rollNo <= 0)
    {
        cout << "Please enter a non negative or non zero value: ";
        cin >> rollNo;
    }

    cout << "Division: ";
    cin >> div;
    while (div <= 0)
    {
        cout << "Please enter a non negative or non zero value: ";
        cin >> div;
    }

    cout << "Name: ";
    cin.ignore(1);
    getline(cin, name);
    if (name.empty())
    {
        cout << "Name field can't be empty!\nName: ";
        getline(cin, name);
    }

    cout << "Address: ";
    getline(cin, address);
    if (address.empty())
    {
        cout << "Address field can't be empty!\nAddress: ";
        getline(cin, address);
    }

    records.open("stuDB.tsv", ios::out | ios::app);
    records << rollNo << '\t' << name << '\t' << div << '\t'
            << address << endl;
    records.close();
}

void Database::displayRecord()
{
    records.open("stuDB.tsv", ios::in);
    string entry, data;
    cout << endl;

    while (!records.eof())
    {
        getline(records, entry);
        stringstream row(entry);
        while (getline(row, data, '\t'))
        {
            cout << data << "\t";
        }
        cout << endl;
    }

    records.close();
}

void Database::searchRecord()
{
    records.open("stuDB.tsv", ios::in);
    string entry, data;
    int rollNo;
    bool notFound = true;

    cout << "Enter the roll no you want to search for: ";
    cin >> rollNo;
    cout << endl;

    cout << "RollNo" << '\t' << "Name" << '\t' << "Division" << '\t' << "Address";
    while (!records.eof())
    {
        getline(records, entry);
        stringstream row(entry);
        while (getline(row, data, '\t'))
        {
            if (to_string(rollNo) == data)
            {
                cout << row.str();
                notFound = false;
                continue;
            }
        }
        cout << endl;
    }

    if (notFound)
    {
        cout << "No student with roll no " << rollNo << " found";
    }

    records.close();
}

void Database::deleteEntry()
{
    fstream temp;
    int rollNo;
    string entry, data;

    records.open("stuDB.tsv", ios::in);
    temp.open("stuDB_temp.tsv", ios::out | ios::app);

    cout << "Enter the roll no whose record you want to delete: ";
    cin >> rollNo;
    cout << endl;

    while (!records.eof())
    {
        string rowArray[4];
        int index = 0;
        getline(records, entry);
        stringstream row(entry);

        while (getline(row, data, '\t'))
        {
            rowArray[index++] = data;
        }

        if (rowArray[0] != to_string(rollNo))
        {
            temp << rowArray[0] << '\t' << rowArray[1] << '\t' << rowArray[2] << '\t'
                 << rowArray[3] << endl;
        }
    }

    temp.close();
    records.close();
    remove("stuDB.tsv");
    rename("stuDB_temp.tsv", "stuDB.tsv");
}

void Database::updateEntry()
{
    fstream temp;
    int rollNo;
    string entry, data;

    records.open("stuDB.tsv", ios::in);
    temp.open("stuDB_temp.tsv", ios::out | ios::app);

    cout << "Enter the roll no whose record you want to update: ";
    cin >> rollNo;
    cout << endl;

    while (!records.eof())
    {
        string rowArray[4];
        int index = 0;
        getline(records, entry);
        stringstream row(entry);

        while (getline(row, data, '\t'))
        {
            rowArray[index++] = data;
        }

        if (rowArray[0] == to_string(rollNo))
        {
            int rollNo, div;
            string name, address;
            cout << "Enter the update record\n";

            cout << "Roll No: ";
            cin >> rollNo;
            while (rollNo <= 0)
            {
                cout << "Please enter a non negative or non zero value: ";
                cin >> rollNo;
            }

            cout << "Division: ";
            cin >> div;
            while (div <= 0)
            {
                cout << "Please enter a non negative or non zero value: ";
                cin >> div;
            }

            cout << "Name: ";
            cin.ignore(1);
            getline(cin, name);
            if (name.empty())
            {
                cout << "Name field can't be empty!\nName: ";
                getline(cin, name);
            }

            cout << "Address: ";
            getline(cin, address);
            if (address.empty())
            {
                cout << "Address field can't be empty!\nAddress: ";
                getline(cin, address);
            }

            temp << rollNo << '\t' << name << '\t' << div << '\t'
                 << address << endl;

            continue;
        }

        temp << rowArray[0] << '\t' << rowArray[1] << '\t' << rowArray[2] << '\t'
             << rowArray[3] << endl;
    }

    temp.close();
    records.close();
    remove("stuDB.tsv");
    rename("stuDB_temp.tsv", "stuDB.tsv");
}
