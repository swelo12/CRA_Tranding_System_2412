#include <string>

class StockBrokerDriver {
public:
    virtual bool login(const std::string& id, const std::string& pass) = 0;
    virtual bool buy(const std::string& stockCode, int quantity, int price) = 0;
    virtual bool sell(const std::string& stockCode, int quantity, int price) = 0;
    virtual int getCurrentPrice(const std::string& stockCode) = 0;
};