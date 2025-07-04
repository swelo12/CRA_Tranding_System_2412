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

class AutoTradingFixture : public Test {
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
// Auto Trading system test
//////////////////////////////////////////
TEST_F(AutoTradingFixture, TEST_buyNiceTiming__Buy_success) {
	stockBrokerDriver = &mockDriver;
	autoTradingSystem = new AutoTradingSystem(*stockBrokerDriver);
	std::vector<int> price = { 12, 20, 30 };

	EXPECT_CALL(mockStockAPI, getCurrentPrice(STOCK_CODE))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]))
		.WillOnce(Return(price[2]))
		.WillRepeatedly(Return(price[2]));

	bool success = autoTradingSystem->buyNiceTiming(STOCK_CODE, money);
	EXPECT_EQ(true, success);
}

TEST_F(AutoTradingFixture, TEST_buyNiceTiming__Buy_fail) {
	stockBrokerDriver = &mockDriver;
	autoTradingSystem = new AutoTradingSystem(*stockBrokerDriver);
	std::vector<int> price = { 40, 20, 30 };

	EXPECT_CALL(mockStockAPI, getCurrentPrice(STOCK_CODE))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]));

	bool success = autoTradingSystem->buyNiceTiming(STOCK_CODE, money);
	EXPECT_EQ(false, success);
}

TEST_F(AutoTradingFixture, TEST_sellNiceTiming__Sell_success) {
	stockBrokerDriver = &mockDriver;
	autoTradingSystem = new AutoTradingSystem(*stockBrokerDriver);
	std::vector<int> price = { 30, 20, 12 };

	EXPECT_CALL(mockStockAPI, getCurrentPrice(_))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]))
		.WillOnce(Return(price[2]))
		.WillRepeatedly(Return(price[2]));

	int cellCount = 3;
	bool success = autoTradingSystem->sellNiceTiming(STOCK_CODE, cellCount);

	EXPECT_EQ(true, success);
}

TEST_F(AutoTradingFixture, TEST_sellNiceTiming__Sell_fail) {
	stockBrokerDriver = &mockDriver;
	autoTradingSystem = new AutoTradingSystem(*stockBrokerDriver);
	std::vector<int> price = { 40, 20, 30 };

	EXPECT_CALL(mockStockAPI, getCurrentPrice(_))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]))
		.WillOnce(Return(price[2]))
		.WillRepeatedly(Return(price[2]));

	int cellCount = 3;
	bool success = autoTradingSystem->sellNiceTiming(STOCK_CODE, price[2]);

	EXPECT_EQ(false, success);
}