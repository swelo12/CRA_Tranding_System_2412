#include "gmock/gmock.h"
#include "StockBrokerDriver.h"
#include <string>

using std::string;

class MockStockAPI {
public:
	MOCK_METHOD(void, login, (string ID, string password), ());
	MOCK_METHOD(void, buy, (string stockCode, int count, int price), ());
	MOCK_METHOD(void, sell, (string stockCode, int count, int price), ());
	MOCK_METHOD(int, currentPrice, (string stockCode), ());
};

class MockDriver : public StockBrokerDriver {
public:
	MockDriver(MockStockAPI* mockStockAPI) : mockStockAPI { mockStockAPI }{}

	void login(std::string ID, std::string password) {
		mockStockAPI->login(ID, password);
		std::cout << ID << " [Mock Driver] login success\n";
	}

	void buy(std::string stockCode, int count, int price) {
		mockStockAPI->buy(stockCode, count, price);
		std::cout << stockCode << " : [Mock Driver] Buy stock ( " << price << " * " << count << ")\n";
	}

	void sell(std::string stockCode, int count, int price) {
		mockStockAPI->sell(stockCode, count, price);
		std::cout << stockCode << " : [Mock Driver] Sell stock ( " << price << " * " << count << ")\n";
	}

	int currentPrice(std::string stockCode) {
		int stockPrice = mockStockAPI->currentPrice(stockCode);
		if (stockPrice < 0)
			std::cout << stockCode << " : [Warning] Mock current price under zero ( " << stockPrice << " )\n";
		
		return stockPrice;
	}

private:
	MockStockAPI* mockStockAPI;
};