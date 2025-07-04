#include "auto_trading_system.h"

#include <iostream>

bool AutoTradingSystem::buyNiceTiming(std::string stockCode,
                                      int availableFunds) {
  int prev = -1;
  int current = -1;
  for (int i = 0; i < 3; i++) {
    current = driverInterface.getCurrentPrice(stockCode);
    if (current < prev) {
      return false;
    }
    prev = current;
  }

  std::cout << "Bought " << availableFunds / current << " shares at" << current
            << " dollars automatically!" << std::endl;
  return true;
}

bool AutoTradingSystem::sellNiceTiming(std::string stockCode, int numShares) {
  int prev = -1;
  int current = -1;
  for (int i = 0; i < 3; i++) {
    current = driverInterface.getCurrentPrice(stockCode);
    if (prev != -1 && current > prev) {
      return false;
    }
    prev = current;
  }
  std::cout << "Sold " << numShares << " shares at" << current
            << " dollars automatically!" << std::endl;
  return true;
}