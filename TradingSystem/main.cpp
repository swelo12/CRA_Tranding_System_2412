#include "gmock/gmock.h"
#include "nemo_api.cpp"
#include "kiwer_api.cpp"

using namespace testing;

class TraingFixture {
public:
	StockerBrockerDriverInterface mockInterface;
	std::string ID = "1234";
	std::string SUCCESS_PASSWORD = "1234";
	std::string STOCK_CODE = "code";

	AutoTradingSystem* autoTradingSystem; // need to  inheritance

private:

};

/* 1. StockerBrockerDriverInterface Mock Test*/
TEST_F(TraingFixture, TEST_LOGIN)
{
	mockInterface.login(ID, SUCCESS_PASSWORD);

	EXPECT_CALL(StockerBrockerDriverInterface, login(_,_))
		.call(1);
}

TEST_F(TraingFixture, TEST_BUY)
{
	int price = 100;
	int num = 10;

	mockInterface.buy(STOCK_CODE, price, num);

	EXPECT_CALL(StockerBrockerDriverInterface, buy(_,_, _))
		.call(1);
}

TEST_F(TraingFixture, TEST_SELL)
{
	int price = 100;
	int num = 10;

	mockInterface.sell(STOCK_CODE, price, num);

	EXPECT_CALL(StockerBrockerDriverInterface, sell(_, _, _))
		.call(1);
}

TEST_F(TraingFixture, TEST_GET_PRICE)
{
	int except = 100;
	int actual = mockInterface.getPrice(STOCK_CODE);

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

	bool success = autoTradingSystem->buyNiceTiming(STOCK_CODE, price[2]);

	EXPECT_EQ(true, success);
}

TEST_F(TraingFixture, TEST_buyNiceTiming__Buy_fail)
{
	autoTradingSystem = new AutoTradingSystem(mockInterface); // inherit mock.
	std::vector<int> price = { 40,20,30 }

		EXPECT_CALL(mockInterface, getPrice(_))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]))
		.WillOnce(Return(price[2]));

	bool success = autoTradingSystem->buyNiceTiming(STOCK_CODE, price[2]);

	EXPECT_EQ(false, success);
}

TEST_F(TraingFixture, TEST_sellNiceTiming__Buy_success)
{
	autoTradingSystem = new AutoTradingSystem(mockInterface); // inherit mock.
	std::vector<int> price = { 12,20,30 }

		EXPECT_CALL(mockInterface, getPrice(_))
		.WillOnce(Return(price[0]))
		.WillOnce(Return(price[1]))
		.WillOnce(Return(price[2]));

	bool success = autoTradingSystem->sellNiceTiming(STOCK_CODE, price[2]);

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

	bool success = autoTradingSystem->sellNiceTiming(STOCK_CODE, price[2]);

	EXPECT_EQ(false, success);
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
