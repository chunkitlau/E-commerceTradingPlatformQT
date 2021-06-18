#ifndef _ECOMMERCETRADINGPLATFORMSERVER_H_
#define _ECOMMERCETRADINGPLATFORMSERVER_H_

/**********************************************************
 * 实验(综合-电商交易平台设计)-面向对象程序设计与实践-2021春
 * 题目三：电商交易平台（网络版）
 * 2019211301班 2019213687 刘俊杰
 * Copyright: Copyright 2021 Chunkit Lau
 * License:
 * Author: Chunkit Lau(刘俊杰)
 * Date: 2021.06.17
 * Email: chunkitlaucont@outlook.com
 * Current versison: V0.1.0
 **********************************************************
 * Version: V0.1.0
 * Date: 2021.06.17
 * Change log: Implement predetermined functions and perform simple tests
 **********************************************************
 * Description:
 *
 */

#ifdef _WIN32 /* for Windows Visual Studio */

#include <winsock2.h>
#include <io.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <ws2tcpip.h>
#define stricmp _stricmp
static void socket_init(void);
#pragma comment(lib,"wsock32.lib")

#else /* for Linux */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define stricmp strcasecmp
#define socket_init()
#define WSAGetLastError() 0

#endif

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include "shoppingcart.h"
#include "commodity.h"
#include "user.h"

#define BACKLOG 20
#define NUM_THREADS 5
#define BUFSIZE 10240

class Server {
public:
    std::string prompt = "";
    int signUp();
    /**********************************************************
     * 用户登录：用户通过客户端以账号密码登录平台。
     */
    int signIn(Merchant* &merchant, Customer* &customer);
    int signOut(Merchant* &merchant, Customer* &customer);
    int editPassword(Merchant* &merchant, Customer* &customer);
    int getBalance(Merchant* &merchant, Customer* &customer);
    int charge(Customer* &customer);
    int consume(Merchant* &merchant, Customer* &customer);
    /**********************************************************
     * 展示平台商品信息：通过客户端展示平台商品信息。
     */
    int addCommodity(Merchant* &merchant);
    /**********************************************************
     * 搜索平台商品信息：通过客户端依据商品名称对平台商品进行搜索筛选，并展示筛选结果。
     */
    int showCommodity();
    int searchCommodity();
    int editPrice(Merchant* &merchant);
    int editAmount(Merchant* &merchant);
    /**********************************************************
     * 购物车管理：通过客户端支持消费者向购物车添加指定数量的商品。
     */
    int addCommodityToShoppingCart(Customer* &customer);
    /**********************************************************
     * 购物车管理：通过客户端支持消费者向购物车删除指定数量的商品。
     */
    int deleteCommodityInShoppingCart(Customer* &customer);
    int editCommodityInShoppingCart(Customer* &customer);
    int showCommodityInShoppingCart(Customer* &customer);
    /**********************************************************
     * 订单生产： 系统生成订单。
     */
    int generateOrders(Customer* &customer);
    int cancelOrders(Customer* &customer);
    /**********************************************************
     * 订单生产： 通过客户端展示用户的订单信息。
     */
    int showOrders(Customer* &customer);
    /**********************************************************
     * 订单支付：用户通过客户端向系统提交订单支付的申请，并展示系统完成支付的状态。
     */
    int pay(Customer* &customer);
    int discount(Merchant* &merchant);
    static int socketInit(int &listenfd);
    int read(std::string &string);
    int write(std::string string);
    //static void* handleConnect(char clientIP[], struct sockaddr_in clientAddr);
    static void* handleConnect(void *threadid);
    int conn;
protected:
private:
};

#endif