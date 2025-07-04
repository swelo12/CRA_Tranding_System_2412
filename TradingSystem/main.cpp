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

class TradingFixture : public Test {
public:
	MockStockAPI mockStockAPI;

	KiwerDriver kiwerDriver{ &kiwerAPI };
	NemoDriver nemoDriver{ &nemoAPI };
	MockDriver mockDriver{ &mockStockAPI };

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
// Mock test
//////////////////////////////////////////
TEST_F(TradingFixture, TEST_LOGIN) {
	stockBrokerDriver = &mockDriver;

	EXPECT_CALL(mockStockAPI, login(_, _)).Times(1).WillOnce(Return(true));

	stockBrokerDriver->login(ID, SUCCESS_PASSWORD);
}

TEST_F(TradingFixture, TEST_BUY) {
	stockBrokerDriver = &mockDriver;

	int quantity = 10;
	int price = 100;

	EXPECT_CALL(mockStockAPI, buy(STOCK_CODE, quantity, price))
		.Times(1)
		.WillOnce(Return(true));

	stockBrokerDriver->buy(STOCK_CODE, quantity, price);
}

TEST_F(TradingFixture, TEST_SELL) {
	stockBrokerDriver = &mockDriver;

	int quantity = 10;
	int price = 100;

	EXPECT_CALL(mockStockAPI, sell(STOCK_CODE, quantity, price))
		.Times(1)
		.WillOnce(Return(true));

	stockBrokerDriver->sell(STOCK_CODE, quantity, price);
}

TEST_F(TradingFixture, TEST_GET_PRICE) {
	stockBrokerDriver = &mockDriver;
	int expectedPrice = 100;

	EXPECT_CALL(mockStockAPI, getCurrentPrice(STOCK_CODE))
		.Times(1)
		.WillOnce(Return(expectedPrice));

	int actualPrice = stockBrokerDriver->getCurrentPrice(STOCK_CODE);

	EXPECT_EQ(expectedPrice, actualPrice);
}

///////////////////////////////////////////
// kiwerAPI test
//////////////////////////////////////////
TEST_F(TradingFixture, kiwerAPI_LOGIN) {
	stockBrokerDriver = &kiwerDriver;

	stockBrokerDriver->login(ID, SUCCESS_PASSWORD);

	std::string expect = ID + " login success\n" + ID + " [KiwerDriver] login success\n";
	
	EXPECT_EQ(oss.str(), expect);
}

TEST_F(TradingFixture, kiwerAPI_BUY) {
	stockBrokerDriver = &kiwerDriver;
	int price = 100;
	int num = 10;

	stockBrokerDriver->buy(STOCK_CODE, price, num);

	std::string expect = STOCK_CODE + " : Buy stock ( " + std::to_string(num) + " * " + std::to_string(price) + ")\n"
		+ STOCK_CODE + " : [KiwerDriver] Buy stock ( " + std::to_string(num) + " * " + std::to_string(price) + ")\n";

	EXPECT_EQ(oss.str(), expect);
}

TEST_F(TradingFixture, kiwerAPI_SELL) {
	stockBrokerDriver = &kiwerDriver;
	int price = 100;
	int num = 10;

	stockBrokerDriver->sell(STOCK_CODE, price, num);

	std::string expect = STOCK_CODE + " : Sell stock ( " + std::to_string(num) + " * " + std::to_string(price) + ")\n"
		+ STOCK_CODE + " : [KiwerDriver] Sell stock ( " + std::to_string(num) + " * " + std::to_string(price) + ")\n";
	
	EXPECT_EQ(oss.str(), expect);
}

TEST_F(TradingFixture, kiwerAPI_GET_PRICE) {
	stockBrokerDriver = &kiwerDriver;
	int except = 100;
	int actual = stockBrokerDriver->getCurrentPrice(STOCK_CODE);

	// EXPECT_EQ(except, actual);
}

///////////////////////////////////////////
// NemoAPI test
//////////////////////////////////////////
TEST_F(TradingFixture, NemoAPI_LOGIN) {
	stockBrokerDriver = &nemoDriver;

	stockBrokerDriver->login(ID, SUCCESS_PASSWORD);

	std::string expect = "[NEMO]"+ID + " login GOOD\n" + ID + " [NemoDriver] login success\n";

	EXPECT_EQ(oss.str(), expect);
}

TEST_F(TradingFixture, NemoAPI_BUY) {
	stockBrokerDriver = &nemoDriver;
	int price = 100;
	int num = 10;

	stockBrokerDriver->buy(STOCK_CODE, price, num);

	std::string expect = "[NEMO]code buy stock ( price : " + std::to_string(price) + " ) * ( count : " + std::to_string(num) + ")\n"
		+ STOCK_CODE + " : [NemoDriver] Buy stock ( " + std::to_string(num) + " * " + std::to_string(price) + ")\n";

	EXPECT_EQ(oss.str(), expect);
}

TEST_F(TradingFixture, NemoAPI_SELL) {
	stockBrokerDriver = &nemoDriver;
	int price = 100;
	int num = 10;

	stockBrokerDriver->sell(STOCK_CODE, price, num);

	std::string expect = "[NEMO]" + STOCK_CODE + " sell stock ( price : " + std::to_string(price) + " ) * ( count : " + std::to_string(num) + ")\n"
		+ STOCK_CODE + " : [NemoDriver] Sell stock ( " + std::to_string(num) + " * " + std::to_string(price) + ")\n";

	EXPECT_EQ(oss.str(), expect);
}

TEST_F(TradingFixture, NemoAPI_GET_PRICE) {
	stockBrokerDriver = &nemoDriver;
	int except = 100;
	int actual = stockBrokerDriver->getCurrentPrice(STOCK_CODE);

	// EXPECT_EQ(except, actual);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
