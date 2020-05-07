
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// Global Variables

ofstream fout;
ifstream fin;
fstream fileTool;

const int LIMITROW = 100;
const int LIMITCOLUMN = 100;

int rows = 0;
int columns = 0;
int ticketsSold = 0;
double revenue = 0;

char seatingChart[LIMITROW][LIMITCOLUMN];


/* PROTOTYPES */

// Collects number of rows.
void rowInput(int &rows);

// Collects number of columns.
void columnInput(int &columns);

// Collects price of each row.
void priceInput(vector<double> &rowPrices);

// Stores rows, columns and rowPrices array in theater.txt file.
void storeInConfig(int rows, int columns, vector<double> &rowPrices);

// Reads values of rows and columns from theater.txt.
void readFromConfig(int &rows, int &columns, vector<double> &rowPrices);

// Fills seatingChart with '#'.
void fillChart();

// Prints seating chart with #.
void printChart(int rows, int columns);

// Sells single tickets.
void sellTicket(vector<double> &rowPrices);

// Sells multiple tickets.
void sellTickets(vector<double> &rowPrices);

// Runs through seating char to check for #, then increments variable if true.
int seatsAvailable();

// Clears global variables and prompts for rows / columns again
void resetProgram(vector<double> &rowPrices);

// Prints main menu.
void mainMenu(vector<double> &rowPrices);

// Initializes
void initialize(int rows, int columns, vector<double> &rowPrices);

int main() {
  char setting;
  vector<double> rowPrices;

cout << "Welcome to the seating chart assistant program!"<< endl;
// Reads previous information stored in theater.txt
readFromConfig(rows,columns,rowPrices);

cout << "Pre-loaded Rows: " << rows << endl;
cout << "Pre-loaded Columns: " << columns << endl;

// Asks is user wants to put in new price / seating info or use old
cout << "Would you like to use your (o)ld settings or create (n)ew ones? ";
cin >> setting;
// If using old, fill chart with # and display main menu
if (setting == 'o') {
  fillChart();
  mainMenu(rowPrices);
}
// If using new, prompt for all neccesary information,
// store in config file, fill chart, show menu.
if (setting == 'n') {
  rowInput(rows);
  columnInput(columns);
  priceInput(rowPrices);
  storeInConfig(rows, columns, rowPrices);
  readFromConfig(rows,columns,rowPrices);
  fillChart();
  mainMenu(rowPrices);
}

  return 0;
}

// Collects number of rows.
void rowInput(int &rows) {

  cout << "Welcome! Enter the amount of rows (Max of " << LIMITROW << "): ";
  cin >> rows;
  // Checks to make sure that rows are within limits.
  while (rows > LIMITROW || rows < 1) {
    cout << "Error, number of rows is not valid." << endl;
    cout << "Please enter the amount of rows: ";
    cin >> rows;
  }
}

// Collects number of columns.
void columnInput(int &columns) {

  cout << "Next, enter the amount of columns (Max of " << LIMITCOLUMN << "): ";
  cin >> columns;
  // Checks to make sure that columns are within limits.
  while (columns > LIMITCOLUMN || columns < 1) {
    cout << "Error, number of columns is not valid." << endl;
    cout << "Please enter the amount of columns: ";
    cin >> columns;
  }
}

// Collects price of each row.
void priceInput(vector<double> &rowPrices) {
  double price;
  cout << "Now, you will enter the price of each row." << endl;

  // Cycles through number of rows and asks for price of seats in each.
  for (int i = 0; i < rows; i++) {
    cout << "Price of row " << i + 1 << ": $";
    cin >> price;
    rowPrices.push_back(price);


    // If an invalid price (<0) is entered, asks for and stores again.
    if (rowPrices.at(i) < 0) {
      rowPrices.pop_back();
      cout << "Error, invalid price." << endl;
      cout << "Please enter the price of row " << i + 1 << "again: ";
      cin >> price;
      rowPrices.push_back(price);
    }
  }
}

// Stores rows, columns and rowPrices array in theater.txt file.
void storeInConfig(int rows, int columns, vector<double> &rowPrices) {

  // Opens theater.txt and checks if it's open.
  fout.open("theater.txt");

  // Error for if it cannot be opened.
  if (!fout.is_open()) {
    cout << "Error, unable to open file" << endl;
  }

  // Prints rows, columns and array to config file.
  else {
    fout << rows << endl;
    fout << columns << endl;
    for (int i = 0; i < rows; i++) {
      fout << rowPrices.at(i) << endl;
    }
  }
 fout.close();
}

// Reads values of rows and columns from theater.txt.
void readFromConfig(int &rows, int &columns, vector<double> &rowPrices) {
double price;

  fin.open("theater.txt");

  if (!fin.is_open()) {
    cout << "Error, unable to open file" << endl;
  } else {
      fin >> rows;
      fin >> columns;
      for (int i = 0; i < rows; i++) {
        fin >> price;
        rowPrices.push_back(price);
      }
    }
    fin.close();
  }


// Fills seatingChart with '#'.
void fillChart() {
  for (int l = 0; l < rows; l++) {
    for (int m = 0; m < columns; m++) {
      seatingChart[l][m] = '#';
    }
  }
}


// Prints seating chart with #.
void printChart(int rows, int columns) {

  cout << endl;

  // Prints column numbers
  cout << "        ";
  cout << "Column";
  cout << endl;
  cout << "        ";

// Displays
  for (int i = 1; i <= columns; i++) {
      if (i == 1) {
          cout << "0";
      }
      else if (i % 10 == 0) {
          cout << i / 10;
      }
      else {
          cout << " ";
      }
  }
  cout << endl;

 cout << "        ";
 for (int k = 1; k <= columns; k++) {
     cout << k % 10;
 }
 cout << endl;

  // Outputs values in seatingChart.
  for (int i = 0; i < rows; i++) {
      if (i >= 9) {
          cout << "Row " << i + 1 << ": ";
      } else {
      cout << "Row " << i + 1 << ":  ";
      }
    for (int j = 0; j < columns; j++) {
      cout << seatingChart[i][j];
    }
    cout << endl;
  }

  cout << endl;
}

// Sells multiple tickets.
void sellTickets(vector<double> &rowPrices) {
  int rowChoice;
  int columnChoiceOne;
  int columnChoiceTwo;
  char seatChar;
  bool isSold = false;

  // Gets row of series of seats being sold
  cout << "Enter the row of the seats: ";
  cin >> rowChoice;
  while (rowChoice < 1 || rowChoice > rows) {
    cout << "Invalid row, enter another: ";
    cin >> rowChoice;
  }
  // Gets beginning of range
  cout << "Enter the number of the first seat (the one on the left): ";
  cin >> columnChoiceOne;
  while (columnChoiceOne < 1 || columnChoiceOne > columns) {
    cout << "Invalid seat, enter another within range: ";
    cin >> columnChoiceOne;
  }
  // Gets end of range
  cout << "Enter the number of the last seat (the one on the right): ";
  cin >> columnChoiceTwo;
  while (columnChoiceTwo < 1 || columnChoiceTwo > columns) {
    cout << "Invalid seat, enter another within range: ";
    cin >> columnChoiceTwo;
  }

  // If seat is sold, subtract ticketsSold and revenue, then display error and set isSold to true.
  for (int i = columnChoiceOne - 1; i < columnChoiceTwo; i++) {
    if (seatingChart[rowChoice - 1][i] == '*') {
      cout << endl;
      cout << "Error, seat " << i + 1 << " already sold." << endl;
      bool isSold = true;
      ticketsSold--;
      revenue -= rowPrices.at(rowChoice - 1);
      break;
    } else {
        bool isSold = false;
    }
  }
  // If isSold is false, sell seat and update ticketsSold and revenue.
if (isSold == false) {
  for (int j = columnChoiceOne - 1; j < columnChoiceTwo; j++) {
      seatingChart[rowChoice - 1][j] = '*';
      ticketsSold++;
      revenue += rowPrices.at(rowChoice - 1);
    }
  }
}

// Sells single tickets.
void sellTicket(vector<double> &rowPrices) {
  char choice = 'y';
  int rowChoice;
  int columnChoice;
  char seatChar;

  // Akss for row and column of seat being sold and checks that they're valid.
  while (choice == 'y') {
    // Gets row of seat and checks validity.
    cout << "Enter the row of the seat: ";
    cin >> rowChoice;
    while (rowChoice < 1 || rowChoice > rows) {
      cout << "Invalid row, enter another: ";
      cin >> rowChoice;
    }
    // Gets column of seat and checks validity.
    cout << "Enter the column of the seat: ";
    cin >> columnChoice;
    while (columnChoice < 1 || columnChoice > columns) {
      cout << "Invalid column, enter another: ";
      cin >> columnChoice;
    }

    // Checks to see if selection is sold or not.
    if (seatingChart[rowChoice - 1][columnChoice - 1] == '*') {
      cout << "Seat already sold, would you like to sell another? (y)es or (n)o: ";
      cin >> choice;

    // If seat isn't sold, update it with a '*',
    // increment ticketsSold and update the revenue.
    } if (seatingChart[rowChoice - 1][columnChoice - 1] == '#') {
      seatingChart[rowChoice - 1][columnChoice - 1] = '*';
      ticketsSold++;
      revenue += rowPrices.at(rowChoice - 1);
    }
    cout << endl;
    cout << "Would you like to sell another seat? (y)es or (n)o: ";
    cin >> choice;

  }
}

// Runs through seating char to check for #, then increments variable if true.
int seatsAvailable() {
  int available = 0;
  for (int l = 0; l < rows; l++) {
    for (int m = 0; m < columns; m++) {
      if (seatingChart[l][m] == '#') {
          available++;
      }
    }
  }
return available;
}

 // Clears global variables and prompts for rows / columns again
void resetProgram(vector<double> &rowPrices) {
      revenue = 0;
      ticketsSold = 0;
      rows = 0;
      columns = 0;
      // Clears the rowPrices vector
      rowPrices.clear();

      // Runs all the original functions to get info about the board
      rowInput(rows);
      columnInput(columns);
      priceInput(rowPrices);
      storeInConfig(rows, columns, rowPrices);
      readFromConfig(rows, columns, rowPrices);
      fillChart();
    }

// Prints main menu.
void mainMenu(vector<double> &rowPrices) {

    char sellChoice;
    int userChoice;

      cout << endl;

      cout << "Choose from one of the following:" << endl;
      cout << "1). Display a seating chart" << endl;
      cout << "2). Sell one or more tickets" << endl;
      cout << "3). View how many tickets have been sold" << endl;
      cout << "4). View how many seats are available" << endl;
      cout << "5). View the total revenue" << endl;
      cout << "6). Reset the program and re-enter seating and pricing information" << endl;
      cout << "7). Exit program" << endl;

      cout << "Choice: ";
      cin >> userChoice;
      cout << endl;

      // Checks userChoice to see if valid.
      while (userChoice != 1 && userChoice != 2 && userChoice != 3 &&
             userChoice != 4 && userChoice != 5 && userChoice != 6 && userChoice != 7) {
        cout << "Error, invalid choice." << endl;
        cout << "Please choose a valid option: ";
        cin >> userChoice;
      }

      // Displays seating chart
      if (userChoice == 1) {
        printChart(rows, columns);
        mainMenu(rowPrices);
      }
      // Sells tickets.
      if (userChoice == 2) {
        cout << "Would you like to sell (o)ne ticket or (m)ultiple tickets?: ";
        cin >> sellChoice;
        while (sellChoice != 'o' && sellChoice != 'm') {
          cout << "Invalid input." << endl;
          cout
              << "Would you like to sell (o)ne ticket or (m)ultiple tickets?: ";
          cin >> sellChoice;
        }
        if (sellChoice == 'o') {
          sellTicket(rowPrices);
        }
        if (sellChoice == 'm') {
          sellTickets(rowPrices);
        }
        mainMenu(rowPrices);
      }

      // Displays number of tickets sold.
      if (userChoice == 3) {
        cout << ticketsSold << " ticket(s) have been sold." << endl;
        mainMenu(rowPrices);
      }

      if (userChoice == 4) {
          cout << "Seats available: " << seatsAvailable();
          cout << endl;
          mainMenu(rowPrices);
      }
      // Displays total revenue.
      if (userChoice == 5) {
        cout << "Total revenue: $" << revenue;
        cout << endl;
        mainMenu(rowPrices);
      }
      // Resets program and returns to main menu.
      if (userChoice == 6) {
        resetProgram(rowPrices);
        mainMenu(rowPrices);
      }
      // Exits program
      if (userChoice == 7) {
          exit(0);
      }
    }

