#pragma once
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "Event.h"

class EventSystem {
public:
    template<typename EventType>
    void addHandler(std::function<void(const EventType&)> handler) {
        static_assert(std::is_base_of<Event, EventType>::value, "EventType must derive from Event");
        std::lock_guard<std::mutex> lock(mutex);
        handlers[typeid(EventType)].push_back(
            [handler](const Event* event) {
                handler(*static_cast<const EventType*>(event));
            }
        );
    }

    template<typename EventType>
    void dispatchEvent(const EventType& event) {
        static_assert(std::is_base_of<Event, EventType>::value, "EventType must derive from Event");
        std::lock_guard<std::mutex> lock(mutex);
        auto it = handlers.find(typeid(EventType));
        if (it != handlers.end()) {
            for (const auto& handler : it->second) {
                handler(&event);
            }
        }
    }

    template<typename EventType>
    void queueEvent(EventType&& event) {
        static_assert(std::is_base_of<Event, EventType>::value, "EventType must derive from Event");
        std::lock_guard<std::mutex> lock(mutex);
        eventQueue.emplace_back(std::make_unique<EventType>(std::forward<EventType>(event)));
        cv.notify_one();
    }

    void processEvents() {
        std::vector<std::unique_ptr<Event>> localQueue;
        {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this] { return !eventQueue.empty(); });
            localQueue.swap(eventQueue);
        }
        for (const auto& event : localQueue) {
            auto it = handlers.find(typeid(*event));
            if (it != handlers.end()) {
                for (const auto& handler : it->second) {
                    handler(event.get());
                }
            }
        }
    }

private:
    std::unordered_map<std::type_index, std::vector<std::function<void(const Event*)>>> handlers;
    std::vector<std::unique_ptr<Event>> eventQueue;
    std::mutex mutex;
    std::condition_variable cv;
};
