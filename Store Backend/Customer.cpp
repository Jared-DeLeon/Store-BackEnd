#include <iostream>
#include <sstream>
#include "Customer.h"
#include "Product.h"
using namespace std;

int Customer::counter = 0; // defines and initializes

Customer::Customer(int customerID, const char name[], bool credit) ://instantiate customer
    ID(customerID),
    credit(credit),
    balance(0),
    numPurchased(0)
{
    setName(name);
}

int Customer::getID() const{ return ID;}

const char* Customer::getName() const{return name;}

void Customer::setName(char const customerName[]){//if not empty set name, else set to default counter name
    if (strlen(customerName) > 0) {
        strcpy(this->name, customerName);
    }
    else {
        counter++;
        ostringstream oss;
        oss << "Customer " << counter;
        strcpy(this->name, oss.str().c_str());
    }
}

bool Customer::getCredit() const {return credit;}

void Customer::setCredit(bool hasCredit){
    this->credit = hasCredit;
}

double Customer::getBalance() const {return balance;}

bool Customer::processPayment(double amount){//if ammount is not negatice then add the ammount to balance
    if(amount < 0)
        return false;
    else
        balance += amount;
    return true;
}

bool Customer::processPurchase(double amount, Product product){
    bool success = false;// sale fails unless otherwise stated
    if(this->credit){//if has credit
        this->balance -= amount;//procede with purchase
        success = true;
    }else{//if no credit
        if(this->balance >= amount){//if they have funds
            this->balance -= amount;//procede
            success = true;
        }
    }
    
    if(success){//if transaction succeded
        if(numPurchased != 5)
            numPurchased++; //increnment numPurchased if its not 5 yet
            for(int i = 4; i > 0; i--){
                strcpy(this->productsPurchased[i],this->productsPurchased[i-1]);//moving all values up in the list
            }//removes oldest value
            strcpy(this->productsPurchased[0],product.getName());//sets newest value at 0
    }
        
    return success;
}

void Customer::outputRecentPurchases(std::ostream& os) const{
        os << "Products Purchased --" << endl;
    for(int i = 0; i < this->numPurchased; i++){
        os << productsPurchased[i] << endl;//output char array of the names of the products bought by the customer
    }
    
}

std::ostream& operator<<(std::ostream& os, const Customer& customer) {//overload the << operator for customers
    char cred[6];
    (customer.getCredit())? strcpy(cred,"true") : strcpy(cred,"false");
    os << "Customer Name: " << customer.getName() << endl;
    os << "Customer ID: " << customer.getID() << endl;
    os << "Has Credit: " << cred << endl;
    os << "Balance: " << customer.getBalance() << endl;
    customer.outputRecentPurchases(os);
    return os;
    }
