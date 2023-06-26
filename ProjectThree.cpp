/* Derbi Calderon
* June 18th, 2023
* Programming languages, CS 210
* Project Three
* Program to analyze text records generated throughout the day for a store named 
* Corner Grocer, it prints a menu and outputs the frequency of an inputted item,
* or prints the lists names and frequency, or prints them in a histogram with
* colors
*/
#include <iostream> // library for input output stream

#include <fstream> // library for file stream

#include <map> // library for maps

#include <string> // library for strings

using namespace std;

class Groceries { // class for grocries in input list

public:

    void printMenu(); // function prototype to print the menu options

    int searchGroceryItem(const string& item); // function prototype to search for an item and return its frequency

    void loadData(); // function prototype to load data from input file

    void saveData(); // function prototype to save item frequencies to a file

    void printFrequencies(); // function prototype to print item frequencies

    void printGroceryHisto(); // function prototype to print histogram of item frequencies

private:
   
    map<string, int> itemFreq; // Map to store item frequencies

};

void Groceries::loadData() { //Function implementation to open input file and load data into itemFreq map
    
    ifstream inputFile("groceryInput.txt"); // Open input file
    
    string item;

    while (getline(inputFile, item)) { //Function implementation to read file line by line
    
        itemFreq[item]++; // Increment item frequency in the map
    
    }

    inputFile.close(); // Close input file

}

void Groceries::printFrequencies() { //Function implementation print item frequencies
    
    for (const auto& entry : itemFreq) { // Iterate over itemFreq map
    
        cout << entry.first << " " << entry.second << endl; // Print item and its frequency
    
    }
}

void Groceries::printGroceryHisto() { //Function implementation to print histogram of item frequencies
    
    int colorIndex = 0; // Declare int to hold color index
    
    string colors[] = { "\033[91m", "\033[92m", "\033[93m", "\033[94m", "\033[95m", "\033[96m", "\033[97m" }; // Array to hold colors

    for (const auto& entry : itemFreq) { // Iterate over itemFreq map
        
        cout << colors[colorIndex % 7] << entry.first << " "; // Print colored item name

        for (int i = 0; i < entry.second; i++) { // Print asterisks for item frequency
        
            cout << "*"; // Print star
        
        }

        cout << "\033[0m" << endl; // Reset color and move to the next line
       
        colorIndex++; // Increment color index
    
    }

}

void Groceries::saveData() { //Function implementation to save item frequencies to a file
    
    ofstream outputFile("frequency.dat"); // Open output file

    for (const auto& entry : itemFreq) { // Iterate over itemFreq map

        outputFile << entry.first << " " << entry.second << endl; // Write item and its frequency to the file

    }

    outputFile.close(); // Close output file

}

int Groceries::searchGroceryItem(const string& item) { //Function implementation to search for an item and return its frequency
    
    if (itemFreq.count(item) > 0) { // Check if item is present in the itemFreq map
    
        return itemFreq[item]; // Return its frequency
    
    } else {
    
        return 0; // Return 0 if item is not found
    
    }

}

void Groceries::printMenu() { //Function implementation to print the menu options
   
    cout << "==========================================" << endl; // Print separator line
    
    cout << "Menu:" << endl; // Print menu title
    
    cout << "1. Search for an item" << endl; // Print option 1
    
    cout << "2. Print item frequencies" << endl; // Print option 2
    
    cout << "3. Print histogram" << endl; // Print option 3
    
    cout << "4. Exit" << endl; // Print option 4
    
    cout << "Enter your choice: "; // Prompt for user input

}

int main() {
    
    int userInput = -1; // Variable to store user's choice
    
    string item; // Variable to store item to search for
    
    Groceries groceries; // Create Groceries object
    
    groceries.loadData(); // Load data from input file
    
    cout << "=============== Welcome ==================" << endl; // Print welcome message
    
    while (userInput != 4) { // Loop until user chooses to exit
    
        groceries.printMenu(); // Print the menu options
        
        cin >> userInput; // Read user's choice
        
        cout << "==========================================" << endl; // Print separator line

        if (userInput == 1) { // If user chose option 1
        
            cout << "Enter the item to search for: "; // Prompt for item
            
            cin >> item; // Read item from user
            
            cout << "Frequency: " << groceries.searchGroceryItem(item) << endl; // Print item frequency
        
        }else if (userInput == 2) { // If user chose option 2
        
            groceries.printFrequencies(); // Print item frequencies
        
        } else if (userInput == 3) { // If user chose option 3
        
            groceries.printGroceryHisto(); // Print histogram
        
        }else if (userInput == 4) { // If user chose option 4
        
            groceries.saveData(); // Save data to file
           
            cout << "Exiting the program." << endl; // Print exit message
        
        }else { // If user entered an invalid choice
        
            cout << "Invalid choice. Please try again." << endl; // Print error message
         
            cin.clear(); // Clear the input stream
        
            cin.ignore(100, '\n'); // Ignore remaining characters in input buffer
        
        }
    
    }

    return 0; // end program

}