#ifndef _ECOMMERCETRADINGPLATFORMSERVER_H_
#define _ECOMMERCETRADINGPLATFORMSERVER_H_

#ifdef _WIN32 /* for Windows Visual Studio */

#include <winsock2.h>
#include <io.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <ws2tcpip.h>
//#define getopt_long getopt_int
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
    static std::string prompt;
    static int signUp();
    /**********************************************************
     * 用户登录：用户通过客户端以账号密码登录平台。
     */
    static int signIn(Merchant* &merchant, Customer* &customer);
    static int signOut(Merchant* &merchant, Customer* &customer);
    static int editPassword(Merchant* &merchant, Customer* &customer);
    static int getBalance(Merchant* &merchant, Customer* &customer);
    static int charge(Customer* &customer);
    static int consume(Merchant* &merchant, Customer* &customer);
    /**********************************************************
     * 展示平台商品信息：通过客户端展示平台商品信息。
     */
    static int addCommodity(Merchant* &merchant);
    /**********************************************************
     * 搜索平台商品信息：通过客户端依据商品名称对平台商品进行搜索筛选，并展示筛选结果。
     */
    static int showCommodity();
    static int searchCommodity();
    static int editPrice(Merchant* &merchant);
    static int editAmount(Merchant* &merchant);
    /**********************************************************
     * 购物车管理：通过客户端支持消费者向购物车添加指定数量的商品。
     */
    static int addCommodityToShoppingCart(Customer* &customer);
    /**********************************************************
     * 购物车管理：通过客户端支持消费者向购物车删除指定数量的商品。
     */
    static int deleteCommodityInShoppingCart(Customer* &customer);
    static int editCommodityInShoppingCart(Customer* &customer);
    static int showCommodityInShoppingCart(Customer* &customer);
    /**********************************************************
     * 订单生产： 系统生成订单。
     */
    static int generateOrders(Customer* &customer);
    static int cancelOrders(Customer* &customer);
    /**********************************************************
     * 订单生产： 通过客户端展示用户的订单信息。
     */
    static int showOrders(Customer* &customer);
    /**********************************************************
     * 订单支付：用户通过客户端向系统提交订单支付的申请，并展示系统完成支付的状态。
     */
    static int pay(Customer* &customer);
    static int discount(Merchant* &merchant);
    static int socketInit(int &listenfd);
    static int read(std::string &string);
    static int write(std::string string);
    //static void* handleConnect(char clientIP[], struct sockaddr_in clientAddr);
    static void* handleConnect(void *threadid);
    static int conn;
protected:
private:
};

#endif