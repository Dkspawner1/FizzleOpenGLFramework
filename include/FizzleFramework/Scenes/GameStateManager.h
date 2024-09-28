#pragma once
#include "GameState.h"
#include <memory.h>
#include <memory>
#include <stack>
class GameStateManager {
public:
  void PushState(std::unique_ptr<GameState> state);
  void PopState();
  void ChangeState(std::unique_ptr<GameState> state);
  void Update(float deltaTime);
  void Render();

private:
  std::stack<std::unique_ptr<GameState>> m_states;
};
