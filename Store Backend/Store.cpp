#include <iostream>
#include <sstream>
#include "Store.h"
#include "Product.h"
#include "Customer.h"
using namespace std;

int Store::counter = 0; // defines and initializes

Store::Store(): numProducts(0), numCustomers(0){
    setName("");//set store name to default and all numbers to 0
}

Store::Store(const char name[]): numProducts(0), numCustomers(0){
    setName(name);//set store name to name and all numbers to 0
}

const char* Store::getName(){return name;}//get store name

void Store::setName(const char storeName[]){
    if (strlen(storeName) > 0) {//if name is not 0 long name = store name
        strcpy(this->name, storeName);
    }
    else {//if less than 0 set to default and increment counter
        counter++;
        ostringstream oss;
        oss << "Store " << counter;
        strcpy(this->name, oss.str().c_str());
    }
}

bool Store::addProduct(int productID, const char productName[]){
    if(numProducts==100)//if product array is full already
        return false;
    
    for(int i = 0 ; i < this->numProducts; i++){//if product already exists then return false
        if(products[i] -> getID() == productID)
            return false;
    }
    
    Product *product = new Product(productID,productName);//create new product and add it to array
    products[numProducts] = product;
    numProducts++;//increment number of products
    return true;
}

Product* Store::getProduct(int productID){
    for(int i = 0 ; i < numProducts; i++){//look for product id, if doesnt exist return nullptr
        if(products[i] -> getID() == productID)
            return products[i];
    }
    return nullptr;
}

bool Store::addCustomer(int customerID, const char customerName[], bool credit){
    if(numCustomers==100)//if too many customers return false
        return false;
    
    for(int i = 0 ; i < this->numCustomers; i++){//if customer already here return false
        if(customers[i]->getID() == customerID)
            return false;
    }
    
    Customer *customer = new Customer(customerID,customerName, credit);//create new customer and add them to array
    customers[numCustomers] = customer;
    numCustomers++;
    return true;
}

Customer* Store::getCustomer(int customerID){//look for customers
    for(int i = 0 ; i < this->numCustomers; i++){
        if(customers[i]->getID() == customerID)
            return customers[i];
    }
    return nullptr;
}

bool Store::takeShipment(int productID, int quantity, double cost){
    if(quantity < 0 || cost < 0)//if quantity or cost is impossible return false
        return false;
    
    for(int i = 0 ; i < this->numProducts; i++){//take in products and set inventory and total paid
        if(products[i]->getID() == productID){
            products[i]->setInventory(quantity);
            products[i]->setTotalPaid(cost);
            return true;
        }
    }
    return false;
}

bool Store::sellProduct(int customerID, int productID, int quantity){
    Customer *purchaser;
    purchaser = getCustomer(customerID);//look for customer
    
    Product *sale;
    sale = getProduct(productID);//look for product
    
    if(sale != nullptr && purchaser != nullptr){//if botht the product an dbuyer are registered
        if(quantity<0 || quantity > sale->getInventoryCount())//if reduce inventory will fail
            return false;
        
        if(~purchaser->getCredit())
            if(purchaser->getBalance()<(quantity*sale->getPrice()))//if process purchase will fail
                return false;
        
        sale->reduceInventory(quantity);//if nothing will fail start the transaction
        purchaser->processPurchase((quantity*sale->getPrice()),*sale);
        return true;
    }
    return false;
    
}

bool Store::takePayment(int customerID, double amount){
    if(getCustomer(customerID)!=nullptr){//if customer exists
        return getCustomer(customerID)->processPayment(amount);//return if process payment will even work
    }
    return false;
}
void Store::outputProducts(std::ostream& os){
    for(int i = 0; i < numProducts;i++){
        os<< *products[i] << endl;//use the overloaded operator for products
    }
}
void Store::outputCustomers(std::ostream& os){
    for(int i = 0; i < numCustomers;i++){
        os<< *customers[i] << endl;//use the overloaded operator for customers
    }
}
