#include <iostream>

#include "Game.h"

Game::Game()
    : m_window("Pong", sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)),
      m_ballVelocity({400.f, 400.f}),
      m_paddleLeftMoveDirection(0.f),
      m_paddleRightMoveDirection(0.f) {
  if (!m_ballTexture.loadFromFile("../assets/ball.png") ||
      !m_paddleLeftTexture.loadFromFile("../assets/paddle_left.png") ||
      !m_paddleRightTexture.loadFromFile("../assets/paddle_right.png") ||
      !m_dividerTexture.loadFromFile("../assets/divider.png")) {
    throw std::runtime_error("Failed to load textures");
  }

  m_ballTexture.setSmooth(true);
  m_paddleLeftTexture.setSmooth(true);
  m_paddleRightTexture.setSmooth(true);
  m_dividerTexture.setSmooth(true);

  m_ballSprite.setTexture(m_ballTexture);
  m_ballSprite.setOrigin(getSpriteOrigin(m_ballTexture));
  m_ballSprite.setScale(0.25f, 0.25f);
  m_ballSprite.setPosition(100.f, 100.f);

  auto paddleHeight = WINDOW_HEIGHT / 7.f;

  m_paddleLeftSprite.setTexture(m_paddleLeftTexture);
  m_paddleLeftSprite.setOrigin(getSpriteOrigin(m_paddleLeftTexture));
  auto leftPaddScaleFactor = paddleHeight / static_cast<float>(m_paddleLeftTexture.getSize().y);
  m_paddleLeftSprite.setScale(leftPaddScaleFactor, leftPaddScaleFactor);
  m_paddleLeftSprite.setPosition(getSpriteSize(m_paddleLeftSprite).x / 2.f + 10.f, WINDOW_HEIGHT / 2.f);

  m_paddleRightSprite.setTexture(m_paddleRightTexture);
  m_paddleRightSprite.setOrigin(getSpriteOrigin(m_paddleRightTexture));
  auto rightPaddleScaleFactor = paddleHeight / static_cast<float>(m_paddleRightTexture.getSize().y);
  m_paddleRightSprite.setScale(rightPaddleScaleFactor, rightPaddleScaleFactor);
  m_paddleRightSprite.setPosition(WINDOW_WIDTH - getSpriteSize(m_paddleRightSprite).x / 2.f - 10.f, WINDOW_HEIGHT / 2.f);

  m_dividerSprite.setTexture(m_dividerTexture);
  m_dividerSprite.setOrigin(getSpriteOrigin(m_dividerTexture));
  auto dividerRatio = WINDOW_HEIGHT / static_cast<float>(m_dividerTexture.getSize().y);
  m_dividerSprite.setScale(dividerRatio, dividerRatio);
  m_dividerSprite.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);

  if (!m_ballWallSoundBuffer.loadFromFile("../assets/ball_wall.mp3") ||
      !m_leftPaddleSoundBuffer.loadFromFile("../assets/paddle_left.mp3") ||
      !m_rightPaddleSoundBuffer.loadFromFile("../assets/paddle_right.mp3")) {
    throw std::runtime_error("Failed to load sounds");
  }

  m_ballSound.setBuffer(m_ballWallSoundBuffer);
  m_leftPaddleSound.setBuffer(m_leftPaddleSoundBuffer);
  m_rightPaddleSound.setBuffer(m_rightPaddleSoundBuffer);
}

void Game::update() {
  m_window.update();

  if (m_elapsed.asSeconds() >= FRAME_TIME) {
    movePaddle(m_paddleLeftSprite, m_paddleLeftMoveDirection);
    movePaddle(m_paddleRightSprite, m_paddleRightMoveDirection);
    moveBall();

    m_elapsed -= sf::seconds(FRAME_TIME);
  }
}

void Game::movePaddle(sf::Sprite &paddle, float direction) {
  paddle.move(0.f, direction * PADDLE_VELOCITY);

  const auto paddleHeight = getSpriteSize(paddle).y;
  const auto paddlePosition = paddle.getPosition();

  if (paddlePosition.y - paddleHeight / 2.f <= 0.f) {
    paddle.setPosition(paddlePosition.x, paddleHeight / 2.f);
  }

  if (paddlePosition.y + paddleHeight / 2.f >= WINDOW_HEIGHT) {
    paddle.setPosition(paddlePosition.x, WINDOW_HEIGHT - paddleHeight / 2.f);
  }
}

void Game::moveBall() {
  const auto ballSize = getSpriteSize(m_ballSprite);
  const auto ballPosition = m_ballSprite.getPosition();

  if (ballPosition.x > WINDOW_WIDTH - ballSize.x / 2.f ||
      ballPosition.x < ballSize.x / 2.f) {
    m_ballVelocity.x *= -1.f;
    m_ballSound.play();
  }

  if (ballPosition.y > WINDOW_HEIGHT - ballSize.y / 2.f ||
      ballPosition.y < ballSize.y / 2.f) {
    m_ballVelocity.y *= -1.f;
    m_ballSound.play();
  }

  m_ballSprite.setPosition(m_ballSprite.getPosition() + m_ballVelocity * m_elapsed.asSeconds());
}

void Game::render() {
  // ================= DEBUG =================
  float x1 = m_paddleLeftSprite.getPosition().x + getSpriteSize(m_paddleLeftSprite).x / 2.f;
  float y1 = m_paddleLeftSprite.getPosition().y - getSpriteSize(m_paddleLeftSprite).y / 2.f;
  float x2 = x1;
  float y2 = m_paddleLeftSprite.getPosition().y + getSpriteSize(m_paddleLeftSprite).y / 2.f;

  sf::Vertex leftPaddleSurface[] = {sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Red),
                                    sf::Vertex(sf::Vector2f(x2, y2), sf::Color::Red)};

  float x3 = m_paddleRightSprite.getPosition().x - getSpriteSize(m_paddleRightSprite).x / 2.f;
  float y3 = m_paddleRightSprite.getPosition().y - getSpriteSize(m_paddleRightSprite).y / 2.f;
  float x4 = x3;
  float y4 = m_paddleRightSprite.getPosition().y + getSpriteSize(m_paddleRightSprite).y / 2.f;

  sf::Vertex rightPaddleSurface[] = {sf::Vertex(sf::Vector2f(x3, y3), sf::Color::Red),
                                     sf::Vertex(sf::Vector2f(x4, y4), sf::Color::Red)};

  sf::Vector2f v1{x1 - x2, y1 - y2};
  float dV1 = sqrtf(v1.x * v1.x + v1.y * v1.y);
  v1 /= dV1;
  sf::Vector2f n1{-v1.y, v1.x};

  sf::Vector2f v2{x4 - x3, y4 - y3};
  float dV2 = sqrtf(v2.x * v2.x + v2.y * v2.y);
  v2 /= dV2;
  sf::Vector2f n2{-v2.y, v2.x};

  auto lPos = m_paddleLeftSprite.getPosition();
  lPos.x = x2;

  sf::Vertex leftNormal[] = {sf::Vertex(lPos, sf::Color::Blue),
                             sf::Vertex(lPos + n1 * 25.f, sf::Color::Blue)};

  auto rPos = m_paddleRightSprite.getPosition();
  rPos.x = x4;

  sf::Vertex rightNormal[] = {sf::Vertex(rPos, sf::Color::Blue),
                              sf::Vertex(rPos + n2 * 25.f, sf::Color::Blue)};

  // ================= DEBUG =================

  m_window.beginDraw();

  m_window.draw(m_dividerSprite);
  m_window.draw(m_paddleLeftSprite);
  m_window.draw(m_paddleRightSprite);
  m_window.draw(m_ballSprite);

  m_window.draw(leftPaddleSurface, 2, sf::Lines);
  m_window.draw(rightPaddleSurface, 2, sf::Lines);

  // ================= DEBUG =================
  m_window.draw(leftNormal, 2, sf::Lines);
  m_window.draw(rightNormal, 2, sf::Lines);
  // ================= DEBUG =================

  // m_window.draw(normalLeft);
  // m_window.draw(normalRight);

  m_window.endDraw();
}

void Game::restartClock() {
  m_elapsed += m_clock.restart();
}

void Game::handleInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    m_paddleLeftMoveDirection = -1.f;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    m_paddleLeftMoveDirection = 1.f;
  } else {
    m_paddleLeftMoveDirection = 0.f;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
    m_paddleRightMoveDirection = -1.f;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
    m_paddleRightMoveDirection = 1.f;
  } else {
    m_paddleRightMoveDirection = 0.f;
  }
}

bool Game::isDone() const {
  return m_window.isDone();
}

sf::Vector2f Game::getSpriteSize(const sf::Sprite &sprite) {
  const auto size = sprite.getTexture()->getSize();
  const auto width = static_cast<float>(size.x);
  const auto height = static_cast<float>(size.y);

  return {width * sprite.getScale().x,
          height * sprite.getScale().y};
}

/// Resolves new origin of the sprite, should be called before applying transformations
/// @param texture sprite texture to find it's size before transformations
/// @return origin posisition which is the center of the texture
sf::Vector2f Game::getSpriteOrigin(const sf::Texture &texture) {
  const auto textureSize = texture.getSize();

  return {static_cast<float>(textureSize.x) / 2.f,
          static_cast<float>(textureSize.y) / 2.f};
}
