#include "auto_trading_system.h"
#include "gmock/gmock.h"
#include "kiwer_api.cpp"
#include "kiwer_driver.cpp"
#include "mock_driver.cpp"
#include "nemo_api.cpp"
#include "nemo_driver.cpp"
#include "stock_broker_driver.h"


#include <iostream>
#include <sstream>

using namespace testing;

class SelectStockerBrockerFixture : public Test {
public:
	MockStockAPI mockStockAPI;

	KiwerDriver kiwerDriver{ &kiwerAPI };
	NemoDriver nemoDriver{ &nemoAPI };
	MockDriver mockDriver{ &mockStockAPI };

	AutoTradingSystem* autoTradingSystem;
	StockBrokerDriver* stockBrokerDriver;

	std::string ID = "1234";
	std::string SUCCESS_PASSWORD = "1234";
	std::string STOCK_CODE = "code";
	int money = 100;

	std::ostringstream oss;
	std::streambuf* old_buf;
private:
	KiwerAPI kiwerAPI;
	NemoAPI nemoAPI;
	void SetUp() override {
		old_buf = std::cout.rdbuf(oss.rdbuf());  // cout 리다이렉션
	}

	void TearDown() override {
		std::cout.rdbuf(old_buf);  // 원래 버퍼 복원
	}
};
///////////////////////////////////////////
// kiwerAPI test
//////////////////////////////////////////


///////////////////////////////////////////
// NemoAPI test
//////////////////////////////////////////