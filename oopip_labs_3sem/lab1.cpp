#include <iomanip>
#include <iostream>
#include <vector>


using namespace std;

class Software {
private:
    string name;
    string version;
    string developer;

public:
    Software(string name, string version, string developer)
        : name(name), version(version), developer(developer) {};

    virtual void display() const {
        cout << setw(20) << name << setw(20) << version << setw(20) << developer << endl;
    }

    virtual ~Software() = default;
};

class SystemSoftware final : public Software {
public:
    string type;
    SystemSoftware(string name, string version, string developer, string type)
        : Software(name, version, developer), type(type) {};

    virtual void display() const override {
        cout << setw(20) << "System software" << setw(20) << type << endl;
    }
};

class ApplicationSoftware final : public Software {
public:
    string purpose;

    ApplicationSoftware(string name, string version, string developer, string purpose)
        : Software(name, version, developer), purpose(purpose) {}

    void display() const override {
        Software::display();
        cout << setw(20) << "Application software" << setw(20) << purpose << endl;
    }
};

class Computer {
public:
    string model;
    string serialNumber;
    vector<Software*> installedSoftware;

    Computer(string model, string serialNumber) : model(model), serialNumber(serialNumber) {}

    ~Computer() {
        for (Software* software : installedSoftware) {
            delete software;
        }
    }

    void addSoftware(Software* software) {
        installedSoftware.push_back(software);
    }

    void display() const {
        cout << setw(15) << model << setw(15) << serialNumber << endl;
        for (Software* software : installedSoftware) {
            software->display();
        }
    }
};

class SoftwareCollection {
private:
    vector<Computer> computers;
public:
    void addComputer(Computer computer) {
        computers.push_back(computer);
    }

    void display() const {
        if (computers.empty()) {
            cout << "No computers have been added" << endl;
        }
        else {
            cout.setf(ios::left);
            cout << setw(15) << "Model" << setw(15) << "Serial Number" << endl;
            for (const auto& computer : computers) {
                computer.display();
            }
            cout.unsetf(ios::left);
        }
    }


    void sortComputers() {
        for (size_t i = 0; i < computers.size() - 1; ++i) {
            for (size_t j = 0; j < computers.size() - i - 1; ++j) {
                if (computers[j].model > computers[j + 1].model) {
                    swap(computers[j], computers[j + 1]);
                }
            }
        }
        cout << "Computers sorted by model" << endl;
    }

    Computer* searchComputer(const string& model) {
        for (auto& computer : computers) {
            if (computer.model == model) {
                return &computer;
            }
        }
        return nullptr;
    }

    void deleteComputer(const string& model) {
        auto i = computers.begin();
        while (i != computers.end()) {
            if (i->model == model) {
                i = computers.erase(i);
                cout << "Computer has been deleted" << endl;
                return;
            }
            else {
                ++i;
            }
        }
        cout << "Computer not found" << endl;
    }

};

void checkStreamState(istream& inStream) {
    if (inStream.eof()) {
        cout << "end of file" << endl;
    }
    else if (inStream.fail()) {
        cout << "input error" << endl;
        inStream.clear();
        inStream.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if (inStream.bad()) {
        cout << "error when working with a stream" << endl;
    }
    else if (inStream.good()) {
        cout << "stream is good" << endl;
    }
}

void displayMenu() {
    cout << "\n-----Menu-----\n";
    cout << "1. Add a computer\n";
    cout << "2. Add software\n";
    cout << "3. Delete a computer\n";
    cout << "4. Edit software\n";
    cout << "5. Sort computers\n";
    cout << "6. Search a computer\n";
    cout << "7. Display all computers\n";
    cout << "0. Exit\n";
    cout << "-----------------\n";
}

void addComputer(SoftwareCollection& collection) {
    string model, serialNumber;
    cout << "Please enter model: ";
    cin >> model;
    cout << "Please enter serial number: ";
    cin >> serialNumber;
    collection.addComputer(Computer(model, serialNumber));
    cout << "Computer has been added" << endl;
}

void addSoftwareToComputer(SoftwareCollection& collection) {
    string model, name, version, developer;

    do {
        cout << "Enter model of the computer: ";
        cin >> model;
        if (model.empty()) {
            cout << "Model cannot be empty. Please try again." << endl;
        }
    } while (model.empty());

    Computer* computer = collection.searchComputer(model);

    if (computer) {
        int softwareType;
        bool validType = false;

        do {
            cout << "Choose software type (1 - System Software, 2 - Application Software): ";
            cin >> softwareType;
            if (cin.fail()) {
                checkStreamState(cin);
            }
            else if (softwareType == 1 || softwareType == 2) {
                validType = true;
            }
            else {
                cout << "Invalid choice. Please enter 1 for System Software or 2 for Application Software" << endl;
            }
        } while (!validType);

        cout << "Enter software name: ";
        cin >> name;
        cout << "Enter version: ";
        cin >> version;
        cout << "Enter developer: ";
        cin >> developer;

        if (softwareType == 1) {
            string osType;
            cout << "Enter OS type: ";
            cin >> osType;
            computer->addSoftware(new SystemSoftware(name, version, developer, osType));
        }
        else if (softwareType == 2) {
            string purpose;
            cout << "Enter purpose: ";
            cin >> purpose;
            computer->addSoftware(new ApplicationSoftware(name, version, developer, purpose));
        }
    }
    else {
        cout << "Computer with model '" << model << "' not found." << endl;
        return addSoftwareToComputer(collection);
    }
}

int getChoice() {
    int choice;
    cin >> choice;

    while (cin.fail() || choice < 0 || choice > 7) {
        checkStreamState(cin);
        cout << "Invalid input. Please enter a number between 0 and 7: ";
        cin >> choice;
    }

    return choice;
}

int main() {
    SoftwareCollection collection;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        choice = getChoice();

        switch (choice) {
        case 1:
            addComputer(collection);
            break;
        case 2:
            addSoftwareToComputer(collection);
            break;
        case 3: {
            string model;
            cout << "Enter model to delete: ";
            cin >> model;
            collection.deleteComputer(model);
            break;
        }
        case 4: {

        }
        case 5:
            collection.sortComputers();
            break;
        case 6: {
            string model;
            cout << "Enter model to search: ";
            cin >> model;
            Computer* computer = collection.searchComputer(model);
            if (computer) {
                computer->display();
            }
            else {
                cout << "Computer not found" << endl;
            }
            break;
        }
        case 7:
            collection.display();
            break;
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
