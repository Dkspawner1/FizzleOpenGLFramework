#include "SceneManager.h"
#include "Scene.h"
#include <memory>
#include <string>
#include <utility>

class SceneChangedEvent : public Event {
public:
    SceneChangedEvent(const std::string& oldScene, const std::string& newScene)
        : oldSceneName(oldScene), newSceneName(newScene) {}
    std::string oldSceneName;
    std::string newSceneName;
};

SceneManager::SceneManager(EventSystem& eventSystem) : m_eventSystem(eventSystem) {}

void SceneManager::AddScene(const std::string& name, std::unique_ptr<Scene> scene) {
    m_scenes[name] = std::move(scene);
}

void SceneManager::RemoveScene(const std::string& name) {
    m_scenes.erase(name);
}

void SceneManager::SetActiveScene(const std::string& name) {
    if (activeScene) {
        activeScene->OnExit();
    }
    std::string oldSceneName = activeSceneName;
    activeScene = m_scenes[name].get();
    activeSceneName = name;
    activeScene->OnEnter();

    // Dispatch the scene changed event
    m_eventSystem.queueEvent(SceneChangedEvent(oldSceneName, name));
}

Scene* SceneManager::GetActiveScene() {
    return activeScene;
}

void SceneManager::Update(float deltaTime) {
    if (activeScene) {
        activeScene->Update(deltaTime);
    }
}

void SceneManager::Render() {
    if (activeScene) {
        activeScene->Render();
    }
}
