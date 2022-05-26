#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <bits/stdc++.h>
using std::map;
using std::string;

class E_Shop;
class Product;
class CustomerAccount;
class SellerAccount;

class E_Shop
{
private:
    map<string, SellerAccount*> seller_accounts;     // Map of seller accounts with their username as key
    map<string, CustomerAccount*> customer_accounts; // Map of customer accounts with their username as key
    map<string, Product *> name_products;           // Map of products with their name as key
    map<int, Product *> id_products;                // Map of products with their id as key
    void login_seller();                            // Login seller
    void login_customer();                          // Login customer
    void create_seller_account();                   // Create a seller account
    void create_customer_account();                 // Create a new customer account
    void print_products();                          // Prints all products

public:
    E_Shop();
    void enter_menu(); // Main menu
    friend class SellerAccount;
    friend class CustomerAccount;
};

class SellerAccount
{
private:
    string password;                       // Password of the seller account
    string name;                           // Name of the seller account
    string email;                          // Email of the seller account
    string phone;                          // Phone number of the seller account
    map<int, Product*> products;            // Map of products with their id as key
    E_Shop *e_shop;                        // Pointer to the e-shop
    void enter_menu();                     // Menu of the seller account
    void change_password();                // Change password of the seller account
    void add_product();                    // Add a new product
    void remove_product();                 // Remove a product
    void update_product();                 // Update a product
    void update_product(Product *product); // Update a product
    void view_your_products();             // View all products of the seller account
    void view_all_products();              // View all products

public:
    SellerAccount() = default;
    SellerAccount(string name, string email, string phone, string password, E_Shop *e_shop);
    bool login(string password); // Login seller account
};

class CustomerAccount
{
private:
    string password;                         // Password of the customer account
    string name;                             // Name of the customer account
    string email;                            // Email of the customer account
    string phone;                            // Phone number of the customer account
    map<Product *, int> cart;                // Map of quantity of products with link to product as key
    E_Shop *e_shop;                          // Pointer to the e-shop
    void enter_menu();                       // Menu of the customer account
    void change_password();                  // Change password of the customer account
    void view_products();                    // View all products
    void view_cart();                        // View cart
    void add_to_cart();                      // Add product to cart
    void add_to_cart(Product *product);      // Add product to cart
    void remove_from_cart();                 // Remove product from cart
    void remove_from_cart(Product *product); // Remove product from cart
    void buy();

public:
    CustomerAccount() = default;
    CustomerAccount(string name, string email, string phone, string password, E_Shop *e_shop);
    bool login(string password); // Login customer account
};

class Product
{
private:
    inline static int id_counter = 0;  // Counter for the id of the product
    inline static std::stack<int> ids; // Stack of free ids for the products which are deleted
    int id;                            // Id of the product
    string name;                       // Name of the product
    string description;                // Description of the product
    float price;                       // Price of the product
    int quantity;                      // Quantity of the product
    SellerAccount *seller;             // Seller of the product
    friend class SellerAccount;
    Product(string name, string description, float price, int quantity, int id, SellerAccount *seller);
    int new_id(); // Get a new id for the product
public:
    Product() = default;
    void print();        // Prints the product
    int &get_quantity(); // Get quantity of the product
};

#endif // CLASSES_HPP