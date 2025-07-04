#pragma once
#include <string>

#include "stock_broker_driver.h"

class AutoTradingSystem {
public:
	AutoTradingSystem(StockBrokerDriver* driver) : driverInterface{ driver } {};
	void selectBroker(StockBrokerDriver* driver);
	bool login(const std::string& id, const std::string& pass);
	bool buy(const std::string& stockCode, int price, int numShare);
	bool sell(const std::string& stockCode, int price, int numShare);
	int getPrice(const std::string& stockCode);
	bool buyNiceTiming(const std::string& stockCode, int availableFunds);
	bool sellNiceTiming(const std::string& stockCode, int numShares);

private:
	StockBrokerDriver* driverInterface = nullptr;
	int checkPriceIncrease(const std::string& stockCode);
	int checkPriceDecrease(const std::string& stockCode);
};