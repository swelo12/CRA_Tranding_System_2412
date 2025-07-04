#include <string>

// ���ǻ� ����̹� �������̽�
class StockBrokerDriver {
public:
    // �α��� ���
    virtual bool login(const std::string& id, const std::string& pass) = 0;

    // �ż� ��� (�����ڵ�, ����, ����)
    virtual bool buy(const std::string& stockCode, int quantity, int price) = 0;

    // �ŵ� ��� (�����ڵ�, ����, ����)
    virtual bool sell(const std::string& stockCode, int quantity, int price) = 0;

    // ���簡 Ȯ�� ��� (�����ڵ�)
    virtual int getCurrentPrice(const std::string& stockCode) = 0;
};