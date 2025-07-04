#pragma once
#include <string>

#include "stock_broker_driver.h"

class AutoTradingSystem {
public:
	AutoTradingSystem(StockBrokerDriver& driverInterface)
		: driverInterface{ driverInterface } {};

	bool buyNiceTiming(std::string& stockCode, int availableFunds);
	bool sellNiceTiming(std::string& stockCode, int numShares);

private:
	StockBrokerDriver& driverInterface;
	int checkPriceIncrease(std::string& stockCode);
	int checkPriceDecrease(std::string& stockCode);
};