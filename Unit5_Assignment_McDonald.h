// Carson McDonald
// Programming Fundamentals 2
// Dr. T
// COSC-1437
// 5-1-24
// Header File for Unit 5 Assignment McDonald
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class MenuItem
{
private:
    string name;
    double itemCost;
    string desc;
    char addLetter;
    char removeLetter;
    int count;

public:
    // Constructor.
    MenuItem(string name = " ", double itemCost = 0.00, string desc = " ",
             char addLetter = ' ', char removeLetter = ' ', int count = 0);
    // Setters or Mutators.
    void setName(string name);
    void setItemCost(double itemCost);
    void setDesc(string desc);
    void setAddLetter(char addLetter);
    void setRemoveLetter(char removeLetter);
    void setCount(int count);
    // Getters or Accessors.
    string getName() { return name; }
    double getItemCost() { return itemCost; }
    string getDesc() { return desc; }
    char getAddLetter() { return addLetter; }
    char getRemoveLetter() { return removeLetter; }
    int getCount() { return count; }
};

// Function definitions.
void populateMenu(vector<MenuItem> &entireMenu);
void showMenu(vector<MenuItem> &m);
void acceptOrder(vector<MenuItem> &m, double &subtotal);
void printReceipt(vector<MenuItem> &m, double &subtotal);

// Constructor definition
MenuItem::MenuItem(string name, double itemCost, string desc,
                   char addLetter, char removeLetter, int count)
    : name(name), itemCost(itemCost), desc(desc),
      addLetter(addLetter), removeLetter(removeLetter), count(count) {}

// Setters or Mutators. Pointers thowards those actual values.
void MenuItem::setName(string name) 
{
    this->name = name;
}

void MenuItem::setItemCost(double itemCost) 
{
    this->itemCost = itemCost;
}

void MenuItem::setDesc(string desc) 
{
    this->desc = desc;
}

void MenuItem::setAddLetter(char addLetter) 
{
    this->addLetter = addLetter;
}

void MenuItem::setRemoveLetter(char removeLetter) 
{
    this->removeLetter = removeLetter;
}

void MenuItem::setCount(int count) 
{
    this->count = count;
}

void populateMenu(vector<MenuItem> &entireMenu) 
{
    // Put some default values in our Menu.
    const int numItems = 7;
    vector<string> defaultMenuNames = {
        "Chicken Sandwich", "Chicken Salad", "Hot Dog",   "Corn Dog",
        "French Fries",     "Tater Tots",    "Dr. Pepper"};
    vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    vector<double> defaultMenuCost = {5.00, 4.00, 3.00, 3.00, 2.00, 2.00, 1.00};
    vector<string> defaultMenuDescriptions = {
        "Crispy Chicken, Brioche Bun, Lettuce, Tomato, Mayo, and Pickles.",
        "Crispy Chicken, Lettuce, Tomato, Cucumber, Cheese, Bacon Bits, and Ranch Dressing.",
        "Frank Weeney, Pretzel Bun, Mustard, and Ketchup.",
        "Crispy Corn Dog served with Ketchup and Mustard.",
        "Crispy French Fries served with Ketchup and Mustard.",
        "Crispy Tater Tots served with Ketchup and Mustard.",
        "A 32 oz Dr. Pepper."};
    for (int i = 0; i < numItems; i++) 
    {
        // Create MenuItem objects and add them to entireMenu
        MenuItem item(defaultMenuNames[i], defaultMenuCost[i], defaultMenuDescriptions[i],
                      defaultAddLetters[i], defaultRemoveLetters[i], 0);
        entireMenu.push_back(item);
    }
}

void showMenu(vector<MenuItem> &m) {
    cout << "\x1b[1;33m";
    cout << fixed << setprecision(2); // Set doubles to 2 decimal places.
    cout << "The Concession Zone" << endl;
    cout << "______________________________________________________" << endl;
    cout << "ADD:  \tNAME: \t\t\t COST: \tREMOVE:\tCOUNT:" << endl;
    cout << "______________________________________________________" << endl;

    for (int i = 0; i < m.size(); i++) {
        cout << m[i].getAddLetter() << ")    " << setw(10) << m[i].getName()
             << setw(5) << "$" << m[i].getItemCost() << setw(5) << "("
             << m[i].getRemoveLetter() << ")" << setw(7) << m[i].getCount()
             << setw(13) << "\nDESC: " << m[i].getDesc() << "\n\n";
    }
    cout << "\x1b[0m";
}

void acceptOrder(vector<MenuItem> &m, double &subtotal) 
{
    char option = '\0'; // The user-selected menu item.

    do 
    {
        cout << "\nPlease choose an item (x to Exit): ";
        cin >> option;

        bool found = false; // Flag to track if the option is found in the menu

        for (int i = 0; i < m.size(); i++) {
            if (option == m[i].getAddLetter()) {
                found = true;
                cout << "\nMenu Item " << m[i].getAddLetter() << " selected.";
                m[i].setCount(m[i].getCount() + 1); // Increment the count by 1.
                cout << "\033[2J\033[1;1H"; // Clear screen.
                cout << "\n1 UP on " << m[i].getName() << endl;
                subtotal += m[i].getItemCost(); // Increment the subtotal by the cost of the item
                showMenu(m); // show the updated menu.
                cout << "\nSubtotal: $" << subtotal << endl;
            } else if (option == m[i].getRemoveLetter()) {
                found = true;
                cout << "\nRemove Item " << m[i].getRemoveLetter() << " selected.";
                if (m[i].getCount() > 0) { // Subtract if and only if the count is > 0.
                    m[i].setCount(m[i].getCount() - 1); // Decrement the count by 1.
                    cout << "\033[2J\033[1;1H"; // Clear screen.
                    cout << "\n1 DOWN on " << m[i].getName() << endl;
                    subtotal -= m[i].getItemCost(); // Decrement the subtotal by the cost of the item.
                    showMenu(m); // Show the updated menu.
                    cout << "\nSubtotal: $" << subtotal << endl;
                } else {
                    cout << "\nItem count must be > 0 to remove: " << m[i].getName() << endl;
                }
            }
        }

        if (!found && option != 'x' && option != 'X') {
            cout << "\nInvalid input (" << option << "). Please try again." << endl;
        }

    } while (option != 'x' && option != 'X');

    cout << "\nThank you for placing your order." << endl;
}

void printReceipt(vector<MenuItem> &m, double &subtotal) 
{
    double tip = 0.0;
    cout << "Would you like to add a tip? (Suggested amounts: 20%)" << endl;
    cout << "Enter tip amount: $";
    cin >> tip;

    double tax = subtotal * 0.0825;
    cout << "\nThank you for your tip of $" << tip << endl;
    cout << "\nYour total due is: $" << subtotal + tip + tax << endl;

    cout << "\nWill you be paying with cash or card?" << endl;
    cout << "Enter 1 for cash or 2 for card: ";
    int payment = 0;
    cin >> payment;

    while (payment != 1 && payment != 2) 
    {
        cout << "\nInvalid input. Please enter 1 for cash or 2 for card: ";
        cin >> payment;
    }

    if (payment == 1) 
    {
        cout << "\nPlease enter your cash amount: $";
        double cash = 0.0;
        cin >> cash;
        cout << "\nYour change is: $" << cash - (subtotal + tip + tax) << endl;
        cout << "\nThank you for dining with us!" << endl;
    } else if (payment == 2) {
        cout << "\nThank you for dining with us!" << endl;
    }
    cout << "Here's your receipt:" << endl;
  // So that my receipt can be show on the console and in the text file I made sure to include both.
  ofstream myfile ("Printed_Reciept.txt");
  cout << "\x1b[1;33m"; // Character sequence for yello text.
  if (myfile.is_open()){
      myfile << "____________________" << endl;
      myfile << "RECEIPT" << endl;
      myfile << "____________________" << endl;
      myfile << "ITEMS: " << endl;
      myfile << "PRICE: " << endl;
      myfile << "AMOUNT: " << endl;
      myfile << "____________________" << endl;
    for (int i = 0; i < m.size(); i++) 
    {
          myfile << m[i].getName() << endl
             << "$" << m[i].getItemCost() << endl
             << "Amount:" << m[i].getCount() << endl;
    }
      myfile << "____________________" << endl;
      myfile << "Subtotal: $" << subtotal << endl;
      myfile << "Tip: $" << tip << endl;
      myfile << "Tax: $" << tax << endl;
      myfile << "Total Due: $" << subtotal + tip + tax << endl;
      myfile << "____________________" << endl;
    cout << "____________________" << endl;
    cout << "RECEIPT" << endl;
    cout << "____________________" << endl;
    cout << "ITEMS: " << endl;
    cout << "PRICE: " << endl;
    cout << "AMOUNT: " << endl;
    cout << "____________________" << endl;
    for (int i = 0; i < m.size(); i++) 
    {
        cout << m[i].getName() << endl
             << "$" << m[i].getItemCost() << endl
             << "Amount:" << m[i].getCount() << endl;
    }
    cout << "____________________" << endl;
    cout << "Subtotal: $" << subtotal << endl;
    cout << "Tip: $" << tip << endl;
    cout << "Tax: $" << tax << endl;
    cout << "Total Due: $" << subtotal + tip + tax << endl;
    cout << "____________________" << endl;
    myfile.close();}
  cout << "\x1b[1;0m"; // Character sequence for normal text.
}

}