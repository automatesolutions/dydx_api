#include "dydx_api.h"
#include <iostream>
#include <stdexcept>

size_t DydxApiClient::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    s->append((char*)contents, newLength);
    return newLength;
}

DydxApiClient::DydxApiClient(const std::string& baseUrl, const std::string& address, int subaccount)
    : baseUrl(baseUrl), address(address), subaccount(subaccount) {
    if (!baseUrl.empty() && baseUrl.back() != '/') {
        this->baseUrl += "/";
    }
}

std::string DydxApiClient::httpGet(const std::string& endpoint) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        std::string url = baseUrl + endpoint;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        long http_code = 0;
        CURLcode res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            throw std::runtime_error("HTTP GET failed: " + std::string(curl_easy_strerror(res)));
        }

        std::cout << "HTTP Status: " << http_code << std::endl;
        std::cout << "Raw Response: '" << response << "'" << std::endl;

        if (response.empty() && http_code != 200) {
            throw std::runtime_error("Empty response from " + url + " (HTTP " + std::to_string(http_code) + ")");
        }
    } else {
        throw std::runtime_error("CURL initialization failed");
    }
    return response;
}

std::vector<std::string> DydxApiClient::getMarkets() {
    std::string response;
    try {
        response = httpGet("perpetualMarkets");
    } catch (const std::runtime_error& e) {
        std::cout << "Error fetching markets: " << e.what() << std::endl;
        return {};
    }

    try {
        json j = json::parse(response);
        if (!j.contains("perpetualMarkets")) {
            std::cout << "Response does not contain 'perpetualMarkets' key." << std::endl;
            return {};
        }

        std::vector<std::string> activeMarkets;
        for (auto& [key, value] : j["perpetualMarkets"].items()) {
            if (value.contains("status") && value["status"] == "ACTIVE") {
                activeMarkets.push_back(value["ticker"].get<std::string>());
            }
        }
        return activeMarkets;
    } catch (const json::parse_error& e) {
        std::cout << "JSON Parse Error: " << e.what() << std::endl;
        return {};
    }
}

std::string DydxApiClient::getOrderbook(const std::string& ticker) {
    return httpGet("orderbooks/" + ticker);
}

std::string DydxApiClient::getAccountData(const std::string& address, int subaccount) {
    std::string endpoint = "addresses/" + address + "/subaccountNumber/" + std::to_string(subaccount);
    try {
        return httpGet(endpoint);
    } catch (const std::runtime_error& e) {
        std::cout << "Error fetching account data: " << e.what() << std::endl;
        return "";
    }
}

void DydxApiClient::printResponse(const std::string& response) {
    if (response.empty()) {
        std::cout << "No data to display." << std::endl;
        return;
    }
    try {
        json j = json::parse(response);
        std::cout << j.dump(4) << std::endl;
    } catch (const json::parse_error& e) {
        std::cout << "Failed to parse response as JSON: " << e.what() << std::endl;
        std::cout << "Raw response: " << response << std::endl;
    }
}

std::vector<std::string> DydxApiClient::getPerpetualMarkets() {
    std::string response;
    try {
        response = httpGet("perpetualMarkets");
    } catch (const std::runtime_error& e) {
        std::cout << "Error fetching perpetual markets: " << e.what() << std::endl;
        return {};
    }

    try {
        json j = json::parse(response);
        if (!j.contains("perpetualMarkets")) {
            std::cout << "Response does not contain 'perpetualMarkets' key." << std::endl;
            return {};
        }

        std::vector<std::string> markets;
        for (auto& [key, value] : j["perpetualMarkets"].items()) {
            markets.push_back(value["ticker"].get<std::string>());
        }
        return markets;
    } catch (const json::parse_error& e) {
        std::cout << "JSON Parse Error: " << e.what() << std::endl;
        return {};
    }
}

std::string DydxApiClient::getSubaccount(const std::string& address, int subaccountNumber) {
    std::string endpoint = "addresses/" + address + "/subaccountNumber/" + std::to_string(subaccountNumber);
    try {
        return httpGet(endpoint);
    } catch (const std::runtime_error& e) {
        std::cout << "Error fetching subaccount data: " << e.what() << std::endl;
        return "";
    }
}

std::string DydxApiClient::getAffiliateSnapshot() {
    std::cout << "Affiliate snapshot not supported in v4 testnet API.\n";
    return "";
}

std::string DydxApiClient::getAssetPositions() {
    std::string endpoint = "assetPositions?address=" + this->address + "&subaccountNumber=" + std::to_string(this->subaccount);
    try {
        return httpGet(endpoint);
    } catch (const std::runtime_error& e) {
        std::cout << "Error fetching asset positions: " << e.what() << std::endl;
        return "";
    }
}

std::string DydxApiClient::getFills() {
    std::string endpoint = "fills?address=" + this->address + "&subaccountNumber=" + std::to_string(this->subaccount);
    try {
        return httpGet(endpoint);
    } catch (const std::runtime_error& e) {
        std::cout << "Error fetching fills: " << e.what() << std::endl;
        return "";
    }
}

std::string DydxApiClient::listOrders() {
    std::string endpoint = "orders?address=" + this->address + "&subaccountNumber=" + std::to_string(this->subaccount);
    try {
        return httpGet(endpoint);
    } catch (const std::runtime_error& e) {
        std::cout << "Error fetching orders: " << e.what() << std::endl;
        return "";
    }
}

std::string DydxApiClient::getPerpetualMarketOrderbook(const std::string& ticker) {
    return httpGet("orderbooks/" + ticker);
}