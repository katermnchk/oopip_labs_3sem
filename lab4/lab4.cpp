#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include "classes4.h"

map<int, Fridge> fridges;
unordered_map<int, WashingMachine> washers;
multimap<int, TV> tvs;
unordered_set<string> applianceNames;
set<string> transactionTypes;

using namespace std;

void displayMenu();
int getChoice();
void checkStreamState(istream& inStream);
void addAppliance();
void removeAppliance();
void editAppliance();
void displayAllAppliances();
void searchAppliance();
void sortTransactions();
void writeToFile();
void readFromFile();
void clearFile();

int main() {
    int choice;

    do {
        displayMenu();
        choice = getChoice();

        switch (choice) {
        case 1:
            addAppliance();
            break;
        case 2:
            removeAppliance();
            break;
        case 3:
            editAppliance();
            break;
        case 4:
            displayAllAppliances();
            break;
        case 5:
            searchAppliance();
            break;
        case 6:
            sortTransactions();
            break;
        case 7:
            writeToFile();
            break;
        case 8:
            readFromFile();
            break;
        case 9:
            clearFile();
            break;
        case 0:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}

void displayMenu() {
    cout << "\n----------Menu----------\n";
    cout << "1. Add appliance\n";
    cout << "2. Remove appliance\n";
    cout << "3. Edit appliance\n";
    cout << "4. Display all appliances\n";
    cout << "5. Search appliance\n";
    cout << "6. Sort transactions\n";
    cout << "7. Write transactions to file\n";
    cout << "8. Read transactions from file\n";
    cout << "9. Clear file\n";
    cout << "0. Exit\n";
    cout << "------------------------\n";
    cout << "Enter your choice: ";
}

int getChoice() {
    int choice;
    cin >> choice;

    while (cin.fail() || choice < 0 || choice > 9) {
        checkStreamState(cin);
        cout << "Invalid input. Please enter a number between 0 and 9: ";
        cin >> choice;
    }

    return choice;
}

void checkStreamState(istream& inStream) {
    if (inStream.eof()) {
        cout << "End of file" << endl;
    }
    else if (inStream.fail()) {
        cout << "Input error" << endl;
        inStream.clear();
        inStream.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if (inStream.bad()) {
        cout << "Error when working with a stream" << endl;
    }
}

bool getValidatedInput(int& input, const string& prompt) {
    cout << prompt;
    cin >> input;

    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number.\n" << prompt;
        cin >> input;
    }
    return true;
}

bool getValidatedInput(unsigned int& input, const string& prompt) {
    cout << prompt;
    cin >> input;

    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number.\n" << prompt;
        cin >> input;
    }
    return true;
}

bool getValidatedInput(string& input, const string& prompt) {
    cout << prompt;
    cin >> input;

    while (input.empty()) {
        cout << "Input cannot be empty.\n" << prompt;
        cin >> input;
    }
    return true;
}

bool getValidatedInput(double& input, const string& prompt) {
    cout << prompt;
    cin >> input;

    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number.\n" << prompt;
        cin >> input;
    }
    return true;
}

void addAppliance() {
    int type;
    cout << "\nSelect appliance type for transaction:\n";
    cout << "1. Fridge\n";
    cout << "2. Washing Machine\n";
    cout << "3. TV\n";

    getValidatedInput(type, "\nEnter your choice: ");

    unsigned int transactionID;
    unsigned int quantity;
    cout << "\nEnter Transaction ID: ";
    cin >> transactionID;

    getValidatedInput(quantity, "Enter quantity: ");

    switch (type) {
    case 1: {
        string name, brand;
        double price, capacity;

        getValidatedInput(name, "Enter fridge name: ");
        getValidatedInput(brand, "Enter fridge brand: ");
        getValidatedInput(price, "Enter fridge price: ");
        getValidatedInput(capacity, "Enter fridge capacity (in liters): ");

        fridges[fridges.size()] = Fridge(name, brand, price, capacity);
        applianceNames.insert(name);
        cout << "Transaction for Fridge added successfully!\n";
        break;
    }
    case 2: {
        string name, brand;
        double price, loadCapacity;

        getValidatedInput(name, "Enter washing machine name: ");
        getValidatedInput(brand, "Enter washing machine brand: ");
        getValidatedInput(price, "Enter washing machine price: ");
        getValidatedInput(loadCapacity, "Enter washing machine load capacity (in kg): ");

        washers[washers.size()] = WashingMachine(name, brand, price, loadCapacity);
        applianceNames.insert(name);
        cout << "Transaction for Washing Machine added successfully!\n";
        break;
    }
    case 3: {
        string name, brand;
        double price, screenSize;

        getValidatedInput(name, "Enter TV name: ");
        getValidatedInput(brand, "Enter TV brand: ");
        getValidatedInput(price, "Enter TV price: ");
        getValidatedInput(screenSize, "Enter TV screen size (in inches): ");

        tvs.insert(make_pair(tvs.size(), TV(name, brand, price, screenSize)));
        applianceNames.insert(name);
        cout << "Transaction for TV added successfully!\n";
        break;
    }
    default:
        cout << "Invalid option. Please enter a number between 1 and 3.\n";
    }
}

void removeAppliance() {
    string name;
    getValidatedInput(name, "Enter the name of the appliance to remove: ");

    auto it = fridges.begin();
    while (it != fridges.end()) {
        if (it->second.getName() == name) {
            it = fridges.erase(it);
            cout << "Fridge " << name << " removed successfully!\n";
            return;
        }
        else {
            ++it;
        }
    }

    for (auto it = washers.begin(); it != washers.end(); ) {
        if (it->second.getName() == name) {
            it = washers.erase(it);
            cout << "Washing Machine " << name << " removed successfully!\n";
            return;
        }
        else {
            ++it;
        }
    }

    auto range = tvs.equal_range(tvs.size());
    for (auto it = range.first; it != range.second; ) {
        if (it->second.getName() == name) {
            it = tvs.erase(it);
            cout << "TV " << name << " removed successfully!\n";
            return;
        }
        else {
            ++it;
        }
    }

    cout << "Appliance " << name << " not found.\n";
}

void displayAllAppliances() {
    cout << "\n=== All Appliances ===\n";

    const int width = 25;

    cout << left << setw(width) << "Type"
        << setw(width) << "Name"
        << setw(width) << "Brand"
        << setw(width) << "Price"
        << setw(width) << "Capacity/Load"
        << setw(width) << "Screen Size" << endl;
    cout << string(120, '-') << endl;

    for (const auto& [id, fridge] : fridges) {
        cout << left << setw(width) << "Fridge"
            << setw(width) << fridge.getName()
            << setw(width) << fridge.getBrand()
            << setw(width) << fixed << setprecision(2) << fridge.getPrice()
            << setw(width) << fridge.getCapacity() << " liters"
            << setw(width) << "" << endl;
    }

    for (const auto& [id, washer] : washers) {
        cout << left << setw(width) << "Washing Machine"
            << setw(width) << washer.getName()
            << setw(width) << washer.getBrand()
            << setw(width) << fixed << setprecision(2) << washer.getPrice()
            << setw(width) << washer.getLoadCapacity() << " kg"
            << setw(width) << "" << endl;
    }

    for (const auto& [key, tv] : tvs) {
        cout << left << setw(width) << "TV"
            << setw(width) << tv.getName()
            << setw(width) << tv.getBrand()
            << setw(width) << fixed << setprecision(2) << tv.getPrice()
            << setw(width) << tv.getScreenSize() << " inches" << endl;
    }

    cout << string(120, '-') << endl;
}
