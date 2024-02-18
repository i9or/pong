#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Window.h"

class Game {
public:
  Game();
  ~Game();

  void handleInput();
  void update();
  void render();
  bool isDone() const;
  sf::Time getElapsed() const;
  void restartClock();

private:
  void moveBall();

  Window m_window;

  sf::Texture m_ballTexture;
  sf::Sprite m_ballSprite;
  sf::Vector2f m_ballSize;
  sf::Vector2f m_ballPosition;
  sf::Vector2f m_ballDirection;

  sf::Clock m_clock;
  sf::Time m_elapsed;

  static constexpr float FRAME_TIME = 1.0f / 60.f;
  static constexpr float WINDOW_WIDTH = 1024.f;
  static constexpr float WINDOW_HEIGHT = 768.f;
};
