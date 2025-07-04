#include "auto_trading_system.h"

#include <chrono>
#include <iostream>
#include <thread>

void AutoTradingSystem::selectBroker(StockBrokerDriver* driver) {
	driverInterface = driver;
}

bool AutoTradingSystem::login(const std::string& id, const std::string& pass) {
	return driverInterface->login(id, pass);
}

bool AutoTradingSystem::buy(const std::string& stockCode, int price, int numShare) {
	return driverInterface->buy(stockCode, price, numShare);
}

bool AutoTradingSystem::sell(const std::string& stockCode, int price, int numShare) {
	return driverInterface->sell(stockCode, price, numShare);
}

int AutoTradingSystem::getPrice(const std::string& stockCode) {
	return driverInterface->getCurrentPrice(stockCode);
}

bool AutoTradingSystem::buyNiceTiming(const std::string& stockCode,
	int availableFunds) {
	int price = checkPriceIncrease(stockCode);
	if (price == -1) {
		return false;
	}
	buy(stockCode, price, availableFunds / price);
	std::cout << "Bought " << availableFunds / price << " shares at " << price
		<< " dollars automatically!" << std::endl;
	return true;
}

bool AutoTradingSystem::sellNiceTiming(const std::string& stockCode, int numShares) {
	int price = checkPriceDecrease(stockCode);
	if (price == -1) {
		return false;
	}
	sell(stockCode, price, numShares);
	std::cout << "Sold " << numShares << " shares at " << price
		<< " dollars automatically!" << std::endl;
	return true;
}

int AutoTradingSystem::checkPriceIncrease(const std::string& stockCode) {
	int current = 0;
	int prev = 0;
	for (int i = 0; i < 3; i++) {
		current = getPrice(stockCode);
		if (current < prev) {
			return -1;
		}
		prev = current;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	return current;
}

int AutoTradingSystem::checkPriceDecrease(const std::string& stockCode) {
	int prev = -1;
	int current = -1;
	for (int i = 0; i < 3; i++) {
		current = getPrice(stockCode);
		if (prev != -1 && current > prev) {
			return -1;
		}
		prev = current;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	return current;
}
