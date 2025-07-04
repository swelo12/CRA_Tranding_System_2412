#include <iostream>
#include "nemo_api.cpp"

class NemoDriver : public StockBrokerDriver {
public:

	void login(std::string ID, std::string password) {
		nemoAPI->certification(ID, password);
		std::cout << ID << " [NemoDriver Driver] login success\n";
	}

	void buy(std::string stockCode, int count, int price) {
		nemoAPI->purchasingStock(stockCode, count, price);
		std::cout << stockCode << " : [NemoDriver Driver] Buy stock ( " << price << " * " << count << ")\n";
	}

	void sell(std::string stockCode, int count, int price) {
		nemoAPI->sellingStock(stockCode, count, price);
		std::cout << stockCode << " : [Mock Driver] Sell stock ( " << price << " * " << count << ")\n";
	}

	int currentPrice(std::string stockCode) {
		int stockPrice = nemoAPI->getMarketPrice(stockCode, 0);
		if (stockPrice < 0)
			stockPrice = 0;
		return stockPrice;
	}
private:
	NemoAPI* nemoAPI;
};