#include <iostream>
#include "kiwer_api.cpp"
#include "stock_broker_driver.h"

class KiwerDriver : public StockBrokerDriver {
public:
	KiwerDriver(KiwerAPI* kiwerAPI) : kiwerAPI{ kiwerAPI } {}

	bool login(const std::string& id, const std::string& pass) override{
		kiwerAPI->login(id, pass);
		return true;
	}

	bool buy(const std::string& stockCode, int quantity, int price) override {
		kiwerAPI->buy(stockCode, quantity, price);
		return true;
	}

	bool sell(const std::string& stockCode, int quantity, int price) override {
		kiwerAPI->sell(stockCode, quantity, price);
		return true;
	}

	int getCurrentPrice(const std::string& stockCode) override {
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