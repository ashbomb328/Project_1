/*
Ashton Carruthers- Covid-19 store helper
The use of this program is to take a store and have a program keep track of people entering until the limit reached.
It will record the departures of customers and then update how much new space is available. Once the store is filled then an output message
will be sent that the store cant accept anymore customers at the time.
*/






#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>

using std::cout;
using std::endl;
using std::cin;
using std::ifstream;

const int NUMBER_OF_ROWS = 4;
const int ROW_SIZE = 4;
const char AVAILABLE_SPOTS = 'A';
const char CUSTOMERS_LEAVING = 'C';
const char CUSTOMERS_IN_THE_STORE = 'S';
const char CUSTOMERS_TRANSFERING = 'T' ; // like the oppisite exit of the entrence cause it could be in the mall

//prints the grid for the user to see
void printGrid(const char storeSize[NUMBER_OF_ROWS][ROW_SIZE])
{
    for(int i = 0; i < 16; i++)
    {
        cout << "-";
    }
    cout << endl;
    for(int a=0; a<NUMBER_OF_ROWS; a++)    //makes loop for the code
    {
        for(int b=0; b< ROW_SIZE; b++)
        {
            cout << storeSize[a][b] << " ";
        }
        cout << endl;
    }
    for(int i = 0; i < 16; i++)
        {
        cout << "-";
    }
    cout << endl;

}
void readGrid(char storeSize[NUMBER_OF_ROWS][ROW_SIZE])   //reads in the text file
{
    ifstream inputStore;             //reads the data given by the file
    char store;                       //given a variable to hold the data

    inputStore.open("store.txt"); //opens the specific file

    if(inputStore) //makes sure the file is an actual file
    {
        //loop to assign values to array elements
        for(int c = 0; c < NUMBER_OF_ROWS; c++)
        {
        for(int d = 0; d < ROW_SIZE; d++)
    {
        inputStore >> store; //read data from file into variable


    if(store == '0')         // desgnated the text file numbers a specifc value so a 0 is turned in the const char A for available spots
 {
    storeSize[c][d]=AVAILABLE_SPOTS;
 }
    else if(store == '1')
{
        storeSize[c][d]=CUSTOMERS_LEAVING;
    }
        else if(store == '2')
    {
        storeSize[c][d]=CUSTOMERS_IN_THE_STORE;
    }

    else if(store == '3')
{
        storeSize[c][d]= CUSTOMERS_TRANSFERING;
    }

    }
}
    inputStore.close();
    }
    printGrid(storeSize);  //prints grid
}



void customersLeaving(char storeSize[NUMBER_OF_ROWS][ROW_SIZE])
{                                                                                        //does the LEAVINGs of the customers
    for(int f = 0; f<NUMBER_OF_ROWS; f++)
    {
    for(int g=0; g<ROW_SIZE; g++)
{
    if(storeSize[f][g] == CUSTOMERS_LEAVING)
{
    storeSize[f][g] = AVAILABLE_SPOTS;
    }

  }
 }
}


// This section of code goes through and does the transfer array for people leaving and transferring to a different store in the mall
void customerTranfers(char storeSize[NUMBER_OF_ROWS][ROW_SIZE])
{
    char *avaibleSpace, *transferCustomer;
    int spaceAvailable = 0, numberTransfer = 0;
   customersLeaving(storeSize);
for(int i = (NUMBER_OF_ROWS - 1); i>= 0;i--)
    {
    for(int j = (ROW_SIZE - 1); j>= 0;j--)
{
    if(storeSize[i][j] == AVAILABLE_SPOTS)
    {
        avaibleSpace = &storeSize[i][j];
        spaceAvailable++;
    }
    else if(storeSize[i][j] == CUSTOMERS_TRANSFERING)
    {
    transferCustomer = &storeSize[i][j];
    numberTransfer++;
    }
        }
    }
    if(spaceAvailable > 0)
    {
        avaibleSpace = new char[spaceAvailable];
    for(int i = 0; i < NUMBER_OF_ROWS; i++)
 {
    for(int j = 0; j < ROW_SIZE; j++)
{
      if(storeSize[i][j] == CUSTOMERS_TRANSFERING)
        {
            storeSize[i][j] = AVAILABLE_SPOTS;
            avaibleSpace = &storeSize[i][j];
            spaceAvailable++;
        }
       if(numberTransfer > 0 && (storeSize[i][j] == AVAILABLE_SPOTS))
    {
        storeSize[i][j] = CUSTOMERS_IN_THE_STORE;
        numberTransfer--;
     }
    }
  }

    }

    printGrid(storeSize);
}

int getCustomerAmount(char storeSize[NUMBER_OF_ROWS][ROW_SIZE])   //had to create a section that gets the amount of customers are able to come in
 {
    int avaibleSpace = 0;
    for(int h = (NUMBER_OF_ROWS - 1); h >= 0; h--)
   {
    for(int k = (ROW_SIZE - 1); k >= 0; k--)
    {
     if(storeSize[h][k] == AVAILABLE_SPOTS)
     {
        avaibleSpace++;
     }
    }
   }
    return avaibleSpace;
}
int newCustomer(int totalCustomers)
 {

	return totalCustomers;
}

int main()
{
    cout << "The store can only hold up to 16 customers according to COVID-19 rules." << endl <<
    "The 'C' stands for customers leaving through the main entrance, The 'T' stands for customers" << endl <<
    "transferring to a different store, more used in a mall scenarios where there can be two exits, The" << endl <<
    "'A' stands for available spots in the store within the 16 limit, and finally the 'S' stands for a" << endl << "customer already in the store." << endl;
    char arr[NUMBER_OF_ROWS][ROW_SIZE];
    readGrid(arr);
    cout << "The store before people leave or transfer" << endl;
    customerTranfers(arr);
	cout << "Grid updated from Customers that have either left through the front or transferred to another store" << endl << endl;
	while (getCustomerAmount(arr) > 0)
    {
    int newCustomer;
    cout << "Now enter the number of customers entering that fit within the range, from one up to "<< getCustomerAmount(arr) << ": ";
    cin >> newCustomer;
    if(newCustomer > getCustomerAmount(arr))
        {

    }
    for(int i = 0; i < NUMBER_OF_ROWS && newCustomer > 0; i++)
 {
    for(int j = 0; j < ROW_SIZE && newCustomer > 0; j++)
{
    if(arr[i][j] == AVAILABLE_SPOTS)
        {
        arr[i][j] = CUSTOMERS_IN_THE_STORE;
        newCustomer--;
    }
    }
 }
 printGrid(arr);
 cout << "New store numbers updated" << endl << endl;
}
cout << endl << endl << " No more customers can enter at this time " << endl;
printGrid(arr);
  return 0;
 }

