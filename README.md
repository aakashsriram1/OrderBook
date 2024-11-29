#Orderbook Simulation
A C++ project simulating a basic orderbook, used in financial markets to match buy and sell orders based on price and quantity.

#Features
Add, modify, and cancel orders.
Match buy and sell orders for trade execution.
Automatically remove expired orders using threading.
Efficient use of std::map for order sorting and matching.

#How It Works
Orderbook: Manages buy/sell orders and matches them based on price.
Trade Execution: Logs trades between matched orders.
Concurrency: Uses threading to remove expired orders.
