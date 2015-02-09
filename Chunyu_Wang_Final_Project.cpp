//************************************************************************************************
// Assignment 8: Final project (b. Customer Account)
// Name: Chunyu Wang
// Header file: customerAccount.h
//************************************************************************************************
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
class customerAccount
{
public:
	void enterRecord();
	void displayRecord() const;
	void deleteRecord();
	customerAccount();
	int index;
	string name;
	string address;
	string city;
	string state;
	string zip;
	string tel;
	double balance;
	int year;
	int month;
	int day;
};

//************************************************************************************************
// Assignment 8: Final project (b. Customer Account)
// Name: Chunyu Wang
// Implementation file: customerAccountImp.cpp
//************************************************************************************************
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "customerAccount.h"
using namespace std;
void customerAccount::enterRecord()
{
	cout<<"Name (First Last): ";
	getline(cin, name);
	cout<<"Address: ";
	getline(cin, address);
	cout<<"City: ";
	getline(cin, city);
	cout<<"State: ";
	getline(cin, state);
	cout<<"Zip: ";
	getline(cin, zip);
	cout<<"Telephone: ";
	getline(cin, tel);
	do
	{
	cout<<"Balance: $";
	cin>>balance;
	if (balance<0)
		cout<<"Balance cannot be negative!\n";
	} while (balance<0);
	do
	{
	cout<<"Year (1900~2100): ";
	cin>>year;
	if (year<1900||year>2100)
		cout<<"Invalid year!\n";
	} while (year<1900||year>2100);
	do
	{
	cout<<"Month (1~12): ";
	cin>>month;
	if (month<1||month>12)
		cout<<"Invalid month!\n";
	} while (month<1||month>12);
	do
	{
	cout<<"Day (1~31): ";
	cin>>day;
	if (day<1||day>31)
		cout<<"Invalid day!\n";
	} while (day<1||day>31);
}

void customerAccount::displayRecord() const
{
	cout<<"Name: "<<name<<endl;
	cout<<"Address: "<<address<<endl;
	cout<<"City: "<<city<<"  ";
	cout<<"State: "<<state<<"  ";
	cout<<"Zip: "<<zip<<endl;
	cout<<"Telephone: "<<tel<<endl;
	cout<<"Balance: $"<<fixed<<showpoint<<setprecision(2)<<balance<<endl;
	cout<<"Date of last payment: ";
	cout<<month<<"/"<<day<<"/"<<year;
	cout<<endl<<endl;
}

void customerAccount::deleteRecord()
{
	name=" "; //set name to empty
	address=" ";
	city=" ";
	state=" ";
	zip=" ";
	tel=" ";
	balance=0.0;
	month=0;
	day=0;
	year=0;
}

customerAccount::customerAccount() //constructor
{
	customerAccount::deleteRecord();
}

//************************************************************************************************
// Assignment 8: Final project (b. Customer Account)
// Name: Chunyu Wang
// User file: customerAccountUserFile.cpp
//************************************************************************************************
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "customerAccount.h"
using namespace std;
void displayMenu();
int main()
{
	int selection; //selection from menu
	int i,n;
	const int MAX_NUM=100; //change maximum number of records, if needed
	int occupied=0; //this is a counter for any existing customers stored in "data.txt"
	customerAccount customer[MAX_NUM];
	string customername; //for keyboard input customer name
	bool found;
	ifstream inData;
	ofstream outData;
	char ch; //for the newline character and discard it
	
	for (i=0;i<MAX_NUM;i++)
		customer[i].index=i+1; //initialize the customer index

	//check if data file exist before any operations
	inData.open("data.txt");
	if (inData)
		{
			for (i=0;i<MAX_NUM;i++)
			{							
			inData>>customer[i].index; //Note: in "data.txt", the first line is customer index
			inData.get(ch); //read the newline character and discard it
			getline(inData, customer[i].name);
			getline(inData, customer[i].address);
			getline(inData, customer[i].city);
			getline(inData, customer[i].state);
			getline(inData, customer[i].zip);
			getline(inData, customer[i].tel);
			inData>>customer[i].balance;
			inData>>customer[i].year;
			inData>>customer[i].month;
			inData>>customer[i].day;
			inData.get(ch); //read the newline character and discard it
			}
			for (i=0;i<MAX_NUM;i++)
				if (customer[i].name!=" "&&customer[i].name!="")
					occupied++;
		}
	inData.close();

	do //begin loop for selection from menu
	{
			//next line is for debugging purpose only
			//cout<<"occupied "<<occupied<<", available "<<MAX_NUM-occupied;
	
	found=0; //reset found=false
	displayMenu();
	cin>>selection;
	switch (selection)
	{
	case 1: //keyboard input new record
		cout<<"Note: The system can hold a maximum of "<<MAX_NUM<<" customers.\n";
		if (occupied>0)
			cout<<"There are already "<<occupied<<" customer(s) in the records (select menu 5 or see \"data.txt\")";
		do
		{
			cout<<"How many new customers do you want to enter their new records? ";
			cin>>n;
			if (n>MAX_NUM-occupied)
				cout<<"That\'s too many! Please re-enter. \n";
		} while (n>MAX_NUM-occupied||n<=0);
		for (i=0;i<n;i++)
		{
			cout<<"Please enter new record for customer "<<i+occupied+1<<"\n";
			cin.ignore(100,'\n');
			customer[i+occupied].enterRecord();
		}
		occupied+=n;
		cout<<"You have successfully entered "<<n<<" record(s).\n";
		break;

	case 2: //display single record on screen
		cout<<"Please enter customer name: ";
		cin.ignore(100,'\n');
		getline(cin, customername);
		for (i=0;i<MAX_NUM;i++)
		{
			if (customername==customer[i].name)
				{
					customer[i].displayRecord();
					found=1;
				}
		}
		if (!found)
			cout<<"Customer not found!\n";
		break;

	case 3: //delete record
		cout<<"Please enter customer name: ";
		cin.ignore(100,'\n');
		getline(cin, customername);
		for (i=0;i<MAX_NUM;i++)
		{
			if (customername==customer[i].name)
				{
					found=1;
					customer[i].deleteRecord();
					cout<<"The record for "<<customername<<" has been deleted.\n";
					occupied--;
				}
		}
		for (i=0;i<MAX_NUM-1;i++)
		{
			if (customer[i].name==""||customer[i].name==" ") //delete empty record, move next record up
				{
					customer[i]=customer[i+1];
					customer[i+1].deleteRecord();
				}
		}
		if (!found)
			cout<<"Customer not found!\n";
		break;

	case 4: //change record
		cout<<"Please enter customer name: ";
		cin.ignore(100,'\n');
		getline(cin, customername);
		for (i=0;i<MAX_NUM;i++)
		{
			if (customername==customer[i].name)
				{
					found=1;
					customer[i].enterRecord();
					cout<<"The record for "<<customername<<" has been changed.\n";
				}
		}
		if (!found)
			cout<<"Customer not found!\n";
		break;

	case 5: //display entire file on screen
		cout<<endl;
		for (i=0;i<MAX_NUM;i++)
		{
			if (customer[i].name!=" "&&customer[i].name!="") //will not display empty records
				{
					cout<<" Record #"<<i+1<<": "<<endl;
					customer[i].displayRecord();
					found=1;
				}
		}
		if (!found)
			cout<<"No record is found!\n";
		break;

	case 6: //save all data to file
		outData.open("data.txt");
		if (outData)
			for (i=0;i<MAX_NUM;i++)
			{
				if (customer[i].name!=" "&&customer[i].name!="")
				{
				outData<<i+1<<endl; //output customer index to file
				outData<<customer[i].name<<endl;
				outData<<customer[i].address<<endl;
				outData<<customer[i].city<<endl;
				outData<<customer[i].state<<endl;
				outData<<customer[i].zip<<endl;
				outData<<customer[i].tel<<endl;
				outData<<customer[i].balance<<endl;
				outData<<customer[i].year<<endl;
				outData<<customer[i].month<<endl;
				outData<<customer[i].day<<endl;
				}
			}
		else
			cout<<"Cannot save \"data.txt\"!\n";
		outData.close();
		cout<<"All customer\'s information has been saved to \"data.txt\"!\n";
		cout<<"Existing file, if any, has been overwritten and updated!\n";
		break;

	case 0: //quit
		break;
	}
	} while (selection!=0); //loop until select 0 for quit
		
	system("pause");
	return 0;
}

void displayMenu()
{
	cout<<endl<<"--------------Welcome to Customer Account Management System---------------\n";
	cout<<"Please select one of the following operations:\n";
	cout<<"1. Enter new customer records.\n";
	cout<<"2. Search for a particular customer record and display it.\n";
	cout<<"3. Search for a particular customer record and delete it.\n";
	cout<<"4. Search for a particular customer record and change it.\n";
	cout<<"5. Display the entire records.\n";
	cout<<"6. Save all records to \"data.txt\" (Warning: Existing file will be overwritten!)\n";
	cout<<"0. Quit\n";
	cout<<"Your selection: ";
}

/************************************************************************************************
//Below is the input/output file named "data.txt", which should be saved as a separate file.
1
Allan Anderson
1111 Arlington Ave
Ashland
AL
10001
(111) 111-1111
100
2001
1
11
2
Barrett Brown
2222 Bristol Blvd
Baytown
RI
20002
(222) 222-2222
222.2
2002
2
22
3
Caryn Campbell
3333 Caroline St
Clayton
CT
30003
(333) 333-3333
333.33
2003
3
30
//*****************************************end of "data.txt"************************************/