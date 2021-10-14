#ifndef _ACCOUNTANDCOMMODITYSYSTEM_H_
#define _ACCOUNTANDCOMMODITYSYSTEM_H_

/**********************************************************
 * 实验(综合-电商交易平台设计)-面向对象程序设计与实践-2021春
 * 题目一：账户管理子系统和商品管理子系统（单机版）
 * 2019211301班 2019213687 刘俊杰
 * Copyright: Copyright 2021 Chunkit Lau
 * License:
 * Author: Chunkit Lau(刘俊杰)
 * Date: 2021.06.16
 * Email: chunkitlaucont@outlook.com
 * Current versison: V0.1.0
 **********************************************************
 * Version: V0.1.0
 * Date: 2021.04.03
 * Change log: Implement predetermined functions and perform simple tests
 **********************************************************
 * Description:
 *
 */

#include <iostream>
#include "commodity.h"
#include "user.h"

class System{
public:
    static void prompt();
    static int signUp();
    static int signIn(User* &user);
    static int signOut(User* &user);
    static int editPassword(User* &user);
    static int getBalance(User* &user);
    static int charge(User* &user);
    static int consume(User* &user);
    static int addCommodity(User* &user);
    static int showCommodity(User* &user);
    static int searchCommodity(User* &user);
    static int editPrice(User* &user);
    static int editAmount(User* &user);
    static int discount(User* &user);
protected:
private:
};

#endif