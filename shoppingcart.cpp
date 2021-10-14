#include "shoppingcart.h"

class User {
public:
	virtual std::string getUserType() const = 0;
    /**********************************************************
     * 用户注册：支持新用户注册平台账号
     * 要求2：注册新账户的时候，要求注册的账户名不能已经存在于文件中，即账户名唯一
     */
    virtual int signUp() = 0;
    virtual int addCommodity(Commodity* commodity) = 0;
    virtual int editPrice(std::string description, double price) = 0;
    virtual int editAmount(std::string description, int amount) = 0;
    int getUserStatus();
    std::string getName();
    /**********************************************************
     * 用户登录：已注册用户用平台账号登录平台，要求已注册用户的信息长久保留。
     */
    int signIn();
    int signOut();
    /**********************************************************
     * 修改账户密码：支持登录后对用户账号的密码修改。
     */
    int editPassword(std::string password);
    /**********************************************************
     * 余额管理：支持用户账号中余额的查询
     */
    double getBalance() const;
    /**********************************************************
     * 余额管理：支持用户账号中余额的充值
     */
    int charge(double amount);
    /**********************************************************
     * 余额管理：支持用户账号中余额的消费
     */
    int consume(double amount);
    static int buying;
    static User* findUser(std::string name);
    static int loadUser(std::string filename);
    //要求2：请把所有的用户账户信息写入文件（要求使用文件存储各类信息，以练习对文件的操作和流的输入输出）
    static int saveUser(std::string filename);
protected:
    std::string _name, _password, _type;
    double _balance = 0;
    int _loginStatus = LOGOUT;
    static std::map<std::string, User*> _userMap;
private:
};

int User::buying = 0;

Shoppingcart::~Shoppingcart() {
    cancelOrders();
    for (std::map<std::string, Commodity*>::iterator commodityIter = _commodityMap.begin(); commodityIter != _commodityMap.end(); ++commodityIter) {
        delete commodityIter->second;
    }
}

int Shoppingcart::addCommodity(Commodity* commodity) {
    Commodity* existCommodity = Commodity::findCommodity(commodity->getDescription());
    if (existCommodity) {
        std::map<std::string, Commodity*>::iterator iter = _commodityMap.find(commodity->getDescription());
        if (iter != _commodityMap.end()) {
            if (iter->second->getAmount() + commodity->getAmount() <= existCommodity->getAmount()) {
                iter->second->editPrice(existCommodity->getPrice());
                iter->second->editAmount(iter->second->getAmount() + commodity->getAmount());
                delete commodity;
                return SUCCESS;
            }
            else {
                delete commodity;
                return ERROR1;
            }
        }
        else {
            if (commodity->getAmount() <= existCommodity->getAmount()) {
                commodity->editPrice(existCommodity->getPrice());
                _commodityMap[commodity->getDescription()] = commodity;
                return SUCCESS;
            }
            else {
                delete commodity;
                return ERROR1;
            }
            
        }
    }
    else {
        delete commodity;
        return ERROR1;
    }
}

int Shoppingcart::deleteCommodity(Commodity* commodity) {
    std::map<std::string, Commodity*>::iterator iter = _commodityMap.find(commodity->getDescription());
    if (iter != _commodityMap.end()) {
        if (iter->second->getAmount() >= commodity->getAmount()) {
            Commodity* existCommodity = Commodity::findCommodity(commodity->getDescription());
            iter->second->editPrice(existCommodity->getPrice());
            iter->second->editAmount(iter->second->getAmount() - commodity->getAmount());
            delete commodity;
            return SUCCESS;
        }
        else {
            delete commodity;
            return ERROR1;
        }
    }
    else {
        delete commodity;
        return ERROR1;
    }
}

int Shoppingcart::editCommodity(Commodity* commodity) {
    std::map<std::string, Commodity*>::iterator iter = _commodityMap.find(commodity->getDescription());
    if (iter != _commodityMap.end()) {
        Commodity* existCommodity = Commodity::findCommodity(commodity->getDescription());
        if (commodity->getAmount() <= existCommodity->getAmount()) {
            iter->second->editPrice(existCommodity->getPrice());
            iter->second->editAmount(commodity->getAmount());
            delete commodity;
            return SUCCESS;
        }
        else {
            delete commodity;
            return ERROR1;
        }
    }
    else {
        delete commodity;
        return ERROR1;
    }
}

int Shoppingcart::showCommodity(std::string &string) {
    string = "";
    for (std::map<std::string, Commodity*>::iterator iter = _commodityMap.begin(); iter != _commodityMap.end(); ++iter) {
        string += iter->second->getDescription() + " " + std::to_string(iter->second->getPrice()) + " " + std::to_string(iter->second->getAmount()) + "\n";
    }
    return SUCCESS;
}

int Shoppingcart::generateOrders(std::vector<std::string> &commodityList) {
    if (!_orderedCommodityMap.empty()) {
        return ERROR1;
    }
    for (std::vector<std::string>::iterator stringIter = commodityList.begin(); stringIter != commodityList.end(); ++stringIter) {
        if (_commodityMap.find(*stringIter) == _commodityMap.end()) {
            return ERROR1;
        }
        else if (_commodityMap.find(*stringIter)->second->getAmount() >
            Commodity::findCommodity(*stringIter)->getAmount()) {
            return ERROR1;
        }
    }
    _orderedTotalPrice = 0;
    for (std::vector<std::string>::iterator stringIter = commodityList.begin(); stringIter != commodityList.end(); ++stringIter) {
        std::map<std::string, Commodity*>::iterator commodityIter = _commodityMap.find(*stringIter);
        Commodity* orderedCommodity = commodityIter->second;
        _orderedCommodityMap[*stringIter] = orderedCommodity;
        _commodityMap.erase(commodityIter);
        Commodity* commodity = Commodity::findCommodity(*stringIter);
        orderedCommodity->editPrice(commodity->getPrice());
        commodity->editAmount(commodity->getAmount() - orderedCommodity->getAmount());
        _orderedTotalPrice += orderedCommodity->getPrice() * orderedCommodity->getAmount();
    }
    return SUCCESS;
}

int Shoppingcart::showOrders(std::string &string) {
    string = "";
    for (std::map<std::string, Commodity*>::iterator iter = _orderedCommodityMap.begin(); iter != _orderedCommodityMap.end(); ++iter) {
        string += iter->second->getDescription() + " " + std::to_string(iter->second->getPrice()) + " " + std::to_string(iter->second->getAmount()) + "\n";
    }
    return SUCCESS;
}

int Shoppingcart::cancelOrders() {
    for (std::map<std::string, Commodity*>::iterator commodityIter = _orderedCommodityMap.begin(); commodityIter != _orderedCommodityMap.end(); ++commodityIter) {
        Commodity* commodity = Commodity::findCommodity(commodityIter->second->getDescription());
        commodity->editAmount(commodity->getAmount() + commodityIter->second->getAmount());
        delete commodityIter->second;
    }
    _orderedCommodityMap.clear();
    return SUCCESS;
}

int Shoppingcart::pay(std::string name, double &orderedTotalPrice) {
    User* user = User::findUser(name);
    if (_orderedTotalPrice > user->getBalance() + EPS) {
        return ERROR1;
    }
    User::buying = 1;
    user->consume(_orderedTotalPrice);
    orderedTotalPrice = _orderedTotalPrice;
    for (std::map<std::string, Commodity*>::iterator commodityIter = _orderedCommodityMap.begin(); commodityIter != _orderedCommodityMap.end(); ++commodityIter) {
        User::findUser(Commodity::findCommodity(commodityIter->second->getDescription())->getMerchant())->charge(commodityIter->second->getPrice() * commodityIter->second->getAmount());
    }
    User::buying = 0;
    return SUCCESS;
}