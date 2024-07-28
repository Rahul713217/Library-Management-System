#include <iostream>
#include <conio.h>
#include <iomanip> // For input-output manipulation
#include <cstdlib> // For system() and other standard library functions
#include <cstring> // For C-style string functions
#include <cstdio>  // For fgets
#include <fstream>
#include <windows.h> // For Windows API functions

using namespace std;

// Function to move the cursor to a specific position on the screen
void gotoxy(size_t x, size_t y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to clear the screen
void clrscr()
{
    system("cls");
}

class Book
{
    char bno[6];    // Book number
    char bname[50]; // Book name
    char aname[20]; // Author name

public:
    void createBook()
    {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nENTER BOOK NO.: ";
        cin >> bno;
        cin.ignore(); // Ignore the newline character left in the buffer
        cout << "\nENTER BOOK NAME: ";
        fgets(bname, sizeof(bname), stdin);
        bname[strcspn(bname, "\n")] = '\0'; // Remove the newline character
        cout << "\nENTER AUTHOR NAME: ";
        fgets(aname, sizeof(aname), stdin);
        aname[strcspn(aname, "\n")] = '\0'; // Remove the newline character
        cout << "\n\n\nBook Created..";
    }

    void showBook()
    {
        cout << "\nBook Number: " << bno;
        cout << "\nBook Name: " << bname;
        cout << "\nBook Author Name: " << aname;
    }

    void modifyBook()
    {
        cout << "\nBook Number: " << bno;
        cout << "\nModify Book Name: ";
        fgets(bname, sizeof(bname), stdin);
        bname[strcspn(bname, "\n")] = '\0'; // Remove the newline character
        cout << "\nModify Author's Name: ";
        fgets(aname, sizeof(aname), stdin);
        aname[strcspn(aname, "\n")] = '\0'; // Remove the newline character
    }

    char *retBno()
    {
        return bno;
    }

    void report()
    {
        cout << bno << setw(30) << bname << setw(30) << aname << endl;
    }
}; // class Book ends here

class Student
{
    char admno[6]; // Admission number
    char name[20];
    char stbno[6]; // Student book number
    size_t token;  // Number of books issued to student

public:
    void createStudent()
    {
        clrscr();
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter The Admission No.: ";
        cin >> admno;
        cin.ignore(); // Ignore the newline character left in the buffer
        cout << "Enter The Student Name: ";
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0'; // Remove the newline character
        token = 0;
        stbno[0] = '\0';
        cout << "\n\nStudent Record Created...";
    }

    void showStudent()
    {
        cout << "\nAdmission Number: " << admno;
        cout << "\nStudent Name: " << name;
        cout << "\nNo of Book Issued: " << token;
        if (token == 1)
        {
            cout << "\nBook Number: " << stbno;
        }
    }

    void modifyStudent()
    {
        cout << "\nAdmission No.: " << admno;
        cout << "\nModify Student Name: ";
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0'; // Remove the newline character
    }

    char *retAdmno()
    {
        return admno;
    }

    char *retStbno()
    {
        return stbno;
    }

    size_t retToken()
    {
        return token;
    }

    void addToken()
    {
        token = 1;
    }

    void resetToken()
    {
        token = 0;
    }

    void getStbno(char t[])
    {
        strcpy(stbno, t);
    }

    void report()
    {
        cout << "\t" << admno << setw(20) << name << setw(10) << token << endl;
    }
}; // class Student ends here

fstream fp, fp1;
Book bk;
Student st;

void writeBook()
{
    char ch;
    fp.open("book.dat", ios::out | ios::app); // write and append data
    do
    {
        clrscr();
        bk.createBook();
        fp.write(reinterpret_cast<char *>(&bk), sizeof(Book)); // size of class
        cout << "\n\nDo you want to add more records... (y/n?) ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writeStudent()
{
    char ch;
    fp.open("student.dat", ios::out | ios::app); // write and append data
    do
    {
        clrscr();
        st.createStudent();
        fp.write(reinterpret_cast<char *>(&st), sizeof(Student)); // size of class
        cout << "\n\nDo you want to add more records... (y/n?) ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void displaySpb(char n[])
{
    cout << "\nBOOK DETAILS\n";
    size_t flag = 0;              // book not found
    fp.open("book.dat", ios::in); // read data
    while (fp.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        if (strcmpi(bk.retBno(), n) == 0)
        { // not case sensitive
            bk.showBook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    { // book not found
        cout << "\n\nBook does not exist";
    }
    getch();
}

void displaySps(char n[])
{
    cout << "\nSTUDENT DETAILS\n";
    size_t flag = 0;                 // student not found
    fp.open("student.dat", ios::in); // read data
    while (fp.read(reinterpret_cast<char *>(&st), sizeof(Student)))
    {
        if (strcmpi(st.retAdmno(), n) == 0)
        { // not case sensitive
            st.showStudent();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    { // student not found
        cout << "\n\nStudent does not exist";
    }
    getch();
}

void modifyBook()
{
    char n[6];
    size_t found = 0; // search book of given data
    clrscr();
    cout << "\n\nMODIFY BOOK RECORD...";
    cout << "\n\nEnter the book no.: ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char *>(&bk), sizeof(Book)) && found == 0)
    {
        if (strcmpi(bk.retBno(), n) == 0)
        {
            bk.showBook();
            cout << "\nEnter the new details of the book";
            bk.modifyBook();
            size_t pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur); // back from current position
            fp.write(reinterpret_cast<char *>(&bk), sizeof(Book));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\n\nRecord Not Found";
    }
    getch(); // press key to get out
}

void modifyStudent()
{
    char n[6];
    size_t found = 0; // search book of given data
    clrscr();
    cout << "\n\nMODIFY STUDENT RECORD...";
    cout << "\n\nEnter the Admission no.: ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char *>(&st), sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.retAdmno(), n) == 0)
        {
            st.showStudent();
            cout << "\nEnter the new details of the student";
            st.modifyStudent();
            size_t pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur); // back from current position
            fp.write(reinterpret_cast<char *>(&st), sizeof(Student));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\n\nRecord Not Found";
    }
    getch(); // press key to get out
}

void deleteStudent()
{
    char n[6];
    size_t flag = 0;
    clrscr();
    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter the Admission no.: ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read(reinterpret_cast<char *>(&st), sizeof(Student)))
    {
        if (strcmpi(st.retAdmno(), n) != 0)
        {
            fp2.write(reinterpret_cast<char *>(&st), sizeof(Student));
        }
        else
        {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    if (flag == 1)
    {
        cout << "\n\n\tRecord Deleted";
    }
    else
    {
        cout << "\n\nRecord not found";
    }
    getch();
}

void deleteBook()
{
    char n[6];
    clrscr();
    cout << "\n\n\n\tDELETE BOOK...";
    cout << "\n\nEnter the Book no.: ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        if (strcmpi(bk.retBno(), n) != 0)
        {
            fp2.write(reinterpret_cast<char *>(&bk), sizeof(Book));
        }
    }
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat", "book.dat");
    cout << "\n\n\tRecord Deleted";
    getch();
}

void displayAllStudents()
{
    clrscr();
    fp.open("student.dat", ios::in);
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
        cout << "\n\n\n Program is closing ....";
        getch();
        exit(0);
    }
    cout << "\n\n\t\tSTUDENT LIST\n\n";
    cout << "==================================================================\n";
    cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued\n";
    cout << "==================================================================\n";
    while (fp.read(reinterpret_cast<char *>(&st), sizeof(Student)))
    {
        st.report();
    }
    fp.close();
    getch();
}

void displayAllBooks()
{
    clrscr();
    fp.open("book.dat", ios::in);
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
        cout << "\n\n\n Program is closing ....";
        getch();
        exit(0);
    }
    cout << "\n\n\t\tBook LIST\n\n";
    cout << "========================================================================\n";
    cout << "Book Number" << setw(20) << "Book Name" << setw(25) << "Author\n";
    cout << "========================================================================\n";
    while (fp.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        bk.report();
    }
    fp.close();
    getch();
}

void bookIssue()
{
    char sn[6], bn[6];
    size_t found = 0, flag = 0;
    clrscr();
    cout << "\n\nBOOK ISSUE...";
    cout << "\n\n\tEnter The student's admission no.: ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char *>(&st), sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.retAdmno(), sn) == 0)
        {
            found = 1;
            if (st.retToken() == 0)
            {
                cout << "\n\n\tEnter the book no.: ";
                cin >> bn;
                while (fp1.read(reinterpret_cast<char *>(&bk), sizeof(Book)) && flag == 0)
                {
                    if (strcmpi(bk.retBno(), bn) == 0)
                    {
                        bk.showBook();
                        flag = 1;
                        st.addToken();
                        st.getStbno(bk.retBno());
                        size_t pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write(reinterpret_cast<char *>(&st), sizeof(Student));
                        cout << "\n\n\t Book issued successfully\n\nPlease note the date of issue \n";
                        cout << "\n\n\t\tIssue Date: 13-05-2023";
                    }
                }
                if (flag == 0)
                {
                    cout << "Book no does not exist";
                }
            }
            else
            {
                cout << "You have not returned the last book";
            }
        }
    }
    if (found == 0)
    {
        cout << "Student record not exist...";
    }
    getch();
    fp.close();
    fp1.close();
}

void bookDeposit()
{
    char sn[6], bn[6];
    size_t found = 0, flag = 0;
    clrscr();
    cout << "\n\nBOOK DEPOSIT...";
    cout << "\n\n\tEnter the student's admission no.: ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char *>(&st), sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.retAdmno(), sn) == 0)
        {
            found = 1;
            if (st.retToken() == 1)
            {
                while (fp1.read(reinterpret_cast<char *>(&bk), sizeof(Book)) && flag == 0)
                {
                    if (strcmpi(bk.retBno(), st.retStbno()) == 0)
                    {
                        bk.showBook();
                        flag = 1;
                        cout << "\n\nBook deposited in no. of days: ";
                        size_t days;
                        cin >> days;
                        if (days > 15)
                        {
                            size_t fine = (days - 15) * 1;
                            cout << "\n\nFine has to be deposited Rs. " << fine;
                        }
                        st.resetToken();
                        size_t pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write(reinterpret_cast<char *>(&st), sizeof(Student));
                        cout << "\n\n\t Book deposited successfully";
                    }
                }
                if (flag == 0)
                {
                    cout << "Book no does not exist";
                }
            }
            else
            {
                cout << "No book is issued.. please check";
            }
        }
    }
    if (found == 0)
    {
        cout << "Student record not exist...";
    }
    getch();
    fp.close();
    fp1.close();
}

void intro()
{
    clrscr();
    gotoxy(35, 11);
    cout << "LIBRARY";
    gotoxy(35, 14);
    cout << "MANAGEMENT";
    gotoxy(35, 17);
    cout << "SYSTEM";
    cout << "\n\nMADE BY: YOUR NAME";
    getch();
}

void adminMenu()
{
    clrscr();
    int ch2;
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\n\t2.DISPLAY ALL STUDENT RECORD";
    cout << "\n\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD";
    cout << "\n\n\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\n\n\t5.DELETE STUDENT RECORD";
    cout << "\n\n\n\t6.CREATE BOOK";
    cout << "\n\n\n\t7.CREATE ALL BOOKS";
    cout << "\n\n\n\t8.DISPLAY SPECIFIC BOOK";
    cout << "\n\n\n\t9.MODIFY BOOK RECORD";
    cout << "\n\n\n\t10.DELETE BOOK RECORD";
    cout << "\n\n\n\t11.BACK TO MAIN MENU";
    cout << "\n\n\n\tPLEASE ENTER YOUR CHOICE(1-11)";
    cin >> ch2;
    switch (ch2)
    {
    case 1:
        writeStudent();
        break;
    case 2:
        displayAllStudents();
        break;
    case 3:
        char num[6];
        clrscr();
        cout << "\n\n\t Please enter admission no.";
        cin >> num;
        displaySps(num);
        break;
    case 4:
        modifyStudent();
        break;
    case 5:
        deleteStudent();
        break;
    case 6:
        writeBook();
        break;
    case 7:
        displayAllBooks();
        break;
    case 8:
    {
        char num[6];
        clrscr();
        cout << "\n\n\tPlease enter book no.";
        cin >> num;
        displaySpb(num);
        break;
    }
    case 9:
        modifyBook();
        break;
    case 10:
        deleteBook();
        break;
    case 11:
        return;
    default:
        cout << "Invalid choice";
    }
    adminMenu();
}

int main()
{
    int ch;
    clrscr();
    intro();
    do
    {
        clrscr();
        cout << "\n\n\n\t MAIN MENU";
        cout << "\n\n\n\t1 BOOK ISSUE";
        cout << "\n\n\n\t2 BOOK DEPOSIT";
        cout << "\n\n\n\t3 ADMINISTRATOR MENU";
        cout << "\n\n\n\t4 EXIT";
        cout << "\n\n\n\t PLEASE SELECT YOUR OPTION(1-4)";
        ch = getche() - '0'; // Convert char to int
        switch (ch)
        {
        case 1:
            bookIssue();
            break;
        case 2:
            bookDeposit();
            break;
        case 3:
            adminMenu();
            break;
        case 4:
            exit(0);
            break;
        default:
            cout << "INVALID CHOICE";
        }
    } while (ch != 4);
    return 0;
}
