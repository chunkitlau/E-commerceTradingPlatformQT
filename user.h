#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "commodity.h"

#define LOGIN 1
#define LOGOUT 0
#define ERROR 1
#define ERROR_D -1
#define SUCCESS 0
#define EPS 1e-6

/**********************************************************
 * 用户基类
 * 为抽象类
 * 商家类和消费者类等用户子类的父类
 * 要求1: 账户有账号名、密码、账户余额、账户类型（商家/消费者） 
 * 要求3：用户基类为抽象类，不能实例化，具有纯虚函数getUserType()用于指示用户类别。
 * 用户注册&登录：支持新用户注册平台账号，已注册用户用平台账号登录平台，要求已注册用户的信息长久保留。
 * 修改账户密码：支持登录后对用户账号的密码修改。
 * 余额管理：支持用户账号中余额的查询、充值、消费等。
 * 要求7：支持一定的错误场景处理能力，例如读文件错误，输入数据不合法等等。
 */
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

/**********************************************************
 * 商家类
 * 继承自用户基类
 */
class Merchant : public User {
public:
    Merchant(std::string name, std::string password);
    Merchant(std::string name, std::string password, double balance);
    std::string getUserType() const;
    int signUp();
    int addCommodity(Commodity* commodity);
    int editPrice(std::string description, double price);
    int editAmount(std::string description, int amount);
private:
};

/**********************************************************
 * 消费者类
 * 继承自用户基类
 */
class Customer : public User {
public:
    Customer(std::string name, std::string password);
    Customer(std::string name, std::string password, double balance);
    std::string getUserType() const;
    int signUp();
    int addCommodity(Commodity* commodity);
    int editPrice(std::string description, double price);
    int editAmount(std::string description, int amount);
private:
};

#endif