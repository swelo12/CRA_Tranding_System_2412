#include "gmock/gmock.h"
#include "nemo_api.cpp"
#include "kiwer_api.cpp"
#include "mock_driver.cpp"
#include "stock_broker_driver.h"

using namespace testing;

class TraingFixture : public Test {
public:
	MockStockAPI mockStockAPI;
	MockDriver mockDriver{ &mockStockAPI };

	std::string ID = "1234";
	std::string SUCCESS_PASSWORD = "1234";
	std::string STOCK_CODE = "code";

	//AutoTradingSystem* autoTradingSystem; // need to  inheritance
	int money = 100;

private:
	void SetUp() override {
		// nothing;
	}
};

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

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
