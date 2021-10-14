#include "accountAndCommoditySystem.h"

void System::prompt() {
	std::cout << std::endl 
		<< "Usage: enter the number representing the command" << std::endl
		<< " 0 : exit system" << std::endl
		<< " 1 : sign up" << std::endl
		<< " 2 : sign in" << std::endl
		<< " 3 : sign out" << std::endl
		<< " 4 : edit password" << std::endl
		<< " 5 : get balance" << std::endl
		<< " 6 : charge" << std::endl
		<< " 7 : consume" << std::endl
		<< " 8 : add commodity" << std::endl
		<< " 9 : show commodity" << std::endl
		<< "10 : search commodity" << std::endl
		<< "11 : edit price" << std::endl
		<< "12 : edit amount" << std::endl
		<< "13 : discount" << std::endl;
}

int System::signUp() {
	std::string type, name, password;
	std::cout << "type(merchant or customer): ";
	std::cin >> type;
	std::cout << "username: ";
	std::cin >> name;
	std::cout << "password: ";
	std::cin >> password;
	if (type == "merchant") {
		Merchant merchant(name, password);
		if (merchant.signUp() == SUCCESS) {
			std::cout << "Signed up successfully! merchant " << name << std::endl;
			return SUCCESS;
		}
		else {
			std::cout << "Sign up error!" << std::endl;
			return ERROR;
		}
	}
	else if (type == "customer"){
		Customer customer(name, password);
		if (customer.signUp() == SUCCESS) {
			std::cout << "Signed up successfully! customer " << name << std::endl;
			return SUCCESS;
		}
		else {
			std::cout << "Sign up error!" << std::endl;
			return ERROR;
		}
	}
	std::cout << "Type error!" << std::endl;
	return ERROR;
}

int System::signIn(User* &user) {
	if (user) {
		delete user;
		user = NULL;
	}
	std::string name, password;
	std::cout << "username: ";
	std::cin >> name;
	std::cout << "password: ";
	std::cin >> password;
	user = new Merchant(name, password);
	if (user->signIn() == SUCCESS) {
		std::cout << "welcome! merchant " << name << std::endl;
		return SUCCESS;
	}
	else {
		delete user;
	}
	user = new Customer(name, password);
	if (user->signIn() == SUCCESS) {
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

int System::signOut(User* &user) {
	if (user) {
		user->signOut();
		std::cout << user->getUserType() << " " << user->getName() << 
			" signed out successfully" << std::endl;
		delete user;
		user = NULL;
		return SUCCESS;
	}
	else {
		std::cout << "Signed out error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::editPassword(User* &user) {
	std::string password;
	std::cout << "new password: ";
	std::cin >> password;
	if (user && user->editPassword(password) == SUCCESS) {
		std::cout << user->getUserType() << " " << user->getName() << 
		" edit password successfully" << std::endl;
		return SUCCESS;
	}
	else {
		std::cout << "Edit password error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::getBalance(User* &user) {
	if (user && user->getBalance() != ERROR_D) {
		std::cout << user->getUserType() << " " << user->getName() << 
			" 's balance is " << user->getBalance() << std::endl;
		return SUCCESS;
	}
	else {
		std::cout << "Get balance error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::charge(User* &user) {
	double balance;
	std::cout << "charge balance: ";
	std::cin >> balance;
	if (user && user->charge(balance) == SUCCESS) {
		std::cout << user->getUserType() << " " << user->getName() << 
			" charge balance " << balance << " successfully" << std::endl;
		return SUCCESS;
	}
	else {
		std::cout << "Charge balance error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::consume(User* &user) {
	double balance;
	std::cout << "consume balance: ";
	std::cin >> balance;
	if (user) {
		if (user->consume(balance) == SUCCESS) {
			std::cout << user->getUserType() << " " << user->getName() << 
				" consume balance " << balance << " successfully" << std::endl;
			return SUCCESS;
		}
		else {
			std::cout << "Consume balance error! you haven't enough balance" << std::endl;
			return ERROR;
		}
	}
	else {
		std::cout << "Consume balance error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::addCommodity(User* &user) {
	std::string type, description;
	double price;
	int amount;
	std::cout << "type(Book, Electronic, Clothing): ";
	std::cin >> type;
	std::cout << "description: ";
	std::cin >> description;
	std::cout << "price: ";
	std::cin >> price;
	std::cout << "amount: ";
	std::cin >> amount;
	Commodity* commodity = NULL;
	if (type == "Book") {
		commodity = new Book(description, price, amount);
	}
	else if (type == "Electronic") {
		commodity = new Electronic(description, price, amount);
	}
	else if (type == "Clothing") {
		commodity = new Clothing(description, price, amount);
	}
	else {
		std::cout << "type error" << std::endl;
		return ERROR;
	}
	if (user && user->addCommodity(commodity) == SUCCESS) {
		std::cout << user->getUserType() << " " << user->getName() << 
			" add commodity " << type << " " << description << " " << 
			price << " " << amount << " successfully" << std::endl;
		return SUCCESS;
	}
	else if (user && user->getUserType() != "Merchant"){
		std::cout << "Add commodity error! you aren't merchant" << std::endl;
		return ERROR;
	}
	else{
		std::cout << "Add commodity error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::showCommodity(User* &user) {
	std::string string;
	Commodity::showCommodity(string);
	std::cout << "All commodities are shown below: " << std::endl << string;
	return SUCCESS;
}

int System::searchCommodity(User* &user) {
	std::string command, string;
	std::cout << "regex: ";
	std::cin >> command;
	Commodity::searchCommodity(command, string);
	std::cout << "All commodities match regex: " << command << " are shown below: " << std::endl << string;
	return SUCCESS;
}

int System::editPrice(User* &user) {
	std::string type, description;
	double price;
	std::cout << "description: ";
	std::cin >> description;
	std::cout << "price: ";
	std::cin >> price;
	if (user && user->getUserStatus() == LOGIN) {
		if (user->getUserType() == "Merchant") {
			Commodity* commodity = Commodity::findCommodity(description);
			if (commodity) {
				commodity->editPrice(price);
				std::cout << user->getUserType() << " " << user->getName() << 
					" edit price " << description << " " << price << " successfully" << std::endl;
				return SUCCESS;
			}
			else {
				std::cout << "edit price error! can't find commodity" << std::endl;
				return ERROR;
			}
		}
		else {
			std::cout << "edit price error! you aren't merchant" << std::endl;
			return ERROR;
		}
	}
	else{
		std::cout << "edit price error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::editAmount(User* &user) {
	std::string type, description;
	int amount;
	std::cout << "description: ";
	std::cin >> description;
	std::cout << "amount: ";
	std::cin >> amount;
	if (user && user->getUserStatus() == LOGIN) {
		if (user->getUserType() == "Merchant") {
			Commodity* commodity = Commodity::findCommodity(description);
			if (commodity) {
				commodity->editAmount(amount);
				std::cout << user->getUserType() << " " << user->getName() << 
					" edit amount " << description << " " << amount << " successfully" << std::endl;
				return SUCCESS;
			}
			else {
				std::cout << "edit amount error! can't find commodity" << std::endl;
				return ERROR;
			}
		}
		else {	
			std::cout << "edit amount error! you aren't merchant" << std::endl;
			return ERROR;
		}
	}
	else{
		std::cout << "edit amount error! please sign in first" << std::endl;
		return ERROR;
	}
}

int System::discount(User* &user) {
	std::string type;
	double discount;
	std::cout << "type(Book, Electronic, Clothing): ";
	std::cin >> type;
	std::cout << "discount: ";
	std::cin >> discount;
	if (user && user->getUserStatus() == LOGIN) {
		if (user->getUserType() == "Merchant") {
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
				std::cout << "type error \n + Server::prompt" << std::endl;
				return ERROR;
			}
			std::cout << "you have successfully discount" << std::endl;
		}
		else {	
			std::cout << "discount error! you aren't merchant" << std::endl;
			return ERROR;
		}
	}
	else{
		std::cout << "discount error! please sign in first" << std::endl;
		return ERROR;
	}
	return SUCCESS;
}

int main(int argc, char* argv[]) {
	std::cout << "Welcome to account and comodity system" << std::endl;
	Commodity::loadCommodity("commodity.txt");
	User::loadUser("user.txt");
	System::prompt();
	int opt;
	User* user = NULL;
	while (std::cin >> opt) {
		switch (opt)
		{
		case 0:
			Commodity::saveCommodity("commodity.txt");
			User::saveUser("user.txt");
			return 0;
			break;

		case 1:
			System::signUp();
			break;

		case 2:
			System::signIn(user);
			break;

		case 3:
			System::signOut(user);
			break;

		case 4:
			System::editPassword(user);
			break;

		case 5:
			System::getBalance(user);
			break;

		case 6:
			System::charge(user);
			break;

		case 7:
			System::consume(user);
			break;

		case 8:
			System::addCommodity(user);
			break;

		case 9:
			System::showCommodity(user);
			break;

		case 10:
			System::searchCommodity(user);
			break;

		case 11:
			System::editPrice(user);
			break;

		case 12:
			System::editAmount(user);
			break;

		case 13:
			System::discount(user);
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

// g++ accountAndCommoditySystem.cpp user.cpp commodity.cpp -o main -g