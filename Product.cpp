#include "classes.hpp"
using namespace std;

Product::Product(string name, string description, float price, int quantity, int id, SellerAccount *seller)
{
    this->name = name;
    this->description = description;
    this->price = price;
    this->quantity = quantity;
    this->id = id;
    this->seller = seller;
}

int Product::new_id()
{
    int id;
    if (ids.empty())
    {
        id = id_counter;
        id_counter++;
    }
    else
    {
        id = ids.top();
        ids.pop();
    }
    return id;
}

int &Product::get_quantity()
{
    return quantity;
}

void Product::print()
{
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Description: " << description << endl;
    cout << "Price: " << price << endl;
}