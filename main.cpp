#include <bits/stdc++.h>
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
    }
}
void E_Shop::enter_menu()
{
    int choice = 1;
    while (choice != 0)
    {
        cout << "1. Login as seller" << endl;
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
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
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
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
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
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter phone: ";
    cin >> phone;
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
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter phone: ";
    cin >> phone;
    seller_accounts[username] = SellerAccount(name, email, phone, password, this);
}

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
    cin >> old_password;
    if (this->password == old_password)
    {
        cout << "Enter new password: ";
        cin >> password;
        cout << "Confirm new password: ";
        cin >> password_confirmation;
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
    int price;
    int quantity;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter description: ";
    cin >> description;
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
    cout << "1. Remove by name" << endl;
    cout << "2. Remove by id" << endl;
    cout << "0. Back" << endl;
    cin >> choice;
    string name;
    int id;
    switch (choice)
    {
    case 1:
        cout << "Enter name: ";
        cin >> name;
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
    cout << "1. Update by name" << endl;
    cout << "2. Update by id" << endl;
    cout << "0. Back" << endl;
    cin >> choice;
    string name;
    int id;
    switch (choice)
    {
    case 1:
        cout << "Enter name: ";
        cin >> name;
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
    cout << "1. Update name" << endl;
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
        cin >> name;
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
        cin >> description;
        product->description = description;
        break;
    case 3:
        int price;
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
        cout << product.second.get_quantity() << endl
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
        cout << "1. Add product" << endl;
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

CustomerAccount::CustomerAccount(string name, string email, string phone, string password, E_Shop *e_shop)
{
    this->password = password;
    this->name = name;
    this->email = email;
    this->phone = phone;
    this->e_shop = e_shop;
}

bool CustomerAccount::login(string password)
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

void CustomerAccount::change_password()
{
    string old_password;
    string password;
    string password_confirmation;
    cout << "Enter old password: ";
    cin >> old_password;
    if (this->password == old_password)
    {
        cout << "Enter new password: ";
        cin >> password;
        cout << "Confirm new password: ";
        cin >> password_confirmation;
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

void CustomerAccount::view_products()
{
    e_shop->print_products();
}

void CustomerAccount::view_cart()
{
    for (auto &product : cart)
    {
        product.first->print();
        cout << "Quantity:" << product.second << endl
             << endl;
    }
}

void CustomerAccount::add_to_cart()
{
    int choice;
    cout << "1. Add by name" << endl;
    cout << "2. Add by id" << endl;
    cout << "0. Back" << endl;
    cin >> choice;
    string name;
    int id;
    switch (choice)
    {
    case 1:
        cout << "Enter name: ";
        cin >> name;
        if (e_shop->name_products.find(name) != e_shop->name_products.end())
        {
            add_to_cart(e_shop->name_products[name]);
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
            add_to_cart(e_shop->id_products[id]);
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

void CustomerAccount::add_to_cart(Product *product)
{
    int quantity;
    do
    {
        cout << "Enter quantity: ";
        cin >> quantity;
        if (quantity <= product->get_quantity())
        {
            cart[product] += quantity;
            product->get_quantity() -= quantity;
        }
        else
        {
            cout << "Invalid quantity" << endl;
        }
    } while (quantity > product->get_quantity());
}

void CustomerAccount::remove_from_cart()
{
    int choice;
    cout << "1. Remove by name" << endl;
    cout << "2. Remove by id" << endl;
    cout << "0. Back" << endl;
    cin >> choice;
    string name;
    int id;
    switch (choice)
    {
    case 1:
        cout << "Enter name: ";
        cin >> name;
        if (e_shop->name_products.find(name) != e_shop->name_products.end())
        {
            remove_from_cart(e_shop->name_products[name]);
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
            remove_from_cart(e_shop->id_products[id]);
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

void CustomerAccount::remove_from_cart(Product *product)
{
    int quantity;
    do
    {
        cout << "Enter quantity: ";
        cin >> quantity;
        if (quantity <= cart[product])
        {
            cart[product] -= quantity;
            product->get_quantity() += quantity;
            if (cart[product] == 0)
            {
                cart.erase(product);
            }
            return;
        }
        else
        {
            cout << "Invalid quantity" << endl;
        }
    } while (quantity > cart[product]);
}

void CustomerAccount::buy()
{
    if (cart.size() == 0)
    {
        cout << "Cart is empty" << endl;
    }
    else
    {
        cart.clear();
        cout << "Thank you for your purchase" << endl;
    }
}

void CustomerAccount::enter_menu()
{
    int choice = 1;
    while (choice != 0)
    {
        cout << "1. View products" << endl;
        cout << "2. View cart" << endl;
        cout << "3. Add to cart" << endl;
        cout << "4. Remove from cart" << endl;
        cout << "5. Change password" << endl;
        cout << "6. Buy" << endl;
        cout << "0. Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            view_products();
            break;
        case 2:
            view_cart();
            break;
        case 3:
            add_to_cart();
            break;
        case 4:
            remove_from_cart();
            break;
        case 5:
            change_password();
            break;
        case 6:
            buy();
            break;
        case 0:
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    }
}

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
    cout << "Description: " << description << endl;
    cout << "Price: " << price << endl;
    cout << "Quantity: " << quantity << endl;
}

int main()
{
    E_Shop e_shop;
    e_shop.enter_menu();
    return 0;
}