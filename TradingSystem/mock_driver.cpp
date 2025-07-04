#include "gmock/gmock.h"
#include "stock_broker_driver.h"
#include <string>

using std::string;

class MockStockAPI {
public:
	// StockBrokerDriver의 login, buy, sell이 bool을 반환하므로 MockStockAPI도 bool 반환
	MOCK_METHOD(bool, login, (const string& id, const string& pass), ());
	MOCK_METHOD(bool, buy, (const string& stockCode, int quantity, int price), ());
	MOCK_METHOD(bool, sell, (const string& stockCode, int quantity, int price), ());
	// StockBrokerDriver의 getCurrentPrice와 메서드 이름이 일치해야 합니다.
	MOCK_METHOD(int, getCurrentPrice, (const string& stockCode), ());
};

class MockDriver : public StockBrokerDriver {
public:
	MockDriver(MockStockAPI* mockStockAPI) : mockStockAPI{ mockStockAPI } {}

	bool login(const std::string& id, const std::string& pass) override {
		bool result = mockStockAPI->login(id, pass);
		std::cout << id << " [Mock Driver] login success\n";
		return result;
	}

	bool buy(const std::string& stockCode, int quantity, int price) override {
		bool result = mockStockAPI->buy(stockCode, quantity, price);
		std::cout << stockCode << " : [Mock Driver] Buy stock ( " << price << " * " << quantity << ")\n";
		return result;
	}

	bool sell(const std::string& stockCode, int quantity, int price) override {
		bool result = mockStockAPI->sell(stockCode, quantity, price);
		std::cout << stockCode << " : [Mock Driver] Sell stock ( " << price << " * " << quantity << ")\n";
		return result;
	}

	int getCurrentPrice(const std::string& stockCode) override {
		int stockPrice = mockStockAPI->getCurrentPrice(stockCode);
		if (stockPrice < 0)
			std::cout << stockCode << " : [Warning] Mock current price under zero ( " << stockPrice << " )\n";

		return stockPrice;
	}

private:
	MockStockAPI* mockStockAPI;
};

