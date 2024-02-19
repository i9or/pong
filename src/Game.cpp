#include <iostream>

#include "Game.h"

Game::Game()
    : m_window("Pong", sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)),
      m_ballVelocity({400.f, 400.f}) {
  if (!m_ballTexture.loadFromFile("../assets/ball.png")) {
    std::cout << "Failed to load textures" << std::endl;
  }

  m_ballTexture.setSmooth(true);

  auto textureSize = m_ballTexture.getSize();
  m_ballSprite.setTexture(m_ballTexture);
  m_ballSprite.setOrigin(static_cast<float>(textureSize.x) / 2.f,
                         static_cast<float>(textureSize.y) / 2.f);

  m_ballSprite.setScale(0.25f, 0.25f);
  m_ballSprite.setPosition(100.f, 100.f);
}

Game::~Game() = default;

void Game::update() {
  m_window.update();

  if (m_elapsed.asSeconds() >= FRAME_TIME) {
    moveBall();

    m_elapsed -= sf::seconds(FRAME_TIME);
  }
}

void Game::moveBall() {
  auto ballSize = getBallSpriteSize();
  auto ballPosition = m_ballSprite.getPosition();

  if (ballPosition.x > (WINDOW_WIDTH - ballSize.x / 2.f) ||
      ballPosition.x < ballSize.x / 2.f) {
    m_ballVelocity.x *= -1.f;
  }

  if (ballPosition.y > (WINDOW_HEIGHT - ballSize.y / 2.f) ||
      ballPosition.y < ballSize.y / 2.f) {
    m_ballVelocity.y *= -1.f;
  }

  m_ballSprite.setPosition(m_ballSprite.getPosition() + m_ballVelocity * m_elapsed.asSeconds());
}

void Game::render() {
  m_window.beginDraw();

  m_window.draw(m_ballSprite);

  m_window.endDraw();
}

void Game::restartClock() {
  m_elapsed += m_clock.restart();
}

void Game::handleInput() {
  // TODO: add input processing here
}

bool Game::isDone() const {
  return m_window.isDone();
}

sf::Vector2f Game::getBallSpriteSize() {
  auto size = m_ballSprite.getTexture()->getSize();
  auto width = static_cast<float>(size.x);
  auto height = static_cast<float>(size.y);

  return {width * m_ballSprite.getScale().x,
          height * m_ballSprite.getScale().y};
}
