#include "gmock/gmock.h"
#include "nemo_api.cpp"
#include "kiwer_api.cpp"

using namespace testing;

class TraingFixture {
public:
	StockerBrockerDriverInterface sbdInterface;
	std::string ID = "1234";
	std::string SUCCESS_PASSWORD = "1234";
	std::string stockCode = "code";

private:

};

TEST_F(TraingFixture, TEST_LOGIN)
{
	sbdInterface.login(ID, SUCCESS_PASSWORD);

	EXPECT_CALL(StockerBrockerDriverInterface, login(_,_))
		.call(1);
}

TEST_F(TraingFixture, TEST_BUY)
{
	int price = 100;
	int num = 10;

	sbdInterface.buy(stockCode, price, num);

	EXPECT_CALL(StockerBrockerDriverInterface, buy(_,_, _))
		.call(1);
}

TEST_F(TraingFixture, TEST_SELL)
{
	int price = 100;
	int num = 10;

	sbdInterface.sell(stockCode, price, num);

	EXPECT_CALL(StockerBrockerDriverInterface, sell(_, _, _))
		.call(1);
}

TEST_F(TraingFixture, TEST_GET_PRICE)
{
	int except = 100;
	int actual = sbdInterface.getPrice(stockCode);

	EXPECT_EQ(except, actual);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
