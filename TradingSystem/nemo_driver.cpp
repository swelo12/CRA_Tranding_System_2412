#include <iostream>
#include "nemo_api.cpp"
#include "stock_broker_driver.h"

class NemoDriver : public StockBrokerDriver {
public:
	NemoDriver(NemoAPI* nemoAPI) : nemoAPI{ nemoAPI } {}

	bool login(const std::string& id, const std::string& pass) override {
		nemoAPI->certification(id, pass);
		std::cout << id << " [NemoDriver] login success\n";
		return true;
	}

	bool buy(const std::string& stockCode, int quantity, int price) override  {
		nemoAPI->purchasingStock(stockCode, quantity, price);
		std::cout << stockCode << " : [NemoDriver] Buy stock ( " << price << " * " << quantity << ")\n";
		return true;
	}

	bool sell(const std::string& stockCode, int quantity, int price) override  {
		nemoAPI->sellingStock(stockCode, quantity, price);
		std::cout << stockCode << " : [NemoDriver] Sell stock ( " << price << " * " << quantity << ")\n";
		return true;
	}

	int getCurrentPrice(const std::string& stockCode) override  {
		int stockPrice = nemoAPI->getMarketPrice(stockCode, 0);
		if (stockPrice < 0) {
			std::cout << "[NemoDriver] Abnormal price. price set to 0" << "\n";
			stockPrice = 0;
		}
		return stockPrice;
	}
private:
	NemoAPI* nemoAPI;
};