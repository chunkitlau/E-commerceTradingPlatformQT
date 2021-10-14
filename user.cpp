#include "user.h"

int User::getUserStatus() {
    return _loginStatus;
}

std::string User::getName() {
    return _name;
}

int User::signIn() {
    if (_userMap.find(_name) != _userMap.end() && 
        _userMap.find(_name)->second->_password == _password) {
        _loginStatus = LOGIN;
        _userMap.find(_name)->second->_loginStatus = LOGIN;
        _balance = _userMap.find(_name)->second->_balance;
        return SUCCESS;
    }
    else {
        return ERROR;
    }
}

int User::signOut() {
    _loginStatus = LOGOUT;
    return SUCCESS;
}

int User::editPassword(std::string password) {
    if (_loginStatus == LOGIN) {
        _password = password;
        _userMap[_name]->_password = password;
        return SUCCESS;
    }
    else {
        return ERROR;
    }
}

double User::getBalance() const {
    if (_loginStatus == LOGIN) {
        return _balance;
    }
    else {
        return ERROR_D;
    }
}

int User::charge(double amount) {
    if (_loginStatus == LOGIN || buying) {
        _balance += amount;
        _userMap[_name]->_balance = _balance;
        return SUCCESS;
    }
    else {
        return ERROR;
    }
}

int User::consume(double amount) {
    if (_loginStatus == LOGIN && _balance > amount + EPS) {
        _balance -= amount;
        _userMap[_name]->_balance = _balance;
        return SUCCESS;
    }
    else {
        return ERROR;
    }
}

User* User::findUser(std::string name) {
    if (_userMap.find(name) != _userMap.end()) {
        return _userMap[name];
    }
    else {
        return NULL;
    }
}

int User::loadUser(std::string filename) {
    try {
        std::ifstream userFile(filename);
        if (!userFile.is_open()) {
            return ERROR;
        }
        std::string type, name, password;
        double balance;
        while (!userFile.eof()) {
            userFile >> type >> name >> password >> balance;
            if (type == "Merchant") {
                _userMap[name] = new Merchant(name, password, balance);
            }
            else if (type == "Customer") {
                _userMap[name] = new Customer(name, password, balance);
            }
        }
        return SUCCESS;
    }
    catch (const char* msg) {
        std::cerr << msg << std::endl;
        return ERROR;
    }
}

int User::saveUser(std::string filename) {
    try {
        std::ofstream userFile(filename);
        if (!userFile.is_open()) {
            return ERROR;
        }
        for (std::map<std::string, User*>::iterator iter = _userMap.begin(); iter != _userMap.end(); ++iter) {
            userFile << iter->second->_type << " " << iter->first << " " 
                << iter->second->_password << " " << iter->second->_balance << std::endl;
        }
        return SUCCESS;
    }
    catch (const char* msg) {
        std::cerr << msg << std::endl;
        return ERROR;
    }
}

Merchant::Merchant(std::string name, std::string password) {
    _name = name;
    _password = password;
    _type = "Merchant";
    _balance = 0;
    _loginStatus = LOGOUT;
}

Merchant::Merchant(std::string name, std::string password, double balance) {
    _name = name;
    _password = password;
    _type = "Merchant";
    _balance = balance;
    _loginStatus = LOGOUT;
}

std::string Merchant::getUserType() const {
    return _type;
}

int Merchant::signUp() {
    if (_userMap.find(_name) == _userMap.end()) {
        _userMap[_name] = new Merchant(_name, _password);
        return SUCCESS;
    }
    else {
        return ERROR;
    }
}

int Merchant::addCommodity(Commodity* commodity) {
    if (_loginStatus == LOGIN) {
        Commodity::addCommodity(commodity);
        return SUCCESS;
    }
    else {
        return ERROR;
    }
}

int Merchant::editPrice(std::string description, double price) {
    if (_loginStatus == LOGIN) {
        Commodity::findCommodity(description)->editPrice(price);
        return SUCCESS;
    }
    else {
        return ERROR;
    }
}

int Merchant::editAmount(std::string description, int amount) {
    if (_loginStatus == LOGIN) {
        Commodity::findCommodity(description)->editAmount(amount);
        return SUCCESS;
    }
    else {
        return ERROR;
    }
}

Customer::Customer(std::string name, std::string password) {
    _name = name;
    _password = password;
    _type = "Customer";
    _balance = 0;
    _loginStatus = LOGOUT;
}

Customer::Customer(std::string name, std::string password, double balance) {
    _name = name;
    _password = password;
    _type = "Customer";
    _balance = balance;
    _loginStatus = LOGOUT;
}

std::string Customer::getUserType() const {
    return _type;
}

int Customer::signUp() {
    if (_userMap.find(_name) == _userMap.end()) {
        _userMap[_name] = new Customer(_name, _password);
        return SUCCESS;
    }
    else {
        return ERROR;
    }
}
int Customer::addCommodity(Commodity* commodity) {
    return ERROR;
}

int Customer::editPrice(std::string description, double price) {
    return ERROR;
}

int Customer::editAmount(std::string description, int amount) {
    return ERROR;
}

std::map<std::string, User*> User::_userMap;