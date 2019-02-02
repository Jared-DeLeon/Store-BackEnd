#include <cstring>
#include <sstream>
#include "Product.h"

using namespace std;

int Product::counter = 0; // defines and initializes

Product::Product(int productID, const char productName[]) : 
        ID(productID), inventory(0), numSold(0), totalPaid(0.0) {
    setName(productName);
    setDescription("");
}

int Product::getID() const { return ID; }//get id

const char* Product::getName() const {//retun name
    return name;
}

void Product::setName(const char productName[]) {//if not empty set name, else set it to default counter name
    if (strlen(productName) > 0) {
        strcpy(this->name, productName);
    }
    else {
        counter++;
        ostringstream oss;
        oss << "Product " << counter;
        strcpy(this->name, oss.str().c_str());
    }        
}

const char* Product::getDescription() const { return description; }

void Product::setDescription(const char description[]) {//set the discription
    strcpy(this->description, description);
}

int Product::getNumberSold() const { return numSold; }

double Product::getTotalPaid() const { return totalPaid; }

int Product::getInventoryCount() const { return inventory; }

bool Product::addShipment(int shipmentQuantity, double shipmentCost) {
    if (shipmentQuantity < 0 || shipmentCost < 0) {//if shipment quantity or cost is negative fail
        return false;
    }
    else {
        inventory += shipmentQuantity;//increment the two
        totalPaid += shipmentCost;
    }
    return true;
} 

bool Product::reduceInventory(int purchaseQuantity) {
    if (purchaseQuantity < 0)//only reduce if there is something to reduce
        return false;
    if (inventory < purchaseQuantity)
        return false;
    inventory -= purchaseQuantity;
    numSold += purchaseQuantity;//keep track of how much sold
    return true;
}

double Product::getPrice() const {
    if ((inventory + numSold) == 0)
        return -1;
    return 1.25 * totalPaid / ((double)inventory + numSold);//get the price
} 

void Product::setTotalPaid(double cost){//set total paid
    totalPaid = cost;
}

void Product::setInventory(int inventory){//set inventory
    this->inventory = inventory;
}
 std::ostream& operator<<(std::ostream& os, const Product& product) {
     os << "Product Name: " << product.getName() << endl;
     os << "Product ID: " << product.getID() << endl;
     os << "Description: " << product.getDescription() << endl;
     os << "Inventory: " << product.getInventoryCount() << endl;
     os << "Number Sold: " << product.getNumberSold() << endl;
     os << "Total Paid: " << product.getTotalPaid() << endl;
     os << "Price: ";
     (product.getInventoryCount()+product.getNumberSold() != 0)?os <<product.getPrice() << endl:os << "Unavailable" << endl;//if getPrice is undefined
     return os;
 }

