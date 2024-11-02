#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <fstream>
#include <functional>
#include <string>
#include "classes5.h"

using namespace std;

queue<Appliance*> applianceQueue;
stack<Appliance*> applianceStack;
auto comparator = [](Appliance* a, Appliance* b) {
    return a->getPrice() > b->getPrice();
    };
priority_queue<Appliance*, vector<Appliance*>, function<bool(Appliance*, Appliance*) >> appliancePQueue(comparator);

void addItemToQueue(queue<Appliance*>& applianceQueue, Appliance* appliance);
void removeItemFromQueue(queue<Appliance*>& applianceQueue);

void addItemToStack(stack<Appliance*>& applianceStack, Appliance* appliance);
void removeItemFromStack(stack<Appliance*>& applianceStack);

void addItemToPriorityQueue(priority_queue<Appliance*, vector<Appliance*>, function<bool(Appliance*, Appliance*)>>& appliancePQueue, Appliance* appliance);
void removeItemFromPriorityQueue(priority_queue<Appliance*, vector<Appliance*>, function<bool(Appliance*, Appliance*)>>& appliancePQueue);

void checkStreamState(istream& inStream);
int getChoice();
void addAppliance();
void removeAppliance();
int showAddedMenu();
void displayMenu();
void editAppliance();
void displayAppliance(Appliance* appliance);
void displayAllAppliances();
void searchAppliance();
void sortTransactions();
void writeTransactionsToFile();
void readTransactionsFromFile();
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
            writeTransactionsToFile();
            break;
        case 8:
            readTransactionsFromFile();
            break;
        case 9:
            clearFile();
            break;
        case 0:
            cout << "Exiting program" << endl;
            break;

        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 0);

    return 0;
}

void addItemToQueue(queue<Appliance*>& applianceQueue, Appliance* appliance) {
    applianceQueue.push(appliance);
}

void removeItemFromQueue(queue<Appliance*>& applianceQueue) {
    if (!applianceQueue.empty()) {
        applianceQueue.pop();
    }
    else {
        cout << "Queue is empty!" << endl;
    }
}

void addItemToStack(stack<Appliance*>& applianceStack, Appliance* appliance) {
    applianceStack.push(appliance);
}

void removeItemFromStack(stack<Appliance*>& applianceStack) {
    if (!applianceStack.empty()) {
        applianceStack.pop();
    }
    else {
        cout << "Stack is empty!" << endl;
    }
}

void addItemToPriorityQueue(priority_queue<Appliance*, vector<Appliance*>, function<bool(Appliance*, Appliance*)>>& appliancePQueue, Appliance* appliance) {
    appliancePQueue.push(appliance);
}

void removeItemFromPriorityQueue(priority_queue<Appliance*, vector<Appliance*>, function<bool(Appliance*, Appliance*)>>& appliancePQueue) {
    if (!appliancePQueue.empty()) {
        appliancePQueue.pop();
    }
    else {
        cout << "Priority queue is empty!" << endl;
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

void addAppliance() {
    int choice = showAddedMenu();
    string name, brand;
    double price, capacity, load, screenSize;

    cout << "Enter name: ";
    cin >> name;
    cout << "Enter brand: ";
    cin >> brand;
    cout << "Enter price: ";
    cin >> price;

    Appliance* newAppliance = nullptr;

    switch (choice) {
    case 1:
        cout << "Enter capacity (liters): ";
        cin >> capacity;
        newAppliance = new Fridge(name, brand, price, capacity);
        break;
    case 2:
        cout << "Enter load capacity (kg): ";
        cin >> load;
        newAppliance = new WashingMachine(name, brand, price, load);
        break;
    case 3:
        cout << "Enter screen size (inches): ";
        cin >> screenSize;
        newAppliance = new TV(name, brand, price, screenSize);
        break;
    case 0:
        cout << "Exiting add menu" << endl;
        return;
    default:
        cout << "Invalid choice" << endl;
        return;
    }

    int addChoice;
    cout << "Where do you want to add the appliance?\n";
    cout << "1. Queue\n2. Stack\n3. Priority Queue\n";
    cout << "Your choice: ";
    cin >> addChoice;

    while (cin.fail() || addChoice < 1 || addChoice > 3) {
        checkStreamState(cin);
        cout << "Invalid input. Please enter a number between 1 and 3: ";
        cin >> addChoice;
    }

    switch (addChoice) {
    case 1:
        addItemToQueue(applianceQueue, newAppliance);
        break;
    case 2:
        addItemToStack(applianceStack, newAppliance);
        break;
    case 3:
        addItemToPriorityQueue(appliancePQueue, newAppliance);
        break;
    default:
        cout << "Invalid option!" << endl;
        delete newAppliance;
    }
}

void removeAppliance() {
    int removeChoice;
    cout << "From where do you want to remove the appliance?\n";
    cout << "1. Queue\n2. Stack\n3. Priority Queue\n";
    cout << "Your choice: ";
    cin >> removeChoice;

    while (cin.fail() || removeChoice < 1 || removeChoice > 3) {
        checkStreamState(cin);
        cout << "Invalid input. Please enter a number between 0 and 3: ";
        cin >> removeChoice;
    }

    switch (removeChoice) {
    case 1:
        if (!applianceQueue.empty()) {
            cout << "Removing the first appliance from the queue:\n";
            applianceQueue.front()->displayInfo();
            removeItemFromQueue(applianceQueue);
        }
        else {
            cout << "Queue is empty!" << endl;
        }
        break;
    case 2:
        if (!applianceStack.empty()) {
            cout << "Removing the top appliance from the stack:\n";
            applianceStack.top()->displayInfo();
            removeItemFromStack(applianceStack);
        }
        else {
            cout << "Stack is empty!" << endl;
        }
        break;
    case 3:
        if (!appliancePQueue.empty()) {
            cout << "Removing the top appliance from the priority queue:\n";
            appliancePQueue.top()->displayInfo();
            removeItemFromPriorityQueue(appliancePQueue);
        }
        else {
            cout << "Priority Queue is empty!" << endl;
        }
        break;
    default:
        cout << "Invalid option!" << endl;
    }
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

void editFridge(Fridge* fridge) {
    int editChoice;

    do {
        cout << "\n--- Edit Fridge Menu ---\n";
        cout << "1. Edit Name\n";
        cout << "2. Edit Brand\n";
        cout << "3. Edit Price\n";
        cout << "4. Edit Capacity\n";
        cout << "0. Exit to main menu\n";
        cout << "Choose an option: ";
        cin >> editChoice;

        string newName, newBrand;
        double newPrice, newCapacity;

        switch (editChoice) {
        case 1:
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, newName);
            fridge->setName(newName);
            cout << "Name updated successfully!" << endl;
            break;
        case 2:
            cout << "Enter new brand: ";
            cin.ignore();
            getline(cin, newBrand);
            fridge->setBrand(newBrand);
            cout << "Brand updated successfully!" << endl;
            break;
        case 3:
            cout << "Enter new price: ";
            cin >> newPrice;
            fridge->setPrice(newPrice);
            cout << "Price updated successfully!" << endl;
            break;
        case 4:
            cout << "Enter new capacity (liters): ";
            cin >> newCapacity;
            fridge->setCapacity(newCapacity);
            cout << "Capacity updated successfully!" << endl;
            break;
        case 0:
            cout << "Exiting edit menu." << endl;
            break;
        default:
            cout << "Invalid option! Please try again." << endl;
        }
    } while (editChoice != 0);
}

void editWashingMachine(WashingMachine* washingMachine) {
    int editChoice;

    do {
        cout << "\n--- Edit Washing Machine Menu ---\n";
        cout << "1. Edit Name\n";
        cout << "2. Edit Brand\n";
        cout << "3. Edit Price\n";
        cout << "4. Edit Load Capacity\n";
        cout << "0. Exit to main menu\n";
        cout << "Choose an option: ";
        cin >> editChoice;

        string newName, newBrand;
        double newPrice, newLoadCapacity;

        switch (editChoice) {
        case 1:
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, newName);
            washingMachine->setName(newName);
            cout << "Name updated successfully!" << endl;
            break;
        case 2:
            cout << "Enter new brand: ";
            cin.ignore();
            getline(cin, newBrand);
            washingMachine->setBrand(newBrand);
            cout << "Brand updated successfully!" << endl;
            break;
        case 3:
            cout << "Enter new price: ";
            cin >> newPrice;
            washingMachine->setPrice(newPrice);
            cout << "Price updated successfully!" << endl;
            break;
        case 4:
            cout << "Enter new load capacity (kg): ";
            cin >> newLoadCapacity;
            washingMachine->setLoadCapacity(newLoadCapacity);
            cout << "Load capacity updated successfully!" << endl;
            break;
        case 0:
            cout << "Exiting edit menu." << endl;
            break;
        default:
            cout << "Invalid option! Please try again." << endl;
        }
    } while (editChoice != 0);
}

void editTV(TV* tv) {
    int editChoice;

    do {
        cout << "\n--- Edit TV Menu ---\n";
        cout << "1. Edit Name\n";
        cout << "2. Edit Brand\n";
        cout << "3. Edit Price\n";
        cout << "4. Edit Screen Size\n";
        cout << "0. Exit to main menu\n";
        cout << "Choose an option: ";
        cin >> editChoice;

        string newName, newBrand;
        double newPrice, newScreenSize;

        switch (editChoice) {
        case 1:
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, newName);
            tv->setName(newName);
            cout << "Name updated successfully!" << endl;
            break;
        case 2:
            cout << "Enter new brand: ";
            cin.ignore();
            getline(cin, newBrand);
            tv->setBrand(newBrand);
            cout << "Brand updated successfully!" << endl;
            break;
        case 3:
            cout << "Enter new price: ";
            cin >> newPrice;
            tv->setPrice(newPrice);
            cout << "Price updated successfully!" << endl;
            break;
        case 4:
            cout << "Enter new screen size (inches): ";
            cin >> newScreenSize;
            tv->setScreenSize(newScreenSize);
            cout << "Screen size updated successfully!" << endl;
            break;
        case 0:
            cout << "Exiting edit menu." << endl;
            break;
        default:
            cout << "Invalid option! Please try again." << endl;
        }
    } while (editChoice != 0);
}

void editAppliance() {
    int editChoice;
    cout << "From where do you want to edit the appliance?\n";
    cout << "1. Queue\n2. Stack\n3. Priority Queue\n";
    cout << "Your choice: ";
    cin >> editChoice;

    while (cin.fail() || editChoice < 1 || editChoice > 3) {
        checkStreamState(cin);
        cout << "Invalid input. Please enter a number between 1 and 3: ";
        cin >> editChoice;
    }

    switch (editChoice) {
    case 1:
        if (!applianceQueue.empty()) {
            Appliance* appliance = applianceQueue.front(); 
            if (Fridge* fridge = dynamic_cast<Fridge*>(appliance)) {
                cout << "Editing fridge from queue:\n";
                fridge->displayInfo(); 
                editFridge(fridge); 
            }
            else if (WashingMachine* washingMachine = dynamic_cast<WashingMachine*>(appliance)) {
                cout << "Editing washing machine from queue:\n";
                washingMachine->displayInfo();
                editWashingMachine(washingMachine);
            }
            else if (TV* tv = dynamic_cast<TV*>(appliance)) {
                cout << "Editing TV from queue:\n";
                tv->displayInfo();
                editTV(tv);
            }
            else {
                cout << "Selected appliance is not recognized." << endl;
            }
        }
        else {
            cout << "Queue is empty!" << endl;
        }
        break;

    case 2:
        if (!applianceStack.empty()) {
            Appliance* appliance = applianceStack.top(); 
            if (Fridge* fridge = dynamic_cast<Fridge*>(appliance)) {
                cout << "Editing fridge from stack:\n";
                fridge->displayInfo(); 
                editFridge(fridge); 
            }
            else if (WashingMachine* washingMachine = dynamic_cast<WashingMachine*>(appliance)) {
                cout << "Editing washing machine from stack:\n";
                washingMachine->displayInfo();
                editWashingMachine(washingMachine);
            }
            else if (TV* tv = dynamic_cast<TV*>(appliance)) {
                cout << "Editing TV from stack:\n";
                tv->displayInfo();
                editTV(tv);
            }
            else {
                cout << "Selected appliance is not recognized." << endl;
            }
        }
        else {
            cout << "Stack is empty!" << endl;
        }
        break;

    case 3:
        if (!appliancePQueue.empty()) {
            Appliance* appliance = appliancePQueue.top(); 
            if (Fridge* fridge = dynamic_cast<Fridge*>(appliance)) {
                cout << "Editing fridge from priority queue:\n";
                fridge->displayInfo(); 
                editFridge(fridge); 
            }
            else if (WashingMachine* washingMachine = dynamic_cast<WashingMachine*>(appliance)) {
                cout << "Editing washing machine from priority queue:\n";
                washingMachine->displayInfo();
                editWashingMachine(washingMachine);
            }
            else if (TV* tv = dynamic_cast<TV*>(appliance)) {
                cout << "Editing TV from priority queue:\n";
                tv->displayInfo();
                editTV(tv);
            }
            else {
                cout << "Selected appliance is not recognized." << endl;
            }
        }
        else {
            cout << "Priority queue is empty!" << endl;
        }
        break;

    default:
        cout << "Invalid option!" << endl;
    }
}

void displayAppliance(Appliance* appliance) {
    if (Fridge* fridge = dynamic_cast<Fridge*>(appliance)) {
        fridge->displayInfo();
    }
    else if (WashingMachine* washingMachine = dynamic_cast<WashingMachine*>(appliance)) {
        washingMachine->displayInfo();
    }
    else if (TV* tv = dynamic_cast<TV*>(appliance)) {
        tv->displayInfo();
    }
    else {
        cout << "Unknown appliance type" << endl;
    }
}

void displayAllAppliances() {
    cout << "\n--- All appliances ---\n";

    cout << "\n** Appliances in Queue **\n";
    if (applianceQueue.empty()) {
        cout << "Queue is empty!" << endl;
    }
    else {
        queue<Appliance*> tempQueue = applianceQueue; 
        while (!tempQueue.empty()) {
            displayAppliance(tempQueue.front());
            tempQueue.pop();
        }
    }

    cout << "\n** Appliances in Stack **\n";
    if (applianceStack.empty()) {
        cout << "Stack is empty!" << endl;
    }
    else {
        stack<Appliance*> tempStack = applianceStack; 
        while (!tempStack.empty()) {
            displayAppliance(tempStack.top());
            tempStack.pop();
        }
    }

    cout << "\n** Appliances in Priority Queue **\n";
    if (appliancePQueue.empty()) {
        cout << "Priority queue is empty!" << endl;
    }
    else {
        vector<Appliance*> tempVec; 
        while (!appliancePQueue.empty()) {
            tempVec.push_back(appliancePQueue.top());
            appliancePQueue.pop();
        }

        for (Appliance* appliance : tempVec) {
            displayAppliance(appliance);
        }

        for (Appliance* appliance : tempVec) {
            appliancePQueue.push(appliance);
        }
    }
}

void searchAppliance() {
    string searchName;
    cout << "Enter the name of the appliance to search for: ";
    cin >> searchName;

    cout << "\n** Searching in Queue **\n";
    bool foundInQueue = false;
    queue<Appliance*> tempQueue = applianceQueue;
    while (!tempQueue.empty()) {
        if (tempQueue.front()->getName() == searchName) {
            cout << "Found in Queue: ";
            displayAppliance(tempQueue.front());
            foundInQueue = true;
        }
        tempQueue.pop();
    }
    if (!foundInQueue) {
        cout << "Appliance not found in Queue." << endl;
    }

    cout << "\n** Searching in Stack **\n";
    bool foundInStack = false;
    stack<Appliance*> tempStack = applianceStack; 
    while (!tempStack.empty()) {
        if (tempStack.top()->getName() == searchName) {
            cout << "Found in Stack: ";
            displayAppliance(tempStack.top());
            foundInStack = true;
        }
        tempStack.pop();
    }
    if (!foundInStack) {
        cout << "Appliance not found in Stack." << endl;
    }

    cout << "\n** Searching in Priority Queue **\n";
    bool foundInPriorityQueue = false;
    vector<Appliance*> tempVec; 
    while (!appliancePQueue.empty()) {
        tempVec.push_back(appliancePQueue.top());
        appliancePQueue.pop();
    }

    for (Appliance* appliance : tempVec) {
        if (appliance->getName() == searchName) {
            cout << "Found in Priority Queue: ";
            displayAppliance(appliance);
            foundInPriorityQueue = true;
        }
    }

    for (Appliance* appliance : tempVec) {
        appliancePQueue.push(appliance);
    }

    if (!foundInPriorityQueue) {
        cout << "Appliance not found in Priority Queue." << endl;
    }
}

void sortTransactions() {
    cout << "\n** Sorting Queue **\n";
    vector<Appliance*> queueAppliances;
    while (!applianceQueue.empty()) {
        queueAppliances.push_back(applianceQueue.front());
        applianceQueue.pop();
    }

    sort(queueAppliances.begin(), queueAppliances.end(), [](Appliance* a, Appliance* b) {
        return a->getPrice() < b->getPrice();
        });

    for (Appliance* appliance : queueAppliances) {
        applianceQueue.push(appliance);
    }

    for (Appliance* appliance : queueAppliances) {
        displayAppliance(appliance);
    }

    cout << "\n** Sorting Stack **\n";
    vector<Appliance*> stackAppliances;
    while (!applianceStack.empty()) {
        stackAppliances.push_back(applianceStack.top());
        applianceStack.pop();
    }

    sort(stackAppliances.begin(), stackAppliances.end(), [](Appliance* a, Appliance* b) {
        return a->getPrice() < b->getPrice();
        });

    for (int i = stackAppliances.size() - 1; i >= 0; --i) {
        applianceStack.push(stackAppliances[i]);
    }

    for (Appliance* appliance : stackAppliances) {
        displayAppliance(appliance);
    }

    cout << "\n** Sorting Priority Queue **\n";
    vector<Appliance*> priorityQueueAppliances;

    while (!appliancePQueue.empty()) {
        priorityQueueAppliances.push_back(appliancePQueue.top());
        appliancePQueue.pop();
    }

    sort(priorityQueueAppliances.begin(), priorityQueueAppliances.end(), [](Appliance* a, Appliance* b) {
        return a->getPrice() < b->getPrice();
        });

    for (Appliance* appliance : priorityQueueAppliances) {
        appliancePQueue.push(appliance);
    }

    for (Appliance* appliance : priorityQueueAppliances) {
        displayAppliance(appliance);
    }
}

void writeTransactionsToFile() {
    ofstream outFile("transactions5.txt");
    if (!outFile) {
        cout << "Error opening a file for writing" << endl;
        return;
    }

    outFile << "** Devices in the queue **\n";
    queue<Appliance*> tempQueue = applianceQueue;
    while (!tempQueue.empty()) {
        Appliance* appliance = tempQueue.front();
        string applianceType;

        if (Fridge* fridge = dynamic_cast<Fridge*>(appliance)) {
            applianceType = "Fridge";
            outFile << applianceType << ","
                << fridge->getName() << ","
                << fridge->getBrand() << ","
                << fridge->getPrice() << ","
                << fridge->getCapacity() << "\n";
        }
        else if (WashingMachine* washingMachine = dynamic_cast<WashingMachine*>(appliance)) {
            applianceType = "WashingMachine";
            outFile << applianceType << ","
                << washingMachine->getName() << ","
                << washingMachine->getBrand() << ","
                << washingMachine->getPrice() << ","
                << washingMachine->getLoadCapacity() << "\n";
        }
        else if (TV* tv = dynamic_cast<TV*>(appliance)) {
            applianceType = "TV";
            outFile << applianceType << ","
                << tv->getName() << ","
                << tv->getBrand() << ","
                << tv->getPrice() << ","
                << tv->getScreenSize() << "\n";
        }
        else {
            applianceType = "Unknown";
            outFile << applianceType << ","
                << appliance->getName() << ","
                << appliance->getBrand() << ","
                << appliance->getPrice() << "\n";
        }

        tempQueue.pop();
    }

    outFile << "\n** Devices in the stack **\n";
    stack<Appliance*> tempStack = applianceStack;
    while (!tempStack.empty()) {
        Appliance* appliance = tempStack.top();
        string applianceType;

        if (Fridge* fridge = dynamic_cast<Fridge*>(appliance)) {
            applianceType = "Fridge";
            outFile << applianceType << ","
                << fridge->getName() << ","
                << fridge->getBrand() << ","
                << fridge->getPrice() << ","
                << fridge->getCapacity() << "\n";
        }
        else if (WashingMachine* washingMachine = dynamic_cast<WashingMachine*>(appliance)) {
            applianceType = "WashingMachine";
            outFile << applianceType << ","
                << washingMachine->getName() << ","
                << washingMachine->getBrand() << ","
                << washingMachine->getPrice() << ","
                << washingMachine->getLoadCapacity() << "\n";
        }
        else if (TV* tv = dynamic_cast<TV*>(appliance)) {
            applianceType = "TV";
            outFile << applianceType << ","
                << tv->getName() << ","
                << tv->getBrand() << ","
                << tv->getPrice() << ","
                << tv->getScreenSize() << "\n";
        }
        else {
            applianceType = "Unknown";
            outFile << applianceType << ","
                << appliance->getName() << ","
                << appliance->getBrand() << ","
                << appliance->getPrice() << "\n";
        }

        tempStack.pop();
    }

    outFile << "\n** Devices in the priority queue **\n";

    auto comparator = [](Appliance* a, Appliance* b) {
        return a->getPrice() < b->getPrice();
        };

    priority_queue<Appliance*, vector<Appliance*>, decltype(comparator)> tempPQueue(comparator);

    while (!appliancePQueue.empty()) {
        tempPQueue.push(appliancePQueue.top());
        appliancePQueue.pop();
    }

    while (!tempPQueue.empty()) {
        Appliance* appliance = tempPQueue.top();
        string applianceType;

        if (Fridge* fridge = dynamic_cast<Fridge*>(appliance)) {
            applianceType = "Fridge";
            outFile << applianceType << ","
                << fridge->getName() << ","
                << fridge->getBrand() << ","
                << fridge->getPrice() << ","
                << fridge->getCapacity() << "\n";
        }
        else if (WashingMachine* washingMachine = dynamic_cast<WashingMachine*>(appliance)) {
            applianceType = "WashingMachine";
            outFile << applianceType << ","
                << washingMachine->getName() << ","
                << washingMachine->getBrand() << ","
                << washingMachine->getPrice() << ","
                << washingMachine->getLoadCapacity() << "\n";
        }
        else if (TV* tv = dynamic_cast<TV*>(appliance)) {
            applianceType = "TV";
            outFile << applianceType << ","
                << tv->getName() << ","
                << tv->getBrand() << ","
                << tv->getPrice() << ","
                << tv->getScreenSize() << "\n";
        }
        else {
            applianceType = "Unknown";
            outFile << applianceType << ","
                << appliance->getName() << ","
                << appliance->getBrand() << ","
                << appliance->getPrice() << "\n";
        }

        tempPQueue.pop();
    }

    outFile.close();
    cout << "The data was successfully written to the file" << endl;
}


Appliance* createApplianceFromLine(const string& line) {
    size_t pos1 = line.find(',');
    size_t pos2 = line.find(',', pos1 + 1);
    size_t pos3 = line.find(',', pos2 + 1);
    size_t pos4 = line.find(',', pos3 + 1);

    string applianceType = line.substr(0, pos1);
    string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
    string brand = line.substr(pos2 + 1, pos3 - pos2 - 1);
    double price = stod(line.substr(pos3 + 1));
    double el = (pos4 != string::npos) ? stod(line.substr(pos4 + 1)) : 0;

    Appliance* appliance;
    if (applianceType == "Fridge") {
        appliance = (pos4 != string::npos) ? new Fridge(name, brand, price, el) : new Fridge(name, brand, price);
    }
    else if (applianceType == "WashingMachine") {
        appliance = (pos4 != string::npos) ? new WashingMachine(name, brand, price, el) : new WashingMachine(name, brand, price);
    }
    else if (applianceType == "TV") {
        appliance = (pos4 != string::npos) ? new TV(name, brand, price, el) : new TV(name, brand, price);
    }
    else {
        appliance = new Appliance(name, brand, price);
    }

    return appliance;
}


void readTransactionsFromFile() {
    ifstream inFile("transactions5.txt");
    if (!inFile) {
        cout << "Error opening a file for reading" << endl;
        return;
    }

    string line;

    cout << "Reading devices from the queue\n";
    while (getline(inFile, line)) {
        if (line == "** Devices in the queue **") break;
    }

    while (getline(inFile, line) && !line.empty() && line[0] != '*') {
        Appliance* appliance = createApplianceFromLine(line);
        applianceQueue.push(appliance);
    }

    cout << "Reading devices from the stack\n";
    while (getline(inFile, line)) {
        if (line == "** Devices in the stack **") break;
    }

    while (getline(inFile, line) && !line.empty() && line[0] != '*') {
        Appliance* appliance = createApplianceFromLine(line);
        applianceStack.push(appliance);
    }

    cout << "Reading devices from the priority queue\n";
    while (getline(inFile, line)) {
        if (line == "** Devices in the priority queue **") break;
    }

    while (getline(inFile, line) && !line.empty() && line[0] != '*') {
        Appliance* appliance = createApplianceFromLine(line);
        appliancePQueue.push(appliance);
    }

    inFile.close();
    cout << "Data successfully read from the file" << endl;
}

void clearFile() {
    ofstream outFile("transactions5.txt", ios::trunc);
    if (!outFile) {
        cout << "Error opening file for clearing.\n";
        return;
    }
    outFile.close();
    cout << "File cleared successfully!\n";
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
