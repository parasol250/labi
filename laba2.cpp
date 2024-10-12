#include <iostream>
#include <windows.h>
#include <string>
#include <map>

using namespace std;

class station { // åäèíñòâåííàÿ ñòàíöèÿ ñ øàáëîíîì Singleton
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
			instance = new station("                >>>Ñòàíöèÿ ãîðîäà ÈÑÈÒ<<<");
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
		list[destination] = price; // ïåðåíàçíà÷åíèå òàðèôà
		//for (auto s : list) {
		//	cout << s.first << ' ' << s.second << endl; //âûâîä òàðèôîâ
		//}
	}

	void buy_and_register(string name, string passportNumber, string dest, multimap<string, pair<string, string>> &registering) {
		registering.insert(pair<string, pair<string, string>>(dest, make_pair(passportNumber, name))); // ñîõðàíåíèå äàííûõ î ïàññàæèðå
		cout << "Ïîêóïêà áèëåòà çàðåãèñòðèðîâàíà!\n";
	}

	void countTicketsCost(string name, string passNumb, multimap<string, pair<string, string>> &m, map<string, double> &pr) {
		bool found = false;
		for (auto& it : m) { // ïîèñê ïàññàæèðà ïî íîìåðó ïàñïîðòà
			if (passNumb == it.second.first) {
				found = true;
				break;
			}
		}
		if (!found) {
			cout << "Ïàññàæèð ñ óêàçàííûì íîìåðîì ïàñïîðòà íå íàéäåí!\n";
			return;
		}

		int total = 0;
		for (auto& f : m) { //map m: destination, <number, name>
			if (passNumb == f.second.first && name == f.second.second) {
				for (auto& s : pr) {  //map pr: destination price
					if (f.first == s.first) { // ïðîâåðêà ñîïîñòàâëåíèÿ öåíû ñ ïóíêòîì íàçíà÷åíèÿ
						total += s.second;
						break;
					}
				}
			}
		}
		cout << "Ñòîèìîñòü êóïëåííûõ ïàññàæèðîì áèëåòîâ: " << total << endl;
	}

	void show_passengers_by_destination(string dest, multimap<string, pair<string, string>> &pbd) {
		for (auto& s : pbd) {
			if (dest == s.first) {
				cout << s.second.second << endl;
			}
		}
	}
};

enum Destination{Ìîñêâà = 1, Êàçàíü, Ïåòåðáóðã};

string cinDestination() {
	double choice1;
	cout << "Ñïèñîê äîñòóïíûõ íàïðàâëåíèé: \n";
	cout << "1. Ìîñêâà " << endl;
	cout << "2. Êàçàíü " << endl;
	cout << "3. Ïåòåðáóðã ";
begin:
	cout << "\nÂûáåðèòå íîìåð ïóíêòà íàçíà÷åíèÿ: "; cin >> choice1;
	if (!cin.fail() && (int(choice1)) == choice1 && (to_string(choice1).find(",") == string::npos)) {
		int choice = choice1;
		switch (choice) {
		case Ìîñêâà:
		{
			return "Ìîñêâà";
			break;
		}
		case Êàçàíü:
		{
			return "Êàçàíü";
			break;
		}
		case Ïåòåðáóðã:
		{
			return "Ïåòåðáóðã";
			break;
		}
		default:
			cout << "~~~Îøèáêà! Âûáåðèòå äîïóñòèìîå íàïðàâëåíèå~~~";
			cin.clear();
			cin.ignore(32767, '\n');
			goto begin;
		}
	}
	else {
		cout << "~~~Îøèáêà! Âûáåðèòå äîïóñòèìîå íàïðàâëåíèå~~~";
		cin.clear();
		cin.ignore(32767, '\n');
		goto begin;
	}
}

bool checkName(string s) {
	int counter = 0;
	for (int i = 0; i < s.length(); i++) { // ïðîõîä ïî ñèìâîëàì
		if ((s[i] >= 'À' && s[i] <= 'ß' || s[i] >= 'à' && s[i] <= 'ÿ') ||
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
	cout << "|   Ñïèñîê äîñòóïíûõ äåéñòâèé:                           |" << endl;
	cout << "|1. Ââåñòè äàííûå î òàðèôàõ                              |" << endl;
	cout << "|2. Êóïèòü áèëåò                                         |" << endl;
	cout << "|3. Ðàññ÷èòàòü ñòîèìîñòü êóïëåííûõ ïàññàæèðîì áèëåòîâ    |" << endl;
	cout << "|4. Âûâåñòè ñïèñîê ïàññàæèðîâ, êóïèâøèõ áèëåò äî ñòàíöèè |" << endl;
	cout << "|5. Âûéòè                                                |" << endl;
	cout << " --------------------------------------------------------\n";
doing_func:
	cout << "Âûáåðèòå äåéñòâèå: "; cin >> choice;
	if (!cin.fail() && (int(choice)) == choice && (to_string(choice).find(",") == string::npos)) {
		switch (int(choice)) {
		case 1:              // ââîä äàííûõ î òàðèôàõ
		{
			double price;
			string destination;
			destination = cinDestination();
		goprice:
			cout << "Ââåäèòå öåíó (öåëîå ÷èñëî îò 1 äî 10^10): "; cin >> price;
			if (cin.fail() || (int(price)) != price || price < 1 || price > 999999999) {
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "~~~Îøèáêà! Íåîáõîäèìî äîïóñòèìîå öåëîå ÷èñëî~~~" << endl;
				goto goprice;
			}
			else {
				office.enterTariffsInfo(destination, price, list);
			}
			break;
		}
		case 2:              // ðåãèñòðàöèÿ ïîêóïêè áèëåòà
		{
			string name;
			string passportNumber;
		goreg:
			cout << "Ââåäèòå èìÿ ïàññàæèðà: "; cin >> name;
			cout << "Ââåäèòå ñåðèþ è íîìåð ïàñïîðòà (6 öèôð, áåç ïðîáåëà): "; cin >> passportNumber;
			if (cin.fail() || (stoi(passportNumber)) != stod(passportNumber) || checkName(name) == 0 || passportNumber.length() != 6) {
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "~~~Îøèáêà! Ââåäèòå êîððåêòíûå äàííûå~~~" << endl;
				goto goreg;
			}
			passenger human(name, passportNumber);

			string destination;                // ââîä äàííûõ î òàðèôàõ
			destination = cinDestination();
			if (list.count(destination) == 0) {
				cout << "~~~Îøèáêà! Ñíà÷àëà ïðè ïîìîùè êîìàíäû '1' ââåäèòå ñîîòâåòñòâóþùèé òàðèô~~~\n";
				cin.clear();
				cin.ignore(32767, '\n');
				goto doing_func;
			}
			else {
				office.buy_and_register(human.getName(), human.getPassportNumber(), destination, data_and_destination);
			}
			break;
		}
		case 3:               //ðàñ÷åò ñòîèìîñòè êóïëåííûõ ïàññàæèðîì áèëåòîâ
		{
			string name;
			string passportNumber;
		counting:
			cout << "Ââåäèòå èìÿ: "; cin >> name;
			cout << "Ââåäèòå ñåðèþ è íîìåð ïàñïîðòà (áåç ïðîáåëà): "; cin >> passportNumber;
			if (cin.fail() || (stoi(passportNumber)) != stod(passportNumber) || checkName(name) == 0 || passportNumber.length() != 6) {
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "~~~Îøèáêà! Ââåäèòå êîððåêòíûå äàííûå~~~" << endl;
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
		cout << "~~~Îøèáêà! Âûáåðèòå äîïóñòèìûé íîìåð ôóíêöèè~~~\n";
		cin.clear();
		cin.ignore(32767, '\n');
		goto doing_func;
	}
	if (choice != 5 && choice >= 1 && choice < 5) {
			goto doing_func;
	}
	return 0;
}
