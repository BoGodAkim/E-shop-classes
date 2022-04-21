#include "classes.hpp"
using namespace std;

SellerAccount::SellerAccount(string name, string email, string phone, string password, E_Shop *e_shop)
{
    this->password = password;
    this->name = name;
    this->email = email;
    this->phone = phone;
    this->e_shop = e_shop;
}

bool SellerAccount::login(string password)
{
    if (this->password == password)
    {
        enter_menu();
        return true;
    }
    else
    {
        return false;
    }
}

void SellerAccount::change_password()
{
    string old_password;
    string password;
    string password_confirmation;
    cout << "Enter old password: ";
    cin.ignore();
    getline(cin, old_password);
    if (this->password == old_password)
    {
        cout << "Enter new password: ";
        getline(cin, password);
        cout << "Confirm new password: ";
        getline(cin, password_confirmation);
        if (password == password_confirmation)
        {
            this->password = password;
            cout << "Password changed successfully" << endl;
        }
        else
        {
            cout << "Passwords don't match" << endl;
        }
    }
    else
    {
        cout << "Invalid password" << endl;
    }
}

void SellerAccount::add_product()
{
    string name;
    string description;
    float price;
    int quantity;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    if (e_shop->name_products.find(name) != e_shop->name_products.end())
    {
        cout << "Product already exists" << endl;
        return;
    }
    cout << "Enter description: ";
    getline(cin, description);
    cout << "Enter price: ";
    cin >> price;
    cout << "Enter quantity: ";
    cin >> quantity;
    int id = Product().new_id();
    products[id] = Product(name, description, price, quantity, id, this);
    e_shop->name_products[name] = &products[id];
    e_shop->id_products[id] = &products[id];
}

void SellerAccount::remove_product()
{
    int choice;
    cout << endl
         << "1. Remove by name" << endl;
    cout << "2. Remove by id" << endl;
    cout << "0. Back" << endl;
    cin >> choice;
    string name;
    int id;
    switch (choice)
    {
    case 1:
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        if (e_shop->name_products.find(name) != e_shop->name_products.end())
        {
            Product *product = e_shop->name_products[name];
            product->ids.push(product->id);
            products.erase(product->id);
            e_shop->name_products.erase(name);
            e_shop->id_products.erase(product->id);
        }
        else
        {
            cout << "Invalid name" << endl;
        }
        break;
    case 2:
        cout << "Enter id: ";
        cin >> id;
        if (e_shop->id_products.find(id) != e_shop->id_products.end())
        {
            Product *product = e_shop->id_products[id];
            product->ids.push(product->id);
            products.erase(id);
            e_shop->name_products.erase(product->name);
            e_shop->id_products.erase(id);
        }
        else
        {
            cout << "Invalid id" << endl;
        }
        break;
    case 0:
        break;
    default:
        cout << "Invalid choice" << endl;
    }
}

void SellerAccount::update_product()
{
    int choice;
    cout << endl
         << "1. Update by name" << endl;
    cout << "2. Update by id" << endl;
    cout << "0. Back" << endl;
    cin >> choice;
    string name;
    int id;
    switch (choice)
    {
    case 1:
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        if (e_shop->name_products.find(name) != e_shop->name_products.end())
        {
            update_product(e_shop->name_products[name]);
        }
        else
        {
            cout << "Invalid name" << endl;
        }
        break;
    case 2:
        cout << "Enter id: ";
        cin >> id;
        if (e_shop->id_products.find(id) != e_shop->id_products.end())
        {
            update_product(e_shop->id_products[id]);
        }
        else
        {
            cout << "Invalid id" << endl;
        }
        break;
    case 0:
        break;
    default:
        cout << "Invalid choice" << endl;
    }
}

void SellerAccount::update_product(Product *product)
{
    cout << endl
         << "1. Update name" << endl;
    cout << "2. Update description" << endl;
    cout << "3. Update price" << endl;
    cout << "4. Update quantity" << endl;
    cout << "0. Back" << endl;
    int choice;
    cin >> choice;
    string name;
    string description;
    switch (choice)
    {
    case 1:
        cout << "Enter new name: ";
        cin.ignore();
        getline(cin, name);
        if (e_shop->name_products.find(name) == e_shop->name_products.end())
        {
            product->name = name;
            e_shop->name_products[name] = product;
            e_shop->name_products.erase(product->name);
        }
        else
        {
            cout << "Invalid name" << endl;
        }
        break;
    case 2:
        cout << "Enter new description: ";
        cin.ignore();
        getline(cin, description);
        product->description = description;
        break;
    case 3:
        float price;
        cout << "Enter new price: ";
        cin >> price;
        product->price = price;
        break;
    case 4:
        int quantity;
        cout << "Enter new quantity: ";
        cin >> quantity;
        product->quantity = quantity;
        break;
    case 0:
        break;
    default:
        cout << "Invalid choice" << endl;
    }
}

void SellerAccount::view_your_products()
{
    for (auto &product : products)
    {
        product.second.print();
        cout << "Quantity:" << product.second.get_quantity() << endl
             << endl;
    }
}

void SellerAccount::view_all_products()
{
    e_shop->print_products();
}

void SellerAccount::enter_menu()
{
    int choice = 1;
    while (choice != 0)
    {
        cout << endl
             << "1. Add product" << endl;
        cout << "2. Remove product" << endl;
        cout << "3. Update product" << endl;
        cout << "4. View your products" << endl;
        cout << "5. View all products" << endl;
        cout << "6. Change password" << endl;
        cout << "0. Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            add_product();
            break;
        case 2:
            remove_product();
            break;
        case 3:
            update_product();
            break;
        case 4:
            view_your_products();
            break;
        case 5:
            view_all_products();
            break;
        case 6:
            change_password();
            break;
        case 0:
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    }
}