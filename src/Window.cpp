#include "Window.h"

Window::Window() {
  create("Window", sf::Vector2u(1280, 800));
}

Window::Window(const std::string &title, const sf::Vector2u &size) {
  create(title, size);
}

Window::~Window() {
  destroy();
}

void Window::create(const std::string &title, const sf::Vector2u &size) {
  m_isDone = false;
  m_window.create({size.x, size.y}, title, sf::Style::Close);
}

void Window::destroy() {
  m_window.close();
}

void Window::update() {
  sf::Event event{};

  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_isDone = true;
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
      case sf::Keyboard::Escape:
        m_isDone = true;
        break;
      default:
        break;
      }
    }
  }
}

void Window::beginDraw() {
  // m_window.clear(sf::Color::White);
  m_window.clear(sf::Color(0x444444ff)); // TODO: remove before merge
}

void Window::endDraw() {
  m_window.display();
}

bool Window::isDone() const {
  return m_isDone;
}

void Window::draw(const sf::Drawable &drawable) {
  m_window.draw(drawable);
}

void Window::draw(const sf::Vertex *vertices, const std::size_t vertexCount, const sf::PrimitiveType type) {
  m_window.draw(vertices, vertexCount, type);
}

void Window::setTitle(const std::string &newTitle) {
  m_window.setTitle(newTitle);
}