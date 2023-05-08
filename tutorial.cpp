
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <fstream>
#define FLBCLAS "SeniorHighSchool.txt"
#define FLBSTUD "CandidateInfo.txt"

using namespace std;


char* strTitle(int x) {       //Coverting Title from Integer to readable text
    static char title[8] = " ";
    if (x == 1)
        strcpy_s(title, "Master");
    else if (x == 2)
        strcpy_s(title, "Mr");
    else
        strcpy_s(title, "Miss");
    return title;
}
char* strGender(int y) {        //Coverting Gender from Integer to readable text
    static char gender[8] = " ";
    if (y == 1)
        strcpy_s(gender, "Male");
    else if (y == 2)
        strcpy_s(gender, "Female");
    else
        strcpy_s(gender, "N/A");
    return gender;
}
char* strStatus(int b) {        //Coverting Gender from Integer to readable text
    static char status[8] = " ";
    if (b == 1)
        strcpy_s(status, "Boarder");
    else if (b == 2)
        strcpy_s(status, "Day");
    return status;
}


class CandidateInfo {           //Student class for storing Records in the student file
    char candidateName[30];
    int title;  //Master  = 1, Mr = 2, Miss = 3
    int gender;  //male = 1, female = 2, N/A =3
    int indexNumber;
    char fatherName[30];
    char motherName[30];
    char schoolName[90];
    char address[80];
    int phoneNumber;
    char shs[100];
    char programName[100];
    int status;
    int grade;

public:
    void categoryA(void);
    void categoryB(void);
    void categoryC(void);
    void categoryD(void);
    void getDetails(void);
    void printDetails(void)
    {
        cout << "Candidate Name" << strTitle(title) << " " << candidateName << endl;
        cout << "Gender :" << strGender(gender) << endl;
        cout << "Phone number:" << phoneNumber << endl;
        cout << "Name of JHS :" << schoolName << endl;
        cout << "Index Number    : " << indexNumber << endl;
        cout << "Father's Name : " << fatherName << endl;
        cout << "Mother's Name : " << motherName << endl;
        cout << "Address       : " << address << endl;
        cout << "Name of JHS :" << schoolName << endl;
        cout << "Grade: " << grade << endl;
        cout << "Status: " << strStatus(status) << endl;
    }
    int retIndexNumber() {       //Return Roll No
        return indexNumber;
    }
    char* retString(char x) {   //Return all strings avaialable from the Student Class
        if (x == 'T')
            return strTitle(title);
        if (x == 'N')
            return candidateName;
        if (x == 'F')
            return fatherName;
        if (x == 'M')
            return motherName;
        if (x == 'A')
            return address;
        if (x == 'P')
            return programName;
        if (x == 'S')
            return strStatus(status);
        if (x == 'G')
            return strGender(gender);
    }
    char* retCandidateName() {    //Returns Student Name
        return retString('N');
    }
    void modDetail(char ch);    //Modify Details for Student
};
void CandidateInfo::getDetails() {     //Get Student Details from user
    system("CLS");
    cout << "Enter Title \n(Master = 1, Mr = 2, Miss = 3)  : ";
    do {
        cin >> title;
    } while (title != 1 && title != 2 && title != 3);
    cout << "Enter Title \n(Male = 1, Female = 2, N/A = 3)  : ";
    do {
        cin >> gender;
    } while (gender != 1 && gender != 2 && gender != 3);

    cout << "Enter Candidate Name    : ";
    do {
        cin >> candidateName;
    } while (strlen(candidateName) == 0);
    cout << "Enter Index Number        : ";
    do {
        cin >> indexNumber;
    } while (indexNumber < 1);
    cout << "Enter Father Name     : ";
    do {
        cin >> fatherName;
    } while (strlen(fatherName) == 0);
    cout << "Enter Mother Name     : ";
    do {
        cin >> motherName;
    } while (strlen(motherName) == 0);
    cout << "Enter Address         : ";
    do {
        cin >> address;
    } while (strlen(address) == 0);
    cout << "Enter Your Phone Number: ";
    cin >> phoneNumber;
    cout << "Enter Your JHS: ";
    do {
        cin >> schoolName;
    } while (strlen(schoolName) == 0);
    cout << "Enter Status \n(Boarder = 1, Day = 2)  : ";
    do {
        cin >> status;
    } while (status != 1 && status != 2);
    cout << "Enter your grade: ";
    cin >> grade;
}
void CandidateInfo::modDetail(char ch) { //Modify Details for Student
    system("CLS");
    if (ch == 'T') {          //Argument will tell which detail to modify
        cout << "Enter Title \n(Master = 1, Mr = 2, Miss = 3)  : ";
        do {
            cin >> title;
        } while (title != 1 && title != 2 && title != 3);
    }
    else if (ch == 'N') {
        cout << "Enter Student Name    : ";
        do {
            cin >> candidateName;
        } while (strlen(candidateName) == 0);
    }
    else if (ch == 'R') {
        int r = indexNumber;          //Save current Roll No.
        cout << "Enter Roll No.        : ";
        fstream fl(FLBSTUD, ios::in | ios::binary);
        CandidateInfo obj;
        do {
            cin >> indexNumber;
            fl.close();
            fl.open(FLBSTUD, ios::in | ios::binary);
            while (!fl.eof()) {
                fl.read((char*)&obj, sizeof(obj));
                if (fl.eof())
                    break;
                if (obj.retIndexNumber() == indexNumber && r != indexNumber) {  //Check if the new rollNo already exists
                    cout << "\nSame Roll No. Already Exists !\n";
                    cout << "Enter Roll No.        : ";
                    indexNumber = -1;
                }
            }
        } while (indexNumber < 1);
        fl.close();
    }
    else if (ch == 'F') {
        cout << "Enter Father Name     : ";
        do {
            cin >> fatherName;
        } while (strlen(fatherName) == 0);
    }
    else if (ch == 'M') {
        cout << "Enter Mother Name     : ";
        do {
            cin >> motherName;
        } while (strlen(motherName) == 0);
    }
    else if (ch == 'A') {
        cout << "Enter Address         : ";
        do {
            cin >> address;
        } while (strlen(address) == 0);
    }

}

void CandidateRegistration() {             //Insert Class Record in File
    system("CLS");
    CandidateInfo obj, obj2;
    char ch;
    int v = 0;
    cout << "Enter the candidate Index Number: \n";
    obj.getDetails();
    obj.categoryD();
    obj.categoryC();
    obj.categoryB();
    obj.categoryA();
    fstream fl1(FLBSTUD, ios::in | ios::binary);
    ofstream fl2;
    if (!fl1) {               //Create new file if it does not exist
        fl2.open(FLBSTUD, ios::out | ios::binary);
        fl2.write((char*)&obj, sizeof(obj));
        fl2.close();
        return;
    }
    while (!fl1.eof()) {
        fl1.read((char*)&obj2, sizeof(obj));
        if (fl1.eof()) {
            break;
        }
        if (obj.retIndexNumber() == obj2.retIndexNumber()) {    //Abort if same Roll No already exists
            cout << "Record with same Roll No. with following details already exists : \n";
            obj2.printDetails();
            cout << "Registration Aborted !\n";
            return;
        }
        else if (_strcmpi(obj.retCandidateName(), obj2.retCandidateName()) == 0) {
            if (!v)                 //Warns user if record with same Roll No. Already Exists
                cout << "Warning : Record with same name exists with follwing details : \n";
            obj2.printDetails();
            cout << '\n';
            v = 1;
        }
    }
    if (v) {                  //Asks for confirmation after warning
        cout << "Do you still wish to insert record (Y/N) ? ";
        do {
            cin >> ch;
            ch = toupper(ch);
        } while (ch != 'Y' && ch != 'N');
        if (ch == 'N') {
            cout << "Registration Aborted !\n";
            return;
        }
    }
    fl2.open(FLBSTUD, ios::out | ios::app | ios::binary);
    fl2.seekp(0, ios::end);
    fl2.write((char*)&obj, sizeof(obj));
    fl2.close();
}


int searchStudentID(const string str = "search") { //Search Student by Attributes
    system("CLS");
    fstream fl(FLBSTUD, ios::in | ios::ate | ios::binary);
    if ((!fl) || fl.tellg() == 0) {           //If file is empty or zero size
        cout << " No Records Found !\n";
        return 0;
    }
    fl.close();
    fl.open(FLBSTUD, ios::in | ios::binary);
    char ch;
    char query[30];
    CandidateInfo obj;
    int found = 0;
    cout << "Enter Attribute to " << str << " :\n";
    cout << "  (T)itle.\n";
    cout << "  (N)ame of Candidate.\n";
    cout << "  (F)ather's Name.\n";
    cout << "  (M)other's Name.\n";
    cout << "  (A)ddress.\n";
    cout << "Enter your choice : ";
    do {
        cin >> ch;
        ch = toupper(ch);
    } while (ch != 'T' && ch != 'N' && ch != 'F' && ch != 'M' && ch != 'A');
    cout << "\nEnter Query : ";
    do {
        cin >> query;
    } while (strlen(query) == 0);
    while (!fl.eof()) {
        fl.read((char*)&obj, sizeof(obj));
        if (fl.eof()) {
            break;
        }
        if ((_strcmpi(query, obj.retString(ch)) == 0)) {
            if (!found)
                cout << "\nSearch Results : \n\n";
            obj.printDetails();
        }
    }
    if (!found)
        cout << "No Records Found !\n";
    fl.close();
    return found;
}

void CandidateInfo::categoryA()
{
    int  choice;
    if (grade >= 6 || grade <= 12)
        do
        {
            cout << "\t1. Prempeh College \n";
            cout << "\t2. OpokuWare School \n";
            cout << "\t3. Wesley  Girls College \n";
            cout << "\t4.  Presbyterians Boys SHS \n";
            cout << "\t5.  St Louis College \n";
            cout << "\t6.  Achimota SHS \n";
            cout << "\nEnter your option: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Congratulations you have Gain admission into Prempeh College.\n" << endl;
                break;
            case 2:
                cout << "Congratulations you have Gain admission into OpokuWare School.\n" << endl;
                break;
            case 3:
                cout << "Congratulations you have Gain admission into Wesley Girls Shs.\n" << endl;
                break;
            case 4:
                cout << "Congratulations you have Gain admission into Presbyterians Boys SHS.\n" << endl;
                break;
            case 5:
                cout << "Congratulations you have Gain admission into St Louis College.\n" << endl;
                break;
            case 6:
                cout << "Congratulations you have Gain admission into Achimota SHS.\n" << endl;
                break;
            }

        } while (choice != 0);
}

void CandidateInfo::categoryB()
{
    int  choice;
    if (grade >= 12 || grade <= 20)
        do
        {

            cout << "\t\t\tYou can only select one school from this category ";

            cout << "\t1. Konogo Odumasi SHS \n";
            cout << "\t2. Mawuli School \n";
            cout << "\t3. Temale SHS \n";
            cout << "\t4. Anglican SHS\n";
            cout << "\t5. Toase  SHS \n";
            cout << "\t6. West Africa SHS  \n";
            cout << "\nEnter your option: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Congratulations you have Gain admission into  Konogo Odumasi SHS.\n" << endl;
                break;
            case 2:
                cout << "Congratulations you have Gain admission into Mawuli School.\n" << endl;
                break;
            case 3:
                cout << "Congratulations you have Gain admission into  Temale SHS .\n" << endl;
                break;
            case 4:
                cout << "Congratulations you have Gain admission into Anglican SHS.\n" << endl;
                break;
            case 5:
                cout << "Congratulations you have Gain admission into Toase  SHS.\n" << endl;
                break;
            case 6:
                cout << "Congratulations you have Gain admission into  West Africa SHS.\n" << endl;
                break;
            }

        } while (choice != 0);
}
void CandidateInfo::categoryC()
{
    int choice;
    if (grade >= 20 || grade <= 27)
        do
        {

            cout << "\t\t\tYou can only select one school from this category ";
            cout << "\t1. Ejisuman SHS \n";
            cout << "\t2. Nkawie SHS \n";
            cout << "\t3. Sekyere Odumasi SHS \n";
            cout << "\t4.  Achina Krom SHS \n";
            cout << "\t5.  Bonwire SHS\n";
            cout << "\t6.  Antoa SHS \n";
            cout << "\nEnter your option: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Congratulations you have Gain admission into  Ejisuman SHS.\n" << endl;
                break;
            case 2:
                cout << "Congratulations you have Gain admission into  Nkawie SHS .\n" << endl;
                break;
            case 3:
                cout << "Congratulations you have Gain admission into Sekyere Odumasi SHS.\n" << endl;
                break;
            case 4:
                cout << "Congratulations you have Gain admission into  Achina Krom SHS.\n" << endl;
                break;
            case 5:
                cout << "Congratulations you have Gain admission into Bonwire SHS.\n" << endl;
                break;
            case 6:
                cout << "Congratulations you have Gain admission into  Antoa SHS.\n" << endl;
                break;
            }

        } while (choice != 0);
}
void CandidateInfo::categoryD()
{
    int choice;
    if (grade >= 28 || grade <= 35)

        do
        {
            cout << "\t\t\tCategory D is your Day school ";
            cout << "\t\t Candidate will be automatically selected as day student ";
            cout << "\t1. Esasaase Bontefofo SHS \n";
            cout << "\t2. Atia Community Day SHS\n";
            cout << "\t3. Adutwaman Community Day SHS \n";
            cout << "\t4. Bonkra Community Day SHS \n";
            cout << "\t5. Ejisu Techical SHS\n";
            cout << "\t6.  Chrisic SHS \n";
            cout << "\nEnter your option: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Congratulations you have Gain admission into Esasaase Bontefofo SHS.\n" << endl;
                break;
            case 2:
                cout << "Congratulations you have Gain admission into Atia Community Day SHS.\n" << endl;
                break;
            case 3:
                cout << "Congratulations you have Gain admission into Adutwaman Community Day.\n" << endl;
                break;
            case 4:
                cout << "Congratulations you have Gain admission into Bonkra Community Day SHS.\n" << endl;
                break;
            case 5:
                cout << "Congratulations you have Gain admission into Ejisu Techical SHS.\n" << endl;
                break;
            case 6:
                cout << "Congratulations you have Gain admission into Chrisic SHS.\n" << endl;
                break;
            }

        } while (choice != 0);
}

int main()
{
    char ch;
    char ch1;
    int ch2;
    do {
        cout << "\t\t\t   School Placement System By Group 14";
        cout << "\t1. Candidate Database Management.\n";
        cout << "\t2. School  Database Management.\n";
        cout << "\t0. Exit.\n\n";
        cout << "Enter your choice : ";
        cin >> ch1;
        if (ch1 == '1')
        {
            do {
                cout << "\t\t\t    School Placement System";
                cout << "\t\t\tCandidateDatabase Management System";
                cout << "\t1.  Register .\n";
                cout << "\t2.  Search for a student\n";
                cout << "\t3.  Modify a Record.\n";
                cout << "\t0.  Exit.\n";
                cout << "\nEnter your choice : ";
                cin >> ch2;
                switch (ch2) {
                case 1:
                    CandidateRegistration();
                    break;
                case 2:
                    searchStudentID();
                    break;
                case 3:
                    //  modEntry('S');
                    break;
                }
                if (ch2)
                    cin >> ch;
            } while (ch2 != 0);
        }
        if (ch1 == '2') {

            do {
                cout << "\t\t\t     School Placement System";
                cout << "\t\t School  Management System";
                cout << "\t1.  Add School.\n";
                cout << "\t2.  Modify school.\n";
                cin >> ch2;
                switch (ch2) {
                case 1:
                    // AddSchool();
                    break;
                case 2:

                    break;
                }
                if (ch2)
                    cin >> ch;
                else {

                }
            } while (ch2 != 0);
        }
    } while (ch1 != '0');

    return 0;
}
