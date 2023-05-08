#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>
#include<ctype.h>

#define FBSTUD "CandidateInfo.txt"
#define FBCLASS "School.txt"

using namespace std;

char *strTitle(int x)
{
  static char title[8] = " ";
  if(x==1)
    strcpy(title, "Master");
  else if(x==2)
    strcpy(title, "Mr");
  else
    strcpy(title, "Miss");
}

char *strGender(int y)
{
  static char gender[8] = " ";
  if(y==1)
    strcpy(gender, "Male");
  else if(y==2)
    strcpy(gender, "Female");
  else
    strcpy(gender, "N/A");
}

char *strStatus(int z)
{
  static char status[8] = " ";
  if(z==1)
    strcpy(status, "Boarder");
  else
    strcpy(status, "Day");
}


class CandidateInfo
{
  char candidateName[100];
  int gender;
  int status;
  int title;
  char shs[200];
  char programName[100];
  int indexNumber;
  int grade;

public:
  void printDetails()
  {
    cout << "Candidate Name" << strTitle(title) << " " << candidateName << endl;
    cout << "Status: " << strStatus(status) << status << endl;
    cout << "Gender: " << strGender(gender) << gender << endl;
    cout << "Grade: " << grade << endl;
    cout << "Program : " << programName << endl;
    cout << "Name of Jhs: " << shs << endl;
    cout << "Index Number: " << indexNumber << endl;
    cout << "Grade : " << grade << endl;
    }
    int retIndexNumber()
    {
      return indexNumber;
    }
    char *retString(char x)
    {
      if(x=='T')
        return strTitle(title);
      if(x=='S')
        return strStatus(status);
      if(x=='G')
        return strGender(gender);
      if(x=='N')
        return candidateName;
      if(x=='P')
        return programName;
      if(x=='H')
        return shs;
    }
    char *retCandidateName()
    {
      return retString('N');
    }
    void modDetail(char ch);
    void getDetail();
    void categoryA();
    void categoryB();
    void categoryC();
    void categoryD();
};

void CandidateInfo::getDetail()
{
    system("CLS");
    cout << "Enter the title\n(master=1,mr=2,miss=3): ";
    do
    {
      cin >> title;
    } while (title != 1 && title != 2 && title != 3);
    cout << "Enter the Gender\n(Male=1,Female=2,N/A=3): ";
    do
    {
      cin >> gender;
    } while (gender != 1 && gender != 2 && gender != 3);
    cout << "Enter the Status\n(Boarder=1,Day=2): ";
    do
    {
      cin >> status;
    } while (status != 1 && status != 2);

    cout << "Enter the Candidate Name:   ";
    do
    {
      cin.getline(candidateName,100);
    } while (strlen(candidateName) == 0);
    cout << "Enter your JHS: ";
    do
    {
      cin.getline(shs, 200);
    } while (strlen(shs)==0);
    cout << "Enter your Grade: ";
    do
    {
      cin >> grade;
    } while (grade <1);
    
}

void CandidateInfo::modDetail(char ch)
{
    system("CLS");
    if(ch=='T')
    {
      cout << "Enter the title\n(master=1,mr=2,miss=3): ";
    do
    {
      cin >> title;
    } while (title != 1 && title != 2 && title != 3);
    }
    else if(ch =='N')
    {
    cout << "Enter the candidate Name: ";
    do{
      cin >> candidateName;
    } while (strlen(candidateName) == 0);
    }
    else if (ch == 'R' || ch == 'I')
    {
    int r = indexNumber;
    cout << "Enter the index number:   ";
    fstream f1(FBSTUD, ios::in | ios::binary);
    CandidateInfo obj;
    do
    {
      cin >> indexNumber;
      f1.close();
      f1.open(FBSTUD, ios::in | ios::binary);
      while(!f1.eof()){
        f1.read((char *)&obj, sizeof(obj));
        if(f1.eof()) break;
        if(obj.retIndexNumber()==indexNumber&& r!=indexNumber)
        {
          cout << "\nSame Index Number already exists !\n";
          cout << "Enter Roll No: ";
          indexNumber = -1;
        }
      }
    } while (indexNumber < 1);
    f1.close();
    }
}

void CandidateRegistration()
{
    system("CLS");
    CandidateInfo obj, obj2;
    char ch;
    int v = 0;
    cout << "Enter the candidate Index Nunber: \n";
    obj.getDetail();
    obj.categoryA();
	  obj.categoryB();
	  obj.categoryC();
	  obj.categoryD();
    fstream fl1(FBSTUD, ios::in | ios::binary);
    ofstream fl2;
    if(!fl1)
    {
    fl2.open(FBSTUD, ios::in | ios::binary);
    fl2.write((char *)&obj, sizeof(obj));
    fl2.close();
    return;
    }
    while(!fl1.eof())
    {
      fl1.read((char *)&obj, sizeof(obj));
      if(fl1.eof())
      {
        break;
      }
      if(obj.retIndexNumber()==obj2.retIndexNumber())
      {
        cout << "Record with the same Index number exist already \n";
        obj2.printDetails();
        cout << "Registration Aborted !\n";
        return;
      }
      else if(strcmpi(obj.retCandidateName(),obj2.retCandidateName()) == 0)
      if(!v)
        cout << "Warning:  Record with the same name already exists with the following details:\n";
      obj2.getDetail();
      cout << "\n";
      v = 1;
    }
    if(v)
    {
      cout << "do you still wish to insert record (Y/N)? ";
      do
    {
      cin >> ch;
      ch = toupper(ch);
    } while (ch != 'Y' && ch != 'N');
    if (ch == 'N')
    {
      cout << "Registration Aborted!\n";
      return;
    }
  }
  fl2.open(FBSTUD, ios::out | ios::app | ios::binary);
  fl2.seekp(0, ios::end);
  fl2.write((char *)&obj, sizeof(obj));
  fl2.close();
}



int searchStudentID(const string str = "search") { //Search Student by Attributes
    system("CLS");
    fstream fl(FBSTUD, ios::in | ios::ate | ios::binary);
    if ((!fl) || fl.tellg() == 0) {           //If file is empty or zero size
        cout << " No Records Found !\n";
        return 0;
    }
    fl.close();
    fl.open(FBSTUD, ios::in | ios::binary);
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
        if ((strcmpi(query, obj.retString(ch)) == 0)) {
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
  if(grade >=6 || grade<=12)
  {
    int choice;
	do
	{
			cout << "\t\t\tYou can only select one school from this category A \n";
			cout << "\t1. Prempeh College \n";
			cout << "\t2. OpokuWare School \n";
			cout << "\t3. Wesley  Girls College \n";
			cout << "\t4.  Presbyterians Boys SHS \n";
			cout << "\t5.  St Louis College \n";
			cout << "\t6.  Achimota SHS \n";
			cout<<"\nEnter your option: ";
			cin >> choice;
			switch(choice)
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
}
void CandidateInfo::categoryB()
{
  if(grade >=12 || grade <=20 )
  {
    	int  choice;
	{
			cout << "\t\t\tYou can only select one school from this category \n";
			cout << "\t1. Konogo Odumasi SHS \n";
			cout << "\t2. Mawuli School \n";
			cout << "\t3. Temale SHS \n";
			cout << "\t4. Anglican SHS\n";
			cout << "\t5. Toase  SHS \n";
			cout << "\t6. West Africa SHS  \n";
			cout<<"\nEnter your option: ";
			cin >> choice;
			switch(choice)
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

}
void CandidateInfo::categoryC()
{
  if(grade >= 20 || grade <= 27 )
  {
    int  choice;
	do
	{
			cout << "\t\t\tYou can only select one school from this category \n";
			cout << "\t1. Ejisuman SHS \n";
			cout << "\t2. Nkawie SHS \n";
			cout << "\t3. Sekyere Odumasi SHS \n";
			cout << "\t4.  Achina Krom SHS \n";
			cout << "\t5.  Bonwire SHS\n";
			cout << "\t6.  Antoa SHS \n";
			cout<<"\nEnter your option: ";
			cin >> choice;
        switch(choice)
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
	
}
void CandidateInfo::categoryD()
{
  if(grade >= 28 || grade<= 35 )
  {
    int  choice;
	do
	{
			cout << "\t\t\tCategory D is your Day school \n";
			cout << "\t\t Candidate will be automatically selected as day student ";
			cout << "\t1. Esasaase Bontefofo SHS \n";
			cout << "\t2. Atia Community Day SHS\n";
			cout << "\t3. Adutwaman Community Day SHS \n";
			cout << "\t4. Bonkra Community Day SHS \n";
			cout << "\t5. Ejisu Techical SHS\n";
			cout << "\t6.  Chrisic SHS \n";
			cout<<"\nEnter your option: ";
			cin >> choice;
			switch(choice)
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
	
}

int main()
{
    char ch;
    char ch1;
    int ch2;
    do {
        cout << "  School Placement System By Group 14\n";
        cout << "\t1. Candidate Database Management.\n";
        cout << "\t2. School  Database Management.\n";
        cout << "\t0. Exit.\n\n";
        cout << "Enter your choice : ";
        cin >> ch1;
        if (ch1 == '1')
        {
            do {
                cout << "\t\t\t    School Placement System\n";
                cout << "\t\t\tCandidateDatabase Management System\n";
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
                cout << "\t\t\t     School Placement System\n";
                cout << "\t\t School  Management System\n";
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
