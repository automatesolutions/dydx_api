#ifndef DYDX_API_H
#define DYDX_API_H

#include <string>
#include <vector>
#include <cstddef>
#include <nlohmann/json.hpp>
#include <curl/curl.h>

using json = nlohmann::json;

class DydxApiClient {
private:
    std::string baseUrl;
    std::string address;  // Stores the address for the instance
    int subaccount;       // Stores the subaccount number for the instance

public:
    DydxApiClient(const std::string& baseUrl, const std::string& address = "", int subaccount = 0);
    

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
    std::string httpGet(const std::string& endpoint);
    std::vector<std::string> getMarkets();
    std::string getOrderbook(const std::string& ticker);
    std::string getAccountData(const std::string& address, int subaccount);
    void printResponse(const std::string& response);
    std::vector<std::string> getPerpetualMarkets();
    std::string getSubaccount(const std::string& address, int subaccountNumber);
    std::string getAffiliateSnapshot();
    std::string getAssetPositions();
    std::string getFills();
    std::string listOrders();
    std::string getPerpetualMarketOrderbook(const std::string& ticker);
};

#endif // DYDX_API_H