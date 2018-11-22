#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class item{
public:
    string description;
    int units;
    int price;
    
    item( string d, int u, int p ){
        description = d;
        units = u;
        price = p;
    }
    ~item();
};

int main(){
    vector<item*>* itemList = new vector<item*>();
    ifstream file ("input.txt");
    if (file.is_open())
    {
        string line;    //line from file
        string word;    //word from line
        string subLine;    //subtr of line
        string anItem[3];
        string itemDesc;
        int itemUnits, itemPrice;
        while ( getline(file, line) ) {
            subLine = line.substr(0,4);
            if( subLine == "Item" ){    //if the word is Item_
                int itemIndex = 0;
                istringstream iss(line);
                while( iss >> word ){
                    anItem[itemIndex] = word;
                    itemIndex++;
                }
                itemDesc = anItem[0];
                itemUnits = atoi(anItem[1].c_str());
                itemPrice = atoi(anItem[2].c_str());
                item* newItem = new item( itemDesc,itemUnits,itemPrice );
                itemList->push_back(newItem);
            }
        }
        
        file.close();
        
    }
    else cout << "Unable to open file";
    //to access items and their properties
    /*
     for(int i = 0; i < itemList->size(); i++){
     cout << "Here is an item: " << i << endl;
     cout << itemList->at(i)->description << endl;
     cout << itemList->at(i)->units << endl;
     cout << itemList->at(i)->price << endl;
     cout << endl << endl;
     }*/
    return 0;
}
