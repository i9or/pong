#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Window {
public:
  Window();
  Window(const std::string &title, const sf::Vector2u &size);
  ~Window();

  void beginDraw();
  void endDraw();
  void update();
  bool isDone() const;
  void draw(sf::Drawable &drawable);

private:
  void create(const std::string &title, const sf::Vector2u &size);
  void destroy();

  sf::RenderWindow m_window;
  bool m_isDone{};
};
