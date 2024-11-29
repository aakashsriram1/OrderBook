# Orderbook Simulation

A C++ project simulating a basic **orderbook**, used in financial markets to match buy and sell orders based on price and quantity.

---

## Features

- Add, modify, and cancel buy/sell orders.
- Automatically match orders for trade execution.
- Remove expired "Good for Day" orders using threading.
- Efficient sorting and matching with `std::map`.

---

## How It Works

- **Orderbook**: Stores buy and sell orders, matches them based on price.
- **Trade Execution**: Logs trades between matched orders.
- **Concurrency**: Cleans expired orders with a background thread.

---

## Example Output

```plaintext
Adding orders...
Orderbook Levels:
Bid Price: 100, Quantity: 5
Adding a matching sell order...
Trades Executed:
Buy Order ID: 1, Sell Order ID: 3, Quantity: 5, Price: 100
