#include <iostream>
#include "kiwer_api.cpp"

class KiwerDriver : public StockBrokerDriver {
public:

	void login(std::string ID, std::string password) {
		kiwerAPI->login(ID, password);
		std::cout << ID << " [KiwerDriver] login success\n";
	}

	void buy(std::string stockCode, int count, int price) {
		kiwerAPI->buy(stockCode, count, price);
		std::cout << stockCode << " : [KiwerDriver] Buy stock ( " << price << " * " << count << ")\n";
	}

	void sell(std::string stockCode, int count, int price) {
		kiwerAPI->sell(stockCode, count, price);
		std::cout << stockCode << " : [KiwerDriver] Sell stock ( " << price << " * " << count << ")\n";
	}

	int currentPrice(std::string stockCode) {
		int stockPrice = kiwerAPI->currentPrice(stockCode);
		if (stockPrice < 0) {
			std::cout << "Abnormal price. price set to 0" << "\n";
			stockPrice = 0;
		}
		return stockPrice;
	}
private:
	KiwerAPI* kiwerAPI;
};