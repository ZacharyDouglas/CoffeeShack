/*
CoffeeShack - Lab 11
Zach Douglas
4/19/16
*/

#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include <vector>
#include <set>
#include <queue>
#include <random>

using std::cout; using std::endl; 
using std::string; using std::cin; 
using std::list; using std::pair; 
using std::make_pair; using std::queue; 
using std::set;

class Subject;	//forward class iteration

//Abstract class that registers to the subject
class Observer {
public:
	Observer(Subject *s);
	virtual void notify() const = 0;
};

class Subject {
public:
	void registerObserver(Observer *order) {customerOrders.insert(order);};
	void deregisterObserver(Observer *order) {customerOrders.erase(order);};
	void notifyObservers() const {
		for(auto e : customerOrders){
			e->notify();
		}
	};
private:
	set<Observer *> customerOrders;
};

Observer::Observer(Subject *s) {
	s->registerObserver(this);
}

//Concrete classes describing the content
//Of the order and barista

class Barista;		//forward class instantiation

class Customer : public Observer {
public:
	Customer(const string &, Barista*);
	void notify() const;
private:
	string name_;
	Barista *s_;
};

class Barista : public Subject {
public:
	Barista(const string &name) : name_(name){};
	void makeOrder(const string &name) { name_ = name; notifyObservers(); }
	const string& getName() const { return name_; }
private:
	string name_;
};

Customer::Customer(const string &name, Barista *s) :
	name_(name), s_(s), Observer(dynamic_cast<Subject*>(s)) {};

void Customer::notify() const {
	cout << "Customer " << s_->getName() << ":  That's my drink!" << endl;
}


//Base component item
class Item {
public:
	//Constructors with initializer lists to set the item and price
	Item() : price_(0.00) {};
	Item(const double &price) : price_(price) {};
	//Virtual function needed to get price of item 
	//When inherited class points to base item.
	virtual double getPrice() const { 
		return price_; 
	}
private:
	double price_;
};

//Decorator for Small Coffee
class SmallCoffee : public Item {
public:
	//Constructor with initializer list 
	//to set the reference to base Item class
	SmallCoffee(const Item &size) : coffeeSize_(size) {};
	//Get price of of item from base class
	double getPrice() const {
		return coffeeSize_.getPrice();
	}
private:
	const Item &coffeeSize_;
};

//Decorator for Medium Coffee
class MediumCoffee : public Item {
public:
	//Constructor with initializer list
	//to set the reference to base Item class
	MediumCoffee(const Item &size) : coffeeSize_(size) {};
	//Get price of item from base class
	double getPrice() const {
		return coffeeSize_.getPrice();
	}
private:
	const Item &coffeeSize_;
};

//Decorator for Large Coffee
class LargeCoffee : public Item {
public:
	//Constructor with initialzier list
	//to set the reference to base Item class
	LargeCoffee(const Item &size) : coffeeSize_(size) {};
	//Get price of item from base class
	double getPrice() const {
		return coffeeSize_.getPrice();
	}
private:
	const Item &coffeeSize_;
};

class Sprinkles : public Item {
public:
	//Constructor with initializer list
	//to set the reference to base Item class
	Sprinkles(const Item &ingredient) : ingredient_(ingredient) {};
	//Get price of item from base class
	double getPrice() const {
		return ingredient_.getPrice();
	}
private:
	const Item &ingredient_;
};

class Caramel : public Item {
public:
	//Constructor with initializer list
	//to set the reference to base Item class
	Caramel(const Item &ingredient) : ingredient_(ingredient) {};
	//Get price of item from base class
	double getPrice() const {
		return ingredient_.getPrice();
	}
private:
	const Item &ingredient_;
};

class MilkFoam : public Item {
public:
	//Constructor with initializer list
	//to set the reference to base Item class
	MilkFoam(const Item &ingredient) : ingredient_(ingredient) {};
	//Get price of item from base class
	double getPrice() const {
		return ingredient_.getPrice();
	}
private:
	const Item &ingredient_;
};

class Ice : public Item {
public:
	//Constructor with intializer list
	//to set the reference to base Item class
	Ice(const Item &ingredient) : ingredient_(ingredient) {};
	//Get price of item from base class
	double getPrice() const {
		return ingredient_.getPrice();
	}
private:
	const Item &ingredient_;
};

auto getCoffeePrice(char coffeeSize) {
	switch (coffeeSize) {
	case 's':{
		Item SmallCoffeeItem(1.00);
		SmallCoffee SmallCoffee(SmallCoffeeItem);
		const auto &coffeePrice = SmallCoffee.getPrice();
		return pair<string, double>("Small Coffee", coffeePrice);	
	}
	case 'm': {
		Item MediumCoffeeItem(2.00);
		MediumCoffee MediumCoffee(MediumCoffeeItem);
		const auto &coffeePrice = MediumCoffee.getPrice();
		return pair<string, double>("Medium Coffee", coffeePrice);
	}
	case 'l': {
		Item LargeCoffeeItem(3.00);
		LargeCoffee LargeCoffee(LargeCoffeeItem);
		const auto &coffeePrice = LargeCoffee.getPrice();
		return pair<string, double>("Large Coffee", coffeePrice);
	}
	default:
		return pair<string, double>("Invalid Entry", 0.00);
	}
}

auto getIngredientPrice(char userIngredientInput) {
	switch (userIngredientInput) {
	case 's': {
		Item SprinklesItem(0.50);
		Sprinkles Sprinkes(SprinklesItem);
		const auto &ingredientPrice = Sprinkes.getPrice();
		return pair<string, double>("Sprinkes", ingredientPrice);
	}
	case 'c': {
		Item CaramelItem(0.20);
		Caramel Caramel(CaramelItem);
		const auto &ingredientPrice = Caramel.getPrice();
		return pair<string, double>("Caramel", ingredientPrice);
	}
	case 'f': {
		Item MilkFoamItem(0.40);
		MilkFoam MilkFoam(MilkFoamItem);
		const auto &ingredientPrice = MilkFoam.getPrice();
		return pair<string, double>("Milk Foam", ingredientPrice);
	}
	case 'i': {
		Item IceItem(0.10);
		Ice Ice(IceItem);
		const auto &ingredientPrice = Ice.getPrice();
		return pair<string, double>("Ice", ingredientPrice);
	}
	default:
		return pair<string, double>("Invalid Entry", 0.00);
	}
}


//Using this to handle the user input
//We will return a list of ingredient/coffee size names and their corresponding prices
auto handleUserInput() {
	char coffeeSize;
	string customerName;
	char userIngredientInput;
	bool wantMoreIngredients = true;

	//Holds customer name, and the corresponding price in a list of pairs
	list<pair<string, double >> userSelectionList;
	list<pair<string, double>>::iterator userSelectionListItr = userSelectionList.begin();

	cout << "Welcome to Coffee Shack, can I get you a [l]arge, [m]edium, or [s]mall coffee? ";
	cin >> coffeeSize;
	const auto &coffeePair = getCoffeePrice(coffeeSize);
	if (coffeePair.first != "Invalid Entry") {
		userSelectionList.insert(userSelectionList.begin(), coffeePair);
	}
	else {
		cout << "Invalid Coffee Size Input!  This will not be factored in your total price!" << endl;
	}
	while (wantMoreIngredients == true) {
		cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce, or [n]one? ";
		cin >> userIngredientInput;
		cout << endl;
		if (userIngredientInput != 'n') {
			auto ingredientPair = getIngredientPrice(userIngredientInput);
			if (ingredientPair.first != "Invalid Entry") {
				userSelectionList.insert(userSelectionList.end() , ingredientPair);
			}
			else {
				cout << "Invalid Ingredient Entry!  This will not be factored in your total price!" << endl;
			}
		}else {
			wantMoreIngredients = false;
		}
	}
	cout << "Can I have your name? ";
	cin >> customerName;
	auto customerInfoPair = pair<string, double>(customerName, 0.00);
	userSelectionList.insert(userSelectionList.begin() , customerInfoPair);
	return userSelectionList;
	
}

//This will handle the total price of all items in the customers order
//We will return a double of the total price
auto getTotalPrice(list<pair<string, double>> userSelectionInfoList) {
	list<pair<string, double>>::iterator userSelectionInfoListItr;
	userSelectionInfoListItr = userSelectionInfoList.begin();
	double totalPrice = 0.00;
	while (userSelectionInfoListItr != userSelectionInfoList.end()) {
		totalPrice += userSelectionInfoListItr->second;
		++userSelectionInfoListItr;
	}
	return totalPrice;
}

//Using this to handle printing the customer's receipt
//We will output the receipt and calculate the prices of all the items within this function
auto printCustomerReceipt(list<pair<string, double>> userSelectionInfoList) {
	cout << endl;
	list<pair<string, double>>::iterator userSelectionInfoListItr;
	userSelectionInfoListItr = userSelectionInfoList.begin();
	//Customer's name is stored in first pair
	cout << userSelectionInfoListItr->first;
	++userSelectionInfoListItr;
	//Customer's coffee size is in the 2nd pair
	cout << ", your " << userSelectionInfoListItr->first << " with ";
	++userSelectionInfoListItr;
	//Starting at the 3rd pair in the list, print out all the ingredients
	auto listSize = userSelectionInfoList.size();
	auto listLoopCounter = 3;
	while(userSelectionInfoListItr != userSelectionInfoList.end()) {
		//Trying to correct statements that have multiple ingredients.  
		//This if/else will add an and rather than another comma
		if (listLoopCounter != listSize) {
			cout << userSelectionInfoListItr->first << ", ";
			++userSelectionInfoListItr;
			++listLoopCounter;
		}
		else {
			cout << "and " << userSelectionInfoListItr->first;	//and rather than comma
			++userSelectionInfoListItr;
		}
	}
	auto totalPrice = getTotalPrice(userSelectionInfoList);
	cout << std::setprecision(2) << std::fixed << " is ready.  It will be $" << totalPrice << ", please.";
	cout << endl;

}

//Needed to get Customer Name in multiple instances
auto getCustomerName() {
	string tempCustomerName;
	cout << "Can I get a name for your order? ";
	cin >> tempCustomerName;
	cout << "Thanks, I'll make that ASAP!" << endl;
	return tempCustomerName;
}

int main() {
	//Handling first order
	const auto &userOrder = handleUserInput();
	printCustomerReceipt(userOrder);

	Barista CoffeeBarista("Barista");	//Declaring Barista to notify customers of when their order is complete
	queue<pair<string, Customer>> customerNames;	//Queue to track customer names to make sure to process all orders properly
	
	//Since we know the Queue is empty, 
	//we must check to see if there are any
	//orders before we conditionally process the queue
	char moreCustomers;
	cout << "Does anyone else need anything? ";
	cin >> moreCustomers;
	
	//Get random int between 1 and 2 to decide
	//if we should make an order or take another customers order
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(1, 2);
	
	//Continuous loop to allow for exit that is controlled
	//by multiple factors (i.e. don't exit until customers are done ordering AND the queue is empty
	while (true) {
		//Checks if there are any more orders
		if (moreCustomers == 'y') {
			auto randNum = uni(rng);
			//if randNum = 1 (50% chance), we will get customer name and place the order
			if (randNum == 1) {
				auto currentCustomerName = getCustomerName();
				Customer CurrentCustomer(currentCustomerName, &CoffeeBarista);
				customerNames.push(make_pair(currentCustomerName, CurrentCustomer));
				cout << "Does anyone else need anything? ";
				cin >> moreCustomers;
			//randNum = 2 (50% chance) to process order
			}else {
				//Make sure the Queue isn't empty
				//If it isn't, get customers name and place his order
				if (customerNames.empty() != true) {
					auto nextOrderToMake = customerNames.front();
					cout << "Making Order for: " << nextOrderToMake.first << endl;
					CoffeeBarista.makeOrder(nextOrderToMake.first);
					CoffeeBarista.deregisterObserver(&nextOrderToMake.second);
					customerNames.pop();
				}
			}

		}
		//if there are no more orders, process the queue until it is empty
		else {
			while (customerNames.empty() != true) {
				auto nextOrderToMake = customerNames.front();
				cout << "Making Order for: " << nextOrderToMake.first << endl;
				CoffeeBarista.makeOrder(nextOrderToMake.first);
				CoffeeBarista.deregisterObserver(&nextOrderToMake.second);
				customerNames.pop();
			}
			cout << "All your orders are complete! Since there are no more customers, we're closing!" << endl;
			return 0;
		}
	}
}