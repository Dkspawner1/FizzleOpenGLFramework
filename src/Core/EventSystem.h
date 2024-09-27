#pragma once

#include "Event.h"
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <functional>
#include <memory>
#include <mutex>

class EventSystem {
public:
    template<typename T>
    void addHandler(std::function<void(const T&)> handler) {
        handlers[typeid(T)].push_back([handler](const Event* e) {
            handler(*static_cast<const T*>(e));
        });
    }

    template<typename T>
    void emitEvent(const T& event) {
        std::lock_guard<std::mutex> lock(mutex);
        eventQueue.push_back(std::make_unique<T>(event));
    }

    void processEvents() {
        std::vector<std::unique_ptr<Event>> localQueue;
        {
            std::lock_guard<std::mutex> lock(mutex);
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
};