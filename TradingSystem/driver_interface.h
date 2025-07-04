#pragma once
#include <string>

class StockerBrockerDriverInterface {
  // Dummy class to test Auto Trading System
 public:
  virtual void login(std::string id, std::string password) = 0;
  virtual int getPrice(std::string stockCode) = 0;
  virtual void buy(std::string stockCode, int price, int num) = 0;
  virtual void sell(std::string stockCode, int price, int num) = 0;
};