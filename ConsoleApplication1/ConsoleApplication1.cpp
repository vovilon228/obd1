#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
using namespace std;

class Medication {
public:
	int medication_id;
	string name;
	float price;
	int quantity;
	string dose;
	string form;
	string manufacturer;
	string group;
};
class Customer {
private:
	int customer_id;
public:
	string customer_name;
	string address;
	string telephone_number;
	float money_check = 0;
};
class Category {
public:
	int category_code;
	string group;
	vector<Medication> medication;
};
class Delivery {
public:
	string address; // not name
	int delivery_id;
	Customer customer;
	string delivery_time;
};
class Order {
private:
	int order_Id; //
public:
	Customer customer;
	vector<Medication> medication;
	Delivery delivery;
	string delivery_address;
	bool is_active; //
	string order_time;
};

vector<Order> all_orders;
vector<Customer> all_customers;
vector<Medication> all_medication;
vector<Delivery> all_deliveries;
vector<Medication> current_medication;

void Update_Deliveries();
void Print_Medications();

void Admin_Menu() {
	cout << "\t*********************" << endl;
	cout << "\tAdmin Menu" << endl;
	cout << "\t1. Check all orders" << endl;
	cout << "\t2. Check all medications" << endl;
	cout << "\t3. Create Delivery" << endl;
	cout << "\t4. Modify Delivery" << endl;
	cout << "\t5. Exit" << endl;
	cout << "\t*********************" << endl;
}

bool Check_Admin_Login(string login, string password) {
	ifstream file;
	file.open("Admin.txt");
	string temp_log, temp_pas;
	if (file.is_open()) {
		file >> temp_log;
		file >> temp_pas;
		if (temp_log == login && temp_pas == password) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		cout << "Couldn't read admin info via \"Admin.txt\"" << endl << endl;
	}
}

void Enter_As_Admin() {
	string temp_log, temp_pas;
	fstream file;
	Delivery temp;
	int inp, index;
	cout << "Enter admin login: "; cin >> temp_log;
	cout << "Enter admin password: "; cin >> temp_pas;
	if (Check_Admin_Login(temp_log, temp_pas)) {
		while (true) {
			int input;
			Admin_Menu();
			cout << "\tChoose a function: "; cin >> input;
			switch (input)
			{
			case 1:
				cout << "\t Customers: " << endl;
				for (int i = 0; i < all_customers.size(); i++) {
					if (all_orders[i].is_active == 1) {
						cout << i + 1 << "\t" << all_customers[i].customer_name << "\t"
							<< all_customers[i].telephone_number << "\t"
							<< all_customers[i].money_check << " UAH  " << endl;
					}

				}


				break;
			case 2:
				Print_Medications();
				break;
			case 3:
				cout << "Enter delivery address: "; cin >> temp.address;
				cout << "\t Customers: " << endl;
				for (int i = 0; i < all_customers.size(); i++) {
					cout << i + 1 << "\t" << all_customers[i].customer_name << "\t"
						<< all_customers[i].telephone_number << "\t"
						<< all_customers[i].money_check << " UAH" << endl;
				}
				cout << "Enter customer ID: "; cin >> inp;
				temp.customer = all_customers[--inp];
				Update_Deliveries();
				break;
			case 4:
				cout << "Enter delivery ID to modify: "; cin >> index;
				cout << "Enter new delivery address: "; cin >> temp.address;
				cout << "Enter customer ID: "; cin >> inp;
				temp.customer = all_customers[--inp];
				Update_Deliveries();
				break;
			case 5:
				return;
			default:
				cout << "Wrong input!" << endl << endl;
			}
		}
	}
	else {
		cout << "\tWrong admin login or password! Try again!" << endl << endl;
	}
}

void Read_Medication_From_File() {
	all_medication.clear();
	ifstream file;
	file.open("medications.txt");
	if (file.is_open()) {
		Medication temp;
		while (!file.eof()) {
			file >> temp.medication_id;
			file >> temp.name;
			file >> temp.price;
			file >> temp.form;
			file >> temp.dose;
			file >> temp.manufacturer;
			file >> temp.group;
			all_medication.push_back(temp);
		}
	}
	else {
		cout << "Couldn't open the file!" << endl;
	}
}

void Print_Medications_Painkillers() {
	for (int i = 0; i < all_medication.size(); i++) {
		if (all_medication[i].group == "painkiller") {
			cout << "\t" << i + 1 << "\t" << all_medication[i].name
				<< "\t" << all_medication[i].form << "\t"
				<< all_medication[i].group << "\t" << "\t"
				<< all_medication[i].dose << "\t" << all_medication[i].price << " UAH" << endl;
		}
	}
}

void Print_Medications_Spasmolytic() {
	for (int i = 0; i < all_medication.size(); i++) {
		if (all_medication[i].group == "spasmolytic") {
			cout << "\t" << i + 1 << "\t" << all_medication[i].name
				<< "\t" << all_medication[i].form << "\t"
				<< all_medication[i].group << "\t" << "\t"
				<< all_medication[i].dose << "\t" << all_medication[i].price << " UAH" << endl;
		}
	}
}

void Print_Medications_Antipyretic() {
	for (int i = 0; i < all_medication.size(); i++) {
		if (all_medication[i].group == "antipyretic") {
			cout << "\t" << i + 1 << "\t" << all_medication[i].name
				<< "\t" << all_medication[i].form << "\t"
				<< all_medication[i].group << "\t" << "\t"
				<< all_medication[i].dose << "\t" << all_medication[i].price << " UAH" << endl;
		}
	}
}

void Print_Medications() {
	fstream file;
	file.open("medications.txt");
	if (file.is_open()) {
		string temp;
		cout << "ID\tName\t\tPrice\tForm\tDose\tManufacturer" << endl;
		while (!file.eof()) {
			getline(file, temp);
			cout << temp << endl;
		}
	}
	else {
		cout << "Can't open " << "\"medications.txt\"" << endl << endl;
	}
}

float Place_Order_Customer() {
	float tempcheck = 0;
	cout << "\tCreating an order..." << endl << endl;
	int input, quantity;
	cout << "Enter the ID of the medication: "; cin >> input;
	input--;
	cout << "You chose: " << all_medication[input].name << endl;
	cout << "\tQuantity of the medication: "; cin >> quantity;
	tempcheck += all_medication[input].price * quantity;
	all_medication[input].quantity = quantity;
	current_medication.push_back(all_medication[input]);
	return tempcheck;
}

void File_All_Customers() {
	ofstream file;
	file.open("customers.txt");
	if (file.is_open()) {
		for (int i = 0; i < all_customers.size(); i++) {
			file << i + 1 << "\t" << all_customers[i].customer_name << "\t"
				<< all_customers[i].telephone_number << "\t"
				<< all_customers[i].money_check << endl;
		}
	}
	else {
		cout << "Couldn't open the file!" << endl << endl;
	}
}

void Check_All_Medications() {
	int input;
	cout << "\tChoose a category: " << endl;
	cout << "\t1. Painkillers" << endl;
	cout << "\t2. Antipyretic" << endl;
	cout << "\t3. Spasmolytic" << endl;
	cout << "\t4. All Medication" << endl;
	cout << "\t Choose a medication: ";
	cin >> input;
	if (input == 1) {
		Print_Medications_Painkillers();
	}
	else if (input == 2) {
		Print_Medications_Antipyretic();
	}
	else if (input == 3) {
		Print_Medications_Spasmolytic();
	}
	else if (input == 4) {
		Print_Medications();
	}
	else {
		cout << "Wrong input!" << endl;
	}
}

void Enter_As_Customer() {
	ofstream file;
	Order temp_order;
	Customer temp;
	cout << "Enter your name: "; cin >> temp.customer_name;
	cout << "Enter your phone: "; cin >> temp.telephone_number;
	cout << "Enter your address: "; cin >> temp.address;
	all_customers.push_back(temp);
	temp_order.customer = temp;
	temp_order.delivery_address = temp.address;
	int input;
	float currentpaycheck = 0;
	temp_order.is_active = true;
	while (true) {
		Read_Medication_From_File();
		cout << "\t____________________" << endl;
		cout << "\tCustomer Menu" << endl;
		cout << "\tCurrent check: " << currentpaycheck << "UAH" << endl;
		cout << "\t1. Place an order" << endl;
		cout << "\t2. Check your orders" << endl;
		cout << "\t3. DELETE your order" << endl;
		cout << "\t4. Modify your order" << endl;
		cout << "\t5. Check all medications" << endl;
		cout << "\t6. Exit" << endl;
		cout << "\t____________________" << endl;
		cout << "Choose a function: "; cin >> input;
		switch (input) {
		case 1:
			temp_order.is_active = true;
			currentpaycheck += Place_Order_Customer();
			all_customers.back().money_check = currentpaycheck;
			break;
		case 2:
			cout << "\tYour order: " << endl;
			for (int i = 0; i < current_medication.size(); i++) {
				cout << "\t\t" << i + 1 << "\t" << current_medication[i].name << "\t"
					<< current_medication[i].price << "\t"
					<< "x" << current_medication[i].quantity << endl;
			}
			cout << "\tTotal: " << currentpaycheck << "UAH" << endl << endl;
			break;
		case 3:
			temp_order.is_active = false;
			current_medication.clear();
			currentpaycheck = 0;
			cout << "Your cancel has been canceled!" << endl << endl;
			break;
		case 4:
			cout << "\tYour order: " << endl;
			for (int i = 0; i < current_medication.size(); i++) {
				cout << "\t\t" << i + 1 << "\t" << current_medication[i].name << "\t"
					<< current_medication[i].price << "\t"
					<< "x" << current_medication[i].quantity << endl;
			}
			cout << "\tTotal: " << currentpaycheck << "UAH" << endl << endl;
			int input;
			cout << "Enter ID of the medication you want to modify: "; cin >> input;
			input--;
			cout << "Your choice: " << endl;
			cout << current_medication[input].name << "\t" << current_medication[input].price
				<< "\tx" << current_medication[input].quantity << endl;
			cout << "\tEnter quantity: (0 if cancel " << current_medication[input].name <<
				")" << endl;
			int temp;
			cin >> temp;
			if (temp == 0) {
				currentpaycheck -= current_medication[input].quantity * current_medication[input].price;
				current_medication.erase(current_medication.begin() + input);
			}
			else {
				currentpaycheck -= current_medication[input].price * current_medication[input].quantity;
				current_medication[input].quantity = temp;
				currentpaycheck += current_medication[input].price * current_medication[input].quantity;
			}cout << endl << endl;
			cout << "\tYour order: " << endl;
			for (int i = 0; i < current_medication.size(); i++) {
				cout << "\t\t" << i + 1 << "\t" << current_medication[i].name << "\t"
					<< current_medication[i].price << "\t"
					<< "x" << current_medication[i].quantity << endl;
			}
			cout << "\tTotal: " << currentpaycheck << "UAH" << endl << endl;
			break;
		case 5:
			Check_All_Medications();
			break;
		case 6:
			File_All_Customers();
			cout << "\treturning to the main menu" << endl << endl;
			temp_order.medication = all_medication;
			file.open("orders.txt");
			file << temp_order.customer.customer_name << "\t"
				<< temp_order.delivery_address << "\t"
				<< currentpaycheck << "UAH\t" << temp_order.is_active << endl;
			all_orders.push_back(temp_order);
			return;
		default:
			cout << "\tWrong input!" << endl << endl;
		}
	}
}

void Update_Deliveries() {
	ofstream file;
	file.open("delivery.txt");
	if (file.is_open()) {
		for (int i = 0; i < all_deliveries.size(); i++)
		{
			file << all_deliveries[i].delivery_id << "\t" <<
				all_deliveries[i].customer.customer_name << "\t"
				<< all_deliveries[i].address << endl << endl;
		}
	}
	else {
		cout << "Couldn't open the file!" << endl << endl;
	}
}

int main()
{

	int input;
	while (true) {
		cout << "1. Enter as customer" << endl;
		cout << "2. Enter as admin" << endl;
		cout << "3. Exit" << endl;
		cout << "Choose a function: "; cin >> input;
		switch (input) {
		case 1:
			Enter_As_Customer();
			break;
		case 2:
			Enter_As_Admin();
			break;
		case 3: return 0;
		default:
			cout << "Error" << endl;
		}
	}
}