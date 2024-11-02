#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
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
	
	virtual void display() const {
		cout << "Model: " << name << "\nBrand: " << brand
			<< "\nPrice: $" << fixed << setprecision(2) << price << endl;
	}

	string getName() const { return name; }
	void setName(const string& name) { this->name = name; }
	
	string getBrand() const { return brand; }
	void setBrand(const string& brand) { this->brand = brand; }
	
	double getPrice() const { return price; }
	void setPrice(double price) { this->price = price; }
	
	virtual unique_ptr<Appliance> clone() const = 0;
	
	virtual ~Appliance() = default;
};

class Fridge : public Appliance {
	double capacity;
public:
	Fridge(string name, string brand, double price, double capacity)
		: Appliance(name, brand, price), capacity(capacity) {}
	
	double getCapacity() const {
		return capacity;
	}
	void setCapacity(double capacity) {
		this->capacity = capacity;
	}
	
	void display() const override {
		cout << "Fridge ";
		Appliance::display();
		cout << "Capacity: " << capacity << " liters" << endl;
		cout << "=======================\n";
	}
	
	unique_ptr<Appliance> clone() const override {
		return make_unique<Fridge>(*this);
	}
};

class WashingMachine : public Appliance {
	double loadCapacity;
public:
	WashingMachine(string name, string brand, double price, double loadCapacity)
		: Appliance(name, brand, price), loadCapacity(loadCapacity) {}
	
	double getLoadCapacity() const { 
		return loadCapacity; 
	}
	void setLoadCapacity(double loadCapacity) { 
		this->loadCapacity = loadCapacity;
	}
	
	void display() const override {
		cout << "Washing Machine ";
		Appliance::display();
		cout << "Load Capacity: " << loadCapacity << " kg" << endl;
		cout << "=======================\n";
	}
	
	unique_ptr<Appliance> clone() const override {
		return make_unique<WashingMachine>(*this);
	}
};

class TV : public Appliance {
	double screenSize;
public:
	TV(string name, string brand, double price, double screenSize)
		: Appliance(name, brand, price), screenSize(screenSize) {}
	
	double getScreenSize() const { 
		return screenSize; 
	}
	void setScreenSize(double screenSize) { 
		this->screenSize = screenSize; 
	}
	
	void display() const override {
		cout << "TV ";
		Appliance::display();
		cout << "Screen Size: " << screenSize << " inches" << endl;
		cout << "=======================\n";
	
	}
	unique_ptr<Appliance> clone() const override {
		return make_unique<TV>(*this);
	}
};

//полиморфная фабрика
class Factory {
public:
	virtual unique_ptr<Appliance> createAppliance(const string& name, const string& brand,
		double price, double spec) const = 0;
	
	virtual ~Factory() = default;
};

class FridgeFactory : public Factory {
public:
	unique_ptr<Appliance> createAppliance(const string& name, const string& brand, 
		double price, double capacity) const override {
		return make_unique<Fridge>(name, brand, price, capacity);
	}
};

class WashingMachineFactory : public Factory {
public:
	unique_ptr<Appliance> createAppliance(const string& name, const string& brand, 
		double price, double loadCapacity) const override {
		return make_unique<WashingMachine>(name, brand, price, loadCapacity);
	}
};

class TVFactory : public Factory {
public:
	unique_ptr<Appliance> createAppliance(const string& name, const string& brand, 
		double price, double screenSize) const override {
		return make_unique<TV>(name, brand, price, screenSize);
	}
};

class Inventory {
	

public:
	vector<unique_ptr<Appliance>> items;
	void addAppliance(unique_ptr<Appliance> appliance) {
		items.push_back(move(appliance));
	}

	void removeAppliance(const string& name) {
		auto it = remove_if(items.begin(), items.end(),
			[&](const unique_ptr<Appliance>& appliance) { return appliance->getName() == name; });
		if (it != items.end()) {
			items.erase(it, items.end());
			cout << "Appliance removed successfully.\n";
		}
		else {
			cout << "Appliance not found.\n";
		}
	}

	void displayAll() const {
		if (items.empty()) {
			cout << "No appliances in inventory.\n";
		}
		else {
			for (const auto& item : items) {
				item->display();
			}
		}
	}

	void clearFile(const string& filename) {
		ofstream file(filename, ios::trunc);
		file.close();
		cout << "File cleared\n";
	}

	void editAppliance(const string& name, const Factory& factory) {
		for (auto& item : items) {
			if (item->getName() == name) {
				string newName, newBrand;
				double newPrice, spec;
				cout << "Enter new details:\nName: ";
				cin >> newName;
				cout << "Brand: ";
				cin >> newBrand;
				cout << "Price: ";
				cin >> newPrice;
				cout << "Spec (capacity/load/screen size): ";
				cin >> spec;
				item = factory.createAppliance(newName, newBrand, newPrice, spec);
				cout << "Appliance edited successfully\n";
				return;
			}
		}
		cout << "Appliance not found\n";
	}

	void sortInventoryByName() {
		sort(items.begin(), items.end(),
			[](const unique_ptr<Appliance>& a, const unique_ptr<Appliance>& b) {
				return a->getName() < b->getName();
			});
		cout << "Inventory sorted by name\n";
	}

	void sortInventoryByPrice() {
		sort(items.begin(), items.end(),
			[](const unique_ptr<Appliance>& a, const unique_ptr<Appliance>& b) {
				return a->getPrice() < b->getPrice();
			});
		cout << "Inventory sorted by price\n";
	}

	unique_ptr<Appliance>& getAppliance(const string& name) {
		for (auto& item : items) {
			if (item->getName() == name) {
				return item;
			}
		}
		throw runtime_error("Appliance not found");
	}
};