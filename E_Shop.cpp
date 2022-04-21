#include "classes.hpp"
using namespace std;

E_Shop::E_Shop()
{
    seller_accounts = map<string, SellerAccount>();
    customer_accounts = map<string, CustomerAccount>();
    name_products = map<string, Product *>();
    id_products = map<int, Product *>();
}

void E_Shop::print_products()
{
    for (auto it = id_products.begin(); it != id_products.end(); it++)
    {
        it->second->print();
        cout << "Quantity: " << it->second->get_quantity() << endl
             << endl;
    }
}
void E_Shop::enter_menu()
{
    int choice = 1;
    while (choice != 0)
    {
        cout << endl
             << "1. Login as seller" << endl;
        cout << "2. Login as customer" << endl;
        cout << "3. Create seller account" << endl;
        cout << "4. Create customer account" << endl;
        cout << "0. Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            login_seller();
            break;
        case 2:
            login_customer();
            break;
        case 3:
            create_seller_account();
            break;
        case 4:
            create_customer_account();
            break;
        case 0:
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    }
}

void E_Shop::login_seller()
{
    string username;
    string password;
    cout << "Enter username: ";
    cin.ignore();
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    if (seller_accounts.find(username) != seller_accounts.end())
    {
        SellerAccount seller_account = seller_accounts[username];
        if (seller_account.login(password))
        {
        }
        else
        {
            cout << "Invalid password" << endl;
        }
    }
    else
    {
        cout << "Invalid username" << endl;
    }
}

void E_Shop::login_customer()
{
    string username;
    string password;
    cout << "Enter username: ";
    cin.ignore();
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    if (customer_accounts.find(username) != customer_accounts.end())
    {
        CustomerAccount customer_account = customer_accounts[username];
        if (customer_account.login(password))
        {
        }
        else
        {
            cout << "Invalid password" << endl;
        }
    }
    else
    {
        cout << "Invalid username" << endl;
    }
}

void E_Shop::create_customer_account()
{
    string username;
    string password;
    string name;
    string email;
    string phone;
    cout << "Enter username: ";
    cin.ignore();
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter email: ";
    getline(cin, email);
    cout << "Enter phone: ";
    getline(cin, phone);
    customer_accounts[username] = CustomerAccount(name, email, phone, password, this);
}

void E_Shop::create_seller_account()
{
    string username;
    string password;
    string name;
    string email;
    string phone;
    cout << "Enter username: ";
    cin.ignore();
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter email: ";
    getline(cin, email);
    cout << "Enter phone: ";
    getline(cin, phone);
    seller_accounts[username] = SellerAccount(name, email, phone, password, this);
}