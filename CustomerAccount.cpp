#include "classes.hpp"
using namespace std;

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

void CustomerAccount::view_products()
{
    e_shop->print_products();
}

void CustomerAccount::view_cart()
{
    for(auto it = cart.begin(); it != cart.end(); it++)
    {
        it->first->print();
        cout << "Quantity:" << it->second << endl
             << endl;
    }
}

void CustomerAccount::add_to_cart()
{
    int choice;
    cout << endl
         << "1. Add by name" << endl;
    cout << "2. Add by id" << endl;
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
            quantity = -1;
        }
        else
        {
            cout << "Invalid quantity" << endl;
        }
    } while (quantity == -1);
}

void CustomerAccount::remove_from_cart()
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
        cout << endl
             << "1. View products" << endl;
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