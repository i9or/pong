#include <iostream>

#include "Game.h"

Game::Game()
    : m_window("Pong", sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)),
      m_ballPosition({100.f, 100.f}),
      m_ballDirection({1.f, 1.f}) {
  if (!m_ballTexture.loadFromFile("../assets/ball.png")) {
    std::cout << "Failed to load textures" << std::endl;
  }

  m_ballTexture.setSmooth(true);
  auto textureSize = m_ballTexture.getSize();
  auto ballTextureWidth = static_cast<float>(textureSize.x);
  auto ballTextureHeight = static_cast<float>(textureSize.y);

  m_ballSprite.setTexture(m_ballTexture);
  m_ballSprite.setOrigin(ballTextureWidth / 2.f,
                         ballTextureHeight / 2.f);

  m_ballSprite.setScale(0.25f, 0.25f);
  m_ballSprite.setPosition(m_ballPosition);

  m_ballSize = {ballTextureWidth * m_ballSprite.getScale().x,
                ballTextureHeight * m_ballSprite.getScale().y};
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
}

void Game::render() {
  m_window.beginDraw();

  m_window.draw(m_ballSprite);

  m_window.endDraw();
}

void Game::restartClock() {
  m_elapsed += m_clock.restart();
}

sf::Time Game::getElapsed() const {
  return m_elapsed;
}

void Game::handleInput() {
  // TODO: add input processing here
}

bool Game::isDone() const {
  return m_window.isDone();
}
