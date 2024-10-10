#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <sstream>

using namespace std;

class Software {
public:
    string name;
    string version;
    string developer;

public:
    Software(string name = "", string version = "", string developer = "")
        : name(name), version(version), developer(developer) {};

    virtual void display() const {
        cout << setw(20) << name << setw(20) << version << setw(20) << developer << endl;
    }

    virtual ~Software() = default;
};

ostream& operator<<(ostream& os, const Software& software) {
    os << "Name: " << software.name << " Version: " << software.version << " Developer: " << software.developer;
    return os;
}

istream& operator>>(istream& is, Software& software) {
    is >> software.name >> software.version >> software.developer;
    return is;
}

class FileHandler {
public:
    fstream file;

    bool openFile(const string& filename, ios::openmode mode) {
        file.open(filename, mode);
        return file.is_open();
    }

    void closeFile() {
        if (file.is_open()) {
            file.close();
        }
    }
 
    void moveToPositionG(streampos pos) {
        if (file.is_open()) {
            file.seekg(pos);//перемещает чтение
        }
    }


    void moveToPositionP(streampos pos) {
        if (file.is_open()) {
            file.seekp(pos);//пермещает запись
        }
    }

   
    streampos getCurrentPositionG() {
        if (file.is_open()) {
            return file.tellg();//получает текущую позицию чтения
        }
        return -1; 
    }

    
    streampos getCurrentPositionP() {
        if (file.is_open()) {
            return file.tellp();//текущая позиция чтения
        }
        return -1; 
    }

    void writeData(const string& data) {
        if (file.is_open()) {
            file << data;
        }
    }

    void readData(string& data) {
        if (file.is_open()) {
            getline(file, data);
        }
    }

    void clearFileContent() {
        if (file.is_open()) {
            file.seekp(0, ios::beg); // укаазатель на начало
            file << "";           
        }
    }
};

class SystemSoftware final : public Software {
public:
    string type;
    SystemSoftware(string name = "", string version = "", string developer = "", string type = "")
        : Software(name, version, developer), type(type) {};

    void display() const override {
        cout << setw(20) << "System software" << setw(20) << type << endl;
    }

    friend ostream& operator<<(ostream& os, const SystemSoftware& software) {
        os << static_cast<const Software&>(software);
        os << " Type: " << software.type;
        return os;
    }

    friend istream& operator>>(istream& is, SystemSoftware& software) {
        is >> static_cast<Software&>(software);
        is >> software.type;
        return is;
    }
};

class ApplicationSoftware final : public Software {
public:
    string purpose;
    ApplicationSoftware(string name = "", string version = "", string developer = "", string purpose = "")
        : Software(name, version, developer), purpose(purpose) {}

    void display() const override {
        Software::display();
        cout << setw(20) << "Application software" << setw(20) << purpose << endl;
    }

    friend ostream& operator<<(ostream& os, const ApplicationSoftware& software) {
        os << static_cast<const Software&>(software);
        os << " Purpose: " << software.purpose;
        return os;
    }

    friend istream& operator>>(istream& is, ApplicationSoftware& software) {
        is >> static_cast<Software&>(software);
        is >> software.purpose;
        return is;
    }
};

class Computer {
public:
    string model;
    string serialNumber;
    vector<Software*> installedSoftware;

    Computer(string model = "", string serialNumber = "")
        : model(model), serialNumber(serialNumber) {}

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
    void addComputer(const Computer& computer) {
        computers.push_back(computer);
    }

    void display() const {
        if (computers.empty()) {
            cout << "No computers have been added" << endl;
        }
        else {
            cout.setf(ios::left);
            cout << setw(15) << "Model" << setw(15) << "Serial number" << endl;
            for (const auto& computer : computers) {
                computer.display();
            }
            cout.unsetf(ios::left);
        }
    }

    void sortComputers() {
        if (computers.empty()) {
            cout << "No computers have been added" << endl;
        }
        else {
            for (size_t i = 0; i < computers.size() - 1; ++i) {
                for (size_t j = 0; j < computers.size() - i - 1; ++j) {
                    if (computers[j].model > computers[j + 1].model) {
                        swap(computers[j], computers[j + 1]);
                    }
                }
            }
            cout << "Computers sorted by model" << endl;
        }
    }

    Computer* searchComputer(const string& model) {
        for (size_t i = 0; i < computers.size(); ++i) {
            Computer& computer = computers[i];
            if (computer.model == model) {
                return &computer;
            }
        }
        return nullptr;
    }

    void deleteComputer(const string& model) {
        for (size_t i = 0; i < computers.size(); ++i) {
            if (computers[i].model == model) {
                computers.erase(computers.begin() + i);
                cout << "Computer has been deleted" << endl;
                return;
            }
        }
        cout << "Computer not found" << endl;
    }

    const vector<Computer>& getComputers() const {
        return computers;
    }
};

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

    cout << "Enter model of the computer: ";
    cin >> model;

    Computer* computer = collection.searchComputer(model);
    if (computer) {
        int softwareType;
        cout << "Choose software type (1 - System Software, 2 - Application Software): ";
        cin >> softwareType;
        
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
        cout << "Computer with model '" << model << "' not found" << endl;
    }
}

void editSoftware(SoftwareCollection& collection) {
    string model, softwareName;
    cout << "Enter model of the computer: ";
    cin >> model;

    Computer* computer = collection.searchComputer(model);
    if (computer) {
        cout << "Enter name of the software to edit: ";
        cin >> softwareName;

        for (Software* software : computer->installedSoftware) {
            if (software->name == softwareName) {
                cout << "Editing software: " << software->name << endl;

                string newName, newVersion, newDeveloper;
                cout << "Enter new name (or leave empty to keep current): ";
                cin.ignore();
                getline(cin, newName);
                cout << "Enter new version (or leave empty to keep current): ";
                getline(cin, newVersion);
                cout << "Enter new developer (or leave empty to keep current): ";
                getline(cin, newDeveloper);

                if (!newName.empty()) software->name = newName;
                if (!newVersion.empty()) software->version = newVersion;
                if (!newDeveloper.empty()) software->developer = newDeveloper;

                cout << "Software has been updated." << endl;
                return;
            }
        }
        cout << "Software not found." << endl;
    }
    else {
        cout << "Computer with model '" << model << "' not found." << endl;
    }
}

void saveToFile(const SoftwareCollection& collection, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& computer : collection.getComputers()) {
            outFile << "Model: " << computer.model << "\n";
            outFile << "Serial Number: " << computer.serialNumber << "\n";
            outFile << "Installed Software: " << computer.installedSoftware.size() << "\n";

            for (const auto& software : computer.installedSoftware) {
                if (auto sysSoftware = dynamic_cast<SystemSoftware*>(software)) {
                    outFile << "  Software Type: System\n";
                    outFile << "  Name: " << sysSoftware->name << 
                        ", Version: " << sysSoftware->version << 
                        ", Developer: " << sysSoftware->developer << ", Type: " << sysSoftware->type << "\n";
                }
                else if (auto appSoftware = dynamic_cast<ApplicationSoftware*>(software)) {
                    outFile << "  Software Type: Application\n";
                    outFile << "  Name: " << appSoftware->name << 
                        ", Version: " << appSoftware->version << 
                        ", Developer: " << appSoftware->developer << ", Purpose: " << appSoftware->purpose << "\n";
                }
            }
            outFile << "------------------------------\n";
        }
        outFile.close();
        cout << "Data has been saved to " << filename << endl;
    }
    else {
        cerr << "Error: Cannot open file for writing." << endl;
    }
}

void addDataToFile(const SoftwareCollection& collection, const string& filename) {
    ofstream outFile(filename, ios::app); //для добавления в конец
    if (outFile.is_open()) {
        for (const auto& computer : collection.getComputers()) {
            outFile << "Model: " << computer.model << "\n";
            outFile << "Serial Number: " << computer.serialNumber << "\n";
            outFile << "Installed Software: " << computer.installedSoftware.size() << "\n";

            for (const auto& software : computer.installedSoftware) {
                if (dynamic_cast<SystemSoftware*>(software)) {
                    outFile << "  Software Type: System\n";
                    outFile << "  " << *dynamic_cast<SystemSoftware*>(software) << "\n";
                }
                else if (dynamic_cast<ApplicationSoftware*>(software)) {
                    outFile << "  Software Type: Application\n";
                    outFile << "  " << *dynamic_cast<ApplicationSoftware*>(software) << "\n";
                }
            }
            outFile << "------------------------------\n";
        }
        outFile.close();
        cout << "Data has been appended to " << filename << endl;
    }
    else {
        cerr << "can't open file" << endl;
    }
}

void deleteDataFromFile(const string& model, const string& filename) {
    ifstream inFile(filename);
    ofstream tempFile("temp.txt"); 

    if (inFile.is_open() && tempFile.is_open()) {
        string line;
        bool toDelete = false;
        while (getline(inFile, line)) {
            if (line.find("Model: " + model) != string::npos) {
                toDelete = true;
            }
            if (!toDelete) {
                tempFile << line << "\n";
            }
            if (line == "------------------------------") {
                toDelete = false; 
            }
        }
        inFile.close();
        tempFile.close();
        remove(filename.c_str());         
        rename("temp.txt", filename.c_str()); 
        cout << "Data for model '" << model << "' has been deleted from " << filename << endl;
    }
    else {
        cerr << "can't open file" << endl;
    }
}

void editDataInFile(const string& model, Computer& computer, const string& filename) {
    ifstream inFile(filename);
    ofstream tempFile("temp.txt"); 

    if (inFile.is_open() && tempFile.is_open()) {
        string line, newModel, newSerialNumber;
        bool toEdit = false;
        while (getline(inFile, line)) {
            if (line.find("Model: " + model) != string::npos) {
                toEdit = true;
                cout << "Editing computer with model: " << model << endl;

                cout << "Enter new model: ";
                cin >> newModel;
                cout << "Enter new serial number: ";
                cin >> newSerialNumber;

                
                tempFile << "Model: " << newModel << "\n";
                tempFile << "Serial Number: " << newSerialNumber << "\n";
                tempFile << "Installed Software: " << computer.installedSoftware.size() << "\n";
                tempFile << "------------------------------\n";

            }
            else if (!toEdit) {
                tempFile << line << "\n"; 
            }
            if (line == "------------------------------") {
                toEdit = false; 
            }
        }
        inFile.close();
        tempFile.close();
        remove(filename.c_str());          
        rename("temp.txt", filename.c_str()); 
        cout << "Data for model '" << model << "' has been edited in " << filename << endl;
    }
    else {
        cerr << "can't open file" << endl;
    }
}

void viewDataFromFile(const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }
    else {
        cerr << "can't open file" << endl;
    }
}

void loadFromFile(SoftwareCollection& collection, const string& filename) {
    ifstream inFile(filename);
    string firstLine;
    //getline(inFile, firstLine); 

    if (inFile.is_open()) {
        string model, serialNumber;

        while (getline(inFile, firstLine)) {
            if (firstLine.find("Model: ") != string::npos) {
                model = firstLine.substr(firstLine.find(": ") + 2);
            }
            else if (firstLine.find("Serial Number: ") != string::npos) {
                serialNumber = firstLine.substr(firstLine.find(": ") + 2);
            }
            else if (firstLine == "Installed Software: 0") {
                Computer computer(model, serialNumber);
                collection.addComputer(computer);
                model.clear();
                serialNumber.clear();
            }
            else if (firstLine.find("Software Type: ") != string::npos) {
                Computer computer(model, serialNumber);
                collection.addComputer(computer);
                model.clear();
                serialNumber.clear();
            }
            if (firstLine == "------------------------------") {
                continue;
            }
        }
        inFile.close();
        cout << "Data has been loaded from " << filename << endl;
    }
    else {
        cerr << "can't open file" << endl;
    }
}

void searchDataInFile(const string& searchModel, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        bool found = false;
        while (getline(inFile, line)) {
            if (line.find("Model: " + searchModel) != string::npos) {
                found = true;
                cout << "Found computer: " << endl;
                do {
                    cout << line << endl;
                    getline(inFile, line);
                } while (line != "------------------------------" && !inFile.eof());
                break;
            }
        }
        if (!found) {
            cout << "No computer with model '" << searchModel << endl;
        }
        inFile.close();
    }
    else {
        cerr << "can't open file" << endl;
    }
}

void clearFile(const string& filename) {
    ofstream outFile(filename, ios::trunc);
    if (outFile.is_open()) {
        outFile.close();
        cout << "File " << filename << " has been cleared" << endl;
    }
    else {
        cerr << "Error: Cannot open file for clearing" << endl;
    }
}

int getChoice() {
    int choice;
    cin >> choice;

    while (cin.fail() || choice < 0 || choice > 14) {
        checkStreamState(cin);
        cout << "Invalid input. Please enter a number between 0 and 14: ";
        cin >> choice;
    }

    return choice;
}

void displayMenu() {
    cout << "\n----------Menu----------\n";
    cout << "1. Add a computer\n";
    cout << "2. Add software\n";
    cout << "3. Delete a computer\n";
    cout << "4. Edit software\n";
    cout << "5. Sort computers\n";
    cout << "6. Search a computer\n";
    cout << "7. Display all computers\n";
    cout << "8. Save to file\n";
    cout << "9. Load from file\n";
    cout << "10. Search data in file\n";
    cout << "11. Add data to file\n";
    cout << "12. Delete data from file\n";
    cout << "13. Edit data in file\n";
    cout << "14. Clear file\n";
    cout << "0. Exit\n";
    cout << "-----------------------\n";
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
            editSoftware(collection);
            break;
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
        case 8: {
            saveToFile(collection, "computers.txt");
            break;
        }
        case 9: {
            loadFromFile(collection, "computers.txt");
            break;
        }
        case 10: {
            string model;
            cout << "Enter model to search in file: ";
            cin >> model;
            searchDataInFile(model, "computers.txt");
            break;
        }
        case 11: {
            addDataToFile(collection, "computers.txt");
            break;
        }
        case 12: {
            string model;
            cout << "Enter model to delete from file: ";
            cin >> model;
            deleteDataFromFile(model, "computers.txt");
            break;
        }
        case 13: {
            string model;
            cout << "Enter model to edit in file: ";
            cin >> model;
            Computer* computer = collection.searchComputer(model);
            editDataInFile(model, *computer, "computers.txt");
            break;
        }
        case 14: {
            clearFile("computers.txt");
            break;
        }
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
