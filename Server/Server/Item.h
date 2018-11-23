#pragma once
#include <string>
class Item
{
private:
	std::string _Description;
	int _Units;
	int _Price;
public:
	Item(std::string Desc, int units, int price) { _Description = Desc; _Units = units; _Price = price; };
	~Item();

	// Getters & Setters
	std::string getDescription() { return _Description; };
	void setDescription(std::string description) { _Description = description; };
	int getUnits() { return _Units; };
	void setUnits(int units) { _Units = units; };
	int getPrice() { return _Price; };
	void setPrice(int price) { _Price = price; };
};

