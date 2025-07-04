#include "auto_trading_system.h"

#include <chrono>
#include <iostream>
#include <thread>

bool AutoTradingSystem::buyNiceTiming(std::string& stockCode,
                                      int availableFunds) {
  int price = checkPriceIncrease(stockCode);
  if (price == -1) {
    return false;
  }
  std::cout << "Bought " << availableFunds / price << " shares at " << price
            << " dollars automatically!" << std::endl;
  return true;
}

bool AutoTradingSystem::sellNiceTiming(std::string& stockCode, int numShares) {
  int price = checkPriceDecrease(stockCode);
  if (price == -1) {
    return false;
  }
  std::cout << "Sold " << numShares << " shares at " << price
            << " dollars automatically!" << std::endl;
  return true;
}

int AutoTradingSystem::checkPriceIncrease(std::string& stockCode) {
  int current = 0;
  int prev = 0;
  for (int i = 0; i < 3; i++) {
    current = driverInterface.getCurrentPrice(stockCode);
    if (current < prev) {
      return -1;
    }
    prev = current;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  return current;
}

int AutoTradingSystem::checkPriceDecrease(std::string& stockCode) {
  int prev = -1;
  int current = -1;
  for (int i = 0; i < 3; i++) {
    current = driverInterface.getCurrentPrice(stockCode);
    if (prev != -1 && current > prev) {
      return -1;
    }
    prev = current;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  return current;
}
