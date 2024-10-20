#include <iostream>
#include <time.h>
#include <string>
#include <windows.h>

using namespace std;

class station {	
private:
	string StationName;
	double Price;
	int SeatsAmount;
	int TicketsSold;
public:
	station(string StationName, double Price, int SeatsAmount, int TicketsSold) :
		StationName(StationName), Price(Price), SeatsAmount(SeatsAmount), TicketsSold(TicketsSold) {}

	string getDestinationName() {
		return StationName;
	}

	double getPrice() {
		return Price;
	}

	int getSeatsAmount() {
		return SeatsAmount;
	}

	int getSoldAmount() {
		return TicketsSold;
	}

	double unsoldTickCounter() {
		return ((SeatsAmount - TicketsSold) * Price);
	}
};


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	int whole = rand() % 250;
	int sold = rand() % 250;
	while (sold > whole) {
		sold = rand() % 250;
	}

	station Morskaya("Морская", 1190, whole, sold);

	cout << "Наименование станции: " << Morskaya.getDestinationName();
	cout << "\nСтоимость билета: " << Morskaya.getPrice();
	cout << "\nЧисло мест: " << Morskaya.getSeatsAmount();
	cout << "\nЧисло проданных билетов: " << Morskaya.getSoldAmount();
	cout << "\n\nОбщая стоимость непроданных билетов: " << Morskaya.unsoldTickCounter() << "\n";

	return 0;
}
