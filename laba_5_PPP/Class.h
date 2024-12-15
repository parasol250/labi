//#pragma once
//
//#include <iostream>
//#include <map>
//#include <windows.h>
//#include <string>
//#include <iomanip>
//#include <vector>
//
//using namespace std;
//
//class tariffs { // шаблон strategy, абстракт
//public:
//	virtual ~tariffs() {}
//	virtual double getFinalPrice(double price, double discount) const = 0;
//};
//
//class basicTariff : public tariffs {
//public:
//
//	double getFinalPrice(double price, double discount) const override {
//		return price;
//	}
//};
//
//class discountedTariff : public tariffs {
//public:
//	double getFinalPrice(double price, double discount) const override {
//		return (price * ((100 - discount) / 100));
//	}
//};
//
//class station {
//protected:
//	map<string, tariffs*> strategies;
//public:
//	station() {};
//	~station() {};
//	void addStrategy(const string& key, tariffs* tariff);
//	double getPrice(const string& key, double basePrice, double discount);
//	void addNewTariff(string destination, double price, double discount, multimap<string, pair<double, double>>& d);
//	void findMinPricedDestination(multimap<string, pair<double, double>>& d);
//};