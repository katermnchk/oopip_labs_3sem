#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <array>
#include <limits>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "classes.h"

using namespace std;


int getChoice();
void checkStreamState(istream& inStream);
void displayMenu();
bool getValidatedInput(string& input, const string& prompt);
bool getValidatedInput(double& input, const string& prompt);
bool getValidatedInput(int& input, const string& prompt);
void removeAppliance(vector<Appliance*>& appliances);
void searchAppliance(const vector<Appliance*>& appliances);
void editAppliance(vector<Appliance*>& appliances);
void addTransaction(vector<Transaction<Fridge>>& fridges, list<Transaction<WashingMachine>>& washers, vector<Transaction<TV>>& tvs);
void displayAllTransactions(const vector<Transaction<Fridge>>& fridges, const list<Transaction<WashingMachine>>& washers, const vector<Transaction<TV>>& tvs);
void sortTransactions(vector<Transaction<Fridge>>& fridges, list<Transaction<WashingMachine>>& washers, vector<Transaction<TV>>& tvs);
void writeToFile(const vector<Transaction<Fridge>>& fridges, const list<Transaction<WashingMachine>>& washers, const vector<Transaction<TV>>& tvs);
void readFromFile(vector<Transaction<Fridge>>& fridges, list<Transaction<WashingMachine>>& washers, vector<Transaction<TV>>& tvs);
void clearFile();

int main() {
    vector<Appliance*> appliances;
    vector<Transaction<Fridge>> fridges;
    list<Transaction<WashingMachine>> washers;
    vector<Transaction<TV>> tvs;

    while (true) {
        displayMenu();
        int choice = getChoice();

        switch (choice) {
        case 1:
            addTransaction(fridges, washers, tvs);
            break;
        case 2:
            removeAppliance(appliances);
            break;
        case 3:
            editAppliance(appliances);
            break;
        case 4:
            displayAllTransactions(fridges, washers, tvs);
            break;
        case 5:
            searchAppliance(appliances);
            break;
        case 6:
            sortTransactions(fridges, washers, tvs);
            break;
        case 7:
            writeToFile(fridges, washers, tvs);
            break;
        case 8:
            readFromFile(fridges, washers, tvs);
            break;
        case 9:
            clearFile();
            break;
        case 0:
            for (auto appliance : appliances) {
                delete appliance;
            }
            return 0;
        default:
            cout << "Invalid option. Please enter a number between 0 and 9\n";
        }
    }
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

bool getValidatedInput(string& input, const string& prompt) {
    cout << prompt;
    cin >> input;

    while (input.empty()) {
        cout << "Input cannot be empty.\n" << prompt;
        cin >> input;
    }
    return true;
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool getValidatedInput(double& input, const string& prompt) {
    cout << prompt;
    cin >> input;

    while (cin.fail()) {
        clearInput();
        cout << "Invalid input. Please enter a valid number.\n" << prompt;
        cin >> input;
    }
    return true;
}

bool getValidatedInput(int& input, const string& prompt) {
    cout << prompt;
    cin >> input;

    while (cin.fail()) {
        clearInput();
        cout << "Invalid input. Please enter a valid number.\n" << prompt;
        cin >> input;
    }
    return true;
}

bool getValidatedInput(unsigned int& input, const string& prompt) {
    cout << prompt;
    cin >> input;

    while (cin.fail()) {
        clearInput();
        cout << "Invalid input. Please enter a valid number.\n" << prompt;
        cin >> input;
    }
    return true;
}

void addTransaction(vector<Transaction<Fridge>>& fridges,
    list<Transaction<WashingMachine>>& washers,
    vector<Transaction<TV>>& tvs) {
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

        Fridge appliance(name, brand, price, capacity);
        fridges.push_back(Transaction<Fridge>(transactionID, appliance, quantity, "Fridge Transaction"));
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

        WashingMachine appliance(name, brand, price, loadCapacity);
        washers.push_back(Transaction<WashingMachine>(transactionID, appliance, quantity, "Washing Machine Transaction"));
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

        TV appliance(name, brand, price, screenSize);
        tvs.push_back(Transaction<TV>(transactionID, appliance, quantity, "TV Transaction"));
        cout << "Transaction for TV added successfully!\n";
        break;
    }
    default:
        cout << "Invalid option. Please enter a number between 1 and 3.\n";
    }
}



void removeAppliance(vector<Appliance*>& appliances) {
    int index;
    cout << "Enter the index of the appliance to remove (0 to " << appliances.size() - 1 << "): ";
    getValidatedInput(index, "Enter index: ");

    if (index >= 0 && index < appliances.size()) {
        delete appliances[index];
        appliances.erase(appliances.begin() + index);
        cout << "Appliance removed successfully!\n";
    }
    else {
        cout << "Invalid index.\n";
    }
}

void displayAllTransactions(const vector<Transaction<Fridge>>& fridges,
    const list<Transaction<WashingMachine>>& washers,
    const vector<Transaction<TV>>& tvs) {
    cout << "\n----------All Transactions----------\n";

    cout << "\nTransactions for fridges:\n";
    if (fridges.empty()) {
        cout << "No fridge transactions available.\n";
    }
    else {
        for (const auto& transaction : fridges) {
            transaction.displayTransaction();
            cout << "-----------------------------------\n";
        }
    }

    cout << "\nTransactions for Washing machines:\n";
    if (washers.empty()) {
        cout << "No washing machine transactions available.\n";
    }
    else {
        for (const auto& transaction : washers) {
            transaction.displayTransaction();
            cout << "-----------------------------------\n";
        }
    }

    cout << "\nTransactions for TVs:\n";
    if (tvs.empty()) {
        cout << "No TV transactions available.\n";
    }
    else {
        for (const auto& transaction : tvs) {
            transaction.displayTransaction();
            cout << "-----------------------------------\n";
        }
    }

    cout << "-----------------------------------\n";
}

void searchAppliance(const vector<Appliance*>& appliances) {
    string name;
    cout << "Enter the name of the appliance to search: ";
    cin >> name;

    bool found = false;
    cout << "\n----------Search Results----------\n";

    for (const auto& appliance : appliances) {
        if (appliance->getName() == name) {
            cout << "Found Appliance: \n";
            appliance->displayInfo(); 
            found = true;
            cout << "-----------------------------------\n";
        }
    }

    if (!found) {
        cout << "No appliances found with the name: " << name << "\n";
    }
}

void editAppliance(vector<Appliance*>& appliances) {
    int index;
    cout << "Enter the index of the appliance to edit (0 to " << appliances.size() - 1 << "): ";
    getValidatedInput(index, "Enter index: ");

    if (index >= 0 && index < appliances.size()) {
        Appliance* appliance = appliances[index];

        cout << "Current details of the appliance:\n";
        appliance->displayInfo();

        while (true) {
            cout << "\n--- Edit Appliance Menu ---\n";
            cout << "1. Edit Name\n";
            cout << "2. Edit Brand\n";
            cout << "3. Edit Price\n";
            cout << "4. Edit Specific Attributes\n"; 
            cout << "0. Exit to main menu\n";
            cout << "Choose an option: ";

            int choice;
            getValidatedInput(choice, "Enter your choice: ");

            switch (choice) {
            case 1: {
                string newName;
                getValidatedInput(newName, "Enter new name (leave blank to keep current): ");
                if (!newName.empty()) {
                    appliance->setName(newName);
                    cout << "Name updated successfully!\n";
                }
                break;
            }
            case 2: {
                string newBrand;
                getValidatedInput(newBrand, "Enter new brand (leave blank to keep current): ");
                if (!newBrand.empty()) {
                    appliance->setBrand(newBrand); 
                    cout << "Brand updated successfully!\n";
                }
                break;
            }
            case 3: {
                double newPrice;
                if (getValidatedInput(newPrice, "Enter new price (enter 0 to keep current): ")) {
                    if (newPrice != 0) {
                        appliance->setPrice(newPrice); 
                        cout << "Price updated successfully!\n";
                    }
                }
                break;
            }
            case 4: {
                if (dynamic_cast<Fridge*>(appliance)) {
                    Fridge* fridge = static_cast<Fridge*>(appliance);
                    double newCapacity;
                    if (getValidatedInput(newCapacity, "Enter new capacity (leave blank to keep current): ")) {
                        fridge->setCapacity(newCapacity);
                        cout << "Capacity updated successfully!\n";
                    }
                }
                else if (dynamic_cast<WashingMachine*>(appliance)) {
                    WashingMachine* washer = static_cast<WashingMachine*>(appliance);
                    double newLoadCapacity;
                    if (getValidatedInput(newLoadCapacity, "Enter new load capacity (leave blank to keep current): ")) {
                        washer->setLoadCapacity(newLoadCapacity);
                        cout << "Load capacity updated successfully!\n";
                    }
                }
                else if (dynamic_cast<TV*>(appliance)) {
                    TV* tv = static_cast<TV*>(appliance);
                    double newScreenSize;
                    if (getValidatedInput(newScreenSize, "Enter new screen size (leave blank to keep current): ")) {
                        tv->setScreenSize(newScreenSize);
                        cout << "Screen size updated successfully!\n";
                    }
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
    else {
        cout << "Invalid index.\n";
    }
}

void sortTransactions(vector<Transaction<Fridge>>& fridges, list<Transaction<WashingMachine>>& washers, vector<Transaction<TV>>& tvs) {
    int choice;
    cout << "\nSelect type of transactions to sort:\n";
    cout << "1. Fridge Transactions\n";
    cout << "2. Washing Machine Transactions\n";
    cout << "3. TV Transactions\n";
    cout << "0. Exit\n";
    cout << "\nEnter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        sort(fridges.begin(), fridges.end(), [](const Transaction<Fridge>& a, const Transaction<Fridge>& b) {
            return a.getTransactionID() < b.getTransactionID();
            });
        cout << "Fridge transactions sorted successfully!\n";
        break;
    case 2:
        washers.sort([](const Transaction<WashingMachine>& a, const Transaction<WashingMachine>& b) {
            return a.getTransactionID() < b.getTransactionID();
            });
        cout << "Washing machine transactions sorted successfully!\n";
        break;
    case 3:
        sort(tvs.begin(), tvs.end(), [](const Transaction<TV>& a, const Transaction<TV>& b) {
            return a.getTransactionID() < b.getTransactionID();
            });
        cout << "TV transactions sorted successfully!\n";
        break;
    case 0:
        break;
    default:
        cout << "Invalid option. Please enter a number between 0 and 3.\n";
    }
}

void writeToFile(const vector<Transaction<Fridge>>& fridges, const list<Transaction<WashingMachine>>& washers, const vector<Transaction<TV>>& tvs) {
    ofstream outFile("transactions.txt");

    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    outFile << "==============================\n";
    outFile << "         Transactions          \n";
    outFile << "==============================\n\n";

    //outFile << "---- Fridge Transactions ----\n";
    for (const auto& transaction : fridges) {
        outFile << "Fridge Transaction\n"; 
        outFile << "Transaction ID: " << transaction.getTransactionID() << "\n"
            << "Quantity: " << transaction.getQuantity() << "\n"
            << "Name: " << transaction.getAppliance().getName() << "\n"
            << "Brand: " << transaction.getAppliance().getBrand() << "\n"
            << "Price: " << transaction.getAppliance().getPrice() << "\n"
            << "Capacity: " << static_cast<Fridge>(transaction.getAppliance()).getCapacity() << " liters\n";
        outFile << "-------------------------------\n";
    }

    //outFile << "---- Washing Machines Transactions ----\n";
    for (const auto& transaction : washers) {
        outFile << "Washing Machine Transaction\n"; 
        outFile << "Transaction ID: " << transaction.getTransactionID() << "\n"
            << "Quantity: " << transaction.getQuantity() << "\n"
            << "Name: " << transaction.getAppliance().getName() << "\n"
            << "Brand: " << transaction.getAppliance().getBrand() << "\n"
            << "Price: " << transaction.getAppliance().getPrice() << "\n"
            << "Load capacity: " << static_cast<WashingMachine>(transaction.getAppliance()).getLoadCapacity() << " kg\n";
        outFile << "-------------------------------\n";
    }

    //outFile << "---- TV Transactions ----\n"; 
    for (const auto& transaction : tvs) {
        outFile << "TV Transaction\n"; 
        outFile << "Transaction ID: " << transaction.getTransactionID() << "\n"
            << "Quantity: " << transaction.getQuantity() << "\n"
            << "Name: " << transaction.getAppliance().getName() << "\n"
            << "Brand: " << transaction.getAppliance().getBrand() << "\n"
            << "Price: " << transaction.getAppliance().getPrice() << "\n"
            << "Screen size: " << static_cast<TV>(transaction.getAppliance()).getScreenSize() << " inches\n";
        outFile << "-------------------------------\n";
    }

    outFile.close();
    cout << "Transactions written to file successfully!\n";
}

void readFromFile(vector<Transaction<Fridge>>& fridges, list<Transaction<WashingMachine>>& washers, vector<Transaction<TV>>& tvs) {
    ifstream inFile("transactions.txt");

    if (!inFile) {
        cout << "Error opening file for reading.\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        try {
            if (line.find("Fridge Transaction") != string::npos) {
                unsigned int transactionID, quantity;
                string name, brand, price, capacity;
                getline(inFile, line);
                transactionID = stoi(line.substr(line.find(":") + 1));

                getline(inFile, line);
                quantity = stoi(line.substr(line.find(":") + 1));

                getline(inFile, line);
                name = line.substr(line.find(":") + 1);

                getline(inFile, line);
                brand = line.substr(line.find(":") + 1);

                getline(inFile, line);
                price = line.substr(line.find(":") + 1);

                getline(inFile, line);
                capacity = line.substr(line.find(":") + 1);

                fridges.push_back(Transaction<Fridge>(transactionID, Fridge(name, brand, stod(price), stod(capacity)), quantity, "Fridge Transaction"));
            }
            else if (line.find("Washing Machine Transaction") != string::npos) {
                unsigned int transactionID, quantity;
                string name, brand, price, loadCapacity;

                getline(inFile, line);
                transactionID = stoi(line.substr(line.find(":") + 1));

                getline(inFile, line);
                quantity = stoi(line.substr(line.find(":") + 1));

                getline(inFile, line);
                name = line.substr(line.find(":") + 1);

                getline(inFile, line);
                brand = line.substr(line.find(":") + 1);

                getline(inFile, line);
                price = line.substr(line.find(":") + 1);

                getline(inFile, line);
                loadCapacity = line.substr(line.find(":") + 1);

                washers.push_back(Transaction<WashingMachine>(transactionID, WashingMachine(name, brand, stod(price), stod(loadCapacity)), quantity, "Washing Machine Transaction"));
            }
            else if (line.find("TV Transaction") != string::npos) {
                unsigned int transactionID, quantity;
                string name, brand, price, screenSize;

                getline(inFile, line);
                transactionID = stoi(line.substr(line.find(":") + 1));

                getline(inFile, line);
                quantity = stoi(line.substr(line.find(":") + 1));

                getline(inFile, line);
                name = line.substr(line.find(":") + 1);

                getline(inFile, line);
                brand = line.substr(line.find(":") + 1);

                getline(inFile, line);
                price = line.substr(line.find(":") + 1);

                getline(inFile, line);
                screenSize = line.substr(line.find(":") + 1);

                tvs.push_back(Transaction<TV>(transactionID, TV(name, brand, stod(price), stod(screenSize)), quantity, "TV Transaction"));
            }
        }
        catch (const exception& e) {
            //cout << "Error processing line: " << line << "\n" << e.what() << endl;
            continue; 
        }
    }

    inFile.close();
    cout << "Transactions read from file successfully!\n";
}

void clearFile() {
    ofstream outFile("transactions.txt", ios::trunc); 
    if (!outFile) {
        cout << "Error opening file for clearing.\n";
        return;
    }
    outFile.close(); 
    cout << "File cleared successfully!\n";
}