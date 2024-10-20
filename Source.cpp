#include <iostream>
#include <map>
#include <windows.h>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

//���������� � C++ � ��� ������ ������� ��������� ��� ����������� ������,
//�� ���������� � ���������� ����������� ����� ������.
//��� ����������� ����� ����������� ������, ���������� ����� ����������� �������

class tariffs { // ������ strategy, ��������
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
			cout << "����� ������� ��������!\n";
		}else {
			for (auto& s : d) {
				if (s.first == destination && s.second.first == price && s.second.second == discount) {
					throw "~~~����� ����� ��� ����������~~~";
				}
				else {
					d.insert(pair<string, pair<double, double>>(destination, make_pair(price, discount)));
					cout << "����� ������� ��������!\n";
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
		cout << "\n�����������       ����       ������" << endl;
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
		if (!siblings.empty()) { // ���� �� ������
			cout << "\n����������� ����: " << minPrice << endl;
			cout << "����������� � ����������� �����: " << endl;
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
	for (int i = 0; i < s.length(); i++) { // ������ �� ��������
		if ((s[i] >= '�' && s[i] <= '�' || s[i] >= '�' && s[i] <= '�') ||
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
	cout << "|   ������ ��������� ��������:                   |" << endl;
	cout << "|1. �������� ����� �����                         |" << endl;
	cout << "|2. ����� ����������� � ����������� ����������   |" << endl;
	cout << "|3. �����                                        |" << endl;
	cout << " ------------------------------------------------\n";
doing_func:
	try {
		cout << "�������� ��������: "; cin >> choice;
		if (choice < 1 || choice > 3 || (int(choice) != choice)) {
			throw "~~~������! ������� ����� �� 1 �� 3~~~";
		}
		switch (int(choice)) {
		case 1:
		{
			string destination;
			double price;
			double discount;
			cout << "������� �������� �����������: "; cin >> destination; //+check 
			if (checkString(destination) == 0) {
				throw "~~~������! �������� ����������� ������ ��������� ������ �����~~~";
			}
			cout << "������� ����: "; cin >> price;
			if (price < 0 || price > 10000000000) {
				throw "~~~������! ���� ����������� �� 0 �� 10^10~~~";
			}
			cout << "������� ������ (� %): "; cin >> discount;
			if (discount < 0 || discount > 100) {
				throw "~~~������! ������� ������ ����������� �� 0 �� 100~~~";
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
		cout << "~~~������! ����������� ������� ��������~~~\n";// << ex.what();
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
		cout << "~~~������! ����������� ������� ��������~~~\n";
		cin.clear();
		cin.ignore(32767, '\n');
		goto doing_func;
	}
	if (choice != 3 && choice >= 1 && choice < 4) {
		goto doing_func;
	}
	return 0;
}