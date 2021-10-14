#ifndef _TRANSACTIONSYSTEM_H_
#define _TRANSACTIONSYSTEM_H_

/**********************************************************
 * 实验(综合-电商交易平台设计)-面向对象程序设计与实践-2021春
 * 题目二：交易管理子系统（单机版）
 * 2019211301班 2019213687 刘俊杰
 * Copyright: Copyright 2021 Chunkit Lau
 * License:
 * Author: Chunkit Lau(刘俊杰)
 * Date: 2021.06.16
 * Email: chunkitlaucont@outlook.com
 * Current versison: V0.1.0
 **********************************************************
 * Version: V0.1.0
 * Date: 2021.06.16
 * Change log: Implement predetermined functions and perform simple tests
 **********************************************************
 * Description:
 *
 */

#include <iostream>
#include "shoppingcart.h"
#include "commodity.h"
#include "user.h"

class System{
public:
    static void prompt();
    static int addCommodity(Customer* &user);
    static int deleteCommodity(Customer* &user);
    static int editCommodity(Customer* &user);
    static int generateOrders(Customer* &user);
    static int cancelOrders(Customer* &user);
    static int pay(Customer* &user);
    static int signIn(Customer* &user);
    static int showCommodity(Customer* &user);
    static int showOrders(Customer* &user);
protected:
private:
};

#endif