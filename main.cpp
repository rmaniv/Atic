/*
 Project Title: Airline Ticketing System
         Version: 1 (2019-20)

 Developed by: Vinamr L Sachdeva
 School: Delhi Public School RK Puram
*/

//HEADERS

#include <fstream.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

//CLASSES AND STRUCTURES

class Flight
{
    int fno;
    char source[20];
    char destination[20];
    char date[10]; //dd/mm/yyyy
    float fare;

    public:

    void Enter()
    {
        cout << "\nFlight No : "; cin >> fno;
        cout << "\nSource : "; gets(source);
        strupr(source);
        cout << "\nDestination : "; gets(destination);
        strupr(destination);
        cout << "\nDate (DD/MM/YYYY) : "; gets(date);
        cout << "\nFare : "; cin >> fare;
    }

    void Show()
    {
        cout << endl << "Flight # " << fno << ":" << source << " to " << destination << " on " << date << " for (Rs " << fare << ")";
    }

    int Rfno() {return fno;}
    char* Rsource() {return source;}
    char* Rdestination() {return destination;}
    char* Rdate() {return date;}
    float Rfare() {return fare;}

    void Change(int F)
    {
        fare = F;
    }

    void Change(char D[])
    {
        strcpy(date,D);
    }
};

struct Passngr
{
    int fno, Pnr;
    char name[20], gender, mobile[12], address[20];
};

//FUNCTION PROTOTYPES

//Menu functions
void Color(int TC,int BC);
void ShowXY(int X,int Y,char CH);
void ShowXY(int X,int Y,char CH[]);
void Vline(int X,int Y,int L);
void Hline(int X,int Y,int L);
void Recta(int C1,int R1,int C2,int R2);
void DVline(int X,int Y,int L);
void DHline(int X,int Y,int L);
void DRecta(int C1,int R1,int C2,int R2);
int Vmenu(int X,int Y,char Mnu[][20],int Noc);
int Hmenu(int X,int Y,char Mnu[][20],int Noc);
void ClearArea(int C1,int R1,int C2,int R2);

//Admin functions
void admin(); //Main admin function
void AddFlight();
void Display();
void Search();
void Delete();
void Edit();
void SortPrice();
//User functions
void user(); //Main user function
void Reserve();
void Cancel();
//Report functions
void reports(); //Main report function
void Details();
void Status();
//Help function
void helpme();

//MAIN FUNCTION

void main()
{
    char MainMenu[][20] = {    "Admin     ",
                "User      ",
                "Reports   ",
                "Help      ",
                "EXIT      "
                };

    int Ch;
    do
    {
        Color(WHITE,BLUE);
        clrscr();

        Ch = Hmenu(1,1,MainMenu,5);

        switch(Ch)
        {
            case 0:admin(); break;
            case 1:user(); break;
            case 2:reports(); break;
            case 3:helpme(); break;
        }
    }
    while(Ch!=4);
}

//FUNCTION DEFINITTIONS

//Admin Menu Functions

void admin()
{
//Add Flight, Display Flight, Search Flight, Delete Flight, Modify Flight, Main Menu
    char AdminMenu[][20] = {    "Add Flight",
                "Display   ",
                "Search    ",
                "Delete    ",
                "Modify    ",
                "GO BACK   "
                };

    int Ch;

    Color(WHITE,BLUE);

    Ch = Vmenu(1,2,AdminMenu,6);

    switch(Ch)
    {
        case 0:AddFlight(); break;
        case 1:Display(); break;
        case 2:Search(); break;
        case 3:Delete(); break;
        case 4:Edit(); break;
    }
}

void AddFlight()
{
    fstream file("Flight.dat", ios::binary|ios::out|ios::app);
    clrscr();
    Flight F;

    F.Enter();
    file.write((char*)&F,sizeof(F));
    cout << "\nFlight added successfully";

    file.close();
}

void Display()
{

    ifstream file("Flight.dat", ios::binary);
    clrscr();
    Flight F;
    while(file.read((char*)&F,sizeof(F)))
    {
        F.Show();
    }

    file.close();
    getch();
}

void Search()
{
    ifstream file("Flight.dat", ios::binary);
    Flight F;
    clrscr();
    char s[20];
    char d[20];
    char dmy[10];

    cout << "\nFlight Source : ";   gets(s);
    cout << "\nFlight Destination : "; gets(d);
    cout << "\nDate : "; gets(dmy);

    int count = 0;

    while(file.read((char*)&F, sizeof(F)))
    {
        if(strcmpi(F.Rsource(),s)==0 && strcmpi(F.Rdestination(),d)==0 && strcmpi(F.Rdate(),dmy)==0)
        {
            count = 1;
            F.Show();
        }
    }

    if(count == 0)
    {
        cout<<"\nFlight unavailaible..."<<endl;
    }

    file.close();
    getch();
}

void SearchFno(int n)
{
    int fno = n;
    ifstream file("Flight.dat", ios::binary);
    Flight F;
    clrscr();

    int count = 0;

    while(!count&&file.read((char*)&F, sizeof(F)))
    {
        if(fno == F.Rfno())
        {
            count = 1; F.Show();
        }
    }
    if(count == 0)
    {
        cout << "\nNo registration found..." << endl;
    }

    file.close();
}


void Delete()
{
    clrscr();
    ifstream F1("Flight.dat", ios::binary);
    ofstream F2("trashcan.dat", ios::binary);
    Flight F; int Fnodel;

    cout << "\nEnter Flight Number of flight to delete ";
    cin >> Fnodel;
    int Del = 0;

    while(F1.read((char*)&F, sizeof(F)))
    {
        if(F.Rfno() == Fnodel)
        {
            Del = 1;
            cout<<"\nFlight Information Deleted...";
        }

        else
            F2.write((char*)&F, sizeof(F));
    }

    F1.close();
    F2.close();

    if(Del == 0)
    {
        cout<<"\nFlight to delete does not exist..." << endl;
    }

    F1.open("trashcan.dat", ios::binary);
    F2.open("Flight.dat", ios::binary);

    while(F1.read((char*)&F, sizeof(F)))
    {
        F2.write((char*)&F, sizeof(F));
    }

    F1.close();
    F2.close();
    getch();
}

void Edit()
{
    clrscr();
    fstream file("Flight.dat", ios::binary | ios::in | ios::out);
    Flight F; int Fnoedit;

    cout << "\nEnter Flight Number to edit ";
    cin >> Fnoedit;
    int Find = 0, ch;

    char dmy[10];
    float fare;

    while(file.read((char*)&F, sizeof(F)))
    {
        if(F.Rfno() == Fnoedit)
        {
            Find=1;

            do
            {
                cout << "\n1. Edit Date   2. Edit Fare ";
                cin >> ch;
                switch(ch)
                {
                    case 1: cout << "\nEnter new Date "; gets(dmy);
                            F.Change(dmy);break;

                    case 2: cout << "\nEnter new Fare "; cin >> fare;
                            F.Change(fare);break;

                    default: cout << "\nWrong choice ";
                }
            }
            while(ch!=1 && ch!=2);

        file.seekp(file.tellg()-sizeof(F));
        file.write((char*)&F,sizeof(F));
        }
    }

    file.close();

    if (Find==0)
        cout << "\nFlight to edit does not exist..."<<endl;

    getch();
}

void SortPrice()
{
    fstream file("Flight.dat", ios::binary | ios::in | ios::out);
    Flight F1, F2;

    file.seekg(0,ios::end);
    int n = file.tellg()/sizeof(Flight);

    for (int i = 0; i < n-1; i++)
        for (int j= 0; j < n-1-i; j++)
        {
            file.seekg(j*sizeof(Flight));
            file.read((char*)&F1, sizeof(F1));
            file.read((char*)&F2, sizeof(F2));
            if (F1.Rfare() > F2.Rfare())
            {
                file.seekp(j*sizeof(Flight));
                file.write((char*)&F2, sizeof(F2));
                file.write((char*)&F1, sizeof(F1));
            }
        }

    file.close();
}

//User Menu Functions

void user()
{
//Reserve, Cancel, Main Menu
    char UserMenu[][20] = {    "Reserve ",
                "Cancel  ",
                "GO BACK "
                };

    int Ch;

    Color(WHITE,BLUE);

    Ch = Vmenu(15,2,UserMenu,3);

    switch(Ch)
    {
        case 0:Reserve(); break;
        case 1:Cancel(); break;
    }
}

void Reserve()
{
    fstream F1("Res.dat", ios::binary | ios::out | ios::app);
    ifstream F2("Flight.dat", ios::binary);

    Flight F;
    Passngr P;

    char s[20], d[20], dmy[20];

    SortPrice();

    clrscr();
    cout << "\nEnter Source: "; gets(s);
    cout << "\nEnter Destination: ";gets(d);
    cout << "\nEnter Date: ";gets(dmy);

    int count = 0;

    while(F2.read((char*)&F, sizeof(F)))
    {
        if(strcmpi(F.Rsource(),s)==0 && strcmpi(F.Rdestination(),d)==0 && strcmpi(F.Rdate(),dmy)==0)
        {
            count = 1; F.Show();
        }
    }

    if(count == 0)
    {
        cout << "\nFlight unavailaible..." << endl;
    }

    else if(count == 1)
    {
        cout << "\nEnter the Flight Number for booking: "; cin >> P.fno;
        cout << "\nEnter your Details";
        cout << "\nName:"; gets(P.name);
        cout << "\nGender (M/F/O): "; cin >> P.gender;
        cout  << "\nContact Number: "; cin >> P.mobile;
        cout << "\nAddress: "; gets(P.address);
        cout << "\nFlight booked";
        randomize();
        P.Pnr = random(9000)+1000; //generating pnr randomly
        cout << "\nYour PNR: " << P.Pnr;
        F1.write((char*)&P, sizeof(P));
    }

    F1.close();
    F2.close();
    getch();
}

void Cancel()
{
    clrscr();
    ifstream F1("Res.dat", ios::binary);
    ofstream F2("cancel.dat", ios::binary);
    Passngr P; int Pnodel;

    cout << "\nEnter your PNR to cancel your flight : ";
    cin >> Pnodel;
    int Del = 0;

    while(F1.read((char*)&P, sizeof(P)))
    {
        if(P.Pnr == Pnodel)
        {
            Del = 1;
            cout<<"\nFlight cancelled...";
        }
        else
            F2.write((char*)&P, sizeof(P));
    }

    F1.close();
    F2.close();

    if(Del == 0)
    {
        cout<<"\nReservation does not exist..." << endl;
    }

    F1.open("cancel.dat", ios::binary);
    F2.open("Res.dat", ios::binary);

    while(F1.read((char*)&P, sizeof(P)))
    {
        F2.write((char*)&P, sizeof(P));
    }

    F1.close();
    F2.close();
    getch();
}

//Report Menu Funtions

void reports()
{
//Flight Passenger Detail,Flight Reservation Status, Main Menu
    char ReportsMenu[][20] = {    "Details ",
                "Status  ",
                "GO BACK "
                };

    int Ch;

    Color(WHITE,BLUE);

    Ch = Vmenu(29,2,ReportsMenu,3);

    switch(Ch)
    {
        case 0:Details(); break;
        case 1:Status(); break;
    }
}

void Details()
{
    ifstream file("Res.dat", ios::binary);
    Passngr P;
    clrscr();

    int Pnr;

    cout << "\nEnter PNR: "; cin >> Pnr;

    int count = 0;

    while(!count && file.read((char*)&P, sizeof(P)))
    {
        if(Pnr == P.Pnr)
        {
            count = 1;
            cout << "\nYour booking: ";
            cout << "\nName: " << P.name;
            cout << "\nFlight Number: " << P.fno;
            cout << "\nGender: " << P.gender;
            cout << "\nContact Number: " << P.mobile;
            cout << "\nAddress: " << P.address;
            cout << "\n\nPress ENTER to see your flight details";
            getch();
            SearchFno(P.fno);
            break;
        }
    }

    if(count == 0)
    {
        cout<<"\nReservation unavailaible..."<<endl;
    }

    file.close();
    getch();
}

void Status()
{
    ifstream file("Res.dat", ios::binary);
    Passngr P;
    clrscr();

    int Pnr;

    cout << "\nEnter PNR: "; cin >> Pnr;

    int count = 0;

    while(!count&&file.read((char*)&P, sizeof(P)))
    {
        if(Pnr == P.Pnr)
        {
            count = 1;
            cout << "\nStatus: booked";
        }
    }

    if(count == 0)
    {
        cout<<"\nStatus: not booked/cancelled"<<endl;
    }

    file.close();
    getch();
}

//Help Function

void helpme()
{
    clrscr();
    ShowXY(5,5,"User Guide: ");
    ShowXY(3,7,"-> Use the LEFT,RIGHT,TOP,DOWN arrow keys to navigate through the menu.");
    ShowXY(3,8,"-> Press ENTER for entering data into the next field.");
    ShowXY(3,9,"-> Press ENTER to exit a sub-menu option.");
    ShowXY(5,13,"About: ");
    ShowXY(5,15,"This is an airline ticketing system for the admin & the passenger.");
    ShowXY(5,17,"The ADMIN menu option can be used to add, view, delete, modify flights.");
    ShowXY(5,19,"The passenger in this program, can:");
    ShowXY(5,20,"1. use the USER menu option to reserve, cancel and");
    ShowXY(5,21,"2. use the REPORTS menu option to view his/her details and status.");

    getch();
}

//Menu Functions

const char VL=179,HL=196,TL=218,TR=191,BL=192,BR=217;
const char DVL=186,DHL=205,DTL=201,DTR=187,DBL=200,DBR=188;

void Color(int TC,int BC)//For Changing Text Color and Text Background
{
    textcolor(TC);
    textbackground(BC);
}

void ShowXY(int X,int Y,char CH)//Displays a character at X,Y position
{
    gotoxy(X,Y);
    cprintf("%c",CH);  //cout<<CH;
}

void ShowXY(int X,int Y,char CH[])//Displays a string at X,Y position
{
    gotoxy(X,Y);
    cprintf("%s",CH);  //cout<<CH;
}

void Vline(int X,int Y,int L)//To vertical line by joining vert. characters
{
    for (int i=Y;i<=Y+L;i++)
        ShowXY(X,i,VL);
}
void Hline(int X,int Y,int L)//To horizontal line by joining hor.characters
{
    for (int i=X;i<=X+L;i++)
        ShowXY(i,Y,HL);
}
void Recta(int C1,int R1,int C2,int R2)
{
    ShowXY(C1,R1,TL);             //
    ShowXY(C1,R2,BL);             //Placing corner characters
    ShowXY(C2,R1,TR);             //
    ShowXY(C2,R2,BR);             //
    Vline(C1,R1+1,R2-R1-2);       //
    Vline(C2,R1+1,R2-R1-2);       //Joining Corners by Vertical lines
    Hline(C1+1,R1,C2-C1-2);       //
    Hline(C1+1,R2,C2-C1-2);       //Joining Corners by Horizontal lines
}
void DVline(int X,int Y,int L)
{
    for (int i=Y;i<=Y+L;i++)
        ShowXY(X,i,DVL);
}
void DHline(int X,int Y,int L)
{
    for (int i=X;i<=X+L;i++)
        ShowXY(i,Y,DHL);
}
void DRecta(int C1,int R1,int C2,int R2)
{
    ShowXY(C1,R1,DTL);
    ShowXY(C1,R2,DBL);
    ShowXY(C2,R1,DTR);
    ShowXY(C2,R2,DBR);
    DVline(C1,R1+1,R2-R1-2);
    DVline(C2,R1+1,R2-R1-2);
    DHline(C1+1,R1,C2-C1-2);
    DHline(C1+1,R2,C2-C1-2);
}

                 //X,Y are coordinates for displaying menu
                 //Mnu all choices which required to be displayed as Menu Choices
                 //Noc no. of choices
int Vmenu(int X,int Y,char Mnu[][20],int Noc)
{
    Color(WHITE,BLUE);
    Recta(X,Y,X+strlen(Mnu[0])+1,Y+Noc+1);
    for (int i=0;i<Noc;i++)
        ShowXY(X+1,Y+i+1,Mnu[i]);

    int Sel=0,Exit=0;//Sel - Current Selected Option
                                     //Exit- Control Variable for loop
    do
    {
        int Tsel=Sel;    //To store the current selection in Tsel
        Color(BLUE,WHITE);
        ShowXY(X+1,Y+Sel+1,Mnu[Sel]);
        Color(WHITE,BLUE);
        char Cho=getch();
        //71:Home  72:Up   73:Pup   75:Left   77:Right  79:End  80:Dn 81:PD
        switch(Cho)
        {
         case 71:Sel=0;break;
         case 79:Sel=Noc-1;break;
         case 72:if (Sel==0)
                 Sel=Noc-1;
             else
                 Sel--;
             break;
         case 80:if (Sel==Noc-1)
                 Sel=0;
             else
                 Sel++;
             break;
         case 13:Exit=1; //Enter Key
             break;
         case 27:Sel=-1; //Escape
             Exit=1;
             break;
        }
        ShowXY(X+1,Y+Tsel+1,Mnu[Tsel]);
    }
    while (!Exit);
    return Sel;
}

int Hmenu(int X,int Y,char Mnu[][20],int Noc)
{
    Color(WHITE,BLUE);
    for (int i=0;i<Noc;i++)
        ShowXY(X+15*i+1,Y,Mnu[i]);
    int Sel=0,Exit=0;
    ShowXY(30,10,"AIR TICKETING SYSTEM");
    ShowXY(25,17,"Developed by: Vinamr L Sachdeva");
    ShowXY(29,18,"Class 12-H DPS RK Puram");

    do
    {
        int Tsel=Sel;    //To store the current selection in Tsel
        Color(BLUE,WHITE);
        ShowXY(X+15*Sel+1,Y,Mnu[Sel]);
        Color(WHITE,BLUE);
        char Cho=getch();
        //71:Home  72:Up   73:Pup   75:Left   77:Right  79:End  80:Dn 81:PD
        switch(Cho)
        {
         case 71:Sel=0;break;
         case 79:Sel=Noc-1;break;
         case 75:if (Sel==0)
                 Sel=Noc-1;
             else
                 Sel--;
             break;
         case 77:if (Sel==Noc-1)
                 Sel=0;
             else
                 Sel++;
             break;
         case 13:Exit=1;
             break;
         case 27:Sel=-1;
             Exit=1;
             break;
        }
        ShowXY(X+15*Tsel+1,Y,Mnu[Tsel]);
    }
    while (!Exit);
    return Sel;
}

void ClearArea(int C1,int R1,int C2,int R2)
{
    window(C1,R1,C2,R2);
    clrscr();
    window(1,1,80,25);
}
