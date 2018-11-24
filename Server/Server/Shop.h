#pragma once
#include <vector>
#include <string>

#include "Item.h"

using namespace std;

class Shop
{
public:
	vector<string> Messages;
	vector<Item> items;

	void LoadShopData();
	void CreateMessages();
	void UpdateShop();

};

