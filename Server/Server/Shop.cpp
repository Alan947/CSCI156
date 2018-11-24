#include "Shop.h"

#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void Shop::LoadShopData()
{
	vector<Item> itemList;
	ifstream file("input.txt");
	if (file.is_open())
	{
		string line;    //line from file
		string word;    //word from line
		string subLine;    //subtr of line
		string anItem[3];
		string itemDesc;
		int itemUnits, itemPrice;
		while (getline(file, line)) {
			subLine = line.substr(0, 4);
			if (subLine == "Item") {    //if the word is Item_
				int itemIndex = 0;
				istringstream iss(line);
				while (iss >> word) {
					anItem[itemIndex] = word;
					itemIndex++;
				}
				itemDesc = anItem[0];
				itemUnits = atoi(anItem[1].c_str());
				itemPrice = atoi(anItem[2].c_str());
				Item newItem = Item(itemDesc, itemUnits, itemPrice);
				items.push_back(newItem);
			}
		}

		file.close();
		return;
	}
	else
	{
		cout << "Unable to open file";
		return;
	}
}
void Shop::CreateMessages()
{
	for (int i = 0; i < items.size(); i++)
	{
		Messages.push_back(items[i].getDescription() + " " + to_string(items[i].getUnits()) + " " + to_string(items[i].getPrice()));
	}
}

void Shop::UpdateShop()
{
	for (int i = 0; i < items.size(); i++) 
	{

	}
}
