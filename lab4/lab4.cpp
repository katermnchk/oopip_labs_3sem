#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm> 
#include "classes4.h"


using namespace std;

map<int, Fridge> fridges;
unordered_map<int, WashingMachine> washers;
multimap<string, TV> tvs;
unordered_set<string> applianceNames;
set<string> transactionTypes;

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
bool getValidatedInput(int& input, const string& prompt);
bool getValidatedInput(unsigned int& input, const string& prompt);
bool getValidatedInput(string& input, const string& prompt);
bool getValidatedInput(double& input, const string& prompt);

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

        tvs.insert(make_pair(name, TV(name, brand, price, screenSize)));
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

    auto range = tvs.equal_range(name);
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

    cout << left << setw(width) << "Transaction ID"
        << setw(width) << "Type"
        << setw(width) << "Name"
        << setw(width) << "Brand"
        << setw(width) << "Price"
        << setw(width) << "Capacity/Load"
        << setw(width) << "Screen Size" << endl;
    cout << string(180, '-') << endl;

   /* cout << left << setw(width) << "Type"
        << setw(width) << "Name"
        << setw(width) << "Brand"
        << setw(width) << "Price"
        << setw(width) << "Capacity/Load"
        << setw(width) << "Screen Size" << endl;
    cout << string(120, '-') << endl;*/

    for (const auto& pair : fridges) { 
        const Fridge& fridge = pair.second;
        unsigned int transactionID = pair.first;

        cout << left << setw(width) << transactionID
            << setw(width) << "Fridge"
            << setw(width) << fridge.getName()
            << setw(width) << fridge.getBrand()
            << setw(width) << fixed << setprecision(2) << fridge.getPrice()
            << setw(width) << fridge.getCapacity() << " liters"
            << setw(width) << "" << endl;
    }

    for (const auto& pair : washers) {
        unsigned int id = pair.first;
        const WashingMachine& washer = pair.second;

        cout << left << setw(width) << id
            << setw(width) << "Washing Machine"
            << setw(width) << washer.getName()
            << setw(width) << washer.getBrand()
            << setw(width) << fixed << setprecision(2) << washer.getPrice()
            << setw(width) << washer.getLoadCapacity() << " kg"
            << setw(width) << "" << endl;
    }

    for (const auto& pair : tvs) {
        const TV& tv = pair.second;
        string name = pair.first;

        cout << left << setw(width) << name
            << setw(width) << "TV"
            << setw(width) << tv.getName()
            << setw(width) << tv.getBrand()
            << setw(width) << fixed << setprecision(2) << tv.getPrice()
            << setw(width) << tv.getScreenSize() << " inches" << endl;
    }


    cout << string(180, '-') << endl;
}

void editAppliance() {
    string name;
    cout << "Enter the name of the appliance to edit: ";
    cin.ignore();
    getline(cin, name);

    for (auto it = fridges.begin(); it != fridges.end(); ++it) {
        if (it->second.getName() == name) {
            cout << "Current details of the fridge:\n";
            it->second.displayInfo();

            
            while (true) {
                cout << "\n--- Edit Fridge Menu ---\n";
                cout << "1. Edit Name\n";
                cout << "2. Edit Brand\n";
                cout << "3. Edit Price\n";
                cout << "4. Edit Capacity\n";
                cout << "0. Exit to main menu\n";
                cout << "Choose an option: ";

                int choice;
                cin >> choice;

                switch (choice) {
                case 1: {
                    string newName;
                    cout << "Enter new name (leave blank to keep current): ";
                    cin.ignore();
                    getline(cin, newName);
                    if (!newName.empty()) {
                        it->second.setName(newName);
                        cout << "Name updated successfully!\n";
                    }
                    break;
                }
                case 2: {
                    string newBrand;
                    cout << "Enter new brand (leave blank to keep current): ";
                    cin.ignore();
                    getline(cin, newBrand);
                    if (!newBrand.empty()) {
                        it->second.setBrand(newBrand);
                        cout << "Brand updated successfully!\n";
                    }
                    break;
                }
                case 3: {
                    double newPrice;
                    cout << "Enter new price (enter a negative number to keep current): ";
                    cin >> newPrice;
                    if (newPrice >= 0) {
                        it->second.setPrice(newPrice);
                        cout << "Price updated successfully!\n";
                    }
                    break;
                }
                case 4: {
                    double newCapacity;
                    cout << "Enter new capacity (enter a negative number to keep current): ";
                    cin >> newCapacity;
                    if (newCapacity >= 0) {
                        it->second.setCapacity(newCapacity);
                        cout << "Capacity updated successfully!\n";
                    }
                    break;
                }
                case 0:
                    cout << "Exiting to main menu.\n";
                    return;
                default:
                    cout << "Invalid option. Please try again.\n";
                    break;
                }
            }
        }
    }

  
    for (auto it = washers.begin(); it != washers.end(); ++it) {
        if (it->second.getName() == name) {
            cout << "Current details of the washing machine:\n";
            it -> second.displayInfo();
           
            while (true) {
                cout << "\n--- Edit Washing Machine Menu ---\n";
                cout << "1. Edit Name\n";
                cout << "2. Edit Brand\n";
                cout << "3. Edit Price\n";
                cout << "4. Edit Load Capacity\n";
                cout << "0. Exit to main menu\n";
                cout << "Choose an option: ";

                int choice;
                cin >> choice;

                switch (choice) {
                case 1: {
                    string newName;
                    cout << "Enter new name (leave blank to keep current): ";
                    cin.ignore();
                    getline(cin, newName);
                    if (!newName.empty()) {
                        it->second.setName(newName);
                        cout << "Name updated successfully!\n";
                    }
                    break;
                }
                case 2: {
                    string newBrand;
                    cout << "Enter new brand (leave blank to keep current): ";
                    cin.ignore();
                    getline(cin, newBrand);
                    if (!newBrand.empty()) {
                        it->second.setBrand(newBrand);
                        cout << "Brand updated successfully!\n";
                    }
                    break;
                }
                case 3: {
                    double newPrice;
                    cout << "Enter new price (enter a negative number to keep current): ";
                    cin >> newPrice;
                    if (newPrice >= 0) {
                        it->second.setPrice(newPrice);
                        cout << "Price updated successfully!\n";
                    }
                    break;
                }
                case 4: {
                    double newLoadCapacity;
                    cout << "Enter new load capacity (enter a negative number to keep current): ";
                    cin >> newLoadCapacity;
                    if (newLoadCapacity >= 0) {
                        it->second.setLoadCapacity(newLoadCapacity);
                        cout << "Load capacity updated successfully!\n";
                    }
                    break;
                }
                case 0:
                    cout << "Exiting to main menu.\n";
                    return;
                default:
                    cout << "Invalid option. Please try again.\n";
                    break;
                }
            }
        }
    }

    auto range = tvs.equal_range(name);
    if (range.first != range.second) {
        cout << "Current details of the TV(s):\n";
        for (auto it = range.first; it != range.second; ++it) {
            it->second.displayInfo();
           
            while (true) {
                cout << "\n--- Edit TV Menu ---\n";
                cout << "1. Edit Name\n";
                cout << "2. Edit Brand\n";
                cout << "3. Edit Price\n";
                cout << "4. Edit Screen Size\n";
                cout << "0. Exit to main menu\n";
                cout << "Choose an option: ";

                int choice;
                cin >> choice;

                switch (choice) {
                case 1: {
                    string newName;
                    cout << "Enter new name (leave blank to keep current): ";
                    cin.ignore();
                    getline(cin, newName);
                    if (!newName.empty()) {
                        it->second.setName(newName);
                        cout << "Name updated successfully!\n";
                    }
                    break;
                }
                case 2: {
                    string newBrand;
                    cout << "Enter new brand (leave blank to keep current): ";
                    cin.ignore();
                    getline(cin, newBrand);
                    if (!newBrand.empty()) {
                        it->second.setBrand(newBrand);
                        cout << "Brand updated successfully!\n";
                    }
                    break;
                }
                case 3: {
                    double newPrice;
                    cout << "Enter new price (enter a negative number to keep current): ";
                    cin >> newPrice;
                    if (newPrice >= 0) {
                        it->second.setPrice(newPrice);
                        cout << "Price updated successfully!\n";
                    }
                    break;
                }
                case 4: {
                    double newScreenSize;
                    cout << "Enter new screen size (enter a negative number to keep current): ";
                    cin >> newScreenSize;
                    if (newScreenSize >= 0) {
                        it->second.setScreenSize(newScreenSize);
                        cout << "Screen size updated successfully!\n";
                    }
                    break;
                }
                case 0:
                    cout << "Exiting to main menu.\n";
                    return;
                default:
                    cout << "Invalid option. Please try again.\n";
                    break;
                }
            }
        }
        return; 
    }

    cout << "Appliance not found." << endl;
}

void searchAppliance() {
    string name;
    cout << "Enter the name of the appliance to search: ";
    cin.ignore();
    getline(cin, name);

    bool found = false;
    cout << "\n----------Search Results----------\n";

    for (auto it = fridges.begin(); it != fridges.end(); ++it) {
        if (it->second.getName() == name) {
            cout << "Found Fridge:\n";
            it->second.displayInfo();
            found = true;
            cout << "-----------------------------------\n";
        }
    }

    for (auto it = washers.begin(); it != washers.end(); ++it) {
        if (it->second.getName() == name) {
            cout << "Found Washing Machine:\n";
            it->second.displayInfo();
            found = true;
            cout << "-----------------------------------\n";
        }
    }

    auto range = tvs.equal_range(name);
    if (range.first != range.second) {
        cout << "Found TV(s):\n";
        for (auto it = range.first; it != range.second; ++it) {
            it->second.displayInfo();
        }
        found = true;
        cout << "-----------------------------------\n";
    }

    if (!found) {
        cout << "No appliances found with the name: " << name << "\n";
    }
}

void sortFridgesByName() {
    cout << "\n=== Sorted Fridges ===\n";
    const int width = 25;

    cout << left << setw(width) << "Type"
        << setw(width) << "Name"
        << setw(width) << "Brand"
        << setw(width) << "Price"
        << setw(width) << "Capacity" << endl;
    cout << string(120, '-') << endl;

    multimap<string, Fridge> sortedFridges;
    for (const auto& pair : fridges) {
        sortedFridges.insert({ pair.second.getName(), pair.second });
    }

    for (const auto& pair : sortedFridges) {
        const Fridge& fridge = pair.second;

        cout << left << setw(width) << "Fridge"
            << setw(width) << fridge.getName()
            << setw(width) << fridge.getBrand()
            << setw(width) << fixed << setprecision(2) << fridge.getPrice()
            << setw(width) << fridge.getCapacity() << " liters" << endl;
    }
    cout << string(120, '-') << endl;
}

void sortWashersByName() {
    cout << "\n=== Sorted Washing Machines ===\n";
    const int width = 25;

    cout << left << setw(width) << "Type"
        << setw(width) << "Name"
        << setw(width) << "Brand"
        << setw(width) << "Price"
        << setw(width) << "Load Capacity" << endl;
    cout << string(120, '-') << endl;

   
    multimap<string, WashingMachine> sortedWashers;
    for (const auto& pair : washers) {
        sortedWashers.insert({ pair.second.getName(), pair.second });
    }

    for (const auto& pair : sortedWashers) {
        const WashingMachine& washer = pair.second;

        cout << left << setw(width) << "Washing Machine"
            << setw(width) << washer.getName()
            << setw(width) << washer.getBrand()
            << setw(width) << fixed << setprecision(2) << washer.getPrice()
            << setw(width) << washer.getLoadCapacity() << " kg" << endl;
    }
    cout << string(120, '-') << endl;
}

void sortTvsByName() {
    cout << "\n=== Sorted TVs ===\n";
    const int width = 25;

    cout << left << setw(width) << "Type"
        << setw(width) << "Name"
        << setw(width) << "Brand"
        << setw(width) << "Price"
        << setw(width) << "Screen Size" << endl;
    cout << string(120, '-') << endl;

   
    for (const auto& pair : tvs) {
        const TV& tv = pair.second;

        cout << left << setw(width) << "TV"
            << setw(width) << tv.getName()
            << setw(width) << tv.getBrand()
            << setw(width) << fixed << setprecision(2) << tv.getPrice()
            << setw(width) << tv.getScreenSize() << " inches" << endl;
    }
    cout << string(120, '-') << endl;
}

void sortTransactions() {
    int sortChoice;

    cout << "\nSelect sorting criteria:\n";
    cout << "1. Sort Fridges by Name\n";
    cout << "2. Sort Washing Machines by Name\n";
    cout << "3. Sort TVs by Name\n";
    cout << "Enter your choice: ";
    cin >> sortChoice;

    switch (sortChoice) {
    case 1:
        sortFridgesByName();
        break;
    case 2:
        sortWashersByName();
        break;
    case 3:
        sortTvsByName();
        break;
    default:
        cout << "Invalid option.\n";
        break;

    }
}

void writeToFile() {
    ofstream outFile("transactions_lab4.txt");

    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    outFile << "==============================\n";
    outFile << "         Transactions          \n";
    outFile << "==============================\n\n";

   
    for (const auto& pair : fridges) {
        int id = pair.first;
        const Fridge& fridge = pair.second;
        outFile << "Fridge Transaction\n";
        outFile << "Transaction ID: " << id << "\n" 
            << "Quantity: 1\n" 
            << "Name: " << fridge.getName() << "\n"
            << "Brand: " << fridge.getBrand() << "\n"
            << "Price: " << fridge.getPrice() << "\n"
            << "Capacity: " << fridge.getCapacity() << " liters\n";
        outFile << "-------------------------------\n";
    }

    
    for (const auto& pair : washers) {
        int id = pair.first;
        const WashingMachine& washer = pair.second;
        outFile << "Washing Machine Transaction\n";
        outFile << "Transaction ID: " << id << "\n"
            << "Quantity: 1\n" 
            << "Name: " << washer.getName() << "\n"
            << "Brand: " << washer.getBrand() << "\n"
            << "Price: " << washer.getPrice() << "\n"
            << "Load capacity: " << washer.getLoadCapacity() << " kg\n";
        outFile << "-------------------------------\n";
    }

    for (const auto& pair : tvs) {
        const TV& tv = pair.second;
        outFile << "TV Transaction\n";
        outFile << "Transaction ID: " << pair.first << "\n" 
            << "Quantity: 1\n" 
            << "Name: " << tv.getName() << "\n"
            << "Brand: " << tv.getBrand() << "\n"
            << "Price: " << tv.getPrice() << "\n"
            << "Screen size: " << tv.getScreenSize() << " inches\n";
        outFile << "-------------------------------\n";
    }

    outFile.close();
    cout << "Transactions written to file successfully!\n";
}

void readFromFile() {
    ifstream inFile("transactions_lab4.txt");

    if (!inFile) {
        cout << "Error opening file for reading.\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.find("Fridge Transaction") != string::npos) {
            int transactionID;
            unsigned int quantity = 1; 
            string name, brand, price, capacity;

            getline(inFile, line);
            transactionID = stoi(line.substr(line.find(":") + 1));

            getline(inFile, line); 
            // quantity = stoi(line.substr(line.find(":") + 1));

            getline(inFile, line); 
            name = line.substr(line.find(":") + 1);

            getline(inFile, line); 
            brand = line.substr(line.find(":") + 1);

            getline(inFile, line); 
            price = line.substr(line.find(":") + 1);

            getline(inFile, line); 
            capacity = line.substr(line.find(":") + 1);

            fridges[transactionID] = Fridge(name, brand, stod(price), stod(capacity));
        }
        else if (line.find("Washing Machine Transaction") != string::npos) {
            int transactionID;
            unsigned int quantity = 1;
            string name, brand, price, loadCapacity;

            getline(inFile, line); 
            transactionID = stoi(line.substr(line.find(":") + 1));

            getline(inFile, line); 
            // quantity = stoi(line.substr(line.find(":") + 1)); 

            getline(inFile, line); 
            name = line.substr(line.find(":") + 1);

            getline(inFile, line);
            brand = line.substr(line.find(":") + 1);

            getline(inFile, line); 
            price = line.substr(line.find(":") + 1);

            getline(inFile, line); 
            loadCapacity = line.substr(line.find(":") + 1);

            washers[transactionID] = WashingMachine(name, brand, stod(price), stod(loadCapacity));
        }
        else if (line.find("TV Transaction") != string::npos) {
            string name, brand, price, screenSize;
            int transactionID;

            getline(inFile, line); 
            transactionID = stoi(line.substr(line.find(":") + 1));

            getline(inFile, line); 
            // unsigned int quantity = stoi(line.substr(line.find(":") + 1)); 

            getline(inFile, line); 
            name = line.substr(line.find(":") + 1);

            getline(inFile, line);
            brand = line.substr(line.find(":") + 1);

            getline(inFile, line); 
            price = line.substr(line.find(":") + 1);

            getline(inFile, line); 
            screenSize = line.substr(line.find(":") + 1);

            tvs.emplace(name, TV(name, brand, stod(price), stod(screenSize))); 
        }
    }

    inFile.close();
    cout << "Data read from file successfully.\n";
}

void clearFile() {
    ofstream outFile("transactions_lab4.txt", ios::trunc);
    if (!outFile) {
        cout << "Error opening file for clearing.\n";
        return;
    }
    outFile.close();
    cout << "File cleared successfully!\n";
}
