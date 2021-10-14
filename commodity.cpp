#include "commodity.h"

std::string Commodity::getDescription() const {
    return _description;
}

int Commodity::getAmount() const {
    return _amount;
}

int Commodity::editPrice(double price) {
    _price = price;
    _commodityMap[_description]->_price = price;
	return SUCCESS;
}

int Commodity::editAmount(int amount) {
    _amount = amount;
    _commodityMap[_description]->_amount = amount;
	return SUCCESS;
}

std::string Commodity::getMerchant() const {
    return _merchant;
}

int Commodity::addCommodity(Commodity* commodity) {
    if (_commodityMap.find(commodity->_description) == _commodityMap.end()) {
        _commodityMap[commodity->_description] = commodity;
        return SUCCESS;
    }
    else {
        delete commodity;
        return ERROR;
    }
}

Commodity* Commodity::findCommodity(std::string description) {
    if (_commodityMap.find(description) != _commodityMap.end()) {
        return _commodityMap[description];
    }
    else {
        return NULL;
    }
}

int Commodity::loadCommodity(std::string filename) {
    try {
        std::ifstream commodityFile(filename);
        if (!commodityFile.is_open()) {
            return ERROR;
        }
        std::string type, description, merchant;
        double price;
	    int amount;
        while (!commodityFile.eof()) {
            commodityFile >> type >> description >> price >> amount >> merchant;
            if (type == "Book") {
                _commodityMap[description] = new Book(description, price, amount, merchant);
            }
            else if (type == "Electronic") {
                _commodityMap[description] = new Electronic(description, price, amount, merchant);
            }
            else if (type == "Clothing") {
                _commodityMap[description] = new Clothing(description, price, amount, merchant);
            }
        }
        return SUCCESS;
    }
    catch (const char* msg) {
        std::cerr << msg << std::endl;
        return ERROR;
    }
}

int Commodity::saveCommodity(std::string filename) {
    try {
        std::ofstream commodityFile(filename);
        if (!commodityFile.is_open()) {
            return ERROR;
        }
        for (std::map<std::string, Commodity*>::iterator iter = _commodityMap.begin(); iter != _commodityMap.end(); ++iter) {
            commodityFile << iter->second->_type << " " << iter->first << " " 
                << iter->second->_price << " " << iter->second->_amount << " " << iter->second->_merchant << std::endl;
        }
        return SUCCESS;
    }
    catch (const char* msg) {
        std::cerr << msg << std::endl;
        return ERROR;
    }
}

int Commodity::showCommodity(std::string &string) {
    string = "";
    for (std::map<std::string, Commodity*>::iterator iter = _commodityMap.begin(); iter != _commodityMap.end(); ++iter) {
        string += iter->second->_type + " " + iter->first + " " 
            + std::to_string(iter->second->_price) + " " + std::to_string(iter->second->_amount) + "\n";
    }
    return SUCCESS;
}

int Commodity::searchCommodity(std::string command, std::string &string) {
    std::regex pattern(command);
    std::smatch result;
    string = "";
    for (std::map<std::string, Commodity*>::iterator iter = _commodityMap.begin(); iter != _commodityMap.end(); ++iter) {
        if(std::regex_match(iter->first, result, pattern)){
            string += iter->second->_type + " " + iter->first + " " 
                + std::to_string(iter->second->_price) + " " + std::to_string(iter->second->_amount) + "\n";
        }
    }
    return SUCCESS;
}

Book::Book(std::string description, int amount) {
    _description = description;
    _price = DBL_MAX;
    _amount = amount;
    _type = "Book";
}

Book::Book(std::string description, double price, int amount) {
    _description = description;
    _price = price;
    _amount = amount;
    _type = "Book";
}

Book::Book(std::string description, double price, int amount, std::string merchant) {
    _description = description;
    _price = price;
    _amount = amount;
    _merchant = merchant;
    _type = "Book";
}

int Book::setDiscount(double discount) {
    _discount = discount;
    return SUCCESS;
}

double Book::getPrice() const {
    return _discount * _price;
}

Electronic::Electronic(std::string description, int amount) {
    _description = description;
    _price = DBL_MAX;
    _amount = amount;
    _type = "Electronic";
}

Electronic::Electronic(std::string description, double price, int amount) {
    _description = description;
    _price = price;
    _amount = amount;
    _type = "Electronic";
}

Electronic::Electronic(std::string description, double price, int amount, std::string merchant) {
    _description = description;
    _price = price;
    _amount = amount;
    _merchant = merchant;
    _type = "Electronic";
}

int Electronic::setDiscount(double discount) {
    _discount = discount;
    return SUCCESS;
}

double Electronic::getPrice() const {
    return _discount * _price;
}

Clothing::Clothing(std::string description, int amount) {
    _description = description;
    _price = DBL_MAX;
    _amount = amount;
    _type = "Clothing";
}

Clothing::Clothing(std::string description, double price, int amount) {
    _description = description;
    _price = price;
    _amount = amount;
    _type = "Clothing";
}

Clothing::Clothing(std::string description, double price, int amount, std::string merchant) {
    _description = description;
    _price = price;
    _amount = amount;
    _merchant = merchant;
    _type = "Clothing";
}

int Clothing::setDiscount(double discount) {
    _discount = discount;
    return SUCCESS;
}

double Clothing::getPrice() const {
    return _discount * _price;
}

double Book::_discount = 1;
double Electronic::_discount = 1;
double Clothing::_discount = 1;

std::map<std::string, Commodity*> Commodity::_commodityMap;