#include "Orderbook.h"
#include "Order.h"
#include <iostream>
#include <memory>
#include <sstream>

int main() {
    Orderbook orderbook;

    // Create orders
    auto buyOrder1 = std::make_shared<Order>(OrderType::GoodForDay, 1, Side::Buy, 100.50, 10);
    auto sellOrder1 = std::make_shared<Order>(OrderType::GoodForDay, 2, Side::Sell, 100.25, 5);

    // Add orders to the orderbook
    std::cout << "Adding orders..." << std::endl;
    orderbook.AddOrder(buyOrder1);
    orderbook.AddOrder(sellOrder1);

    // Display the orderbook levels
    auto orderInfos = orderbook.GetOrderInfos();
    std::cout << "Orderbook Levels:" << std::endl;
    for (const auto& level : orderInfos.GetBids()) {
        std::cout << "Bid Price: " << level.price_ << ", Quantity: " << level.quantity_ << std::endl;
    }
    for (const auto& level : orderInfos.GetAsks()) {
        std::cout << "Ask Price: " << level.price_ << ", Quantity: " << level.quantity_ << std::endl;
    }

    // Add a matching sell order
    auto sellOrder2 = std::make_shared<Order>(OrderType::GoodForDay, 3, Side::Sell, 100.50, 8);
    std::cout << "Adding a matching sell order..." << std::endl;
    auto trades = orderbook.AddOrder(sellOrder2);

    // Display executed trades
    std::cout << "Trades Executed:" << std::endl;
    for (const auto& trade : trades) {
        const auto& bidTrade = trade.GetBidTrade();
        const auto& askTrade = trade.GetAskTrade();
        std::cout << "Buy Order ID: " << bidTrade.orderId_
                  << ", Sell Order ID: " << askTrade.orderId_
                  << ", Quantity: " << bidTrade.quantity_
                  << ", Price: " << bidTrade.price_ << std::endl;
    }

    return 0;
}
