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

#include "e-commerceTradingPlatformServer.h"

std::string Server::prompt = "";
/*
std::string Server::prompt = std::string("") + 
	"\nUsage: enter the number representing the command \n" +
	" 0 : exit system \n" + 
	" 1 : sign up \n" + 
	" 2 : show commodity \n" + 
	" 3 : search commodity \n" + 
	" 4 : sign in \n" + 
	" 5 : sign out \n" + 
	" 6 : edit password \n" + 
	" 7 : get balance \n" + 
	" 8 : consume \n" + 
	" 9 : add commodity \n" + 
	"10 : edit price \n" + 
	"11 : edit amount \n" + 
	"12 : charge \n" + 
	"13 : add commodity to shopping cart \n" + 
	"14 : delete commodity in shopping cart \n" + 
	"15 : edit commodity in shopping cart \n" + 
	"16 : show commodity in shopping cart \n" + 
	"17 : generate orders \n" + 
	"18 : cancel orders \n" + 
	"19 : show orders \n" + 
	"20 : pay \n";
*/
#ifdef _WIN32
static void socket_init(void) {
	WORD wVersionRequested;
	WSADATA WSAData;
	int status;
	wVersionRequested = MAKEWORD(1,1);
	status = WSAStartup(wVersionRequested, &WSAData);
	if (status != 0) {
		printf("Windows Socket DLL ret\n");
		exit(0);
	}
}
#endif

int Server::signUp() {
	std::string type, name, password;
	Server::write("type(Merchant or Customer): ");
	Server::read(type);
	Server::write("username: ");
	Server::read(name);
	Server::write("password: ");
	Server::read(password);
	if (type == "Merchant") {
		Merchant merchant(name, password);
		if (merchant.signUp() == SUCCESS) {
			Server::write("Signed up successfully! merchant " + name + "\n" + Server::prompt);
			return SUCCESS;
		}
		else {
			Server::write("Sign up error! \n" + Server::prompt);
			return ERROR1;
		}
	}
	else if (type == "Customer"){
		Customer customer(name, password);
		if (customer.signUp() == SUCCESS) {
			Server::write("Signed up successfully! customer " + name + "\n" + Server::prompt);
			return SUCCESS;
		}
		else {
			Server::write("Sign up error! \n" + Server::prompt);
			return ERROR1;
		}
	}
	Server::write("Type error! \n" + Server::prompt);
	return ERROR1;
}

int Server::showCommodity() {
	std::string string;
	Commodity::showCommodity(string);
	Server::write("All commodities are shown below: \n" + string + Server::prompt);
	return SUCCESS;
}

int Server::searchCommodity() {
	std::string command, string;
	Server::write("regex: ");
	Server::read(command);
	Commodity::searchCommodity(command, string);
	Server::write("All commodities match regex: " + command + 
		" are shown below: \n" + string + Server::prompt);
	return SUCCESS;
}

int Server::signIn(Merchant* &merchant, Customer* &customer) {
	std::string name, password;
	Server::write("username: ");
	Server::read(name);
	Server::write("password: ");
	Server::read(password);
	if (merchant) {
		delete merchant;
		merchant = NULL;
	}
	if (customer) {
		delete customer;
		customer = NULL;
	}
	merchant = new Merchant(name, password);
	if (merchant->signIn() == SUCCESS) {
		Server::write("welcome! merchant " + name + "\n" + Server::prompt);
		return SUCCESS;
	}
	else {
		delete merchant;
		merchant = NULL;
	}
	merchant = NULL;
	customer = new Customer(name, password);
	if (customer->signIn() == SUCCESS) {
		Server::write("welcome! customer " + name + "\n" + Server::prompt);
		return SUCCESS;
	}
	else {
		delete customer;
		customer = NULL;
	}
	customer = NULL;
	Server::write("Username or password error! please try again \n" + Server::prompt);
	return ERROR1;
}

int Server::signOut(Merchant* &merchant, Customer* &customer) {
	if (merchant) {
		merchant->signOut();
		Server::write(merchant->getUserType() + " " + merchant->getName() + 
			" signed out successfully \n" + Server::prompt);
		delete merchant;
		merchant = NULL;
		return SUCCESS;
	}
	else if (customer) {
		customer->signOut();
		Server::write(customer->getUserType() + " " + customer->getName() + 
			" signed out successfully \n" + Server::prompt);
		delete customer;
		customer = NULL;
		return SUCCESS;
	}
	else {
		Server::write("Signed out error! please sign in first \n" + Server::prompt);
		return ERROR1;
	}
}

int Server::editPassword(Merchant* &merchant, Customer* &customer) {
	if (!(merchant && merchant->getUserStatus() == LOGIN) && 
		!(customer && customer->getUserStatus() == LOGIN)) {
		Server::write("Edit password error! please sign in first \n" + Server::prompt);
		return ERROR1;
	}
	std::string password;
	Server::write("new password: ");
	Server::read(password);
	if (merchant && merchant->editPassword(password) == SUCCESS) {
		Server::write(merchant->getUserType() + " " + merchant->getName() + 
			" edit password successfully \n" + Server::prompt);
		return SUCCESS;
	}
	else if (customer && customer->editPassword(password) == SUCCESS) {
		Server::write(customer->getUserType() + " " + customer->getName() + 
			" edit password successfully \n" + Server::prompt);
		return SUCCESS;
	}
	return SUCCESS;
}

int Server::getBalance(Merchant* &merchant, Customer* &customer) {
	if (!(merchant && merchant->getUserStatus() == LOGIN) && 
		!(customer && customer->getUserStatus() == LOGIN)) {
		Server::write("Get balance error! please sign in first \n" + Server::prompt);
		return ERROR1;
	}
	if (merchant && User::findUser(merchant->getName())->getBalance() != ERROR_D) {
		Server::write(merchant->getUserType() + " " + merchant->getName() + 
			" 's balance is " + std::to_string(User::findUser(merchant->getName())->getBalance()) + "\n" + Server::prompt);
		return SUCCESS;
	}
	else if (customer && User::findUser(customer->getName())->getBalance() != ERROR_D) {
		Server::write(customer->getUserType() + " " + customer->getName() + 
			" 's balance is " + std::to_string(User::findUser(customer->getName())->getBalance()) + "\n" + Server::prompt);
		return SUCCESS;
	}
	return SUCCESS;
}

int Server::consume(Merchant* &merchant, Customer* &customer) {
	if (!(merchant && merchant->getUserStatus() == LOGIN) && 
		!(customer && customer->getUserStatus() == LOGIN)) {
		Server::write("Consume balance error! please sign in first \n" + Server::prompt);
		return ERROR1;
	}
	std::string string;
	Server::write("consume balance: ");
	Server::read(string);
	double balance = stod(string);
	if (merchant && merchant->getUserStatus() == LOGIN) {
		if (merchant->consume(balance) == SUCCESS) {
			Server::write(merchant->getUserType() + " " + merchant->getName() + 
				" consume balance " + std::to_string(balance) + " successfully \n" + Server::prompt);
			return SUCCESS;
		}
		else {
			Server::write("Consume balance error! you haven't enough balance \n" + Server::prompt);
			return ERROR1;
		}
	}
	else if (customer && customer->getUserStatus() == LOGIN) {
		if (customer->consume(balance) == SUCCESS) {
			Server::write(customer->getUserType() + " " + customer->getName() + 
				" consume balance " + std::to_string(balance) + " successfully \n" + Server::prompt);
			return SUCCESS;
		}
		else {
			Server::write("Consume balance error! you haven't enough balance \n" + Server::prompt);
			return ERROR1;
		}
	}
	return SUCCESS;
}

int Server::addCommodity(Merchant* &merchant) {
	if (!(merchant && merchant->getUserStatus() == LOGIN)) {
		Server::write("Add commodity error! please sign in as merchant first \n" + Server::prompt);
		return ERROR1;
	}
	std::string type, description, string;
	Server::write("type(Book, Electronic, Clothing): ");
	Server::read(type);
	Server::write("description: ");
	Server::read(description);
	Server::write("price: ");
	Server::read(string);
	double price = stod(string);
	Server::write("amount: ");
	Server::read(string);
	int amount = stoi(string);
	Commodity* commodity = NULL;
	if (type == "Book") {
		commodity = new Book(description, price, amount, merchant->getName());
	}
	else if (type == "Electronic") {
		commodity = new Electronic(description, price, amount, merchant->getName());
	}
	else if (type == "Clothing") {
		commodity = new Clothing(description, price, amount, merchant->getName());
	}
	else {
		Server::write("type error \n + Server::prompt");
		return ERROR1;
	}
	Commodity* commodityExist = Commodity::findCommodity(description);
	if (!commodityExist) {
		merchant->addCommodity(commodity);
		Server::write(merchant->getUserType() + " " + merchant->getName() + 
			" add commodity " + type + " " + description + " " + std::to_string(price) + " " +
			std::to_string(amount) + " " + merchant->getName() + "successfully \n" + Server::prompt);
		return SUCCESS;
	}
	else {
		Server::write("add commodity error! already have commodity \n" + Server::prompt);
		delete commodity;
		return ERROR1;
	}
}

int Server::editPrice(Merchant* &merchant) {
	if (!(merchant && merchant->getUserStatus() == LOGIN)) {
		Server::write("edit price error! please sign in as merchant first \n" + Server::prompt);
		return ERROR1;
	}
	std::string description, string;
	Server::write("description: ");
	Server::read(description);
	Server::write("price: ");
	Server::read(string);
	double price = stod(string);
	Commodity* commodity = Commodity::findCommodity(description);
	if (commodity) {
		commodity->editPrice(price);
		Server::write(merchant->getUserType() + " " + merchant->getName() + 
			" edit price " + description + " " + std::to_string(price) + "successfully \n" + Server::prompt);
		return SUCCESS;
	}
	else {
		Server::write("edit price error! can't find commodity \n" + Server::prompt);
		return ERROR1;
	}
}

int Server::editAmount(Merchant* &merchant) {
	if (!(merchant && merchant->getUserStatus() == LOGIN)) {
		Server::write("edit amount error! please sign in as merchant first \n" + Server::prompt);
		return ERROR1;
	}
	std::string description, string;
	Server::write("description: ");
	Server::read(description);
	Server::write("amount: ");
	Server::read(string);
	int amount = stoi(string);
	Commodity* commodity = Commodity::findCommodity(description);
	if (commodity) {
		commodity->editAmount(amount);
		Server::write(merchant->getUserType() + " " + merchant->getName() + 
			" edit amount " + description + " " + std::to_string(amount) + "successfully \n" + Server::prompt);
		return SUCCESS;
	}
	else {
		Server::write("edit amount error! can't find commodity \n" + Server::prompt);
		return ERROR1;
	}
}

int Server::charge(Customer* &customer) {
	if (!(customer && customer->getUserStatus() == LOGIN)) {
		Server::write("Charge balance error! please sign in as customer first \n" + Server::prompt);
		return ERROR1;
	}
	std::string string;
	Server::write("charge balance: ");
	Server::read(string);
	double balance = stod(string);
	if (customer && customer->charge(balance) == SUCCESS) {
		Server::write(customer->getUserType() + " " + customer->getName() + 
			" charge balance " + std::to_string(balance) + " successfully \n" + Server::prompt);
		return SUCCESS;
	}
	return SUCCESS;
}

int Server::addCommodityToShoppingCart(Customer* &customer) {
	if (!(customer && customer->getUserStatus() == LOGIN)) {
		Server::write("add commodity error! please sign in as customer first \n" + Server::prompt);
		return ERROR1;
	}
	std::string type, description, string;
	Server::write("type(Book, Electronic, Clothing): ");
	Server::read(type);
	Server::write("description: ");
	Server::read(description);
	Server::write("amount: ");
	Server::read(string);
	int amount = stoi(string);
	Commodity* commodity = NULL;
	if (type == "Book") {
		commodity = new Book(description, amount);
	}
	else if (type == "Electronic") {
		commodity = new Electronic(description, amount);
	}
	else if (type == "Clothing") {
		commodity = new Clothing(description, amount);
	}
	else {
		Server::write("type error \n" + Server::prompt);
		return ERROR1;
	}
	if (customer->shoppingcart.addCommodity(commodity) == SUCCESS) {
		Server::write(customer->getUserType() + " " + customer->getName() + 
			" add commodity to shopping cart " + type + " " + description + " " +
			std::to_string(amount) + " successfully \n" + Server::prompt);
		return SUCCESS;
	}
	else {
		Server::write(std::string("") +
			"add commodity to shopping cart error! \n" + 
			"commodity don't exist or we haven't enough commodities \n" + Server::prompt);
		delete commodity;
		return ERROR1;
	}
}

int Server::deleteCommodityInShoppingCart(Customer* &customer) {
	if (!(customer && customer->getUserStatus() == LOGIN)) {
		Server::write("delete commodity error! please sign in as customer first \n" + Server::prompt);
		return ERROR1;
	}
	std::string type, description, string;
	Server::write("type(Book, Electronic, Clothing): ");
	Server::read(type);
	Server::write("description: ");
	Server::read(description);
	Server::write("amount: ");
	Server::read(string);
	int amount = stoi(string);
	Commodity* commodity = NULL;
	if (type == "Book") {
		commodity = new Book(description, amount);
	}
	else if (type == "Electronic") {
		commodity = new Electronic(description, amount);
	}
	else if (type == "Clothing") {
		commodity = new Clothing(description, amount);
	}
	else {
		Server::write("type error \n" + Server::prompt);
		return ERROR1;
	}
	if (customer->shoppingcart.deleteCommodity(commodity) == SUCCESS) {
		Server::write(customer->getUserType() + " " + customer->getName() + 
			" delete commodity to shopping cart " + type + " " + description + " " +
			std::to_string(amount) + " successfully \n" + Server::prompt);
		return SUCCESS;
	}
	else {
		Server::write(std::string("") + 
			"delete commodity to shopping cart error! \n" +
			"commodity don't exist in shopping cart \n" + 
			"or we haven't enough commodity in shopping cart \n" + Server::prompt);
		delete commodity;
		return ERROR1;
	}
}

int Server::editCommodityInShoppingCart(Customer* &customer) {
	if (!(customer && customer->getUserStatus() == LOGIN)) {
		Server::write("edit commodity error! please sign in as customer first \n" + Server::prompt);
		return ERROR1;
	}
	std::string type, description, string;
	Server::write("type(Book, Electronic, Clothing): ");
	Server::read(type);
	Server::write("description: ");
	Server::read(description);
	Server::write("amount: ");
	Server::read(string);
	int amount = stoi(string);
	Commodity* commodity = NULL;
	if (type == "Book") {
		commodity = new Book(description, amount);
	}
	else if (type == "Electronic") {
		commodity = new Electronic(description, amount);
	}
	else if (type == "Clothing") {
		commodity = new Clothing(description, amount);
	}
	else {
		Server::write("type error \n" + Server::prompt);
		return ERROR1;
	}
	if (customer->shoppingcart.editCommodity(commodity) == SUCCESS) {
		Server::write(customer->getUserType() + " " + customer->getName() + 
			" edit commodity to shopping cart " + type + " " + description + " " +
			std::to_string(amount) + " successfully \n" + Server::prompt);
		return SUCCESS;
	}
	else {
		Server::write(std::string("") + 
			"edit commodity to shopping cart error! \n" +
			"commodity don't exist in shopping cart \n" + 
			"or we haven't enough commodity in shopping cart \n" + Server::prompt);
		delete commodity;
		return ERROR1;
	}
}

int Server::showCommodityInShoppingCart(Customer* &customer) {
	if (!(customer && customer->getUserStatus() == LOGIN)) {
		Server::write("show commodity in shopping cart error! please sign in as customer first \n" + Server::prompt);
		return ERROR1;
	}
	std::string string;
	customer->shoppingcart.showCommodity(string);
	Server::write("commodities in shopping cart:\n" + string + Server::prompt);
	return SUCCESS;
}

int Server::generateOrders(Customer* &customer) {
	if (!(customer && customer->getUserStatus() == LOGIN)) {
		Server::write("generate orders error! please sign in as customer first \n" + Server::prompt);
		return ERROR1;
	}
	Server::write("enter the number of descriptions want to generate orders: \n");
	std::string string;
	Server::read(string);
	int num = stoi(string);
	std::vector<std::string> commodityList;
	std::string description;
	for (int k = 0; k < num; ++k) {
		Server::write("description: ");
		Server::read(description);
		commodityList.push_back(description);
	}
	if (customer->shoppingcart.generateOrders(commodityList) == SUCCESS) {
		Server::showOrders(customer);
		return SUCCESS;
	}
	else {
		Server::write(std::string("") + 
			"generate orders error! \n" +
			"you have order which has not been paid or \n" + 
			"commodity in orders can't find in shopping cart or\n" +
			"we haven't enough commodities \n" + Server::prompt);
		return ERROR1;
	}
}

int Server::cancelOrders(Customer* &customer) {
	if (!(customer && customer->getUserStatus() == LOGIN)) {
		Server::write("cancel orders error! please sign in as customer first \n" + Server::prompt);
		return ERROR1;
	}
	customer->shoppingcart.cancelOrders();
	Server::write("cancel orders successfully! \n" + Server::prompt);
	return SUCCESS;
}

int Server::showOrders(Customer* &customer) {
	if (!(customer && customer->getUserStatus() == LOGIN)) {
		Server::write("show orders in shopping cart error! please sign in as customer first \n" + Server::prompt);
		return ERROR1;
	}
	std::string string;
	customer->shoppingcart.showOrders(string);
	Server::write("commodities in orders: \n" + string + Server::prompt);
	return SUCCESS;
}

int Server::pay(Customer* &customer) {
	if (!(customer && customer->getUserStatus() == LOGIN)) {
		Server::write("pay error! please sign in as customer first \n" + Server::prompt);
		return ERROR1;
	}
	double orderedTotalPrice = 0;
	if (customer->shoppingcart.pay(customer->getName(), orderedTotalPrice) == SUCCESS) {
		Server::write("you have successfully pay " + std::to_string(orderedTotalPrice) + "\n" + Server::prompt);
		return SUCCESS;
	}
	else {
		Server::write("pay error! we haven't enough balance \n" + Server::prompt);
		return ERROR1;
	}
}

int Server::discount(Merchant* &merchant) {
	if (!(merchant && merchant->getUserStatus() == LOGIN)) {
		Server::write("discount error! please sign in as merchant first \n" + Server::prompt);
		return ERROR1;
	}

	std::string type, description, string;
	Server::write("type(Book, Electronic, Clothing): ");
	Server::read(type);
	Server::write("discount: ");
	Server::read(string);
	double discount = stod(string);
	Commodity* commodity = NULL;
	if (type == "Book") {
		Book::setDiscount(discount);
	}
	else if (type == "Electronic") {
		Electronic::setDiscount(discount);
	}
	else if (type == "Clothing") {
		Clothing::setDiscount(discount);
	}
	else {
		Server::write("type error \n + Server::prompt");
		return ERROR1;
	}
	Server::write("you have successfully discount " + type + std::to_string(discount) + "\n" + Server::prompt);
	return SUCCESS;
}

int Server::socketInit(int &listenfd) {
	socket_init();
	// socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        std::cout << "Error: socket" << std::endl;
        return ERROR1;
    }
	// bind
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        std::cout << "Error: bind" << std::endl;
        return ERROR1;
    }
	else {
		std::cout << "server bind on port 8000" << std::endl;
	}
    // listen
    if(listen(listenfd, BACKLOG) == -1) {
        std::cout << "Error: listen" << std::endl;
        return ERROR1;
    }
	return SUCCESS;
}

int Server::read(std::string &string) {
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	std::string strin;
	int len = recv(Server::conn, buf, sizeof(buf), 0);
	buf[len] = '\0';
	string = std::string(buf);
	return SUCCESS;
}

int Server::write(std::string string) {
	char buf[BUFSIZE];
	int len = string.copy(buf, BUFSIZE);
	buf[len] = '\0';
    send(Server::conn, buf, len, 0);
	return SUCCESS;
}

//void* Server::handleConnect(char clientIP[], struct sockaddr_in clientAddr) {
void* Server::handleConnect(void *threadid) {
	/*
	while (true) {
		std::string string;
		Server::read(string);
		//std::cout << "read from clien: " << string << std::endl;
		if (string == "exit") {
			std::cout << "...disconnect " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;
			break;
		}
		std::cout << string << std::endl;
		//std::cout << "write to clien: " << string << std::endl;
		Server::write(string);
	}
	*/
	Server::write(Server::prompt);
	std::string opt, string;
	Merchant* merchant = NULL;
	Customer* customer = NULL;
	while (true) {
		Server::conn = *((int*)threadid);
		Server::read(opt);
		switch (std::stoi(opt))
		{
		case  0:
			Server::cancelOrders(customer);
			Commodity::saveCommodity("commodity.txt");
			User::saveUser("user.txt");
			string = "...disconnect ";
			//string += clientIP;
			string += ":";
			//string += ntohs(clientAddr.sin_port);
			string += "\n";
			Server::write(string);
			return 0;
			break;

		case  1:
			signUp();
			break;

		case  2:
			showCommodity();
			break;

		case  3:
			searchCommodity();
			break;

		case  4:
			signIn(merchant, customer);
			break;

		case  5:
			signOut(merchant, customer);
			break;

		case  6:
			editPassword(merchant, customer);
			break;

		case  7:
			getBalance(merchant, customer);
			break;

		case  8:
			consume(merchant, customer);
			break;

		case  9:
			addCommodity(merchant);
			break;

		case 10:
			editPrice(merchant);
			break;

		case 11:
			editAmount(merchant);
			break;

		case 12:
			charge(customer);
			break;

		case 13:
			addCommodityToShoppingCart(customer);
			break;

		case 14:
			deleteCommodityInShoppingCart(customer);
			break;

		case 15:
			editCommodityInShoppingCart(customer);
			break;

		case 16:
			showCommodityInShoppingCart(customer);
			break;

		case 17:
			generateOrders(customer);
			break;

		case 18:
			cancelOrders(customer);
			break;

		case 19:
			showOrders(customer);
			break;

		case 20:
			pay(customer);
			break;

		case 21:
			discount(merchant);
			break;
		
		default:
			break;
		}
	}
	close(Server::conn);
	return 0;
}

int Server::conn;

int main(int argc, char* argv[]) {
	std::cout << "Welcome to transaction system server" << std::endl;
    int listenfd;
    if (Server::socketInit(listenfd) == ERROR1) {
        return 0;
    }
    Commodity::loadCommodity("commodity.txt");
	User::loadUser("user.txt");

	// accept
    char clientIP[INET_ADDRSTRLEN] = "";
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
	pthread_t threads[NUM_THREADS];
	int threadNum = 0;
   	int indexes[NUM_THREADS];
    while (true) {
        std::cout << "...listening" << std::endl;
        Server::conn = accept(listenfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (Server::conn < 0) {
            std::cout << "Error: accept" << std::endl;
            continue;
        }
		#ifdef _WIN32
		#else
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
		#endif
        std::cout << "...connect " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;
        indexes[threadNum] = Server::conn;
		int rc = pthread_create(&threads[threadNum], NULL, 
                          Server::handleConnect, (void *)&(indexes[threadNum]));
		if (rc){
			std::cout << "Error:无法创建线程," << rc << std::endl;
			exit(-1);
		}
		threadNum++;
    }
	pthread_exit(NULL);
    close(listenfd);
	Commodity::saveCommodity("commodity.txt");
	User::saveUser("user.txt");
	return 0;
}

// lin: g++ e-commerceTradingPlatformServer.cpp user.cpp shoppingcart.cpp commodity.cpp -o server -g -lpthread
// win: g++ e-commerceTradingPlatformServer.cpp user.cpp shoppingcart.cpp commodity.cpp -o server -g -lws2_32 -lpthread

