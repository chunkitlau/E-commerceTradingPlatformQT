#include "transactionSystem.h"

void System::prompt() {
	std::cout << std::endl 
		<< "Usage: enter the number representing the command" << std::endl
		<< " 0 : exit system" << std::endl
		<< " 1 : add commodity" << std::endl
		<< " 2 : delete commodity" << std::endl
		<< " 3 : edit commodity" << std::endl
		<< " 4 : generate orders" << std::endl
		<< " 5 : cancel orders" << std::endl
		<< " 6 : pay" << std::endl
		<< " 7 : sign in" << std::endl
		<< " 8 : show commodity" << std::endl
		<< " 9 : show orders" << std::endl;
}

int System::addCommodity(Customer* &user) {
	std::string type, description;
	double price;
	int amount;
	std::cout << "type: ";
	std::cin >> type;
	std::cout << "description: ";
	std::cin >> description;
	std::cout << "amount: ";
	std::cin >> amount;
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
		std::cout << "type error" << std::endl;
		return ERROR;
	}
	if (user) {
		if (user->shoppingcart.addCommodity(commodity) == SUCCESS) {
			return SUCCESS;
		}
		else {
			return ERROR;
		}
	}
	else {
		std::cout << "add commodity error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::deleteCommodity(Customer* &user) {
	std::string type, description;
	double price;
	int amount;
	std::cout << "type: ";
	std::cin >> type;
	std::cout << "description: ";
	std::cin >> description;
	std::cout << "amount: ";
	std::cin >> amount;
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
		std::cout << "type error" << std::endl;
		return ERROR;
	}
	if (user) {
		if (user->shoppingcart.deleteCommodity(commodity) == SUCCESS) {
			return SUCCESS;
		}
		else {
			return ERROR;
		}
	}
	else {
		std::cout << "delete commodity error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::editCommodity(Customer* &user) {
	std::string type, description;
	int amount;
	std::cout << "type: ";
	std::cin >> type;
	std::cout << "description: ";
	std::cin >> description;
	std::cout << "amount: ";
	std::cin >> amount;
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
		std::cout << "type error" << std::endl;
		return ERROR;
	}
	if (user) {
		if (user->shoppingcart.editCommodity(commodity) == SUCCESS) {
			return SUCCESS;
		}
		else {
			return ERROR;
		}
	}
	else {
		std::cout << "edit commodity error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::generateOrders(Customer* &user) {
	std::cout << "enter the number of descriptions want to generate orders: ";
	int num;
	std::cin >> num;
	std::vector<std::string> commodityList;
	std::string description;
	for (int k = 0; k < num; ++k) {
		std::cout << "description: ";
		std::cin >> description;
		commodityList.push_back(description);
	}
	if (user) {
		if (user->shoppingcart.generateOrders(commodityList) == SUCCESS) {
			return SUCCESS;
		}
		else {
			return ERROR;
		}
	}
	else {
		std::cout << "generate orders error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::cancelOrders(Customer* &user) {
	if (user) {
		if (user->shoppingcart.cancelOrders() == SUCCESS) {
			return SUCCESS;
		}
		else {
			return ERROR;
		}
	}
	else {
		std::cout << "cancel orders error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::pay(Customer* &user) {
	if (user) {
		if (user->shoppingcart.pay(user->getName()) == SUCCESS) {
			return SUCCESS;
		}
		else {
			return ERROR;
		}
	}
	else {
		std::cout << "pay error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::signIn(Customer* &user) {
	if (user) {
		delete user;
		user = NULL;
	}
	std::string name, password;
	std::cout << "username: ";
	std::cin >> name;
	std::cout << "password: ";
	std::cin >> password;
	user = new Customer(name, password);
	if (user->signIn() == SUCCESS) {
		std::cout << "user " << user << std::endl;
		std::cout << "welcome! customer " << name << std::endl;
		return SUCCESS;
	}
	else {
		delete user;
	}
	user = NULL;
	std::cout << "Username or password error! please try again" << std::endl;
	return ERROR;
}

int System::showCommodity(Customer* &user) {
	if (user) {
		std::string string;
		if (user->shoppingcart.showCommodity(string) == SUCCESS) {
			std::cout << "commodity:" << std::endl << string;
			return SUCCESS;
		}
		else {
			return ERROR;
		}
	}
	else {
		std::cout << "show commodity error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::showOrders(Customer* &user) {
	if (user) {
		std::string string;
		if (user->shoppingcart.showOrders(string) == SUCCESS) {
			std::cout << "orders:" << std::endl << string;
			return SUCCESS;
		}
		else {
			return ERROR;
		}
	}
	else {
		std::cout << "generate orders error! please sign in first" << std::endl;
		return ERROR;
	}
}

int main(int argc, char* argv[]) {
	std::cout << "Welcome to transaction system" << std::endl;
    Commodity::loadCommodity("commodity.txt");
	User::loadUser("user.txt");
	System::prompt();
	int opt;
	Customer* user = NULL;
	while (std::cin >> opt) {
		switch (opt)
		{
		case 0:
			Commodity::saveCommodity("commodity.txt");
			User::saveUser("user.txt");
			return 0;
			break;

		case 1:
			System::addCommodity(user);
			break;

		case 2:
			System::deleteCommodity(user);
			break;

		case 3:
			System::editCommodity(user);
			break;

		case 4:
			System::generateOrders(user);
			break;

		case 5:
			System::cancelOrders(user);
			break;

		case 6:
			System::pay(user);
			break;

		case 7:
			System::signIn(user);
			break;

		case 8:
			System::showCommodity(user);
			break;

		case 9:
			System::showOrders(user);
			break;
		
		default:
			break;
		}
		System::prompt();
	}
	Commodity::saveCommodity("commodity.txt");
	User::saveUser("user.txt");
    
	return 0;
}

// g++ transactionSystem.cpp user.cpp shoppingcart.cpp commodity.cpp -o main -g