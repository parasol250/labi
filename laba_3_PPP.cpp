#include <iostream>
#include <map>
#include <windows.h>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

//Интерфейсы в C++ — это способ описать поведение или возможности класса,
//не связываясь с конкретной реализацией этого класса.
//Они реализуются через абстрактные классы, содержащие чисто виртуальные функции

class tariffs { // шаблон strategy, абстракт
public:
	virtual ~tariffs() {}
	virtual double getFinalPrice(double price, double discount) const = 0;
};

class basicTariff : public tariffs {
public:

	double getFinalPrice(double price, double discount) const override {
		return price;
	}
};

class discountedTariff : public tariffs {
public:
	double getFinalPrice(double price, double discount) const override {
		return (price * ((100 - discount) / 100));
	}
};

class station {
protected:
	map<string, tariffs*> strategies;
public:
	station() {};
	~station() {};

	void addStrategy(const string& key, tariffs* tariff) {
		strategies[key] = tariff;
	}

	double getPrice(const string& key, double basePrice, double discount) {
		return strategies[key]->getFinalPrice(basePrice, discount);
	}

	void addNewTariff(string destination, double price, double discount, multimap<string, pair<double, double>>& d) {
		if (d.empty()) {
			d.insert(pair<string, pair<double, double>>(destination, make_pair(price, discount)));
			cout << "Тариф успешно добавлен!\n";
		}else {
			for (auto& s : d) {
				if (s.first == destination && s.second.first == price && s.second.second == discount) {
					throw "~~~Такой тариф уже существует~~~";
				}
				else {
					d.insert(pair<string, pair<double, double>>(destination, make_pair(price, discount)));
					cout << "Тариф успешно добавлен!\n";
					break;
				}
			}
		}
	}

	void findMinPricedDestination(multimap<string, pair<double, double>>& d) {
		vector<string> siblings;
		double minPrice = 10000000000;
		string current;
		string key;
		cout << "\nНаправление       Цена       Скидка" << endl;
		for (auto& s : d) {
			cout << setw(11) << s.first << setw(11) << s.second.first << setw(11) << s.second.second << endl;
			/*if (minPrice >= discountedTariff().getFinalPrice(s.second.first, s.second.second)) {
				minPrice = discountedTariff().getFinalPrice(s.second.first, s.second.second);
				current = s.first;
				siblings.push_back(current);
			}*/
			if (s.second.second == 0) {
				key = "basic";
			} else {
				key = "discounted";
			}
			if (minPrice >= strategies[key]->getFinalPrice(s.second.first, s.second.second)) {
				if (minPrice > strategies[key]->getFinalPrice(s.second.first, s.second.second)) {
					siblings.clear();
					minPrice = strategies[key]->getFinalPrice(s.second.first, s.second.second);
					current = s.first;
					siblings.push_back(current);
				}
				else if (minPrice == strategies[key]->getFinalPrice(s.second.first, s.second.second)) {
					//siblings.clear();
					minPrice = strategies[key]->getFinalPrice(s.second.first, s.second.second);
					current = s.first;
					siblings.push_back(current);
				}
				/*siblings.clear();
				minPrice = strategies[key]->getFinalPrice(s.second.first, s.second.second);
				current = s.first;
				siblings.push_back(current);*/
			}
		}
		if (!siblings.empty()) { // пуст ли вектор
			cout << "\nМинимальная цена: " << minPrice << endl;
			cout << "Направления с минимальной ценой: " << endl;
			int i = 1;
			for (auto k : siblings) {
				cout << i << ") " << k << endl;
				i++;
			} cout << endl;
		}
		else {
			cout << "     -              -           -   " << endl;
			//throw;
		}
	}
};

bool checkString(string s) {
	int counter = 0;
	for (int i = 0; i < s.length(); i++) { // проход по символам
		if ((s[i] >= 'А' && s[i] <= 'Я' || s[i] >= 'а' && s[i] <= 'я') ||
			(s[i] >= 'A' && s[i] <= 'Z' || s[i] >= 'a' && s[i] <= 'z')) {
			counter += 1;
		}
	}
	if (counter == s.length()) {
		return 1;
	}
	else {
		return 0;
	}
}

int main(){

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	station vokzal;      // dest - price, disc
	multimap<string, pair<double, double>> tariffPricesDiscounted; 

	basicTariff basic;
	discountedTariff discounted;

	vokzal.addStrategy("basic", &basic);
	vokzal.addStrategy("discounted", &discounted);
	cin.exceptions(istream::failbit);
	double choice;
	cout << " ------------------------------------------------\n";
	cout << "|   Список доступных действий:                   |" << endl;
	cout << "|1. Добавить новый тариф                         |" << endl;
	cout << "|2. Найти направление с минимальной стоимостью   |" << endl;
	cout << "|3. Выйти                                        |" << endl;
	cout << " ------------------------------------------------\n";
doing_func:
	try {
		cout << "Выберите действие: "; cin >> choice;
		if (choice < 1 || choice > 3 || (int(choice) != choice)) {
			throw "~~~Ошибка! Введите цифру от 1 до 3~~~";
		}
		switch (int(choice)) {
		case 1:
		{
			string destination;
			double price;
			double discount;
			cout << "Введите название направления: "; cin >> destination; //+check 
			if (checkString(destination) == 0) {
				throw "~~~Ошибка! Название направления должно содержать только буквы~~~";
			}
			cout << "Введите цену: "; cin >> price;
			if (price < 0 || price > 10000000000) {
				throw "~~~Ошибка! Цена варьируется от 0 до 10^10~~~";
			}
			cout << "Введите скидку (в %): "; cin >> discount;
			if (discount < 0 || discount > 100) {
				throw "~~~Ошибка! Процент скидки варьируется от 0 до 100~~~";
			}
			vokzal.addNewTariff(destination, price, discount, tariffPricesDiscounted);
			break;
		}
		case 2:
		{
			vokzal.findMinPricedDestination(tariffPricesDiscounted);
			break;
		}
		case 3:
		{
			cout << endl;
			break;
		}
		}
	}
	catch (const istream::failure& ex) {
		cout << "~~~Ошибка! Некорректно введено значение~~~\n";// << ex.what();
		cin.clear();
		cin.ignore(32767, '\n');
		goto doing_func;
	}
	catch (const char* error_message) {
		cout << error_message << endl;
		cin.clear();
		cin.ignore(32767, '\n');
		goto doing_func;
	}
	catch (...) {
		cout << "~~~Ошибка! Некорректно введено значение~~~\n";
		cin.clear();
		cin.ignore(32767, '\n');
		goto doing_func;
	}
	if (choice != 3 && choice >= 1 && choice < 4) {
		goto doing_func;
	}
	return 0;
}
