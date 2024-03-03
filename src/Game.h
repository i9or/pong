#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Window.h"

enum class Turn { Left,
                  Right };

class Game {
public:
  Game();
  ~Game() = default;

  void handleInput();
  void update();
  void render();
  bool isDone() const;
  void restartClock();

private:
  void moveBall();
  static void movePaddle(sf::Sprite &paddle, float direction);

  Window m_window;

  sf::Texture m_ballTexture;
  sf::Sprite m_ballSprite;
  sf::Vector2f m_ballVelocity;

  static sf::Vector2f getSpriteSize(const sf::Sprite &sprite);
  static sf::Vector2f getSpriteOrigin(const sf::Texture &texture);

  sf::Texture m_paddleLeftTexture;
  sf::Sprite m_paddleLeftSprite;
  float m_paddleLeftMoveDirection;

  sf::Texture m_paddleRightTexture;
  sf::Sprite m_paddleRightSprite;
  float m_paddleRightMoveDirection;

  sf::Texture m_dividerTexture;
  sf::Sprite m_dividerSprite;

  sf::Clock m_clock;
  sf::Time m_elapsed;

  sf::SoundBuffer m_ballWallSoundBuffer;
  sf::SoundBuffer m_leftPaddleSoundBuffer;
  sf::SoundBuffer m_rightPaddleSoundBuffer;

  sf::Sound m_ballSound;
  sf::Sound m_leftPaddleSound;
  sf::Sound m_rightPaddleSound;

  unsigned int m_leftPoints;
  unsigned int m_rightPoints;
  void displayPoints();
  void leftScores();
  void rightScores();

  void resetGame(Turn turn);

  static sf::Vector2f getClosestPointOnPaddle(const sf::Sprite &paddle, const sf::Vector2f &point);

  static constexpr float FRAME_TIME{1.0f / 60.f};
  static constexpr float WINDOW_WIDTH{1366.f};
  static constexpr float WINDOW_HEIGHT{768.f};
  static constexpr float PADDLE_VELOCITY{15.f};
  static constexpr float PADDLE_OFFSET{35.f};
};
