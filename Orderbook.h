#pragma once

#include <map>
#include <unordered_map>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic> // Ensure atomic is included

#include "Usings.h"
#include "Order.h"
#include "OrderModify.h"
#include "OrderbookLevelInfos.h"
#include "Trade.h"

class Orderbook
{
private:

    struct OrderEntry
    {
        OrderPointer order_{ nullptr };
        OrderPointers::iterator location_;
    };

    struct LevelData
    {
        Quantity quantity_{ };
        Quantity count_{ };

        enum class Action
        {
            Add,
            Remove,
            Match,
        };
    };

    // Data members
    std::unordered_map<Price, LevelData> data_;
    std::map<Price, OrderPointers, std::greater<Price>> bids_; // Buy side
    std::map<Price, OrderPointers, std::less<Price>> asks_;    // Sell side
    std::unordered_map<OrderId, OrderEntry> orders_; // All orders
    mutable std::mutex ordersMutex_; // Mutex for thread safety
    std::thread ordersPruneThread_; // Background pruning thread
    std::condition_variable shutdownConditionVariable_; // Shutdown signal
    std::atomic<bool> shutdown_{ false }; // Atomic flag for shutdown

    // Private helper methods
    void PruneGoodForDayOrders();

    void CancelOrders(OrderIds orderIds);
    void CancelOrderInternal(OrderId orderId);

    void OnOrderCancelled(OrderPointer order);
    void OnOrderAdded(OrderPointer order);
    void OnOrderMatched(Price price, Quantity quantity, bool isFullyFilled);
    void UpdateLevelData(Price price, Quantity quantity, LevelData::Action action);

    bool CanFullyFill(Side side, Price price, Quantity quantity) const;
    bool CanMatch(Side side, Price price) const;
    Trades MatchOrders();

public:

    // Constructor and Destructor
    Orderbook();
    ~Orderbook();

    // Deleted constructors and assignment operators
    Orderbook(const Orderbook&) = delete;
    void operator=(const Orderbook&) = delete;
    Orderbook(Orderbook&&) = delete;
    void operator=(Orderbook&&) = delete;

    // Public methods
    Trades AddOrder(OrderPointer order);
    void CancelOrder(OrderId orderId);
    Trades ModifyOrder(OrderModify order);

    std::size_t Size() const;
    OrderbookLevelInfos GetOrderInfos() const;
};
