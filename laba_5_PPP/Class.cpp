//#include "Class.h"
//
//
//void station::addStrategy(const string& key, tariffs* tariff) {
//	strategies[key] = tariff;
//}
//
//double station::getPrice(const string& key, double basePrice, double discount) {
//	return strategies[key]->getFinalPrice(basePrice, discount);
//}
//
//void station::addNewTariff(string destination, double price, double discount, multimap<string, pair<double, double>>& d) {
//	if (d.empty()) {
//		d.insert(pair<string, pair<double, double>>(destination, make_pair(price, discount)));
//		cout << "Тариф успешно добавлен!\n";
//	}
//	else {
//		for (auto& s : d) {
//			if (s.first == destination && s.second.first == price && s.second.second == discount) {
//				throw "~~~Такой тариф уже существует~~~";
//			}
//			else {
//				d.insert(pair<string, pair<double, double>>(destination, make_pair(price, discount)));
//				cout << "Тариф успешно добавлен!\n";
//				break;
//			}
//		}
//	}
//}
//
//void station::findMinPricedDestination(multimap<string, pair<double, double>>& d) {
//	vector<string> siblings;
//	double minPrice = 10000000000;
//	string current;
//	string key;
//	cout << "\nНаправление       Цена       Скидка" << endl;
//	for (auto& s : d) {
//		cout << setw(11) << s.first << setw(11) << s.second.first << setw(11) << s.second.second << endl;
//		if (s.second.second == 0) {
//			key = "basic";
//		}
//		else {
//			key = "discounted";
//		}
//		if (minPrice >= strategies[key]->getFinalPrice(s.second.first, s.second.second)) {
//			if (minPrice > strategies[key]->getFinalPrice(s.second.first, s.second.second)) {
//				siblings.clear();
//				minPrice = strategies[key]->getFinalPrice(s.second.first, s.second.second);
//				current = s.first;
//				siblings.push_back(current);
//			}
//			else if (minPrice == strategies[key]->getFinalPrice(s.second.first, s.second.second)) {
//				//siblings.clear();
//				minPrice = strategies[key]->getFinalPrice(s.second.first, s.second.second);
//				current = s.first;
//				siblings.push_back(current);
//			}
//		}
//	}
//	if (!siblings.empty()) { // пуст ли вектор
//		cout << "\nМинимальная цена: " << minPrice << endl;
//		cout << "Направления с минимальной ценой: " << endl;
//		int i = 1;
//		for (auto k : siblings) {
//			cout << i << ") " << k << endl;
//			i++;
//		} cout << endl;
//	}
//	else {
//		cout << "     -              -           -   " << endl;
//	}
//}