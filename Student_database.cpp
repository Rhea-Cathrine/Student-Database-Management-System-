#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <limits>
#include <cstdio>

using namespace std;

const string FILENAME = "studentRecord.txt";
const string TEMP_FILENAME = "tempRecord.txt";
const string DELIMITER = "|||";

/* Email Validation */
bool isValidEmail(string email)
{
    int at = -1;
    int dot = -1;

    for (int i = 0; i < (int)email.length(); i++)
    {
        if (email[i] == '@')
            at = i;

        if (email[i] == '.')
            dot = i;
    }

    if (at > 0 && dot > at + 1 && dot < (int)email.length() - 1)
        return true;

    return false;
}

/* Roll Number Validation */
bool isValidRollNo(string roll_no)
{
    if (roll_no.length() < 3 || roll_no.length() > 20)
        return false;

    for (int i = 0; i < (int)roll_no.length(); i++)
    {
        if (!((roll_no[i] >= 'A' && roll_no[i] <= 'Z') ||
              (roll_no[i] >= 'a' && roll_no[i] <= 'z') ||
              (roll_no[i] >= '0' && roll_no[i] <= '9')))
        {
            return false;
        }
    }

    return true;
}

/* Contact Number Validation */
bool isValidContactNo(long long contact_no)
{
    return contact_no >= 1000000000LL &&
           contact_no <= 9999999999LL;
}


class Student
{
private:

    string name;
    string roll_no;
    string course;
    string address;
    string email_id;

    long long contact_no;

    void getValidContactNo()
    {
        while (true)
        {
            cout << "\tEnter Contact No (10 digits): ";
            cin >> contact_no;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');

                cout << "\tInvalid input. Please enter numbers only.\n";
                continue;
            }

            if (isValidContactNo(contact_no))
            {
                break;
            }

            cout << "\tInvalid Contact Number! "
                 << "Please enter a valid 10-digit number.\n";
        }
    }


public:

    void menu();
    void insert();
    void display();
    void modify();
    void search();
    void deleteStudent();
};


/* MENU */
void Student::menu()
{
    int choice;
    char x;

    while (true)
    {
        cout << "\n\n";
        cout << "\t\t\t-----------------------------\n";
        cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM |\n";
        cout << "\t\t\t-----------------------------\n";

        cout << "\t\t\t 1. Enter New Record\n";
        cout << "\t\t\t 2. Display Record\n";
        cout << "\t\t\t 3. Modify Record\n";
        cout << "\t\t\t 4. Search Record\n";
        cout << "\t\t\t 5. Delete Record\n";
        cout << "\t\t\t 6. Exit\n";

        cout << "\n\t\t\tChoose an Option: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }

        switch (choice)
        {
        case 1:

            do
            {
                insert();

                cout << "\n\n\t\t\tAdd Another Student Record (Y/N): ";
                cin >> x;

            } while (x == 'y' || x == 'Y');

            break;


        case 2:

            display();

            cout << "\n\t\t\tPress Enter to continue...";
            cin.ignore(10000, '\n');
            cin.get();

            break;


        case 3:

            modify();

            cout << "\n\t\t\tPress Enter to continue...";
            cin.ignore(10000, '\n');
            cin.get();

            break;


        case 4:

            search();

            cout << "\n\t\t\tPress Enter to continue...";
            cin.ignore(10000, '\n');
            cin.get();

            break;


        case 5:

            deleteStudent();

            cout << "\n\t\t\tPress Enter to continue...";
            cin.ignore(10000, '\n');
            cin.get();

            break;


        case 6:

            cout << "\n\t\t\tExiting Program...\n";
            exit(0);


        default:

            cout << "\n\t\t\tInvalid Choice... Try Again.\n";

            cout << "\n\t\t\tPress Enter to continue...";
            cin.ignore(10000, '\n');
            cin.get();

            break;
        }
    }
}


/* INSERT STUDENT */
void Student::insert()
{
    fstream file;

    cin.ignore(10000, '\n');

    cout << "\n\tEnter Name: ";
    getline(cin, name);


    do
    {
        cout << "\tEnter Roll No.: ";
        getline(cin, roll_no);

        if (!isValidRollNo(roll_no))
        {
            cout << "\tInvalid Roll Number! Try Again.\n";
        }

    } while (!isValidRollNo(roll_no));


    cout << "\tEnter Course: ";
    getline(cin, course);


    do
    {
        cout << "\tEnter Email Id: ";
        getline(cin, email_id);

        if (!isValidEmail(email_id))
        {
            cout << "\tInvalid Email! Try Again.\n";
        }

    } while (!isValidEmail(email_id));


    getValidContactNo();

    cin.ignore(10000, '\n');

    cout << "\tEnter Address: ";
    getline(cin, address);


    file.open(FILENAME.c_str(), ios::app);

    if (!file)
    {
        cout << "\n\tError opening file for writing!\n";
        return;
    }


    file << name << DELIMITER
         << roll_no << DELIMITER
         << course << DELIMITER
         << email_id << DELIMITER
         << contact_no << DELIMITER
         << address << "\n";


    file.close();

    cout << "\n\t\t\tRecord Added Successfully!\n";
}


/* DISPLAY STUDENTS */
void Student::display()
{
    fstream file;

    file.open(FILENAME.c_str(), ios::in);

    if (!file)
    {
        cout << "\n\t\tNo Data is Present...\n";
        return;
    }


    int total = 0;
    string line;


    while (getline(file, line))
    {
        string data[6];

        int field = 0;

        size_t pos;


        while ((pos = line.find(DELIMITER)) != string::npos)
        {
            data[field] = line.substr(0, pos);

            line.erase(0, pos + DELIMITER.length());

            field++;
        }


        data[5] = line;


        cout << "\n\tStudent No.: " << ++total;
        cout << "\n\tName: " << data[0];
        cout << "\n\tRoll No.: " << data[1];
        cout << "\n\tCourse: " << data[2];
        cout << "\n\tEmail Id: " << data[3];
        cout << "\n\tContact No.: " << data[4];
        cout << "\n\tAddress: " << data[5];

        cout << "\n";
    }


    if (total == 0)
    {
        cout << "\n\t\tNo Data Found...\n";
    }


    file.close();
}


/* MODIFY STUDENT */
void Student::modify()
{
    fstream file;
    fstream file1;

    string rollno;

    int found = 0;


    cout << "\n--------------------------------------------------\n";
    cout << "              STUDENT MODIFY DETAILS\n";
    cout << "--------------------------------------------------\n";


    file.open(FILENAME.c_str(), ios::in);

    if (!file)
    {
        cout << "\n\t\tNo Data is Present..\n";
        return;
    }


    cout << "\nEnter Roll No. of Student which you want to Modify: ";
    cin >> rollno;


    file1.open(TEMP_FILENAME.c_str(), ios::out);


    string line;


    while (getline(file, line))
    {
        string originalLine = line;

        size_t first_delim = line.find(DELIMITER);

        string current_roll;


        if (first_delim != string::npos)
        {
            current_roll = line.substr(0, first_delim);
        }


        if (rollno != current_roll)
        {
            file1 << originalLine << "\n";
        }

        else
        {
            string data[6];

            int field = 0;

            size_t pos;


            while ((pos = line.find(DELIMITER)) != string::npos)
            {
                data[field] = line.substr(0, pos);

                line.erase(0, pos + DELIMITER.length());

                field++;
            }


            data[5] = line;


            cout << "\n\t\t\tCurrent Details:\n";

            cout << "\t\t\tName: " << data[0] << "\n";
            cout << "\t\t\tRoll No.: " << data[1] << "\n";
            cout << "\t\t\tCourse: " << data[2] << "\n";
            cout << "\t\t\tEmail Id: " << data[3] << "\n";
            cout << "\t\t\tContact No.: " << data[4] << "\n";
            cout << "\t\t\tAddress: " << data[5] << "\n";


            cin.ignore(10000, '\n');


            cout << "\n\t\t\tEnter New Details:\n";


            cout << "\t\t\tEnter Name: ";
            getline(cin, name);


            do
            {
                cout << "\t\t\tEnter Roll No.: ";
                getline(cin, roll_no);

                if (!isValidRollNo(roll_no))
                {
                    cout << "\t\t\tInvalid Roll Number! Try Again.\n";
                }

            } while (!isValidRollNo(roll_no));


            cout << "\t\t\tEnter Course: ";
            getline(cin, course);


            do
            {
                cout << "\t\t\tEnter Email Id: ";
                getline(cin, email_id);

                if (!isValidEmail(email_id))
                {
                    cout << "\t\t\tInvalid Email! Try Again.\n";
                }

            } while (!isValidEmail(email_id));


            getValidContactNo();

            cin.ignore(10000, '\n');


            cout << "\t\t\tEnter Address: ";
            getline(cin, address);


            file1 << name << DELIMITER
                  << roll_no << DELIMITER
                  << course << DELIMITER
                  << email_id << DELIMITER
                  << contact_no << DELIMITER
                  << address << "\n";


            found++;

            cout << "\n\t\t\tRecord Updated Successfully!\n";
        }
    }


    if (found == 0)
    {
        cout << "\n\t\t\tStudent Roll No. Not Found....\n";
    }


    file.close();
    file1.close();


    remove(FILENAME.c_str());

    rename(TEMP_FILENAME.c_str(), FILENAME.c_str());
}


/* SEARCH STUDENT */
void Student::search()
{
    fstream file;

    int found = 0;


    file.open(FILENAME.c_str(), ios::in);


    if (!file)
    {
        cout << "\n\t\t\tNo Data is Present...\n";
        return;
    }


    string rollno;

    cout << "\n--------------------------------------------------\n";
    cout << "              STUDENT SEARCH\n";
    cout << "--------------------------------------------------\n";


    cout << "\nEnter Roll No. of Student which you want to search: ";
    cin >> rollno;


    string line;


    while (getline(file, line))
    {
        string data[6];

        int field = 0;

        size_t pos;


        while ((pos = line.find(DELIMITER)) != string::npos)
        {
            data[field] = line.substr(0, pos);

            line.erase(0, pos + DELIMITER.length());

            field++;
        }


        data[5] = line;


        if (rollno == data[1])
        {
            cout << "\n\t\t\tName: " << data[0];
            cout << "\n\t\t\tRoll No.: " << data[1];
            cout << "\n\t\t\tCourse: " << data[2];
            cout << "\n\t\t\tEmail Id: " << data[3];
            cout << "\n\t\t\tContact No.: " << data[4];
            cout << "\n\t\t\tAddress: " << data[5];

            cout << "\n";

            found = 1;

            break;
        }
    }


    if (found == 0)
    {
        cout << "\n\t\t\tStudent Roll No. Not Found....\n";
    }


    file.close();
}


/* DELETE STUDENT */
void Student::deleteStudent()
{
    fstream file;
    fstream file1;

    string roll;

    int found = 0;


    cout << "\n--------------------------------------------------\n";
    cout << "              DELETE STUDENT DETAILS\n";
    cout << "--------------------------------------------------\n";


    file.open(FILENAME.c_str(), ios::in);


    if (!file)
    {
        cout << "\n\t\t\tNo Data is Present..\n";
        return;
    }


    cout << "\nEnter Roll No. of Student which you want to Delete Data: ";
    cin >> roll;


    char confirm;

    cout << "\n\t\tAre you sure you want to delete this record? (Y/N): ";
    cin >> confirm;


    if (confirm != 'Y' && confirm != 'y')
    {
        cout << "\n\t\tDeletion cancelled.\n";

        file.close();

        return;
    }


    file1.open(TEMP_FILENAME.c_str(), ios::out);


    string line;


    while (getline(file, line))
    {
        size_t pos = line.find(DELIMITER);


        if (pos != string::npos)
        {
            string current_roll = line.substr(0, pos);


            if (roll != current_roll)
            {
                file1 << line << "\n";
            }

            else
            {
                found++;
            }
        }
    }


    file.close();
    file1.close();


    remove(FILENAME.c_str());

    rename(TEMP_FILENAME.c_str(), FILENAME.c_str());


    if (found == 0)
    {
        cout << "\n\t\t\tStudent Roll No. Not Found....\n";
    }

    else
    {
        cout << "\n\t\t\tSuccessfully Deleted Data\n";
    }
}


/* MAIN FUNCTION */
int main()
{
    Student project;

    project.menu();

    return 0;
}

