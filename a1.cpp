#include <iostream>

using namespace std;

struct Student
{
    int rollno;
    float sgpa;
    string name;
};

class SE
{
    struct Student list[5];
    int partitionArray(int left, int right)
    {
    }

public:
    void input();
    void display();
    void bubbleSort();
    void insertionSort();
    void searchGPA();
    void binarySearch();
    void quickSort(int left, int right);
};

int main()
{
    SE SE11;
    char choice, loop_var;
    do
    {
        cout << "What do you want to do?\nA. Input\nB. Display\nC. Bubblesort\n"
             << "D. Search for a GPA\nE. Insertion sort\nF. Search for a name (Binary Search)\n"
             << "G. Quick Sort SGPA\n>>> ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 'A':
            SE11.input();
            break;
        case 'B':
            SE11.display();
            break;
        case 'C':
            SE11.bubbleSort();
            break;
        case 'D':
            SE11.searchGPA();
            break;
        case 'E':
            SE11.insertionSort();
            break;
        case 'F':
            SE11.binarySearch();
            break;
        case 'G':
            SE11.quickSort(0, 4);
            break;
        default:
            cout << "Invalid input\t\t:(\n";
            break;
        }
        cout << "Do wou want to continue? (y/n): ";
        cin >> loop_var;

    } while (loop_var == 'y' || loop_var == 'Y');
    return 0;
}

void SE::input()
{
    for (int i = 0; i < 5; i++)
    {
        cout << "Enter the name of student " << i + 1 << " : ";
        cin >> list[i].name;
        cout << "Enter the roll no of student " << i + 1 << " : ";
        cin >> list[i].rollno;
        cout << "Enter the sgpa of student " << i + 1 << " : ";
        cin >> list[i].sgpa;
        cout << endl;
    }
    cout << '\n';
}

void SE::display()
{
    cout << "RollNo " << '\t' << "Name" << '\t' << "SGPA" << endl;
    for (struct Student var : list)
    {
        cout << var.rollno << '\t' << var.name << '\t' << var.sgpa << endl;
    }
    cout << endl;
}

void SE::bubbleSort()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if (list[j].rollno > list[j + 1].rollno)
            {
                struct Student temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

void SE::searchGPA()
{
    bool flag = false;
    float gpa;
    cout << "Enter the GPA you want to search for: ";
    cin >> gpa;
    cout << endl;
    cout << "RollNo " << '\t' << "Name" << '\t' << "SGPA" << endl;
    for (struct Student var : list)
    {
        if (var.sgpa == gpa)
        {
            cout << var.rollno << '\t' << var.name << '\t' << var.sgpa << endl;
            flag = true;
        }
    }
    if (!flag)
    {
        cout << "\nOops! No records found!\n";
    }
}

void SE::insertionSort()
{
    int j;
    for (int i = 1; i < 5; i++)
    {
        struct Student key = list[i];
        j = i - 1;

        while (j >= 0 && list[j].name > key.name)
        {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
}

void SE::binarySearch()
{
    int length = 5;
    int left = length;
    int right = 0;
    bool foundFlag = false;
    string name;
    cout << "Enter the name of the student you want to search for: ";
    cin >> name;
    insertionSort();
    while (right <= left)
    {
        int mid = (left + right) / 2;
        if (list[mid].name == name)
        {
            cout << "Found a student with name: " << name << '\n';
            cout << list[mid].rollno << '\t' << list[mid].name << '\t' << list[mid].sgpa << endl;
            foundFlag = true;
            break;
        }
        else if (list[mid].name > name)
        {
            left = mid - 1;
        }
        else
        {
            right = mid + 1;
        }
    }
    if (!foundFlag)
    {
        cout << "\nNo student with name " << name << " could be found in the records." << endl;
    }
}

void SE::quickSort(int left, int right)
{
    if (left < right)
    {
        int pivotPosition = partitionArray(left, right);
        quickSort(left, pivotPosition - 1);
        quickSort(pivotPosition + 1, right);
    }
}