

/*
Problem Statement :
-------------------

I own a multi-storey parking lot that can hold up to 'n' cars at any given point in time. Each slot is
given a number starting at 1 increasing with increasing distance from the entry point in steps of
one. I want to create an automated ticketing system that allows my customers to use my parking
lot without human intervention.

When a car enters my parking lot, I want to have a ticket issued to the driver. The ticket issuing
process includes us documenting the registration number (number plate) and the colour of the
car and allocating an available parking slot to the car before actually handing over a ticket to the
driver (we assume that our customers are nice enough to always park in the slots allocated to
them). The customer should be allocated a parking slot which is nearest to the entry. At the exit
the customer returns the ticket which then marks the slot they were using as being available.
This application should let me:

➔ Create the Parking Lot based on the number of parking spaces available taken as N in an
input field. e.g. 100 Parking spaces => N = 100

➔ Generate the initial number of car details.
	◆ e.g. Takes input m = no. of cars currently in the parking lot and generates the car Registration numbers and color randomly but with the following format:

	◆ e.g. KA-01-HH-1234 White or KA-04-TY-3469 Blue

	◆ Please follow the above Registration number format and use 4 colors (Black, White, Blue, Red)

	◆ Also alots them slots (ranging from 1-N)

➔ Shows the list of cars along with their details in a Table. e.g.

	Registration No. | Color | Slot No.

➔ Allows me to select a car from the table and remove it from parking the slot making that slot no. available for the next car to enter the parking slot.
	◆ e.g. This could be done using a button adjacent to the Car row in the Table. You can also have a function which inputs car+slot details to remove it.

➔ Allows me to enter the car details of the incoming car manually but in the format mentioned above and the system automatically alot them to the nearest empty slot.
	(nearest being slot 1 in slots 1-N)
	◆ e.g. if slots 4 and 19 are available, the system alots the car slot 4.


➔ Due to government regulation, the system should provide me with the ability to find out:
	A. Registration numbers of all cars of a particular colour.
	B. Slot number in which a car with a given registration number is parked.
	C. Slot numbers of all slots where a car of a particular colour is parked.


Please include error/warning alerts if and where applicable.






 */

// Solution :

// ------------

/*
author : Baljeet Singh
*/

#include <bits/stdc++.h>
using namespace std;

// class to represent Parking Lot

class ParkingLot
{
public:
	// data member of ParkingLot Class

	int N;							   // number of parking slot
	vector<bool> isbooked;			   // to store status of slots
	map<int, pair<string, string>> ds; // data structure to store information ticket of slots

	// constructor
	ParkingLot(int n)
	{
		N = n;

		for (int i = 0; i <= n; i++)
		{
			isbooked.push_back(false); // intially all are empty
		}
	}

	// member function of ParkingLot Class

	// member function  to get nearest empty slot

	int getSlot()
	{
		for (int i = 1; i <= N; i++)
		{
			if (isbooked[i] == false)
				return i; // nearest emplty slot found
		}

		return -1; // return -1 when no slot is empty i.e all slots are occupied.
	}

	// member function  to adding a car to slot

	void insert(int slot, string reg, string color)
	{
		isbooked[slot] = true; // mark the slot as occupied

		ds[slot] = make_pair(reg, color); // store the information in our data structure
	}

	// member function  to removing a car from slot
	void deleteCar(int slot)
	{
		ds.erase(slot); // remove the ticket related to given slots from the data structure

		isbooked[slot] = false; // making this slot is available for other cars
	}

	// member function  to display the ist of cars along with their details.

	// Validate Slot Number

	bool isvalid(int slotNo)
	{
		return isbooked[slotNo] == 1;
	}
	//

	void display()
	{
		if (ds.size() > 0)
		{
			cout << "\t\t\tlist of cars along with their details :\n\n";
			cout << "Registeration Number \t\t|\tColor\t|\t Slot No." << endl;
			for (auto ele : ds)
			{
				cout << ele.second.first << "\t\t\t|"
					 << "\t" << ele.second.second << "\t|\t" << ele.first << endl;
			}

			while (1)
			{
				string choice;
				cout << "\n\nEnter yes if want to remove car from list else no : ";
				cin >> choice;
				if (choice == "yes")
				{
					int slot_no;
					cout << "Car Slot no from the list : ";

					while (1)
					{
						cin >> slot_no;
						if (isvalid(slot_no) == true)
							break;
						else
						{
							cout << "\nplease Enter valid slot number present in the above list  " << endl;
						}
					}

					deleteCar(slot_no); // removing car from parking slot

					if (ds.size() == 0) // when all cars removed from the parking Lot
					{
						cout << "All cars removed from the parking .... going back to main menu" << endl;
						return;
					}
				}
				else
					break;
			}
		}
		else
		{
			cout << "None of the slot is not booked yet" << endl;
		}
	}

	// member function to provide search functionality using different parameter in the parking Lot

	// return the Registration numbers of all cars of given color
	vector<string> searchUsingColor(string carColor)
	{
		vector<string> res;
		for (auto entry : ds)
		{
			if (entry.second.second == carColor)
			{
				res.push_back(entry.second.first);
			}
		}

		return res;
	}

	// To search a using Registeration Number  & return its slot number if present

	int findByRegNo(string regNo)
	{
		for (auto entry : ds)
		{
			if (entry.second.first == regNo)
			{
				return entry.first; // car of given registeration is  found at this slot
			}
		}

		return -1; // car of given registeration number is not parked int the parking
	}

	// to get  all slot numbers  where a car of a particular colour is parked

	vector<int> searchSlotsUsingColor(string carColor)
	{
		vector<int> res;
		for (auto entry : ds)
		{
			if (entry.second.second == carColor) // if given color is matched
			{
				res.push_back(entry.first); // store it into resultant list
			}
		}
		return res; // return list of slot number
	}

	// member function to Control Search Functionlities

	void search()
	{
		while (1)
		{
			cout << "\nPress 1. Registration numbers of all cars of a particular colour." << endl;
			cout << "Press 2. To search a using Registeration Number " << endl;
			cout << "Press 3. Slot numbers of all slots where a car of a particular colour is parked" << endl;
			cout << "Press 4. To Go Black" << endl;

			// variable to store information  useful in smooth implementaion of search functionality
			int choice;
			cin >> choice;
			string carColor;
			string reg_no;
			int resslot;
			vector<int> res1;
			vector<string> res;

			// swtch case statement to handle different scenerio
			switch (choice)
			{
			case 1:
				cout << "Enter Color : " << endl;
				cin >> carColor;
				res = searchUsingColor(carColor);
				if (res.size() > 0)
				{
					cout << "\nCars having Color " << carColor << " has following Registration number :" << endl;
					for (auto c : res)
					{
						cout << c << endl;
					}
				}
				else
				{
					cout << "\nCar having Color " << carColor << " is not parked at any slot" << endl;
				}
				break;
			case 2:
				cout << "\nEnter Registration Number of Car : " << endl;
				cin >> reg_no;
				resslot = findByRegNo(reg_no);
				if (resslot != -1)
				{
					cout << "\nCar With Registration Number  " << reg_no << " is parked at this Slot number : " << resslot << endl;
				}
				else
				{
					cout << "\nCar With Registration Number  " << reg_no << " is not parked at any slot" << endl;
				}
				break;

			case 3:
				cout << "\nEnter Color : " << endl;
				cin >> carColor;
				res1 = searchSlotsUsingColor(carColor);
				if (res1.size() > 0)
				{
					cout << "\nCars having Color  " << carColor << " are parked at following Slots :" << endl;
					for (auto sl : res1)
					{
						cout << sl << endl;
					}
				}
				else
				{
					cout << "\n Car having Color  " << carColor << " is not parked at any slot" << endl;
				}

				break;
			case 4:
				cout << "\n\nGoing back to main menu ......" << endl;
				return;
			default:
				cout << "\nEnter Valid choice please" << endl;
			}
		}
	}
};

////////////////////////////////////////////////////////////////

/* Utility Functions */

// to generate M random slot number

set<int> getRandSlots(int n, int m)
{
	set<int> st;
	while (st.size() < m)
	{
		int x = rand();
		x = x % n;
		x += 1;
		st.insert(x);
	}
	return st;
}

// to generate random color

string getColor()
{
	string Colors[] = {"Black", "White", "Blue", "Red"};
	int m = rand();
	m = m % 4;
	return Colors[m];
}

// to get random registeration number

// to get random char between [A-Z] , both A & Z are inclusive
char getRanChar()
{
	int m = rand();
	m = m % 26;
	char ch = 65 + m;
	return ch;
}

// to get random digit in close interval [0-9]
int getRandigit()
{
	return rand() % 10;
}

// genrating random registeration number of given  Format : KA-01-HH-1234
string getRegNo()
{

	// to store registeration number
	string res;

	// getting first Two Char
	for (int i = 1; i <= 2; i++)
	{
		res.push_back(getRanChar());
	}
	res.push_back('-');

	// getting next two  digits

	for (int i = 1; i <= 2; i++)
	{
		int x = getRandigit();
		res += to_string(x);
	}
	res.push_back('-');

	// getting next two char
	for (int i = 1; i <= 2; i++)
	{
		res.push_back(getRanChar());
	}
	res.push_back('-');

	// getting last 4 digits
	for (int i = 1; i <= 4; i++)
	{
		int x = getRandigit();
		res += to_string(x);
	}

	return res; // returning registertaion number
}

// Driver module

int main()
{

	int n;
	cout << "Enter Number of slots int Parking : ";
	cin >> n;

	// creating a object of ParkingLot class with n slots
	ParkingLot p1(n);

	// for random car details
	cout << "Enter Number of intials car : "; // no. of cars currently in the parking lot
	int m;

	// validate the value of m
	while (1)
	{
		cin >> m;
		if (m >= 0 && m <= n)
			break;
		else
			cout << "Error!...number of randomly generated car information should be positive & less than equal to total no. of slots \n"
				 << endl;
		cout << "\n Enter Again..." << endl
			 << endl;
	}

	cout << "Wait for a while ... Building up the ParkingLot  " << endl;

	// storing m  random slot number in set data structure, here we use set data structure to store m distnict value
	set<int> slots = getRandSlots(n, m);
	for (auto slot : slots)
	{

		// genrating random car details

		string color = getColor(); // random color
		string regno = getRegNo(); // random registeration number

		// inserting car into parking Lot

		p1.insert(slot, regno, color);
	}

	cout << "\n\n\t\t\t\t\t" << endl;

	// driver function to service functionlities of Parking Lot System

	cout << "****************************************************************************" << endl;
	cout << "*************  WELCOME TO PARKING SYSTEM APPLICATION  ******************" << endl;
	cout << "****************************************************************************" << endl;
	cout << "*******************  SAMPLE INPUT COMMANDS  ****************************";
	cout << endl;

	while (1)
	{

		// main menu

		cout << "Press 1. Display List " << endl;
		cout << "Press 2. Insert New Car at Nearest Slot \t" << endl;
		cout << "Press 3. For Find details" << endl;
		cout << "Press 4. For Exit" << endl;

		// asking for user choice
		cout << "Enter Your Choice : " << endl;
		int choice;
		cin >> choice;

		string rgno;
		string carColor;
		int nearest_slot;

		// switch case  to handle different scenerio

		switch (choice)
		{
		// display functionality
		case 1:

			p1.display();
			break;

		// insertion functionality
		case 2:

			nearest_slot = p1.getSlot(); // getting nearest empty slot

			if (nearest_slot != -1)
			{

				// asking car details to user

				cout << "Enter Number Plate Registration Number : (eg. : KA-01-HH-1234 ) " << endl;
				cin >> rgno;
				cout << "Enter Car Colour : " << endl;
				cin >> carColor;

				// adding car to parking and update the information in Parking Lot

				p1.insert(nearest_slot, rgno, carColor);
			}
			else // if parking is FULL
			{
				cout << "All Parking slots are filled ...Sorry....Come after some time" << endl;
			}

			break;

		// Search Service
		case 3:
			p1.search();
			break;

		// greeting service
		case 4:
			cout << "Thank you For using This System " << endl;
			return 0;

			// warning for wrong choice

		default:
			cout << "Enter Valid choice please" << endl;
		}
	}
}
