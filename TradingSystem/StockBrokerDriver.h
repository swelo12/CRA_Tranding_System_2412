#include <string>

// 증권사 드라이버 인터페이스
class StockBrokerDriver {
public:
    // 로그인 기능
    virtual bool login(const std::string& id, const std::string& pass) = 0;

    // 매수 기능 (종목코드, 수량, 가격)
    virtual bool buy(const std::string& stockCode, int quantity, int price) = 0;

    // 매도 기능 (종목코드, 수량, 가격)
    virtual bool sell(const std::string& stockCode, int quantity, int price) = 0;

    // 현재가 확인 기능 (종목코드)
    virtual int getCurrentPrice(const std::string& stockCode) = 0;
};