// Carson McDonald
// Programming Fundamentals 2
// Dr. T
// COSC-1437
// 5-1-24
// This program's purpose is in a restraunt to calculate the total cost of the
// meal, print a receipt, and calculate the tax and tip.
// Main for Unit 5 Assignment McDonald
#include "Unit5_Assignment_McDonald.h"

int main() 
{
    // This do while loop will allow for the user to keep calling the following functions until they choose to exit.
    char additionalOrder;
    do 
    {
        double subtotal = 0.00;
        vector<MenuItem> wholeMenu;
        populateMenu(wholeMenu); // Put some default values in the menu.
        showMenu(wholeMenu);     // Print the current data of the menu on screen.
        acceptOrder(wholeMenu, subtotal);
        printReceipt(wholeMenu, subtotal);
        cout << "Would you like to place another order? (Y/N)" << endl;
        cin >> additionalOrder;
    } while (additionalOrder == 'Y' || additionalOrder == 'y');
    cout << "Have a great day!" << endl;

    return 0;
}