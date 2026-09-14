#pragma once
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>
#include <cstdint>

class EventBus {
public:
    using SubscriptionId = uint32_t;

    template <typename EventType>
    SubscriptionId subscribe(std::function<void(const EventType&)> callback) {
        auto type = std::type_index(typeid(EventType));
        auto& handlers = m_subscribers[type];

        SubscriptionId id = ++m_nextSubscriptionId;
        auto wrapped = [cb = std::move(callback)](const void* eventPtr) {
            cb(*static_cast<const EventType*>(eventPtr));
        };

        handlers.push_back({id, std::move(wrapped)});
        return id;
    }

    template <typename EventType>
    void unsubscribe(SubscriptionId id) {
        auto type = std::type_index(typeid(EventType));
        auto it = m_subscribers.find(type);
        if (it != m_subscribers.end()) {
            auto& list = it->second;
            list.erase(std::remove_if(list.begin(), list.end(),
                [id](const HandlerEntry& entry) { return entry.id == id; }), list.end());
        }
    }

    template <typename EventType>
    void publish(const EventType& event) {
        auto type = std::type_index(typeid(EventType));
        auto it = m_subscribers.find(type);
        if (it != m_subscribers.end()) {
            for (const auto& entry : it->second) {
                entry.handler(&event);
            }
        }
    }

    void clear() {
        m_subscribers.clear();
    }

private:
    struct HandlerEntry {
        SubscriptionId id;
        std::function<void(const void*)> handler;
    };

    SubscriptionId m_nextSubscriptionId{0};
    std::unordered_map<std::type_index, std::vector<HandlerEntry>> m_subscribers;
};
