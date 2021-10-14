#ifndef _COMMODITY_H_
#define _COMMODITY_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>

#define ERROR 1
#define ERROR_D -1
#define SUCCESS 0
#define EPS 1e-6

/**********************************************************
 * 商品基类
 * 为抽象类
 * 图书类、电子商品类和服装类等商品子类的父类
 * 具有一个虚函数getPrice()用于计算具体商品的价格
 * 添加商品：支持商家添加新商品，要求已添加的商品信息长久保留。
 * 展示平台商品信息：支持针对不同类型用户、无论登录与否均展示平台商品信息。
 * 搜索平台商品信息：支持依据某种条件（比如：名称）对平台商品进行筛选，并展示筛选结果。
 * 商品信息管理：支持商家对其商品的信息进行管理，包括但不限于价格管理、剩余量管理等。
 * 要求4：电商平台上至少有三类商品：如食物、服装、图书等，
 *  每类商品中至少有三个具体的商品（如图书中可以有《C++ Primer》、《Effertive C++》等），
 *  每个具体的商品请至少包含商品描述、商品原价、商品剩余量等数据。
 *  所有的商品信息需要存储在文件或数据库中，不能写在代码中。
 * 要求6：支持对同一品类下所有产品打折的活动。
 * 要求7：支持一定的错误场景处理能力，例如读文件错误，输入数据不合法等等。
 */
class Commodity {
public:
	virtual double getPrice() const = 0;
	int editPrice(double price);
	int editAmount(int amount);
	/**********************************************************
	 * 添加商品：支持商家添加新商品，要求已添加的商品信息长久保留。
	 */
	static int addCommodity(Commodity* commodity);
	static Commodity* findCommodity(std::string description);
	static int loadCommodity(std::string filename);
    static int saveCommodity(std::string filename);
	/**********************************************************
	 * 展示平台商品信息：支持针对不同类型用户、无论登录与否均展示平台商品信息。
	 */
    static int showCommodity(std::string &string);
	/**********************************************************
	 * 搜索平台商品信息：支持依据某种条件（比如：名称）对平台商品进行筛选，并展示筛选结果。
	 */
    static int searchCommodity(std::string command, std::string &string);
protected:
	std::string _description, _type;
	double _price;
	int _amount;
	static std::map<std::string, Commodity*> _commodityMap;
private:
};

/**********************************************************
 * 图书类
 * 继承自商品基类
 */
class Book : public Commodity {
public:
	Book(std::string description, double price, int amount);
	double getPrice() const;
	/**********************************************************
	 * 要求6：支持对同一品类下所有产品打折的活动。 
	 */
	static int setDiscount(double discount);
protected:
    static double _discount;
private:
};

/**********************************************************
 * 电子商品类
 * 继承自商品基类
 */
class Electronic : public Commodity {
public:
	Electronic(std::string description, double price, int amount);
	double getPrice() const;
	/**********************************************************
	 * 要求6：支持对同一品类下所有产品打折的活动。 
	 */
	static int setDiscount(double discount);
private:
    static double _discount;
};

/**********************************************************
 * 服装类
 * 继承自商品基类
 */
class Clothing : public Commodity {
public:
	Clothing(std::string description, double price, int amount);
	double getPrice() const;
	/**********************************************************
	 * 要求6：支持对同一品类下所有产品打折的活动。 
	 */
	static int setDiscount(double discount);
private:
    static double _discount;
};

#endif