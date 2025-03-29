#ifndef DYDX_CLI_H
#define DYDX_CLI_H

#include "dydx_api.h"
#include <string>

class DydxCli {
private:
    DydxApiClient client;
    std::string address;
    int subaccount;

public:
    DydxCli(const std::string& baseUrl, const std::string& address, int subaccount);
    void run();
};

#endif // DYDX_CLI_H