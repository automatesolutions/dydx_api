#include "dydx_cli.h"
#include <iostream>
#include <limits>

DydxCli::DydxCli(const std::string& baseUrl, const std::string& address, int subaccount)
    : client(baseUrl, address, subaccount), address(address), subaccount(subaccount) {}

void DydxCli::run() {
    while (true) {
        std::cout << "\n=== dYdX CLI ===\n";
        std::cout << "1. View Active Markets\n";
        std::cout << "2. View Account\n";
        std::cout << "3. View All Perpetual Markets\n";
        std::cout << "4. View Subaccount\n";
        std::cout << "5. View Affiliate Snapshot\n";
        std::cout << "6. View Asset Positions\n";
        std::cout << "7. View Fills\n";
        std::cout << "8. List Orders\n";
        std::cout << "9. View Perpetual Market Orderbook\n";
        std::cout << "10. Exit\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
            case 1: {
                std::vector<std::string> markets = client.getMarkets();
                if (markets.empty()) {
                    std::cout << "No active markets found.\n";
                } else {
                    std::cout << "Active Markets:\n";
                    for (const auto& market : markets) {
                        std::cout << "- " << market << "\n";
                    }
                }
                break;
            }
            case 2: {
                std::string response = client.getAccountData(address, subaccount);
                client.printResponse(response);
                break;
            }
            case 3: {
                std::vector<std::string> markets = client.getPerpetualMarkets();
                if (markets.empty()) {
                    std::cout << "No perpetual markets found.\n";
                } else {
                    std::cout << "All Perpetual Markets:\n";
                    for (const auto& market : markets) {
                        std::cout << "- " << market << "\n";
                    }
                }
                break;
            }
            case 4: {
                std::string response = client.getSubaccount(address, subaccount);
                client.printResponse(response);
                break;
            }
            case 5: {
                std::string response = client.getAffiliateSnapshot();
                client.printResponse(response);
                break;
            }
            case 6: {
                std::string response = client.getAssetPositions();
                client.printResponse(response);
                break;
            }
            case 7: {
                std::string response = client.getFills();
                client.printResponse(response);
                break;
            }
            case 8: {
                std::string response = client.listOrders();
                client.printResponse(response);
                break;
            }
            case 9: {
                std::string ticker;
                std::cout << "Enter ticker (e.g., BTC-USD): ";
                std::getline(std::cin, ticker);
                std::string response = client.getPerpetualMarketOrderbook(ticker);
                client.printResponse(response);
                break;
            }
            case 10:
                std::cout << "Exiting...\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}