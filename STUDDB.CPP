// StudDB.cpp : Turbo C++ Application to handle student database
//

#include <conio.h>
#include <process.h>
#include <dos.h>
#include <iostream.h>
#include <stdio.h>
#include <string.h>


#pragma pack(2)
struct CStudent
{
public:
    char name[64];
    long age;
    char dept[64];
};

struct CStudents
{
    #define MaxSz  100
    char m_fileName[1024];
    int m_nMaxStudents;
    CStudent m_studList[MaxSz];

    CStudents(const char *filename);

    void AddRecord(const char *name, int age, const char *dept);

    void EditRecord(int pos, const char *name, int age, const char *dept);
    void DeleteRecord(int pos);
    int ReadRecords();
    int WriteRecords();
};

CStudents::CStudents(const char *filename)
{
	m_nMaxStudents = 0;
	strcpy(m_fileName, filename);
}

void CStudents::AddRecord(const char *name, int age, const char *dept)
{
	int pos = m_nMaxStudents;
	strcpy(m_studList[pos].name,name);
	strcpy(m_studList[pos].dept,dept);
	m_studList[pos].age = age;
	m_nMaxStudents++;
	WriteRecords();
}

void CStudents::EditRecord(int pos, const char *name, int age, const char *dept)
{
	strcpy(m_studList[pos].name,name);
	strcpy(m_studList[pos].dept,dept);
	m_studList[pos].age = age;
	WriteRecords();
}

void CStudents::DeleteRecord(int pos)
{
	m_nMaxStudents--;

	for(int i = pos; i < m_nMaxStudents; i++)
	{
	    m_studList[i] = m_studList[i + 1];
	}
	WriteRecords();
}

int CStudents::ReadRecords()
{
        FILE *istream = fopen(m_fileName, "rb");
     
        if (istream == 0)
	    return 0;

	char buf[4096];
        int nTotalRecordsRead = 0;

        for(int i = 0; i < MaxSz; i++)
        {
            if(feof(istream))
                break;
            int nBytesRead = fread(buf, 1, sizeof(CStudent), istream);
            if(nBytesRead < sizeof(CStudent))
                break;
	    char *p = (char*)(&m_studList[i]);
            memcpy(p, buf, sizeof(CStudent));
            nTotalRecordsRead++;
        }

	fclose(istream);
	m_nMaxStudents = nTotalRecordsRead;

	return nTotalRecordsRead;
}

int CStudents::WriteRecords()
{
	FILE *ostream = fopen(m_fileName, "wb");

        if (ostream == 0)
	    return 0;

        int nTotalRecordsWritten = 0;
        char buf[4096];
        for(int i = 0; i < m_nMaxStudents; i++)
        {
            fwrite((char*)&m_studList[i], 1, sizeof(CStudent), ostream);
            nTotalRecordsWritten++;
        }

        fclose(ostream);

        return nTotalRecordsWritten;
}


CStudents theStudents("c:\\students.bin");


int DisplayMainMenu()
{
    ::system("cls");
    
    gotoxy(10,4);
    cout << "Welcome to Student Database Application";

    gotoxy(10,5);
    cout << "___________________________________________";

    gotoxy(10,6);
    cout << "1. Add Student Record";

    gotoxy(10,7);
    cout << "2. Edit Student Record";

    gotoxy(10,8);
    cout << "3. View Student Record";

    gotoxy(10,9);
    cout << "4. Delete Student Record";

    gotoxy(10,10);
    cout << "5. Exit";

    gotoxy(10,11);
    cout << "___________________________________________";

    gotoxy(10,13);
    cout << "Enter your Selection: ";
    int m = -1;
    cin >> m;

    return m;
}

void ViewRecords()
{
    theStudents.ReadRecords();
    
    ::system("cls");
        
    gotoxy(10,4);
    cout << "Welcome to Student Database Application";

    gotoxy(10,5);
    cout << "___________________________________________";

    gotoxy(10,6);
    cout << "SNo Student Name       Age    Department   ";

    gotoxy(10,7);
    cout << "___________________________________________";

    int pos = 8;
    // Enable Paging
    for(int i = 0; i < theStudents.m_nMaxStudents; i++)
    {
        gotoxy(10,pos);
	cout << i + 1;
        gotoxy(14,pos);
	cout << theStudents.m_studList[i].name;
        gotoxy(33,pos);
	cout << theStudents.m_studList[i].age;
        gotoxy(42,pos);
	cout << theStudents.m_studList[i].dept;
        pos++;
    }
    gotoxy(10,pos++);
    cout << "___________________________________________";
    pos++;
    gotoxy(10,pos++);
}


void InputRecords()
{
    while(1)
    {
        ::system("cls");
        
        gotoxy(10,4);
	cout << "Welcome to Student Database Application";

        gotoxy(10,5);
	cout << "___________________________________________";

        gotoxy(10,6);
	cout << "Student Name: ";

        gotoxy(10,7);
	cout << "Age: ";

        gotoxy(10,8);
	cout << "Departement: ";

        gotoxy(10,9);
	cout << "___________________________________________";

        gotoxy(23,6);
        char name[64];
	cin >> name;

        gotoxy(17,7);
        int age;
	cin >> age;

        gotoxy(23,8);
        char dept[64];
	cin >> dept;

        theStudents.AddRecord(name, age, dept);

        gotoxy(10,11);
	cout << "Do you want to add another record (Y/N)? ";
        char ch = getch();

        if(ch == 'Y' || ch == 'y')
            continue;
        else
            break;
    }
}


void EditRecords()
{
    ViewRecords();
    cout << "Enter the serial number you want to edit: ";
    int m;
    cin >> m;

    if(m >= 1 && m <= theStudents.m_nMaxStudents)
    {
        ::system("cls");
        gotoxy(10,4);
	cout << "Welcome to Student Database Application";

        gotoxy(10,5);
	cout << "___________________________________________";

        gotoxy(10,6);
	cout << "Student Name: ";

        gotoxy(10,7);
	cout << "Age: ";

        gotoxy(10,8);
	cout << "Departement: ";

        gotoxy(10,9);
	cout << "___________________________________________";

        gotoxy(23,6);
        char name[64];
	cin >> name;

        gotoxy(17,7);
        int age;
	cin >> age;

        gotoxy(23,8);
        char dept[64];
	cin >> dept;

        theStudents.EditRecord(m - 1, name, age, dept);        
        gotoxy(10,12);
	cout << "Record updated. Press any key to return to Main Menu";
	getch();
    }
    else
    {
	gotoxy(10,12);
	cout << "Invalid Entry. Press any key to return to Main Menu";
	getch();
    }

}

void DeleteRecords()
{
    ViewRecords();
    cout << "Enter the serial number you want to delete: ";
    int m;
    cin >> m;
    if(m >= 1 && m <= theStudents.m_nMaxStudents)
    {
        theStudents.DeleteRecord(m - 1);
	cout << "Record deleted. Press any key to return to Main Menu";
	getch();
    }
    else
    {
	cout << "Invalid Entry. Press any key to return to Main Menu";
	getch();
    }
}

int main()
{
    theStudents.ReadRecords();
    while(1)
    {
        int selection = DisplayMainMenu();

        switch(selection)
        {
        case 1:
            InputRecords();
            break;
	case 2:
            EditRecords();
            break;
        case 3:
            {
            ViewRecords();
	    cout << "Press any key to return to Main Manu: ";
	    getch();
	    }
            break;
        case 4:
	    DeleteRecords();
            break;

        case 5:
        default:
            return 0;
        };
    }
}