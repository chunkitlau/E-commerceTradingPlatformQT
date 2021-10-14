#ifndef _SHOPPINGCART_H_
#define _SHOPPINGCART_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "commodity.h"

#define LOGIN 1
#define LOGOUT 0
#define ERROR 1
#define ERROR_D -1
#define SUCCESS 0
#define EPS 1e-6

/**********************************************************
 * 购物车类
 * 购物车管理：支持消费者向购物车添加、删除指定数量的商品，也支持消费者修改当前购物车商品的拟购买数量。
 * 订单生产：选择购物车的商品生成订单，计算并显示订单总金额。
 * 网上支付：消费者使用余额支付订单，支付成功后，消费者被扣除的余额应转至商家余额中。
 * 要求1：当订单生成后，处于未支付状态时，应将对应数量的商品冻结，不能参与新订单的产生，避免商品被超额售卖。
 * 要求2：支持一定的错误场景处理能力，如生成订单失败，支付失败等。
 */
class Shoppingcart {
public:
    ~Shoppingcart();
    /**********************************************************
	 * 支持消费者向购物车添加指定数量的商品
	 */
    int addCommodity(Commodity* commodity);
    /**********************************************************
	 * 支持消费者向购物车删除指定数量的商品
	 */
    int deleteCommodity(Commodity* commodity);
    /**********************************************************
	 * 支持消费者修改当前购物车商品的拟购买数量。
	 */
    int editCommodity(Commodity* commodity);
    int showCommodity(std::string &string);
    /**********************************************************
	 * 订单生产：选择购物车的商品生成订单，计算并显示订单总金额。
     * 要求1：当订单生成后，处于未支付状态时，应将对应数量的商品冻结，不能参与新订单的产生，避免商品被超额售卖。
	 */
    int generateOrders(std::vector<std::string> &commodityList);
    int showOrders(std::string &string);
    int cancelOrders();
    /**********************************************************
     * 网上支付：消费者使用余额支付订单，支付成功后，消费者被扣除的余额应转至商家余额中。
	 */
    int pay(std::string name);
protected:
    double _orderedTotalPrice;
    std::map<std::string, Commodity*> _commodityMap, _orderedCommodityMap;
private:
};

#endif