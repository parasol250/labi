/*1.	Для заданной предметной области спроектировать программную структуру, состоящую из 3–5 классов.
2.	В соответствии с разработанной диаграммой классов выполнить программную реализацию. 
3.	Предусмотреть использование типа данных – перечисление (enum). 
4.	Ввод/вывод и проверки на ввод должен быть реализован вне проектируемого класса. Проверка полей на правильность ввода обязательна.
5.	Реализовать деструктор.
6.	Реализовать меню.
Индивидуальное задание
Вариант 2. Предметная область: Вокзал. 
Касса вокзала имеет список тарифов на различные направления. При покупке билета регистрируются паспортные данные пассажира. Пассажир покупает билеты на различные направления. 
Система должна:  
-	позволять вводить данные о тарифах;  
-	позволять вводить паспортные данные пассажира и регистрировать покупку билета;  
-	рассчитывать стоимость купленных пассажиром билетов;  
-	после ввода наименования направления выводить список всех пассажиров, купивших на него билет.
*/
#include <iostream>
#include <windows.h>
#include <string>
#include <map>

using namespace std;

class station { // единственная станция с шаблоном Singleton
private:
	string StationName;
	static station* instance;
public:
	station(string StationName) : StationName(StationName) {}
	~station() {
		if (instance) {
			delete instance;
			instance = nullptr;
		}
	}

	static station* getInstance() {
		if (!instance) {
			instance = new station("                >>>Станция города ИСИТ<<<");
		}
		return instance;
	}

	string getStationName() {
		return StationName;
	}
};

station* station::instance = nullptr;

class passenger {
private:
	string name;
	string passportNumber;
public:
	passenger(string name, string passportNumber) :
		name(name), passportNumber(passportNumber){}

	string getName() {
		return name;
	}
	string getPassportNumber() {
		return passportNumber;
	}
};

class ticketOffice {
public:
	void enterTariffsInfo(string destination, int price, map<string, double> &list) {
		list[destination] = price; // переназначение тарифа
		//for (auto s : list) {
		//	cout << s.first << ' ' << s.second << endl; //вывод тарифов
		//}
	}

	void buy_and_register(string name, string passportNumber, string dest, multimap<string, pair<string, string>> &registering) {
		registering.insert(pair<string, pair<string, string>>(dest, make_pair(passportNumber, name))); // сохранение данных о пассажире
		cout << "Покупка билета зарегистрирована!\n";
	}

	void countTicketsCost(string name, string passNumb, multimap<string, pair<string, string>> &m, map<string, double> &pr) {
		bool found = false;
		for (auto& it : m) { // поиск пассажира по номеру паспорта
			if (passNumb == it.second.first) {
				found = true;
				break;
			}
		}
		if (!found) {
			cout << "Пассажир с указанным номером паспорта не найден!\n";
			return;
		}

		int total = 0;
		for (auto& f : m) { //map m: destination, <number, name>
			if (passNumb == f.second.first && name == f.second.second) {
				for (auto& s : pr) {  //map pr: destination price
					if (f.first == s.first) { // проверка сопоставления цены с пунктом назначения
						total += s.second;
						break;
					}
				}
			}
		}
		cout << "Стоимость купленных пассажиром билетов: " << total << endl;
	}

	void show_passengers_by_destination(string dest, multimap<string, pair<string, string>> &pbd) {
		for (auto& s : pbd) {
			if (dest == s.first) {
				cout << s.second.second << endl;
			}
		}
	}
};

enum Destination{Москва = 1, Казань, Петербург};

string cinDestination() {
	double choice1;
	cout << "Список доступных направлений: \n";
	cout << "1. Москва " << endl;
	cout << "2. Казань " << endl;
	cout << "3. Петербург ";
begin:
	cout << "\nВыберите номер пункта назначения: "; cin >> choice1;
	if (!cin.fail() && (int(choice1)) == choice1 && (to_string(choice1).find(",") == string::npos)) {
		int choice = choice1;
		switch (choice) {
		case Москва:
		{
			return "Москва";
			break;
		}
		case Казань:
		{
			return "Казань";
			break;
		}
		case Петербург:
		{
			return "Петербург";
			break;
		}
		default:
			cout << "~~~Ошибка! Выберите допустимое направление~~~";
			cin.clear();
			cin.ignore(32767, '\n');
			goto begin;
		}
	}
	else {
		cout << "~~~Ошибка! Выберите допустимое направление~~~";
		cin.clear();
		cin.ignore(32767, '\n');
		goto begin;
	}
}

bool checkName(string s) {
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

	station* Station = station::getInstance();
	ticketOffice office;
	map<string, double> list;                                     // dest - price
	multimap<string, pair<string, string>> data_and_destination;  // dest - passNumb, name

	double choice;
	cout << Station->getStationName() << endl;
	cout << " --------------------------------------------------------\n";
	cout << "|   Список доступных действий:                           |" << endl;
	cout << "|1. Ввести данные о тарифах                              |" << endl;
	cout << "|2. Купить билет                                         |" << endl;
	cout << "|3. Рассчитать стоимость купленных пассажиром билетов    |" << endl;
	cout << "|4. Вывести список пассажиров, купивших билет до станции |" << endl;
	cout << "|5. Выйти                                                |" << endl;
	cout << " --------------------------------------------------------\n";
doing_func:
	cout << "Выберите действие: "; cin >> choice;
	if (!cin.fail() && (int(choice)) == choice && (to_string(choice).find(",") == string::npos)) {
		switch (int(choice)) {
		case 1:              // ввод данных о тарифах
		{
			double price;
			string destination;
			destination = cinDestination();
		goprice:
			cout << "Введите цену (целое число от 1 до 10^10): "; cin >> price;
			if (cin.fail() || (int(price)) != price || price < 1 || price > 999999999) {
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "~~~Ошибка! Необходимо допустимое целое число~~~" << endl;
				goto goprice;
			}
			else {
				office.enterTariffsInfo(destination, price, list);
			}
			break;
		}
		case 2:              // регистрация покупки билета
		{
			string name;
			string passportNumber;
		goreg:
			cout << "Введите имя пассажира: "; cin >> name;
			cout << "Введите серию и номер паспорта (6 цифр, без пробела): "; cin >> passportNumber;
			if (cin.fail() || (stoi(passportNumber)) != stod(passportNumber) || checkName(name) == 0 || passportNumber.length() != 6) {
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "~~~Ошибка! Введите корректные данные~~~" << endl;
				goto goreg;
			}
			passenger human(name, passportNumber);

			string destination;                // ввод данных о тарифах
			destination = cinDestination();
			if (list.count(destination) == 0) {
				cout << "~~~Ошибка! Сначала при помощи команды '1' введите соответствующий тариф~~~\n";
				cin.clear();
				cin.ignore(32767, '\n');
				goto doing_func;
			}
			else {
				office.buy_and_register(human.getName(), human.getPassportNumber(), destination, data_and_destination);
			}
			break;
		}
		case 3:               //расчет стоимости купленных пассажиром билетов
		{
			string name;
			string passportNumber;
		counting:
			cout << "Введите имя: "; cin >> name;
			cout << "Введите серию и номер паспорта (без пробела): "; cin >> passportNumber;
			if (cin.fail() || (stoi(passportNumber)) != stod(passportNumber) || checkName(name) == 0 || passportNumber.length() != 6) {
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "~~~Ошибка! Введите корректные данные~~~" << endl;
				goto counting;
			}
			passenger human(name, passportNumber);
			office.countTicketsCost(human.getName(), human.getPassportNumber(), data_and_destination, list);
			break;
		}
		case 4:
		{
			string destination;
			destination = cinDestination();
			office.show_passengers_by_destination(destination, data_and_destination);
			break;
		}
		case 5:
		{
			cout << endl;
			break;
		}		
		}
	}
	else {
		cout << "~~~Ошибка! Выберите допустимый номер функции~~~\n";
		cin.clear();
		cin.ignore(32767, '\n');
		goto doing_func;
	}
	if (choice != 5 && choice >= 1 && choice < 5) {
			goto doing_func;
	}
	delete Station;
	return 0;
}
