#include "gmock/gmock.h"
#include "nemo_api.cpp"
#include "kiwer_api.cpp"
#include "mock_driver.cpp"
#include "auto_trading_system.h"

using namespace testing;

class TraingFixture : public Test{
public:
	std::string ID = "1234";
	std::string SUCCESS_PASSWORD = "1234";
	std::string STOCK_CODE = "code";

	AutoTradingSystem* autoTradingSystem; // need to  inheritance
	int money = 100;

	MockStockAPI mockStockAPI;
	MockDriver* mockDriver = new MockDriver(&mockStockAPI);
private:
	void SetUp() override {
		// nothing;
	}
};

/* 1. StockerBrockerDriverInterface Mock Test*/
TEST_F(TraingFixture, TEST_LOGIN)
{
	EXPECT_CALL(mockStockAPI, login(_, _))
		.call(1);

	mockDriver->login(ID, SUCCESS_PASSWORD);
}

TEST_F(TraingFixture, TEST_BUY)
{
	int price = 100;
	int num = 10;

	EXPECT_CALL(mockStockAPI, buy(_, _, _))
		.call(1);

	mockDriver->buy(STOCK_CODE, price, num);
}

TEST_F(TraingFixture, TEST_SELL)
{
	int price = 100;
	int num = 10;

	EXPECT_CALL(mockStockAPI, sell(_, _, _))
		.call(1);

	mockDriver->sell(STOCK_CODE, price, num);
}

TEST_F(TraingFixture, TEST_GET_PRICE)
{
	int except = 100;
	int actual = mockDriver->getPrice(STOCK_CODE);

	EXPECT_EQ(except, actual);
}

/* 2. Auto trading Test*/
TEST_F(TraingFixture, TEST_buyNiceTiming__Buy_success)
{
	autoTradingSystem = new AutoTradingSystem(mockInterface); // inherit mock.
	std::vector<int> price = { 12,20,30 }

	EXPECT_CALL(mockInterface, getPrice(_))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]))
		.WillOnce(Return(price[2]));
		.WillRepeatedly(Return(price[2]));

	int buy = autoTradingSystem->buyNiceTiming(STOCK_CODE, money);
	EXPECT_EQ(money/ price[2], buy);
}

TEST_F(TraingFixture, TEST_buyNiceTiming__Buy_fail)
{
	autoTradingSystem = new AutoTradingSystem(mockInterface); // inherit mock.
	std::vector<int> price = { 40,20,30 }

	EXPECT_CALL(mockInterface, getPrice(_))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]))
		.WillOnce(Return(price[2]));
		.WillRepeatedly(Return(price[2]));

	int buy = autoTradingSystem->buyNiceTiming(STOCK_CODE, money);
	EXPECT_EQ(0, success);
}

TEST_F(TraingFixture, TEST_sellNiceTiming__Buy_success)
{
	autoTradingSystem = new AutoTradingSystem(mockInterface); // inherit mock.
	std::vector<int> price = { 12,20,30 }

	EXPECT_CALL(mockInterface, getPrice(_))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]))
		.WillOnce(Return(price[2]));
		.WillRepeatedly(Return(price[2]));

	int cellCount = 3;
	bool success = autoTradingSystem->sellNiceTiming(STOCK_CODE, cellCount);

	EXPECT_EQ(true, success);
}

TEST_F(TraingFixture, TEST_sellNiceTiming__Buy_fail)
{
	autoTradingSystem = new AutoTradingSystem(mockInterface); // inherit mock.
	std::vector<int> price = { 40,20,30 }

	EXPECT_CALL(mockInterface, getPrice(_))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]))
		.WillOnce(Return(price[2]));
		.WillRepeatedly(Return(price[2]));

	int cellCount = 3;
	bool success = autoTradingSystem->sellNiceTiming(STOCK_CODE, price[2]);

	EXPECT_EQ(false, success);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
