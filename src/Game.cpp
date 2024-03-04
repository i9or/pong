#include <iostream>

#include "Game.h"
#include "Utils.h"

Game::Game()
    : m_window("Pong", sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)),
      m_ballVelocity({-400.f, 400.f}),
      m_paddleLeftMoveDirection(0.f),
      m_paddleRightMoveDirection(0.f),
      m_leftPoints(0),
      m_rightPoints(0) {
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
  m_ballSprite.setPosition(WINDOW_WIDTH - 100.f, 100.f);

  auto paddleHeight = WINDOW_HEIGHT / 7.f;

  m_paddleLeftSprite.setTexture(m_paddleLeftTexture);
  m_paddleLeftSprite.setOrigin(getSpriteOrigin(m_paddleLeftTexture));
  auto leftPaddleScaleFactor = paddleHeight / static_cast<float>(m_paddleLeftTexture.getSize().y);
  m_paddleLeftSprite.setScale(leftPaddleScaleFactor, leftPaddleScaleFactor);
  m_paddleLeftSprite.setPosition(getSpriteSize(m_paddleLeftSprite).x / 2.f + PADDLE_OFFSET, WINDOW_HEIGHT / 2.f);

  m_paddleRightSprite.setTexture(m_paddleRightTexture);
  m_paddleRightSprite.setOrigin(getSpriteOrigin(m_paddleRightTexture));
  auto rightPaddleScaleFactor = paddleHeight / static_cast<float>(m_paddleRightTexture.getSize().y);
  m_paddleRightSprite.setScale(rightPaddleScaleFactor, rightPaddleScaleFactor);
  m_paddleRightSprite.setPosition(WINDOW_WIDTH - getSpriteSize(m_paddleRightSprite).x / 2.f - PADDLE_OFFSET, WINDOW_HEIGHT / 2.f);

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

  displayPoints();
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
  m_ballSprite.setPosition(m_ballSprite.getPosition() + m_ballVelocity * m_elapsed.asSeconds());

  if (checkCollisionAndResolve(m_paddleLeftSprite)) {
    m_leftPaddleSound.play();
  }

  if (checkCollisionAndResolve(m_paddleRightSprite)) {
    m_rightPaddleSound.play();
  }

  const auto ballSize = getSpriteSize(m_ballSprite);
  const auto ballPosition = m_ballSprite.getPosition();

  if (ballPosition.x > WINDOW_WIDTH + ballSize.x) {
    leftScores();
  }

  if (ballPosition.x < -ballSize.x) {
    rightScores();
  }

  if (ballPosition.y > WINDOW_HEIGHT - ballSize.y / 2.f) {
    m_ballVelocity.y *= -1.f;
    m_ballSprite.setPosition(ballPosition.x, WINDOW_HEIGHT - ballSize.y / 2.f);
    m_ballSound.play();
  }

  if (ballPosition.y < ballSize.y / 2.f) {
    m_ballVelocity.y *= -1.f;
    m_ballSprite.setPosition(ballPosition.x, ballSize.y / 2.f);
    m_ballSound.play();
  }
}

void Game::render() {
  m_window.beginDraw();

  m_window.draw(m_dividerSprite);
  m_window.draw(m_paddleLeftSprite);
  m_window.draw(m_paddleRightSprite);
  m_window.draw(m_ballSprite);

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
/// @return origin position which is the center of the texture
sf::Vector2f Game::getSpriteOrigin(const sf::Texture &texture) {
  const auto textureSize = texture.getSize();

  return {static_cast<float>(textureSize.x) / 2.f,
          static_cast<float>(textureSize.y) / 2.f};
}

void Game::displayPoints() {
  if (!m_window.isDone()) {
    m_window.setTitle("Pong: " + std::to_string(m_leftPoints) + " - " + std::to_string(m_rightPoints));
  }
}

void Game::leftScores() {
  m_leftPoints++;
  displayPoints();
  resetGame(Turn::Left);
}

void Game::rightScores() {
  m_rightPoints++;
  displayPoints();
  resetGame(Turn::Right);
}

void Game::resetGame(const Turn turn) {
  const auto ballSize = getSpriteSize(m_ballSprite);

  if (turn == Turn::Left) {
    auto paddlePosition = m_paddleLeftSprite.getPosition();
    auto paddleSize = getSpriteSize(m_paddleLeftSprite);
    m_ballSprite.setPosition(paddlePosition.x + ballSize.x / 2.f + paddleSize.x / 2.f, paddlePosition.y);
  } else if (turn == Turn::Right) {
    auto paddlePosition = m_paddleRightSprite.getPosition();
    auto paddleSize = getSpriteSize(m_paddleRightSprite);
    m_ballSprite.setPosition(paddlePosition.x - ballSize.x / 2.f - paddleSize.x / 2.f, paddlePosition.y);
  }
}

sf::Vector2f Game::getClosestPointOnPaddle(const sf::Sprite &paddle, const sf::Vector2f &point) {
  auto position = paddle.getPosition();
  auto size = getSpriteSize(paddle);

  float closestX = std::max(position.x - size.x / 2.f, std::min(point.x, position.x + size.x / 2.f));
  float closestY = std::max(position.y - size.y / 2.f, std::min(point.y, position.y + size.y / 2.f));

  return {closestX, closestY};
}

bool Game::checkCollisionAndResolve(const sf::Sprite &paddle) {
  auto ballPosition = m_ballSprite.getPosition();
  auto ballRadius = getSpriteSize(m_ballSprite).x / 2.f;
  auto paddlePosition = paddle.getPosition();
  auto paddleSize = getSpriteSize(paddle);
  auto closestPoint = getClosestPointOnPaddle(paddle, ballPosition);
  float distance = Utils::distance(ballPosition, closestPoint);

  if (distance < ballRadius) {
    float collisionDepthX = (paddleSize.x / 2.f + ballRadius) - std::abs(ballPosition.x - paddlePosition.x);
    float collisionDepthY = (paddleSize.y / 2.f + ballRadius) - std::abs(ballPosition.y - paddlePosition.y);

    sf::Vector2f normal;

    if (collisionDepthX < collisionDepthY) {
      auto isBallOnTheLeft = ballPosition.x < paddlePosition.x;
      normal = {isBallOnTheLeft ? -1.f : 1.f, 0.f};
      m_ballSprite.move(isBallOnTheLeft ? -collisionDepthX : collisionDepthX, 0.f);
    } else {
      auto isBallOnTheTop = ballPosition.y < paddlePosition.y;
      normal = {0.f, isBallOnTheTop ? -1.f : 1.f};
      m_ballSprite.move(0.f, isBallOnTheTop ? -collisionDepthY : collisionDepthY);
    }

    m_ballVelocity = Utils::reflect(m_ballVelocity, normal);

    return true;
  }

  return false; // no collision
}
