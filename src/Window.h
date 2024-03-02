#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class Window {
public:
  Window();
  Window(const std::string &title, const sf::Vector2u &size);
  ~Window();

  void beginDraw();
  void endDraw();
  void update();
  bool isDone() const;
  void draw(const sf::Drawable &drawable);
  void draw(const sf::Vertex *vertices, std::size_t vertexCount, sf::PrimitiveType type);

private:
  void create(const std::string &title, const sf::Vector2u &size);
  void destroy();

  sf::RenderWindow m_window;
  bool m_isDone{};
};
