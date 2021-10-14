#include "commodity.h"

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
        std::string type, description;
        double price;
	    int amount;
        while (!commodityFile.eof()) {
            commodityFile >> type >> description >> price >> amount;
            if (type == "Book") {
                _commodityMap[description] = new Book(description, price, amount);
            }
            else if (type == "Electronic") {
                _commodityMap[description] = new Electronic(description, price, amount);
            }
            else if (type == "Clothing") {
                _commodityMap[description] = new Clothing(description, price, amount);
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
                << iter->second->getPrice() << " " << iter->second->_amount << std::endl;
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
            + std::to_string(iter->second->getPrice()) + " " + std::to_string(iter->second->_amount) + "\n";
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
                + std::to_string(iter->second->getPrice()) + " " + std::to_string(iter->second->_amount) + "\n";
        }
    }
    return SUCCESS;
}

Book::Book(std::string description, double price, int amount) {
    _description = description;
    _price = price;
    _amount = amount;
    _type = "Book";
}

int Book::setDiscount(double discount) {
    _discount = discount;
    return SUCCESS;
}

double Book::getPrice() const {
    return _discount * _price;
}

Electronic::Electronic(std::string description, double price, int amount) {
    _description = description;
    _price = price;
    _amount = amount;
    _type = "Electronic";
}

int Electronic::setDiscount(double discount) {
    _discount = discount;
    return SUCCESS;
}

double Electronic::getPrice() const {
    return _discount * _price;
}

Clothing::Clothing(std::string description, double price, int amount) {
    _description = description;
    _price = price;
    _amount = amount;
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