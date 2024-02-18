#include <SFML/Graphics.hpp>

#include "Game.h"

//const auto WIDTH = 1280.f;
//const auto HEIGHT = 720.f;
//const auto BALL_RADIUS = 10.f;

int main() {
//  sf::RenderWindow window{sf::VideoMode{static_cast<unsigned int>(WIDTH), static_cast<unsigned int>(HEIGHT)}, "Pong"};
//
//  sf::CircleShape ball{BALL_RADIUS};
//  ball.setFillColor(sf::Color::White);
//  ball.setOutlineColor(sf::Color::Black);
//  ball.setOutlineThickness(3.f);
//  ball.setOrigin(BALL_RADIUS, BALL_RADIUS);
//
//  sf::Vector2f position{100.f, 100.f};
//  sf::Vector2f direction{1.f, 1.f};
//  float velocity = 0.15f;
//
//      while (window.isOpen()) {
//    sf::Event event{};
//
//    while (window.pollEvent(event)) {
//      if (event.type == sf::Event::Closed) {
//        window.close();
//      }
//
//      if (event.type == sf::Event::KeyPressed &&
//          (event.key.code == sf::Keyboard::Escape)) {
//        window.close();
//      }
//    }
//
//    if (position.x > (WIDTH - BALL_RADIUS) || position.x < BALL_RADIUS) {
//      direction.x *= -1;
//    }
//
//    if (position.y > (HEIGHT - BALL_RADIUS) || position.y < BALL_RADIUS) {
//      direction.y *= -1;
//    }
//
//    position = position + direction * velocity;
//    ball.setPosition(position);
//
//    window.clear(sf::Color::White);
//
//    window.draw(ball);
//
//    window.display();
//  }
  Game game;

  while (!game.isDone()) {
    game.handleInput();
    game.update();
    game.render();
    game.restartClock();
  }

  return EXIT_SUCCESS;
}