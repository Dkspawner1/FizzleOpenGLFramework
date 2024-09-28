#pragma once
#include "FizzleFramework/Core/Event.h"
#include <string>

class SceneChangedEvent : public Event {
public:
    SceneChangedEvent(const std::string& oldScene, const std::string& newScene)
        : oldSceneName(oldScene), newSceneName(newScene) {}
    std::string oldSceneName;
    std::string newSceneName;
};