#include<string>
#include <iostream>
#include <iomanip>
#pragma once

using namespace std;

class Appliance {
protected:
	string name;
	string brand;
	double price;

public:
	Appliance(string name = "Unknown", string brand = "Unknown", double price = 0.0)
		: name(name), brand(brand), price(price) {}

	string getName() const {
		return name;
	};
	void setName(const string& name) {
		this -> name = name;
	};

	string getBrand() const {
		return brand;
	};
	void setBrand(const string& brand) {
		this -> brand = brand;
	};

	double getPrice() const {
		return price;
	};
	void setPrice(double price) {
		this->price = price;
	};

	virtual void displayInfo() const {
		cout << "Model: " << name << "\nBrand: " << brand
			<< "\nPrice: $" << fixed << setprecision(2) << price << endl;
	}

};

class Fridge : public Appliance {
private:
	double capacity;

public:
	Fridge(string name = "Unknown", string brand = "Uknown", double price = 0.0, double capacity = 0.0)
		: Appliance(name, brand, price), capacity(capacity) {}

	double getCapacity() const {
		return capacity;
	}
	void setCapacity(double capacity) {
		this->capacity = capacity;
	}

	void displayInfo() const override {
		cout << "Fridge ";
		Appliance::displayInfo();
		cout << "Capacity: " << capacity << " liters" << endl;
	}
};

class WashingMachine : public Appliance {
private:
	double loadCapacity;

public: 
	WashingMachine(string modelName = "Unknown", string brand = "Uknown", double price = 0.0, double loadCapacity = 0.0)
		: Appliance(modelName, brand, price), loadCapacity(loadCapacity) {}

	double getLoadCapacity() const { 
		return loadCapacity; 
	}
	void setLoadCapacity(double loadCapacity) { 
		this->loadCapacity = loadCapacity; 
	}

	void displayInfo() const override {
		cout << "Washing Machine ";
		Appliance::displayInfo();
		cout << "Load Capacity: " << loadCapacity << " kg" << endl;
	}
};

class TV : public Appliance {
private:
	double screenSize;

public:
	TV(string modelName = "Unknown", string brand = "Uknown", double price = 0.0, double screenSize = 0.0)
		: Appliance(modelName, brand, price), screenSize(screenSize) {}

	int getScreenSize() const { 
		return screenSize; 
	}
	void setScreenSize(int screenSize) { 
		this->screenSize = screenSize; 
	}

	void displayInfo() const override {
		cout << "TV ";
		Appliance::displayInfo();
		cout << "Screen Size: " << screenSize << " inches" << endl;
	}
};

template <class ApplianceType>
class Transaction {
private:
	unsigned int transactionID; 
	ApplianceType appliance;    
	unsigned int quantity;      
	string type;           

public:
	Transaction(unsigned int id, const ApplianceType& appliance, unsigned int qty, string type)
		: transactionID(id), appliance(appliance), quantity(qty), type(type) {}

	unsigned int getTransactionID() const { 
		return transactionID; 
	}
	void setTransactionID(unsigned int id) { 
		transactionID = id; 
	}

	ApplianceType getAppliance() const { 
		return appliance; 
	}
	void setAppliance(const ApplianceType& appliance) {
		this->appliance = appliance; 
	}

	unsigned int getQuantity() const { 
		return quantity; 
	}
	void setQuantity(unsigned int qty) {
		quantity = qty; 
	}

	string getType() const { 
		return type; 
	}
	void setType(const string& type) { 
		this->type = type; 
	}

	void displayTransaction() const {
		cout << "Transaction ID: " << transactionID << "\nType: " << type 
			<< "\nQuantity: " << quantity << endl;
		appliance.displayInfo();
	}
};


