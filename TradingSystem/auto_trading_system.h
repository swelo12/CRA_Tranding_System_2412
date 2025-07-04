#pragma once
#include <string>
#include "driver_interface.h"

class AutoTradingSystem {
 public:
  AutoTradingSystem(StockerBrockerDriverInterface& driverInterface)
      : driverInterface{driverInterface} {};

  bool buyNiceTiming(std::string stockCode, int availableFunds);
  bool sellNiceTiming(std::string stockCode, int numShares);

 private:
  StockerBrockerDriverInterface& driverInterface;
};