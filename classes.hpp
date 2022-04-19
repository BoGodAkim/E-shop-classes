#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <bits/stdc++.h>
using std::map;
using std::string;
using std::vector;

class E_Shop;
class Product;
class CustomerAccount;
class SellerAccount;

class E_Shop
{
private:
    map<string, SellerAccount> seller_accounts;
    map<string, CustomerAccount> customer_accounts;
    map<string, Product *> name_products;
    map<int, Product *> id_products;
    void login_seller();
    void login_customer();
    void create_seller_account();
    void create_customer_account();
    void print_products();

public:
    E_Shop();
    void enter_menu();
    friend class SellerAccount;
    friend class CustomerAccount;
};

class SellerAccount
{
private:
    string password;
    string name;
    string email;
    string phone;
    map<int, Product> products;
    E_Shop *e_shop;
    void enter_menu();
    void change_password();
    void add_product();
    void remove_product();
    void update_product();
    void update_product(Product *product);
    void view_your_products();
    void view_all_products();

public:
    SellerAccount()=default;
    SellerAccount(string name, string email, string phone, string password, E_Shop *e_shop);
    bool login(string password);
};

class CustomerAccount
{
private:
    string password;
    string name;
    string email;
    string phone;
    map<Product *, int> cart;
    E_Shop *e_shop;
    void enter_menu();
    void change_password();
    void view_products();
    void view_cart();
    void add_to_cart();
    void add_to_cart(Product *product);
    void remove_from_cart();
    void remove_from_cart(Product *product);
    void buy();

public:
    CustomerAccount()=default;
    CustomerAccount(string name, string email, string phone, string password, E_Shop *e_shop);
    bool login(string password);
};

class Product
{
private:
    inline static int id_counter = 0;
    inline static std::stack<int> ids;
    int id;
    string name;
    string description;
    float price;
    int quantity;
    SellerAccount *seller;
    friend class SellerAccount;
    Product(string name, string description, float price, int quantity, int id, SellerAccount *seller);
    int new_id();

public:
    Product() = default;
    void print();
    int &get_quantity();
};

#endif // CLASSES_HPP