# dYdX v4 Testnet CLI Client in Rest API

A C++ command-line interface (CLI) for interacting with the dYdX v4 testnet API. Fetch market data, account details, asset positions, and more from the testnet indexer.

## Dependencies

To build and run this client, install the following on your Linux system (e.g., Ubuntu):

### 1. GCC/G++ Compiler
**Purpose:** Compiles C++ code.  
**Install:**
```bash
sudo apt update
sudo apt install build-essential
```


### 2. libcurl
**Purpose:** Makes HTTP requests to the dYdX API.  
**Install:**
```bash
sudo apt install libcurl4-openssl-dev
```

### 3. nlohmann/json
**Purpose:** Parses JSON responses.  

**Install (system-wide):**
```bash
sudo apt install nlohmann-json3-dev
```
## Project Structure

Place all files in a single directory, e.g.:
`~/v4-clients/v4-client-py-v2/examples/dydx_api/`

**Directory Contents:**

| File             | Description                          |
|------------------|--------------------------------------|
| `dydx_api.h`     | API client header                    |
| `dydx_api.cpp`   | API client implementation            |
| `dydx_cli.h`     | CLI header                           |
| `dydx_cli.cpp`   | CLI implementation                   |
| `main.cpp`       | Entry point                          |
| `config_parser.h`| .env parser (assumed provided)       |
| `.env`           | Configuration file                   |
| `compile.sh`     | Build script                         |

## 4. Configure `.env`

Create a `.env` file with the following content:

```bash
BASE_URL=https://indexer.v4testnet.dydx.exchange/v4
TEST_ADDRESS=dydx1m5v0gr5z0ct9uef0c30kxzqzxhad8j848znsgn
SUBACCOUNT_NUMBER=0
```

## 5. How to Compile

Compile the project to create the `dydx_cli` executable:
### Run the Build Script

```bash
./compile.sh
```
What the build script does:
Removes old object files and previous executable: rm -f *.o dydx_cli
Compiles each .cpp file into object files (using C++17 standard): g++ -std=c++17 -I. -c
Links object files with libcurl: -lcurl → produces dydx_cli
Sets executable permissions: chmod +x dydx_cli

### Verify Compilation
Check for the executable:

```bash
ls -l dydx_cli
./dydx_cli
```

## 6. How to Run
Run the compiled CLI to interact with the dYdX v4 testnet:

Execute the CLI
```bash
./dydx_cli
```
### Use the Interface

=== dYdX CLI ===
1. View Active Markets
2. View Account
3. View All Perpetual Markets
4. View Subaccount
5. View Affiliate Snapshot
6. View Asset Positions
7. View Fills
8. List Orders
9. View Perpetual Market Orderbook
10. Exit

Choice:
Enter a number (1-10):


1: Lists active markets.
2: Shows account data for TEST_ADDRESS and SUBACCOUNT_NUMBER.
3: Lists all perpetual markets.
4: Shows subaccount details.
5: Not supported (prints a message).
6: Shows asset positions.
7: Lists fills.
8: Lists orders.
9: Prompts for a ticker (e.g., BTC-USD) and shows the orderbook.
10: Exits the CLI.
Example Usage
View active markets:

Choice: 1
Active Markets:
- BTC-USD
- ETH-USD
View orderbook for BTC-USD:

Choice: 9
Enter ticker (e.g., BTC-USD): BTC-USD
```bash
HTTP Status: 200
Raw Response: '{...}'
{
    "bids": [...],
    "asks": [...]
}
```

