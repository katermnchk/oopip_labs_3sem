#include <string>
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>
#include "classes6.h"

using namespace std;


int getChoice();
void displayMenu();
void checkStreamState(istream& inStream);
void addAppliance(Inventory& inventory, FridgeFactory& frFact, WashingMachineFactory& washFact,
    TVFactory& tvFact);
int showAddedMenu();
int getSortedChoice();
void editAppliance(Inventory& inventory, const FridgeFactory& frFact, const WashingMachineFactory& washFact, const TVFactory& tvFact);
void searchAppliance(const Inventory& inventory);
int showEditMenu();
void saveAllToFile(const Inventory& inventory, const string& filename);
void loadFromFile(Inventory& inventory, const string& filename);
void editFridge(Inventory& inventory, const string& name, const FridgeFactory& frFact);
void editWashingMachine(Inventory& inventory, const string& name, const WashingMachineFactory& washFact);
void editTV(Inventory& inventory, const string& name, const TVFactory& tvFact);

int main() {
    Inventory inventory;
    FridgeFactory fridgeFactory;
    WashingMachineFactory washingMachineFactory;
    TVFactory tvFactory;
    int sortedChoice;

    bool running = true;
    while (running) {
        displayMenu();
        int choice = getChoice();

        switch (choice) {
        case 1: {
            addAppliance(inventory, fridgeFactory, washingMachineFactory, tvFactory);
            break;
        }
        case 2: {
            string name;
            cout << "Enter appliance name to remove: ";
            cin >> name;
            inventory.removeAppliance(name);
            break;
        }
        case 3: {
            editAppliance(inventory, fridgeFactory, washingMachineFactory, tvFactory);
            break;
        }
        case 4:
            inventory.displayAll();
            break;
        case 5:
            searchAppliance(inventory);
            break;
        case 6:
            sortedChoice = getSortedChoice();
            if (sortedChoice == 1) {
                inventory.sortInventoryByName();
                inventory.displayAll();
            }
            else if (sortedChoice == 2) {
                inventory.sortInventoryByPrice();
                inventory.displayAll();
            } 
            break;
        case 7:
            saveAllToFile(inventory, "lab6.txt");
            break;
        case 8:
            loadFromFile(inventory, "lab6.txt");
            break;
        case 9:
            inventory.clearFile("lab6.txt");
            break;
        case 0:
            running = false;
            cout << "Goodbye!";
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
    cout << "6. Sort appliances\n";
    cout << "7. Write appliances to file\n";
    cout << "8. Read appliances from file\n";
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

int showAddedMenu() {
    cout << "\n----------Menu----------\n";
    cout << "1. Add a fridge\n";
    cout << "2. Add a washing machine\n";
    cout << "3. Add a TV\n";
    cout << "0. Exit\n";
    cout << "------------------------\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    while (cin.fail() || choice < 0 || choice > 3) {
        checkStreamState(cin);
        cout << "Invalid input. Please enter a number between 0 and 3: ";
        cin >> choice;
    }
    return choice;
}

void addAppliance(Inventory& inventory, FridgeFactory& frFact, WashingMachineFactory& washFact,
TVFactory& tvFact) {
    int choice = showAddedMenu();
    string name, brand;
    double price, capacity, load, screenSize;

    cout << "Enter name: ";
    cin >> name;
    cout << "Enter brand: ";
    cin >> brand;
    cout << "Enter price: ";
    cin >> price;
    while (cin.fail() || price < 0) {
        checkStreamState(cin);
        cout << "Invalid price. Please enter a positive number: ";
        cin >> price;
    }

    switch (choice) {
    case 1: 
        cout << "Enter capacity (liters): ";
        cin >> capacity;
        while (cin.fail() || capacity < 0) {
            checkStreamState(cin);
            cout << "Invalid capacity. Please enter a positive number: ";
            cin >> capacity;
        }
        inventory.addAppliance(frFact.createAppliance(name, brand, price, capacity));
        break;
    case 2:
        cout << "Enter load capacity (kg): ";
        cin >> load;
        while (cin.fail() || capacity < 0) {
            checkStreamState(cin);
            cout << "Invalid capacity. Please enter a positive number: ";
            cin >> capacity;
        }
        inventory.addAppliance(washFact.createAppliance(name, brand, price, load));
        break;
    case 3:
        cout << "Enter screen size (inches): ";
        cin >> screenSize;
        while (cin.fail() || capacity < 0) {
            checkStreamState(cin);
            cout << "Invalid capacity. Please enter a positive number: ";
            cin >> capacity;
        }
        inventory.addAppliance(tvFact.createAppliance(name, brand, price, screenSize));
        break;
    case 0:
        cout << "Exiting add menu" << endl;
        return;
    default:
        cout << "Invalid choice" << endl;
        return;
    }
        
}

int getSortedChoice() {
    cout << "\n----------Menu----------\n";
    cout << "1. Sort appliances by name\n";
    cout << "2. Sort appliances by price\n";
    cout << "0. Exit\n";
    cout << "------------------------\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    while (cin.fail() || choice < 0 || choice > 2) {
        checkStreamState(cin);
        cout << "Invalid input. Please enter a number between 0 and 2: ";
        cin >> choice;
    }
    return choice;
}

int showEditMenu() {
    cout << "\n----------Edit Menu----------\n";
    cout << "1. Edit Fridge\n";
    cout << "2. Edit Washing Machine\n";
    cout << "3. Edit TV\n";
    cout << "0. Exit\n";
    cout << "-------------------------------\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    while (cin.fail() || choice < 0 || choice > 3) {
        checkStreamState(cin);
        cout << "Invalid input. Please enter a number between 0 and 3: ";
        cin >> choice;
    }
    return choice;
}

//void editAppliance(Inventory& inventory, const FridgeFactory& frFact,
//    const WashingMachineFactory& washFact, const TVFactory& tvFact) {
//    string name;
//    cout << "Enter appliance name to edit: ";
//    cin >> name;
//    int editChoice = showEditMenu();
//    switch (editChoice) {
//    case 1:
//        inventory.editAppliance(name, frFact);
//        break;
//    case 2:
//        inventory.editAppliance(name, washFact);
//        break;
//    case 3:
//        inventory.editAppliance(name, tvFact);
//        break;
//    case 0:
//        break;
//    default:
//        cout << "Invalid choice.\n";
//        break;
//    }
//}
void editAppliance(Inventory& inventory, const FridgeFactory& frFact,
    const WashingMachineFactory& washFact, const TVFactory& tvFact) {
    string name;
    cout << "Enter appliance name to edit: ";
    cin >> name;

    int editChoice = showEditMenu();
    switch (editChoice) {
    case 1:
        editFridge(inventory, name, frFact);
        break;
    case 2:
        editWashingMachine(inventory, name, washFact);
        break;
    case 3:
        editTV(inventory, name, tvFact);
        break;
    case 0:
        break;
    default:
        cout << "Invalid choice\n";
        break;
    }
}

void editFridge(Inventory& inventory, const string& name, const FridgeFactory& frFact) {
    Fridge* fridge = dynamic_cast<Fridge*>(inventory.getAppliance(name).get());
    if (fridge) {
        int editChoice;
        cout << "\n--- Edit Fridge Menu ---\n";
        cout << "1. Edit Name\n";
        cout << "2. Edit Brand\n";
        cout << "3. Edit Price\n";
        cout << "4. Edit Capacity\n";
        cout << "0. Exit to main menu\n";
        cout << "Choose an option: ";
        cin >> editChoice;

        switch (editChoice) {
        case 1: {
            string newName;
            cout << "Enter new name: ";
            cin >> newName;
            fridge->setName(newName);
            break;
        }
        case 2: {
            string newBrand;
            cout << "Enter new brand: ";
            cin >> newBrand;
            fridge->setBrand(newBrand);
            break;
        }
        case 3: {
            double newPrice;
            cout << "Enter new price: ";
            cin >> newPrice;
            fridge->setPrice(newPrice);
            break;
        }
        case 4: {
            double newCapacity;
            cout << "Enter new capacity (liters): ";
            cin >> newCapacity;
            fridge->setCapacity(newCapacity);
            break;
        }
        case 0:
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

void editWashingMachine(Inventory& inventory, const string& name, const WashingMachineFactory& washFact) {
    WashingMachine* washingMachine = dynamic_cast<WashingMachine*>(inventory.getAppliance(name).get());
    if (washingMachine) {
        int editChoice;
        cout << "\n--- Edit Washing Machine Menu ---\n";
        cout << "1. Edit Name\n";
        cout << "2. Edit Brand\n";
        cout << "3. Edit Price\n";
        cout << "4. Edit Load Capacity\n";
        cout << "0. Exit to main menu\n";
        cout << "Choose an option: ";
        cin >> editChoice;

        switch (editChoice) {
        case 1: {
            string newName;
            cout << "Enter new name: ";
            cin >> newName;
            washingMachine->setName(newName);
            break;
        }
        case 2: {
            string newBrand;
            cout << "Enter new brand: ";
            cin >> newBrand;
            washingMachine->setBrand(newBrand);
            break;
        }
        case 3: {
            double newPrice;
            cout << "Enter new price: ";
            cin >> newPrice;
            washingMachine->setPrice(newPrice);
            break;
        }
        case 4: {
            double newLoad;
            cout << "Enter new load capacity (kg): ";
            cin >> newLoad;
            washingMachine->setLoadCapacity(newLoad);
            break;
        }
        case 0:
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

void editTV(Inventory& inventory, const string& name, const TVFactory& tvFact) {
    TV* tv = dynamic_cast<TV*>(inventory.getAppliance(name).get());
    if (tv) {
        int editChoice;
        cout << "\n--- Edit TV Menu ---\n";
        cout << "1. Edit Name\n";
        cout << "2. Edit Brand\n";
        cout << "3. Edit Price\n";
        cout << "4. Edit Screen Size\n";
        cout << "0. Exit to main menu\n";
        cout << "Choose an option: ";
        cin >> editChoice;

        switch (editChoice) {
        case 1: {
            string newName;
            cout << "Enter new name: ";
            cin >> newName;
            tv->setName(newName);
            break;
        }
        case 2: {
            string newBrand;
            cout << "Enter new brand: ";
            cin >> newBrand;
            tv->setBrand(newBrand);
            break;
        }
        case 3: {
            double newPrice;
            cout << "Enter new price: ";
            cin >> newPrice;
            tv->setPrice(newPrice);
            break;
        }
        case 4: {
            double newScreenSize;
            cout << "Enter new screen size (inches): ";
            cin >> newScreenSize;
            tv->setScreenSize(newScreenSize);
            break;
        }
        case 0:
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}


void searchAppliance(const Inventory& inventory) {
    string name;
    cout << "Enter appliance name to search: ";
    cin >> name;

    bool found = false;
    for (const auto& item : inventory.items) {
        if (item->getName() == name) {
            item->display();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Appliance not found.\n";
    }
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



void saveAllToFile(const Inventory& inventory, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (const auto& item : inventory.items) {
        file << item->getName() << ","
            << item->getBrand() << ","
            << item->getPrice();
        if (const Fridge* fridge = dynamic_cast<const Fridge*>(item.get())) {
            file << "," << fridge->getCapacity();
        }
        else if (const WashingMachine* washingMachine = dynamic_cast<const WashingMachine*>(item.get())) {
            file << "," << washingMachine->getLoadCapacity();
        }
        else if (const TV* tv = dynamic_cast<const TV*>(item.get())) {
            file << "," << tv->getScreenSize();
        }
        file << endl; 
    }

    file.close();
    cout << "Data saved to file successfully.\n";
}

void loadFromFile(Inventory& inventory, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file for reading.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        string name, brand;
        double price, spec;
        pos = line.find(',');
        name = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(',');
        brand = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(',');
        price = stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        if (line.find(',') != string::npos) {
            spec = stod(line);
            inventory.addAppliance(make_unique<Fridge>(name, brand, price, spec));
        }
        else {
            try {
                spec = stod(line); //если spec < 50, то это может быть экран телевизора, а если больше, то загрузочная способность
                if (spec < 50) {
                    inventory.addAppliance(make_unique<TV>(name, brand, price, spec));
                }
                else {
                    inventory.addAppliance(make_unique<WashingMachine>(name, brand, price, spec));
                }
            }
            catch (const invalid_argument&) {
                cout << "Invalid specification for appliance: " << name << endl;
            }
            catch (const out_of_range&) {
                cout << "Specification out of range for appliance: " << name << endl;
            }
        }
    }

    file.close();
    cout << "Data read from file successfully.\n";
}

