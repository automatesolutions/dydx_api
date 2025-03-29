#include "dydx_cli.h"
#include "config_parser.h"
#include <iostream>

int main() {
    try {
        EnvConfig config;
        DydxCli cli(
            config.get("BASE_URL"),
            config.get("TEST_ADDRESS"),
            config.getInt("SUBACCOUNT_NUMBER")
        );
        cli.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}