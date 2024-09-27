#pragma once
#include "Scene.h"
#include "../Core/EventSystem.h"
#include <memory>
#include <unordered_map>
#include <string>

class SceneManager
{
public:
    SceneManager(EventSystem& eventSystem);
    void AddScene(const std::string& name, std::unique_ptr<Scene> scene);
    void RemoveScene(const std::string& name);
    void SetActiveScene(const std::string& name);
    Scene* GetActiveScene();
    void Update(float deltaTime);
    void Render();

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
    Scene* activeScene = nullptr;
    std::string activeSceneName;
    EventSystem& m_eventSystem;
};
