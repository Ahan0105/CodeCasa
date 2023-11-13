#include <iostream>
#include <string.h>
#include <conio.h>
#define max 100
using namespace std;

class Guest
{
public:
    char guestName[100];
    char guestAddress[100];
    char guestPhone[12];
    char fromDate[20];
    char toDate[20];
    float paymentAdvance;
    int bookingId;
};

class Room
{
public:
    char type;
    char roomType;
    char ac;
    int roomNumber;
    int rent;
    int status;

    class Guest guest;
    class Room addRoom(int);
    void searchRoom(int);
    void deleteRoom(int);
    void displayRoom(Room);
};

class HotelManagement : protected Room
{
public:
    void performCheckIn();
    void displayAvailableRooms();
    void searchGuestByName(char *);
    void performCheckOut(int);
    void generateGuestSummaryReport();
};

class Room rooms[max];  
int count = 0;  

Room Room::addRoom(int rno)
{
    class Room room;
    room.roomNumber = rno;
    cout << "\nType AC/Non-AC (A/N) : ";
    cin >> room.ac;
    cout << "\nType Comfort (S/N) : ";
    cin >> room.type;
    cout << "\nType Size (B/S) : ";
    cin >> room.roomType;
    cout << "\nDaily Rent : ";
    cin >> room.rent;
    room.status = 0;

    cout << "\n Room Added Successfully!";
    getch();
    return room;
}

void Room::searchRoom(int rno)
{
    int i, found = 0;
    for (i = 0; i < count; i++)
    {
        if (rooms[i].roomNumber == rno)
        {
            found = 1;
            break;
        }
    }
    if (found == 1)
    {
        cout << "Room Details\n";
        if (rooms[i].status == 1)
        {
            cout << "\nRoom is Reserved (not available)";
        }
        else
        {
            cout << "\nRoom is available";
        }
        displayRoom(rooms[i]);
        getch();
    }
    else
    {
        cout << "\nRoom not found";
        getch();
    }
}

void Room::displayRoom(Room tempRoom)
{
    cout << "\nRoom Number: \t" << tempRoom.roomNumber;
    cout << "\nType AC/Non-AC (A/N) " << tempRoom.ac;
    cout << "\nType Comfort (S/N) " << tempRoom.type;
    cout << "\nType Size (B/S) " << tempRoom.roomType;
    cout << "\nRent: " << tempRoom.rent;
}

void HotelManagement::performCheckIn()
{
    int i, found = 0, rno;

    class Room room;
    cout << "\nEnter Room number : ";
    cin >> rno;
    for (i = 0; i < count; i++)
    {
        if (rooms[i].roomNumber == rno)
        {
            found = 1;
            break;
        }
    }
    if (found == 1)
    {
        if (rooms[i].status == 1)
        {
            cout << "\nRoom is already Booked";
            getch();
            return;
        }

        cout << "\nEnter booking id: ";
        cin >> rooms[i].guest.bookingId;

        cout << "\nEnter Guest Name (First Name): ";
        cin >> rooms[i].guest.guestName;

        cout << "\nEnter Address (only city): ";
        cin >> rooms[i].guest.guestAddress;

        cout << "\nEnter Phone: ";
        cin >> rooms[i].guest.guestPhone;

        cout << "\nEnter From Date: ";
        cin >> rooms[i].guest.fromDate;

        cout << "\nEnter to  Date: ";
        cin >> rooms[i].guest.toDate;

        cout << "\nEnter Advance Payment: ";
        cin >> rooms[i].guest.paymentAdvance;

        rooms[i].status = 1;

        cout << "\n Guest Checked-in Successfully..";
        getch();
    }
}

void HotelManagement::displayAvailableRooms()
{
    int i, found = 0;
    for (i = 0; i < count; i++)
    {
        if (rooms[i].status == 0)
        {
            displayRoom(rooms[i]);
            cout << "\n\nPress enter for the next room";
            found = 1;
            getch();
        }
    }
    if (found == 0)
    {
        cout << "\nAll rooms are reserved";
        getch();
    }
}

void HotelManagement::searchGuestByName(char *pname)
{
    int i, found = 0;
    for (i = 0; i < count; i++)
    {
        if (rooms[i].status == 1 && stricmp(rooms[i].guest.guestName, pname) == 0)
        {
            cout << "\nGuest Name: " << rooms[i].guest.guestName;
            cout << "\nRoom Number: " << rooms[i].roomNumber;

            cout << "\n\nPress enter for the next record";
            found = 1;
            getch();
        }
    }
    if (found == 0)
    {
        cout << "\nPerson not found.";
        getch();
    }
}

void HotelManagement::performCheckOut(int roomNum)
{
    int i, found = 0, days, rno;
    float billAmount = 0;
    for (i = 0; i < count; i++)
    {
        if (rooms[i].status == 1 && rooms[i].roomNumber == roomNum)
        {
            found = 1;
            break;
        }
    }
    if (found == 1)
    {
        cout << "\nEnter Number of Days:\t";
        cin >> days;
        billAmount = days * rooms[i].rent;

        cout << "\n\t######## CheckOut Details ########\n";
        cout << "\nGuest Name : " << rooms[i].guest.guestName;
        cout << "\nRoom Number : " << rooms[i].roomNumber;
        cout << "\nAddress : " << rooms[i].guest.guestAddress;
        cout << "\nPhone : " << rooms[i].guest.guestPhone;
        cout << "\nTotal Amount Due : " << billAmount << " /";
        cout << "\nAdvance Paid: " << rooms[i].guest.paymentAdvance << " /";
        cout << "\n*** Total Payable: " << billAmount - rooms[i].guest.paymentAdvance << "/ only";

        rooms[i].status = 0;
    }
    getch();
}

void HotelManagement::generateGuestSummaryReport()
{
    if (count == 0)
    {
        cout << "\n No Guest in Hotel !!";
    }
    for (int i = 0; i < count; i++)
    {
        if (rooms[i].status == 1)
        {
            cout << "\n Guest Name: " << rooms[i].guest.guestName;
            cout << "\n Room Number: " << rooms[i].roomNumber;
            cout << "\n Address (only city): " << rooms[i].guest.guestAddress;
            cout << "\n Phone: " << rooms[i].guest.guestPhone;
            cout << "\n---------------------------------------";
        }
    }

    getch();
}

void manageRooms()
{
    class Room room;
    int opt, rno, i, flag = 0;
    char ch;
    do
    {
        system("cls");
        cout << "\n### Manage Rooms ###";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Back to Main Menu";
        cout << "\n\nEnter Option: ";
        cin >> opt;

        switch (opt)
        {
        case 1:
            cout << "\nEnter Room Number: ";
            cin >> rno;
            i = 0;
            for (i = 0; i < count; i++)
            {
                if (rooms[i].roomNumber == rno)
                {
                    flag = 1;
                }
            }
            if (flag == 1)
            {
                cout << "\nRoom Number is Present.\nPlease enter a unique Number";
                flag = 0;
                getch();
            }
            else
            {
                rooms[count] = room.addRoom(rno);
                count++;
            }
            break;
        case 2:
            cout << "\nEnter room number: ";
            cin >> rno;
            room.searchRoom(rno);
            break;
        case 3:
            // nothing to do
            break;
        default:
            cout << "\nPlease Enter the correct option";
            break;
        }
    } while (opt != 3);
}

int main()
{
    class HotelManagement hm;
    int i, j, opt, rno;
    char ch;
    char pname[100];

    system("cls");

    do
    {
        system("cls");
        cout << "######## Hotel Management #########\n";
        cout << "\n1. Manage Rooms";
        cout << "\n2. Check-In Room";
        cout << "\n3. Available Rooms";
        cout << "\n4. Search Guest";
        cout << "\n5. Check-Out Room";
        cout << "\n6. Guest Summary Report";
        cout << "\n7. Exit";
        cout << "\n\nEnter Option: ";
        cin >> opt;
        switch (opt)
        {
        case 1:
            manageRooms();
            break;
        case 2:
            if (count == 0)
            {
                cout << "\nRooms data is not available.\nPlease add the rooms first.";
                getch();
            }
            else
                hm.performCheckIn();
            break;
        case 3:
            if (count == 0)
            {
                cout << "\nRooms data is not available.\nPlease add the rooms first.";
                getch();
            }
            else
                hm.displayAvailableRooms();
            break;
        case 4:
            if (count == 0)
            {
                cout << "\nRooms are not available.\nPlease add the rooms first.";
                getch();
            }
            else
            {
                cout << "Enter Guest Name: ";
                cin >> pname;
                hm.searchGuestByName(pname);
            }
            break;
        case 5:
            if (count == 0)
            {
                cout << "\nRooms are not available.\nPlease add the rooms first.";
                getch();
            }
            else
            {
                cout << "Enter Room Number : ";
                cin >> rno;
                hm.performCheckOut(rno);
            }
            break;
        case 6:
            hm.generateGuestSummaryReport();
            break;
        case 7:
            cout << "\nTHANK YOU! FOR USING SOFTWARE";
            break;
        default:
            cout << "\nPlease Enter correct option";
            break;
        }
    } while (opt != 7);

    getch();
}
 
