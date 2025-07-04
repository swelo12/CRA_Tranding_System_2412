#include "gmock/gmock.h"
#include "nemo_api.cpp"
#include "kiwer_api.cpp"
#include "mock_driver.cpp"

using namespace testing;

class TraingFixture : public Test{
public:
	StockerBrockerDriverInterface mockInterface;
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
	mockDriver->login(ID, SUCCESS_PASSWORD);

	EXPECT_CALL(StockerBrockerDriverInterface, login(_,_))
		.call(1);
}

TEST_F(TraingFixture, TEST_BUY)
{
	int price = 100;
	int num = 10;

	mockDriver->buy(STOCK_CODE, price, num);

	EXPECT_CALL(StockerBrockerDriverInterface, buy(_,_, _))
		.call(1);
}

TEST_F(TraingFixture, TEST_SELL)
{
	int price = 100;
	int num = 10;

	mockDriver->sell(STOCK_CODE, price, num);

	EXPECT_CALL(StockerBrockerDriverInterface, sell(_, _, _))
		.call(1);
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
	int sellMoney = autoTradingSystem->sellNiceTiming(STOCK_CODE, cellCount);

	EXPECT_EQ(cellCount * price[2], sellMoney);
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
	int sellMoney = autoTradingSystem->sellNiceTiming(STOCK_CODE, price[2]);

	EXPECT_EQ(0, sellMoney);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
