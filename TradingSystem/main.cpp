#include "gmock/gmock.h"
#include "nemo_api.cpp"
#include "kiwer_api.cpp"
#include "mock_driver.cpp"
#include "stock_broker_driver.h"

#include "nemo_driver.cpp"
#include "kiwer_driver.cpp"
#include "auto_trading_system.h"

using namespace testing;

class TraingFixture : public Test {
public:
	MockStockAPI mockStockAPI;
	MockDriver mockDriver{ &mockStockAPI };

	KiwerAPI kiwerAPI;
	KiwerDriver kiwerDriver{ &kiwerAPI };

	NemoAPI nemoAPI;
	NemoDriver nemoDriver{ &nemoAPI };

	std::string ID = "1234";
	std::string SUCCESS_PASSWORD = "1234";
	std::string STOCK_CODE = "code";

	AutoTradingSystem* autoTradingSystem;
	int money = 100;

private:
	void SetUp() override {
		// nothing;
	}
};


///////////////////////////////////////////
// Mock test
//////////////////////////////////////////
TEST_F(TraingFixture, TEST_LOGIN)
{
	EXPECT_CALL(mockStockAPI, login(_, _))
		.Times(1)
		.WillOnce(Return(true));
	mockDriver.login(ID, SUCCESS_PASSWORD);
}

TEST_F(TraingFixture, TEST_BUY)
{
	int quantity = 10;
	int price = 100;

	EXPECT_CALL(mockStockAPI, buy(STOCK_CODE, quantity, price))
		.Times(1)
		.WillOnce(Return(true));

	mockDriver.buy(STOCK_CODE, quantity, price);
}

TEST_F(TraingFixture, TEST_SELL)
{
	int quantity = 10;
	int price = 100;

	EXPECT_CALL(mockStockAPI, sell(STOCK_CODE, quantity, price))
		.Times(1)
		.WillOnce(Return(true));

	mockDriver.sell(STOCK_CODE, quantity, price);
}

TEST_F(TraingFixture, TEST_GET_PRICE)
{
	int expectedPrice = 100;

	EXPECT_CALL(mockStockAPI, getCurrentPrice(STOCK_CODE))
		.Times(1)
		.WillOnce(Return(expectedPrice));

	int actualPrice = mockDriver.getCurrentPrice(STOCK_CODE);

	EXPECT_EQ(expectedPrice, actualPrice);
}

///////////////////////////////////////////
// Auto Trading system test
//////////////////////////////////////////
TEST_F(TraingFixture, TEST_buyNiceTiming__Buy_success)
{
	// TODO: Change mockDriver to StockBrokerDriver after implemented
	autoTradingSystem = new AutoTradingSystem(mockDriver); // inherit mock.
	std::vector<int> price = { 12,20,30 };

	EXPECT_CALL(mockStockAPI, getCurrentPrice(STOCK_CODE))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]))
		.WillOnce(Return(price[2]))
		.WillRepeatedly(Return(price[2]));

	bool success = autoTradingSystem->buyNiceTiming(STOCK_CODE, money);
    EXPECT_EQ(true, success);
}

TEST_F(TraingFixture, TEST_buyNiceTiming__Buy_fail)
{
	autoTradingSystem = new AutoTradingSystem(mockDriver); // inherit mock.
	std::vector<int> price = { 40,20,30 };

	EXPECT_CALL(mockStockAPI, getCurrentPrice(STOCK_CODE))
            .WillOnce(Return(price[0]))
            .WillOnce(Return(price[1]));

	bool success = autoTradingSystem->buyNiceTiming(STOCK_CODE, money);
    EXPECT_EQ(false, success);
}

TEST_F(TraingFixture, TEST_sellNiceTiming__Sell_success)
{
	autoTradingSystem = new AutoTradingSystem(mockDriver); // inherit mock.
	std::vector<int> price = { 30,20,12 };

	EXPECT_CALL(mockStockAPI, getCurrentPrice(_))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]))
		.WillOnce(Return(price[2]))
		.WillRepeatedly(Return(price[2]));

	int cellCount = 3;
	bool success = autoTradingSystem->sellNiceTiming(STOCK_CODE, cellCount);

	EXPECT_EQ(true, success);
}

TEST_F(TraingFixture, TEST_sellNiceTiming__Sell_fail)
{
	autoTradingSystem = new AutoTradingSystem(mockDriver); // inherit mock.
	std::vector<int> price = { 40,20,30 };

	EXPECT_CALL(mockStockAPI, getCurrentPrice(_))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]))
		.WillOnce(Return(price[2]))
		.WillRepeatedly(Return(price[2]));

	int cellCount = 3;
	bool success = autoTradingSystem->sellNiceTiming(STOCK_CODE, price[2]);

	EXPECT_EQ(false, success);
}

///////////////////////////////////////////
// kiwerAPI test
//////////////////////////////////////////
TEST_F(TraingFixture, kiwerAPI_LOGIN)
{
	//EXPECT_CALL(kiwerAPI, login(_, _))
	//	.Times(1);

	kiwerDriver.login(ID, SUCCESS_PASSWORD);
}

TEST_F(TraingFixture, kiwerAPI_BUY)
{
	int price = 100;
	int num = 10;

	//EXPECT_CALL(kiwerAPI, buy(_, _, _))
	//	.Times(1);

	kiwerDriver.buy(STOCK_CODE, price, num);
}

TEST_F(TraingFixture, kiwerAPI_SELL)
{
	int price = 100;
	int num = 10;

	//EXPECT_CALL(kiwerAPI, sell(_, _, _))
	//	.Times(1);

	kiwerDriver.sell(STOCK_CODE, price, num);
}

TEST_F(TraingFixture, kiwerAPI_GET_PRICE)
{
	int except = 100;
	int actual = kiwerDriver.getCurrentPrice(STOCK_CODE);

	//EXPECT_EQ(except, actual);
}


///////////////////////////////////////////
// NemoAPI test
//////////////////////////////////////////
TEST_F(TraingFixture, NemoAPI_LOGIN)
{
	//EXPECT_CALL(kiwerAPI, login(_, _))
	//	.Times(1);

	nemoDriver.login(ID, SUCCESS_PASSWORD);
}

TEST_F(TraingFixture, NemoAPI_BUY)
{
	int price = 100;
	int num = 10;

	//EXPECT_CALL(kiwerAPI, buy(_, _, _))
	//	.Times(1);

	nemoDriver.buy(STOCK_CODE, price, num);
}

TEST_F(TraingFixture, NemoAPI_SELL)
{
	int price = 100;
	int num = 10;

	//EXPECT_CALL(kiwerAPI, sell(_, _, _))
	//	.Times(1);

	nemoDriver.sell(STOCK_CODE, price, num);
}

TEST_F(TraingFixture, NemoAPI_GET_PRICE)
{
	int except = 100;
	int actual = nemoDriver.getCurrentPrice(STOCK_CODE);

	//EXPECT_EQ(except, actual);
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
